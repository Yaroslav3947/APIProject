#pragma once

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QFrame>
#include <QPixmap>
#include "ApiManager.h"
#include "ui_mainwindow.h"

class UserTable : public QWidget {
public:
    UserTable(QWidget *parent = nullptr);

    void loadUsers(Ui::MainWindow *ui);

private:
    ApiManager *_apiManager;
    QVBoxLayout *_userLayout;
};
