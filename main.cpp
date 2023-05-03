#include <QtNetwork>
#include <QFile>

#include <ApiManager.h>

void callBack(QList<User> users, bool success, QString errorString) {
    if (success) {
        qDebug() << "Users:";
        for (const auto &user : users) {
            qDebug() << user.getId() << user.getName() << user.getEmail();
        }
    } else {
        qDebug() << "API request failed:" << errorString;
    }
}

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);

    ApiManager *apiManager = new ApiManager;

    apiManager->getUsers(1,5,callBack);


    return 0;
}
