#include "mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {
    setupUi();
    connectSignalsAndSlots();
}

void MainWindow::setupUi() {
    ui->setupUi(this);

    _movie = new QMovie(LOADING_GIF_PATH);

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
    if (_userTable->getHasMorePages()) {
        ui->showMoreButton->hide();
        QLabel *loadingLabel = showLoadingAnimation();
        QTimer::singleShot(1000, [this, loadingLabel](){
            _userTable->loadMoreUsers(ui);
            hideLoadingAnimation(loadingLabel);
            ui->showMoreButton->setVisible(_userTable->getHasMorePages());  // Show the button again if there are more pages
        });
    }
}

QLabel *MainWindow::showLoadingAnimation() {
    QLabel *loadingLabel = new QLabel;
    loadingLabel->setMovie(_movie);
    _movie->setScaledSize(QSize(100, 100));
    _movie->start();
    ui->loadingLayout->addWidget(loadingLabel, 0, 0, 1, 1, Qt::AlignCenter);
    return loadingLabel;
}

void MainWindow::hideLoadingAnimation(QLabel *loadingLabel) {
    loadingLabel->setMovie(nullptr);
    ui->loadingLayout->removeWidget(loadingLabel);
    delete loadingLabel;
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
        ui->showMoreButton->hide();
    QLabel *loadingLabel = showLoadingAnimation();

    ui->loadingLayout->addWidget(loadingLabel, 0, 0, 1, 1, Qt::AlignCenter);

    // Switch to the first tab and load the user data after a 1 second delay
    QTimer::singleShot(1000, this, [this, loadingLabel]() {
        ui->tabWidget->setCurrentIndex(0);
        ui->tabWidget->setTabEnabled(0, true);

        resetInputForm(ui);

        _userTable = std::make_unique<UserTable>();
        _userTable->loadUsers(ui);

        hideLoadingAnimation(loadingLabel);
        ui->showMoreButton->setVisible(_userTable->getHasMorePages());  // Show the button if there are more pages
        ui->userListButton->show();
    });
}

MainWindow::~MainWindow() {
    delete _movie;
    delete ui;
}
