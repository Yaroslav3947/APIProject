#include "qapplication.h"
#include <QtNetwork>
#include <QFile>

#include <ApiManager.h>

#include <mainwindow.h>

//void callBack(QList<User> users, bool success, QString errorString) {
//    if (success) {
//        qDebug() << "Users:";
//        for (const auto &user : users) {
//            qDebug() << user.getId() << user.getName() << user.getEmail();
//        }
//    } else {
//        qDebug() << "API request failed:" << errorString;
//    }
//}

void callBack(User user, bool success, QString errorString) {
    if (success) {
        qDebug() << "User:";
            qDebug() << user.getId() << user.getName() << user.getEmail();
    } else {
        qDebug() << "API request failed:" << errorString;
    }
}

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    ApiManager *apiManager = new ApiManager;
    qDebug() << apiManager->getTotalUsers() << apiManager->getTotalPages();
//    apiManager->getUser(1,callBack);
//    apiManager->getUsers(1,5,callBack);
    MainWindow w;
    w.show();


    return a.exec();
}
