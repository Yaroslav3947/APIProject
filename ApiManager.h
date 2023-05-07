#pragma once

#include <QUrl>
#include <QMap>
#include <QFile>
#include <QDebug>
#include <QObject>
#include <QHttpPart>
#include <QJsonArray>
#include <QEventLoop>
#include <QJsonObject>
#include <QJsonDocument>

#include <QNetworkAccessManager>
#include <QNetworkReply>

#include "User.h"

class ApiManager : public QObject {
    Q_OBJECT
public:
    ApiManager(QObject* parent = nullptr);

    bool hasMorePages(const int &page);

    // for get Api
    QString getToken();
    int getTotalUsers();
    int getTotalPages();
    User getUser(int id);
    QMap<QString, int> getPositions();
    QList<User> getUsers(int page, int count);

    // for post Api
    void registerUser(const User *user);

private:
    QNetworkAccessManager _networkAccessManager;
    const QString _baseUrl = "https://frontend-test-assignment-api.abz.agency/api/v1/";
};
