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

#include "User.h"
#include "qnetworkreply.h"

class ApiManager : public QObject {
    Q_OBJECT
public:
    ApiManager(QObject* parent = nullptr);

    // for get
    QList<User> getUsers(int page, int count);
    int getTotalUsers();
    int getTotalPages();
    QString getToken();
    QMap<QString, int> getPositions();
    User getUser(int id);

    // for post
    void registerUser(const User *user);

    bool hasMorePages(const int &page);
private:
    QNetworkAccessManager _networkAccessManager;
    QString _baseUrl = "https://frontend-test-assignment-api.abz.agency/api/v1/";
};
