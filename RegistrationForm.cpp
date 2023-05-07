#include "RegistrationForm.h"

RegistrationForm::RegistrationForm() {
    _apiManager = new ApiManager();
    _positions = _apiManager->getPositions();
    _user = new User();
}

void RegistrationForm::loadRadioButtons(Ui::MainWindow *ui) {
    _radioButtonsLayout = new QVBoxLayout(ui->radioButtonFrame);

    for (const auto &position : _positions.keys()) {
        QRadioButton *radioButton = new QRadioButton(position);
        radioButton->setStyleSheet("font-size: 16px;font-family: 'Inter';");
        connect(radioButton, &QRadioButton::clicked, this, &RegistrationForm::onRadioButtonClicked);
        _radioButtonsLayout->addWidget(radioButton);
    }
}

void RegistrationForm::onRadioButtonClicked() {
    QRadioButton *radioButton = qobject_cast<QRadioButton*>(QObject::sender());
    if (radioButton) {
        QString position = radioButton->text();
        _user->setPosition(position);
    }
}

void RegistrationForm::registerUser(Ui::MainWindow *ui) {
    _user->setName(ui->nameLine->text());
    _user->setEmail(ui->emailLine->text());
    _user->setPhoneNumber(ui->phoneLine->text());
//    _user->setPhotoUrl(ui->photoLine->text());

    _apiManager->registerUser(getUser());
    qDebug() << getUser()->getName()
             << getUser()->getEmail()
             << getUser()->getPhoneNumber()
             << getUser()->getPosition();
}

RegistrationForm::~RegistrationForm() {
    delete _radioButtonsLayout;
    delete _apiManager;
    delete _user;
}

User *RegistrationForm::getUser() {
    return _user;
}
