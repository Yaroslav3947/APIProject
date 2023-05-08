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

UserWidget::UserWidget(const User &user, QWidget *parent) : QWidget(parent) {

    _resultLayout = new QHBoxLayout(this);

    _photoLabel = new QLabel(this);
    _photoLabel->setFixedSize(84, 84);

    setPhoto(user.getPhotoUrl());

    _userInfoLayout = new QVBoxLayout();

    _nameLabel = new QLabel(this);
    _nameLabel->setText(user.getName());
    _nameLabel->setStyleSheet("color: #000000; font-size: 18px;");
    _userInfoLayout->addWidget(_nameLabel);

    _emailLabel = new QLabel(this);
    _emailLabel->setText(user.getEmail());
    _emailLabel->setStyleSheet("color: #6B6B6B;font-family: 'Inter'; font-size: 12px;");
    _userInfoLayout->addWidget(_emailLabel);

    _positionLabel = new QLabel(this);
    _positionLabel->setText(user.getPosition());
    _positionLabel->setStyleSheet("color: #6B6B6B;font-family: 'Inter'; font-size: 12px;");
    _userInfoLayout->addWidget(_positionLabel);

    _phoneNumberLabel = new QLabel(this);
    _phoneNumberLabel->setText(user.getPhoneNumber());
    _phoneNumberLabel->setStyleSheet("color: #6B6B6B; font-family: 'Inter'; font-size: 12px;");
    _userInfoLayout->addWidget(_phoneNumberLabel);

    _resultLayout->addWidget(_photoLabel);
    _resultLayout->addLayout(_userInfoLayout);

}

