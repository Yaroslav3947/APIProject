#include "mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {
    ui->setupUi(this);

    _userTable = new UserTable();
    _userTable->loadUsers(ui);

    connect(ui->showMoreButton, &QPushButton::clicked, this, &MainWindow::loadMoreUsers);

}


MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::loadMoreUsers() {
    _userTable->loadMoreUsers(ui);
    ui->showMoreButton->setVisible(_userTable->getHasMoreUsers());
}
