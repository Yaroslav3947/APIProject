#include "RegistrationForm.h"

RegistrationForm::RegistrationForm() {
    _apiManager = std::make_unique<ApiManager>();
    _positions = _apiManager->getPositions();
    _user = std::make_unique<User>();
}

void RegistrationForm::loadRadioButtons(Ui::MainWindow *ui) {
    _radioButtonsLayout = std::make_unique<QVBoxLayout>(ui->radioButtonFrame);

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

    _apiManager->registerUser(getUser().get());
    qDebug() << getUser()->getName()
             << getUser()->getEmail()
             << getUser()->getPhoneNumber()
             << getUser()->getPosition();
}

std::unique_ptr<User>RegistrationForm::getUser() {
    return std::move(_user);
}
