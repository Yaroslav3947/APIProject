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

    QRegularExpression phoneRegex("^\\+?380[0-9]{9}$");
    QValidator *phoneValidator = new QRegularExpressionValidator(phoneRegex, this);
    ui->phoneLine->setValidator(phoneValidator);

    _userTable = new UserTable();
    _registrationForm = new RegistrationForm();

    _userTable->loadUsers(ui);
    _registrationForm->loadRadioButtons(ui);
}

void MainWindow::connectSignalsAndSlots() {
    connect(ui->showMoreButton, &QPushButton::clicked, this, &MainWindow::loadMoreUsers);
    connect(ui->addUserButton, &QPushButton::clicked, this, &MainWindow::regiserUser);
}

MainWindow::~MainWindow() {
    delete _registrationForm;
    delete _userTable;
    delete ui;
}


void MainWindow::loadMoreUsers() {
    _userTable->loadMoreUsers(ui);
    ui->showMoreButton->setVisible(_userTable->getHasMorePages());
}

void MainWindow::regiserUser() {
    _registrationForm->loadRadioButtons(ui);
    _registrationForm->registerUser(ui);
}
