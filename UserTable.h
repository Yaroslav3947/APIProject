#pragma once

#include <QVBoxLayout>
#include <QPushButton>
#include <QHBoxLayout>
#include <QLabel>
#include <QFrame>
#include <QPixmap>
#include "ApiManager.h"
#include "ui_mainwindow.h"

class UserTable : public QWidget {
    Q_OBJECT
public:
    UserTable(QWidget *parent = nullptr);


    void clearUsers();
    bool getHasMoreUsers();
    void loadUsers(Ui::MainWindow *ui);
    void loadMoreUsers(Ui::MainWindow *ui);

private:
    const static int USER_NUM_PER_PAGE = 6;
    ApiManager *_apiManager;
    QVBoxLayout *_userLayout;
    int _page;
    int _count;
    bool _hasMoreUsers;
public:


};
