#include "UserWidget.h"

void UserWidget::setPhoto(const QString &photoUrl) {
    QPixmap userPhoto;
    QNetworkAccessManager networkManager(this);
    QNetworkReply *reply = networkManager.get(QNetworkRequest(photoUrl));

    QEventLoop loop;
    QObject::connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();

    if (reply->error() == QNetworkReply::NoError) {
        userPhoto.loadFromData(reply->readAll());
        _photoLabel->setPixmap(userPhoto.scaled(_photoLabel->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
    } else {
        QPixmap defaultPhoto(":/photo/noPhoto.jfif");
        _photoLabel->setPixmap(defaultPhoto.scaled(_photoLabel->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
    }

    reply->deleteLater();
}

UserWidget::UserWidget(const User &user, QWidget *parent) :
    QWidget(parent),
    _resultLayout(std::make_unique<QHBoxLayout>(this)),
    _userInfoLayout(std::make_unique<QVBoxLayout>()) {

    const QString styleSheet = "color: #6B6B6B; font-family: 'Inter'; font-size: 12px;";

    const QString nameStyleSheet = "color: #000000; font-size: 18px;";

    _photoLabel = new QLabel(this);
    _photoLabel->setFixedSize(84, 84);

    setPhoto(user.getPhotoUrl());

    _nameLabel = new QLabel(this);
    _nameLabel->setText(user.getName());
    _nameLabel->setStyleSheet(nameStyleSheet);
    _userInfoLayout->addWidget(_nameLabel);

    _emailLabel = new QLabel(this);
    _emailLabel->setText(user.getEmail());
    _emailLabel->setStyleSheet(styleSheet);
    _userInfoLayout->addWidget(_emailLabel);

    _positionLabel = new QLabel(this);
    _positionLabel->setText(user.getPosition());
    _positionLabel->setStyleSheet(styleSheet);
    _userInfoLayout->addWidget(_positionLabel);

    _phoneNumberLabel = new QLabel(this);
    _phoneNumberLabel->setText(user.getPhoneNumber());
    _phoneNumberLabel->setStyleSheet(styleSheet);
    _userInfoLayout->addWidget(_phoneNumberLabel);

    _resultLayout->addWidget(_photoLabel);
    _resultLayout->addLayout(_userInfoLayout.get());

}

