#include <mainwindow.h>

#include "qapplication.h"


int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    MainWindow w;
    QNetworkAccessManager manager;
    QNetworkReply *reply = manager.get(QNetworkRequest(QUrl("http://www.google.com")));
    QEventLoop loop;
    ApiManager::connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();
    if (reply->error() == QNetworkReply::NoError) {
        w.show();
        return a.exec();
    } else {
        QMessageBox::critical(nullptr, "No Internet Connection", "Your device is not connected to the Internet. Please check your network connection and try again.");
        return 1;
    }

}
