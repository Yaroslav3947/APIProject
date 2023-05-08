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
#include <QNetworkReply>
#include <QNetworkAccessManager>

#include "User.h"

class ApiManager : public QObject {
    Q_OBJECT
public:
    ApiManager(QObject *parent = nullptr);

    bool hasMorePages(const int &page);

    // For get Api
    QString getToken();
    int getTotalUsers();
    int getTotalPages();
    User getUser(const int &id);
    QMap<QString, int> getPositions();
    QList<User> getUsers(const int &page, const int &count);

    // For post Api
    void registerUser(const std::unique_ptr<User> user);

private:

    QNetworkAccessManager _networkAccessManager;
    const QString _baseUrl = "https://frontend-test-assignment-api.abz.agency/api/v1/";
};
