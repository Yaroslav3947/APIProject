#include "qapplication.h"

#include <ApiManager.h>
#include <mainwindow.h>


int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    QString name = "John Doe";
    QString email = "johndoe@example.com";
    QString phone = "+380955388485";
    int positionId = 3;
    QString photoFilename = "C:\\Users\\Yaroslav\\Desktop\\motobike.jpg";




    ApiManager *apiManager = new ApiManager;
//    qDebug() << apiManager->getTotalUsers() << apiManager->getTotalPages();
//    apiManager->registerUser(name,email,phone,positionId,photoFilename);

    MainWindow w;
    w.show();

    return a.exec();

    delete apiManager;
}
