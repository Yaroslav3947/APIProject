#include "RegistrationForm.h"

RegistrationForm::RegistrationForm() {
    _apiManager = std::make_unique<ApiManager>();
    _positions = _apiManager->getPositions();
    _user = std::make_unique<User>();
}

void RegistrationForm::selectPhoto(Ui::MainWindow *ui) {
    QString fileName = QFileDialog::getOpenFileName(ui->photoPathLine->parentWidget(), tr("Open Image"), "", tr("Image Files (*.jpeg *.jpg *.jfif *.bmp)"));
    if (fileName != "") {
        ui->photoPathLine->setText(fileName);
    }
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

    QString name = ui->nameLine->text();
    QString email = ui->emailLine->text();
    QString phone = ui->phoneLine->text();
    QString photoPath = ui->photoPathLine->text().trimmed();

    if (name.isEmpty() || email.isEmpty() || phone.isEmpty() || photoPath.isEmpty()) {
        QMessageBox::information(ui->addUserButton, "Input Data", "Please fill in all the fields.");
    } else {
        _user->setName(name);
        _user->setEmail(email);
        _user->setPhoneNumber(phone);
        _user->setPhotoUrl(photoPath);

        _apiManager->registerUser(getUser().get(), [&](bool success, QString message) {
            if (success) {
                QMessageBox::information(ui->addUserButton, "Registration Successful", message);
            } else {
                QMessageBox::critical(ui->addUserButton, "Registration Failed", message);
            }
        });
    }
}

std::unique_ptr<User>RegistrationForm::getUser() {
    return std::move(_user);
}
