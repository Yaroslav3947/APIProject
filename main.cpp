#include <QtNetwork>
#include <QFile>

const QString RESULT_FILE_PATH = "C:/Users/Yaroslav/Documents/APITestProject/result_get.json";

void downloadUsers() {
    QNetworkAccessManager manager;

    QNetworkRequest request;
    request.setUrl(QUrl("https://frontend-test-assignment-api.abz.agency/api/v1/users?page=1&count=5"));

    QNetworkReply *reply = manager.get(request);
    QEventLoop loop;
    QObject::connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();

    if (reply->error() == QNetworkReply::NoError)
    {
        QByteArray response = reply->readAll();

        QFile file(RESULT_FILE_PATH);
        QJsonDocument jsonResponse = QJsonDocument::fromJson(response);
        if (file.open(QIODevice::WriteOnly)) {
            qDebug()  << jsonResponse["users"][0]["email"].toString();
            file.write(response);
            file.close();
        }
    }
    else {
        qDebug() << "Error:" << reply->errorString();
    }

    reply->deleteLater();
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    downloadUsers();

    return 0;
}
