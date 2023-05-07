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

//    callback(users, success, errorString);
    if(success) {
        return users;
    } else {
        qDebug() << errorString;
        return users; // fix
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


void ApiManager::getPositions(std::function<void(QList<QString>, bool, QString)> callback) {
    QString apiUrl = _baseUrl + "positions";
    QNetworkRequest request((QUrl(apiUrl)));

    QNetworkReply *reply = _networkAccessManager.get(request);

    QEventLoop loop;
    QObject::connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();

    QList<QString> positions;
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
                positions.append(name);
            }
        } else {
            errorString = jsonResponse["message"].toString();
        }
    } else {
        errorString = reply->errorString();
    }

    reply->deleteLater();
    callback(positions, success, errorString);
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

//    callback(user, success, errorString);
    if(success) {
        return user;
    } else {
        qDebug() << errorString;
        return User();
    }
}

void ApiManager::registerUser(const QString &name, const QString &email, const QString &phone, int positionId, const QString &photoFilename) {

}

bool ApiManager::hasMorePages(const int page) {
    return this->getTotalPages() - 1 > page;
}



