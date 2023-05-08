#include "qapplication.h"

#include <ApiManager.h>
#include <mainwindow.h>

void callBack(bool success, QString message) {
    qDebug() << success << message;
}
int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    QString name = "John Doe";
    QString email = "joiwie@example.com";
    QString phone = "+380985588405";
    QString position = "Security";
    QString photoFilename = "C:/Users/Yaroslav/Desktop/motobike.jpg";

    std::unique_ptr<User> user = std::make_unique<User>(User{name, email, phone, position, photoFilename});

    ApiManager *apiManager = new ApiManager;
//    qDebug() << apiManager->getTotalUsers() << apiManager->getTotalPages();
//    apiManager->registerUser(user.get(), callBack);

    MainWindow w;
    w.show();



    return a.exec();

    delete apiManager;
}
