#include "qapplication.h"

#include <ApiManager.h>
#include <mainwindow.h>


int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    QString name = "John Doe";
    QString email = "johndoe@example.com";
    QString phone = "+380955388485";
    QString position = "Security";
    QString photoFilename = "C:/Users/Yaroslav/Desktop/motobike.jpg";

    std::unique_ptr<User> user = std::make_unique<User>(User{name, email, phone, position, photoFilename});

    ApiManager *apiManager = new ApiManager;
//    qDebug() << apiManager->getTotalUsers() << apiManager->getTotalPages();
    apiManager->registerUser(user.get());
//    qDebug() << apiManager->getToken() << apiManager->getToken() << apiManager->getToken();

    MainWindow w;
    w.show();



    return a.exec();

        delete apiManager;
}
