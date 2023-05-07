#pragma once

#include <User.h>
#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>


class UserWidget : public QWidget {
    Q_OBJECT
public:
    UserWidget(const User &user, QWidget *parent = nullptr);

private:
    QLabel *_photoLabel;
    QLabel *_nameLabel;
    QLabel *_emailLabel;
    QLabel *_positionLabel;
    QLabel *_phoneNumberLabel;

    QVBoxLayout *_userInfoLayout;
    QHBoxLayout *_userFrameLayout;

};
