#include "UserWidget.h"

UserWidget::UserWidget(const User &user, QWidget *parent) : QWidget(parent) {

    QHBoxLayout *layout = new QHBoxLayout(this);

    _photoLabel = new QLabel(this);
    _photoLabel->setFixedSize(84, 84);

    // TODO: Load photo from API
    QPixmap userPhoto("C:/Users/Yaroslav/Desktop/photo.png");
    _photoLabel->setPixmap(userPhoto.scaled(_photoLabel->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
    layout->addWidget(_photoLabel);

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



    layout->addLayout(_userInfoLayout);
}
