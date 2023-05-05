#include "mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {
    ui->setupUi(this);
    _userTable = new UserTable();
    _userTable->loadUsers(ui);

}

MainWindow::~MainWindow() {
    delete ui;
}
