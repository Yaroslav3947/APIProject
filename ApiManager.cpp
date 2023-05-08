#include "ApiManager.h"

ApiManager::ApiManager(QObject* parent) : QObject(parent) {
}

QList<User> ApiManager::getUsers(int page, int count) {
    QString apiUrl = _baseUrl + "users?page=" + QString::number(page) + "&count=" + QString::number(count);
    QNetworkRequest request((QUrl(apiUrl)));

    QNetworkReply *reply = _networkAccessManager.get(request);

    QEventLoop loop;
    QObject::connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();

    QList<User> users;
    bool success = false;
    QString errorString;

    if (reply->error() == QNetworkReply::NoError) {
        QByteArray response = reply->readAll();
        QJsonDocument jsonResponse = QJsonDocument::fromJson(response);
        if (jsonResponse["success"].toBool()) {
            success = true;
            QJsonArray usersJsonArray = jsonResponse["users"].toArray();
            for (const auto& userJson : usersJsonArray) {
                users.append(User::fromJson(userJson.toObject()));
            }
        } else {
            errorString = jsonResponse["message"].toString();
        }
    } else {
        errorString = reply->errorString();
    }

    reply->deleteLater();

    if(success) {
        return users;
    } else {
        qDebug() << errorString;
        QList<User> errorList = {User()};
        return errorList;
    }
}

int ApiManager::getTotalUsers()  {
    QString apiUrl = _baseUrl + "users";
    QNetworkRequest request((QUrl(apiUrl)));
    QNetworkReply *reply = _networkAccessManager.get(request);
    QEventLoop eventLoop;
    QObject::connect(reply, &QNetworkReply::finished, &eventLoop, &QEventLoop::quit);
    eventLoop.exec();

    if (reply->error() != QNetworkReply::NoError) {
        qWarning() << "Error fetching user count:" << reply->errorString();
        return -1;
    }

    QByteArray data = reply->readAll();
    QJsonDocument doc = QJsonDocument::fromJson(data);
    QJsonObject obj = doc.object();

    if (obj.contains("total_users")) {
        return obj.value("total_users").toInt();
    }

    return -1;
}

int ApiManager::getTotalPages()  {
    QString apiUrl = _baseUrl + "users";
    QNetworkRequest request((QUrl(apiUrl)));
    QNetworkReply *reply = _networkAccessManager.get(request);
    QEventLoop eventLoop;
    QObject::connect(reply, &QNetworkReply::finished, &eventLoop, &QEventLoop::quit);
    eventLoop.exec();

    if (reply->error() != QNetworkReply::NoError) {
        qWarning() << "Error fetching user count:" << reply->errorString();
        return -1;
    }

    QByteArray data = reply->readAll();
    QJsonDocument doc = QJsonDocument::fromJson(data);
    QJsonObject obj = doc.object();

    if (obj.contains("total_pages")) {
        return obj.value("total_pages").toInt();
    }

    return -1;
}

QMap<QString, int> ApiManager::getPositions() {
    QString apiUrl = _baseUrl + "positions";
    QNetworkRequest request((QUrl(apiUrl)));

    QNetworkReply *reply = _networkAccessManager.get(request);

    QEventLoop loop;
    QObject::connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();

    QMap<QString, int> positions;
    bool success = false;
    QString errorString;

    if (reply->error() == QNetworkReply::NoError) {
        QByteArray response = reply->readAll();
        QJsonDocument jsonResponse = QJsonDocument::fromJson(response);
        if (jsonResponse["success"].toBool()) {
            success = true;
            QJsonArray positionsJsonArray = jsonResponse["positions"].toArray();
            for (const auto& positionJson : positionsJsonArray) {
                QString name = positionJson.toObject()["name"].toString();
                int positionId = positionJson.toObject()["id"].toInt();
                positions[name] = positionId;
            }
        } else {
            errorString = jsonResponse["message"].toString();
        }
    } else {
        errorString = reply->errorString();
    }

    reply->deleteLater();

    if(success) {
        return positions;
    } else {
        QMap<QString, int> errorMap;
        errorMap.insert("error", -1);
        qDebug() << errorString;
        return errorMap;
    }
}


User ApiManager::getUser(int id) {
    QString apiUrl = _baseUrl + "users/" + QString::number(id);
    QNetworkRequest request((QUrl(apiUrl)));


    QNetworkReply *reply = _networkAccessManager.get(request);

    QEventLoop loop;
    QObject::connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();

    User user;
    bool success = false;
    QString errorString;

    if (reply->error() == QNetworkReply::NoError) {
        QByteArray response = reply->readAll();
        QJsonDocument jsonResponse = QJsonDocument::fromJson(response);
        if (jsonResponse["success"].toBool()) {
            success = true;
            user = User::fromJson(jsonResponse["user"].toObject());
        } else {
            errorString = jsonResponse["message"].toString();
        }
    } else {
        errorString = reply->errorString();
    }

    reply->deleteLater();

    if(success) {
        return user;
    } else {
        qDebug() << errorString;
        return User();
    }
}

void ApiManager::registerUser(const std::unique_ptr<User> user) {
    QUrl apiUrl = _baseUrl + "users";
    QNetworkRequest request((QUrl(apiUrl)));

    // create request using user information
    QHttpMultiPart *multiPart = new QHttpMultiPart(QHttpMultiPart::FormDataType);

    QHttpPart namePart;
    namePart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"name\""));
    namePart.setBody(user->getName().toUtf8());

    QHttpPart emailPart;
    emailPart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"email\""));
    emailPart.setBody(user->getEmail().toUtf8());

    QHttpPart phonePart;
    phonePart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"phone\""));
    phonePart.setBody(user->getPhoneNumber().toUtf8());

    QHttpPart positionIdPart;
    int position = getPositions().value(user->getPosition());
    positionIdPart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"position_id\""));
    positionIdPart.setBody(QString::number(position).toUtf8());

    QFile *file = new QFile(user->getPhotoUrl());
    file->open(QIODevice::ReadOnly);

    QHttpPart photoPart;
    photoPart.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("image/jpeg"));
    photoPart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"photo\"; filename=\"" + file->fileName() + "\""));
    photoPart.setBodyDevice(file);
    file->setParent(multiPart); // delete later using multiPart

    multiPart->append(namePart);
    multiPart->append(emailPart);
    multiPart->append(phonePart);
    multiPart->append(positionIdPart);
    multiPart->append(photoPart);

    // get token and add to request headers
    QString token = this->getToken();
    request.setRawHeader("Authorization", QString("Bearer %1").arg(token).toUtf8());

    // send request
    QNetworkReply* reply = _networkAccessManager.post(request, multiPart);
    multiPart->setParent(reply); // delete using the reply

    QEventLoop loop;
    QObject::connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();

    // parse error response
    QString response1 = QString::fromUtf8(reply->readAll());
    QJsonDocument json1 = QJsonDocument::fromJson(response1.toUtf8());
    QString message = json1.object().value("message").toString();

    if (reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt() == 200) {
        qDebug() << "Registration successful:" << message;
    } else if (reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt() == 401) {
        qDebug() << "Token expired:" << message;
    } else if (reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt() == 409) {
        qDebug() << "Registration failed:" << message << "- User with this phone or email already exists";

    } else {
        qDebug() << "Unknown response:" << response1;
    }

    if (reply->error() != QNetworkReply::NoError) {
        qDebug() << "Error:" << reply->errorString();
        return;
    }

    // parse response
    QString response = QString::fromUtf8(reply->readAll());
    QJsonDocument json = QJsonDocument::fromJson(response.toUtf8());
    qDebug() << "Message" << json.object().value("message").toString();

    if (!json.isObject() || !json.object().value("success").toBool()) {
        qDebug() << "Registration failed:" << response;
        return;
    }

    qDebug() << "Registration successful:" << response;

}

QString ApiManager::getToken() {
    QString apiUrl = _baseUrl + "token";
    QNetworkRequest request((QUrl(apiUrl)));

    QNetworkReply *reply = _networkAccessManager.get(request);

    QEventLoop loop;
    QObject::connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();

    QString token;
    bool success = false;
    QString errorString;

    if (reply->error() == QNetworkReply::NoError) {
        QByteArray response = reply->readAll();
        QJsonDocument jsonResponse = QJsonDocument::fromJson(response);
        if (jsonResponse["success"].toBool()) {
            success = true;
            token = jsonResponse["token"].toString();
        } else {
            errorString = jsonResponse["message"].toString();
        }
    } else {
        errorString = reply->errorString();
    }

    reply->deleteLater();

    if(success) {
        return token;
    } else {
        qDebug() << errorString;
        qDebug() << "failed to get a token";
        return QString(); // return an empty string if failed
    }
}

bool ApiManager::hasMorePages(const int &page) {
    return this->getTotalPages() - 1 > page;
}
