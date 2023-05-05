#include "UserTable.h"


UserTable::UserTable(QWidget *parent) : QWidget(parent) {
    _apiManager = new ApiManager();
}
void UserTable::loadUsers(Ui::MainWindow *ui) {
    const int USER_NUM_PER_PAGE = 6;
    _userLayout = new QVBoxLayout(ui->usersTab);
    _userLayout->setContentsMargins(24, 0, 0, 0);
    QList<User> users = _apiManager->getUsers(1,USER_NUM_PER_PAGE);

    for (int i = 0; i < USER_NUM_PER_PAGE; i++) {
        User *user = new User(users[i]);

        QFrame *userFrame = new QFrame(ui->usersTab);
        userFrame->setFixedSize(640, 117);

        QHBoxLayout *userFrameLayout = new QHBoxLayout(userFrame);

        QLabel *photoLabel = new QLabel(userFrame);
        photoLabel->setFixedSize(84, 84);

        // TODO: Load photo from API
        QPixmap userPhoto("C:/Users/Yaroslav/Desktop/photo.png");
        photoLabel->setPixmap(userPhoto.scaled(photoLabel->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));

        QVBoxLayout *userInfoLayout = new QVBoxLayout();
        userInfoLayout->setSpacing(1);

        QLabel *nameLabel = new QLabel(userFrame);
        nameLabel->setText(user->getName());
        nameLabel->setStyleSheet("color: #000000; font-size: 18px;");

        QLabel *emailLabel = new QLabel(userFrame);
        emailLabel->setText(user->getEmail());
        emailLabel->setStyleSheet("color: #6B6B6B;font-family: 'Inter'; font-size: 12px;");

        QLabel *positionLabel = new QLabel(userFrame);
        positionLabel->setText(user->getPosition());
        positionLabel->setStyleSheet("color: #6B6B6B;font-family: 'Inter'; font-size: 12px;");

        QLabel *phoneNumberLabel = new QLabel(userFrame);
        phoneNumberLabel->setText(user->getPhoneNumber());
        phoneNumberLabel->setStyleSheet("color: #6B6B6B; font-family: 'Inter'; font-size: 12px;");

        userInfoLayout->addWidget(nameLabel);
        userInfoLayout->addWidget(positionLabel);
        userInfoLayout->addWidget(emailLabel);
        userInfoLayout->addWidget(phoneNumberLabel);

        userFrameLayout->addWidget(photoLabel);
        userFrameLayout->addLayout(userInfoLayout);

        _userLayout->addWidget(userFrame);
    }
}
