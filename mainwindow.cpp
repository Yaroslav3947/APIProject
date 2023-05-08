#include "mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {
    setupUi();
    connectSignalsAndSlots();
}

void MainWindow::setupUi() {
    ui->setupUi(this);

    ui->nameLine->setPlaceholderText("Name");
    ui->emailLine->setPlaceholderText("Email");
    ui->phoneLine->setPlaceholderText("Phone");
    ui->photoPathLine->setPlaceholderText("Upload photo");

    QRegularExpression phoneRegex("^\\+?380[0-9]{9}$");
    QValidator *phoneValidator = new QRegularExpressionValidator(phoneRegex, this);
    ui->phoneLine->setValidator(phoneValidator);

    _userTable = std::make_unique<UserTable>();
    _registrationForm = std::make_unique<RegistrationForm>();

    _userTable->loadUsers(ui);
    _registrationForm->loadRadioButtons(ui);

    ui->photoPathLine->setReadOnly(true);

    ui->userAddedMainFrame->hide();
}

void MainWindow::connectSignalsAndSlots() {
    connect(ui->showMoreButton, &QPushButton::clicked, this, &MainWindow::loadMoreUsers);
    connect(ui->addUserButton, &QPushButton::clicked, this, &MainWindow::regiserUser);
    connect(ui->uploadButton, &QPushButton::clicked, this, &MainWindow::selectPhoto);

    connect(ui->userListButton, &QPushButton::clicked, this, &MainWindow::listUsers);
    connect(ui->addOneMoreButton, &QPushButton::clicked, this, &MainWindow::addOneMoreUser);
}

void MainWindow::loadMoreUsers() {
    _userTable->loadMoreUsers(ui);
}

void MainWindow::regiserUser() {
    _registrationForm->registerUser(ui);
}

void MainWindow::selectPhoto() {
    _registrationForm->selectPhoto(ui);
}

void MainWindow::addOneMoreUser() {
    _registrationForm->addOneMoreUser(ui);
    _registrationForm = std::make_unique<RegistrationForm>();
}

void MainWindow::listUsers() {
    ui->tabWidget->setCurrentIndex(0);
    ui->userAddedMainFrame->hide();
    _userTable = std::make_unique<UserTable>();
    _userTable->loadUsers(ui);
}

MainWindow::~MainWindow() {
    delete ui;
}
