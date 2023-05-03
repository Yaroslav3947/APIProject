#include "ApiManager.h"

ApiManager::ApiManager(QObject* parent) : QObject(parent) {
}

void ApiManager::getUsers(int page, int count, std::function<void(QList<User>, bool, QString)> callback) {
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

    callback(users, success, errorString);
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

void ApiManager::registerUser(const QString &name, const QString &email, const QString &phone, int positionId, const QString &photoFilename) {

}



