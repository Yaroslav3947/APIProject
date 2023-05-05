#pragma once

#include <QUrl>
#include <QDebug>
#include <QObject>
#include <QJsonArray>
#include <QEventLoop>
#include <QJsonObject>
#include <QJsonDocument>
#include <QNetworkAccessManager>

#include "User.h"
#include "qnetworkreply.h"

class ApiManager : public QObject {
    Q_OBJECT
public:
    ApiManager(QObject* parent = nullptr);

    // for get
    QList<User> getUsers(int page, int count);
    void getPositions(std::function<void(QList<QString>, bool, QString)> callback);
    User getUser(int id);

    // for post
    void registerUser(const QString &name, const QString &email, const QString &phone, int positionId, const QString &photoFilename);

private:
    QNetworkAccessManager _networkAccessManager;
    QString _baseUrl = "https://frontend-test-assignment-api.abz.agency/api/v1/";
};
