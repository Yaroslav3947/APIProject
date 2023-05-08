#pragma once

#include <User.h>
#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include "QEventLoop"
#include "QNetworkReply"
#include <QNetworkAccessManager>

class UserWidget : public QWidget {
    Q_OBJECT
public:
    UserWidget(const User &user, QWidget *parent = nullptr);
//    ~UserWidget(); // why do I have problem here?

private:
    QLabel *_photoLabel;
    QLabel *_nameLabel;
    QLabel *_emailLabel;
    QLabel *_positionLabel;
    QLabel *_phoneNumberLabel;

    QHBoxLayout *_resultLayout;
    QVBoxLayout *_userInfoLayout;
    QHBoxLayout *_userFrameLayout;

    void setPhoto(const QString &photoUrl);

};
