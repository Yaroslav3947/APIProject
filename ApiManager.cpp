#include "ApiManager.h"

ApiManager::ApiManager(QObject* parent) : QObject(parent) {
}

QList<User> ApiManager::getUsers(const int &page, const int &count) {
    const QString apiUrl = _baseUrl + "users?page=" + QString::number(page) + "&count=" + QString::number(count);
    QNetworkRequest request((QUrl(apiUrl)));

    QNetworkReply *reply = _networkAccessManager.get(request);

    QEventLoop loop;
    QObject::connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();

    QList<User> users;
    bool success = false;
    QString errorString{};

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
    const QString apiUrl = _baseUrl + "users";
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
    const QString apiUrl = _baseUrl + "users";
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
    const QString apiUrl = _baseUrl + "positions";
    QNetworkRequest request((QUrl(apiUrl)));

    QNetworkReply *reply = _networkAccessManager.get(request);

    QEventLoop loop;
    QObject::connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();

    QMap<QString, int> positions;
    bool success = false;
    QString errorString{};

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


User ApiManager::getUser(const int &id) {
    const QString apiUrl = _baseUrl + "users/" + QString::number(id);
    QNetworkRequest request((QUrl(apiUrl)));

    QNetworkReply *reply = _networkAccessManager.get(request);

    QEventLoop loop;
    QObject::connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();

    User user;
    bool success = false;
    QString errorString{};

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

void ApiManager::registerUser(const User *user, std::function<void(bool success, QString message)> callback) {
    const QUrl apiUrl = _baseUrl + "users";
    QNetworkRequest request((QUrl(apiUrl)));

    // Get token and add to request headers
    QString token = getToken();
    request.setRawHeader("Token", token.toUtf8());

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

    // send request
    QNetworkReply* reply = _networkAccessManager.post(request, multiPart);
    multiPart->setParent(reply); // delete using the reply

    QEventLoop loop;
    QObject::connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();

    // parse error response
    int statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
    QString response = QString::fromUtf8(reply->readAll());
    QJsonDocument json = QJsonDocument::fromJson(response.toUtf8());
    QString message = json.object().value("message").toString();

    if (statusCode == 200 || statusCode == 201) {
        callback(true, message);
    } else if (statusCode == 401) {
        callback(false, "Token expired");
    } else if (statusCode == 409) {
        callback(false, "User with this phone or email already exists");
    } else if (statusCode == 422) {
        QJsonObject fails = json.object().value("fails").toObject();
        QString error_message = "Validation failed:\n";
        for (auto fail = fails.begin(); fail != fails.end(); ++fail) {
            error_message += fail.key() + ": ";
            QJsonArray errors = fail.value().toArray();
            for (auto error = errors.begin(); error != errors.end(); ++error) {
                error_message += error->toString() + "\n";
            }
        }

        QJsonObject responseObj = json.object();
        bool success = responseObj.value("success").toBool();
        if (success) {
            QString message = responseObj.value("message").toString();
            callback(true, message);
        } else {
            callback(false, error_message);
        }
    } else {
        QMessageBox::critical(nullptr, "Error", "Unknown response from server");
    }
}

QString ApiManager::getToken() {
    const QString apiUrl = _baseUrl + "token";
    QNetworkRequest request((QUrl(apiUrl)));

    QNetworkReply *reply = _networkAccessManager.get(request);

    QEventLoop loop;
    QObject::connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();

    QString token;
    bool success = false;
    QString errorString{};

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

bool ApiManager::hasMorePages(const int &page, const double usersPerPage) {
    return std::ceil((getTotalUsers() / usersPerPage) > page);
}
