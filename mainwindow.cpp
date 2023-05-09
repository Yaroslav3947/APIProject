#include "mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {
    setupUi();
    connectSignalsAndSlots();
}

void MainWindow::setupUi() {
    ui->setupUi(this);
    setFixedSize(1024, 1129);

    ui->nameLine->setPlaceholderText("Name");
    ui->emailLine->setPlaceholderText("Email");
    ui->phoneLine->setPlaceholderText("Phone");
    ui->photoPathLine->setPlaceholderText("Upload photo");

    QRegularExpression phoneRegex("^\\+380[0-9]{9}$");
    QValidator *phoneValidator = new QRegularExpressionValidator(phoneRegex, this);
    ui->phoneLine->setValidator(phoneValidator);

    _userTable = std::make_unique<UserTable>();
    _registrationForm = std::make_unique<RegistrationForm>();

    _userTable->loadUsers(ui);
    _registrationForm->loadRadioButtons(ui);

    ui->photoPathLine->setReadOnly(true);

    ui->userAddedMainFrame->hide();
}

void MainWindow::resetInputForm(Ui::MainWindow *ui) {
    clearInputForm(ui);

    _registrationForm.reset(new RegistrationForm());
    _registrationForm->loadRadioButtons(ui);

    _registrationForm->addOneMoreUser(ui);
}

void MainWindow::connectSignalsAndSlots() {
    connect(ui->showMoreButton, &QPushButton::clicked, this, &MainWindow::loadMoreUsers);
    connect(ui->addUserButton, &QPushButton::clicked, this, &MainWindow::regiserUser);
    connect(ui->uploadButton, &QPushButton::clicked, this, &MainWindow::selectPhoto);

    connect(ui->userListButton, &QPushButton::clicked, this, &MainWindow::listUsers);
    connect(ui->addOneMoreButton, &QPushButton::clicked, this, &MainWindow::addOneMoreUser);
}

void MainWindow::loadMoreUsers() {
    ui->showMoreButton->setDisabled(true);
    QTimer::singleShot(1000, [this]() {
        ui->showMoreButton->setDisabled(false);
    });
    _userTable->loadMoreUsers(ui);
}

void MainWindow::regiserUser() {
    _registrationForm->registerUser(ui);
}

void MainWindow::selectPhoto() {
    _registrationForm->selectPhoto(ui);
}

void MainWindow::clearInputForm(Ui::MainWindow *ui) {
    ui->nameLine->clear();
    ui->emailLine->clear();
    ui->phoneLine->clear();
    ui->photoPathLine->clear();

    // Reset radio buttons
    QList<QRadioButton*> radioButtons = ui->radioButtonFrame->findChildren<QRadioButton*>();
    for (QRadioButton *rb : radioButtons) {
        rb->setChecked(false);
    }
}

void MainWindow::addOneMoreUser() {
    ui->tabWidget->setTabEnabled(0, true);

    resetInputForm(ui);

    _userTable = std::make_unique<UserTable>();
    _userTable->loadUsers(ui);
}

void MainWindow::listUsers() {
    ui->tabWidget->setTabEnabled(0, true);
    _registrationForm->listUsers(ui);

    resetInputForm(ui);

    _userTable = std::make_unique<UserTable>();
    _userTable->loadUsers(ui);
}

MainWindow::~MainWindow() {
    delete ui;
}
