#pragma once

#include <QLabel>
#include <QWidget>
#include <QEventLoop>
#include <QVBoxLayout>
#include <QNetworkReply>
#include <QNetworkAccessManager>

#include <User.h>

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

    std::unique_ptr<QHBoxLayout> _resultLayout;
    std::unique_ptr<QVBoxLayout> _userInfoLayout;
    std::unique_ptr<QHBoxLayout> _userFrameLayout;

    void setPhoto(const QString &photoUrl);
};
