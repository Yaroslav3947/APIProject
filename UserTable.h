#pragma once

#include <QFrame>
#include <QPixmap>
#include <QHBoxLayout>

#include "ApiManager.h"
#include "UserWidget.h"
#include "ui_mainwindow.h"


class UserTable : public QWidget {
    Q_OBJECT
public:
    UserTable(QWidget *parent = nullptr);
    ~UserTable() = default;

    bool getHasMorePages();
    void loadUsers(Ui::MainWindow *ui);
    void loadMoreUsers(Ui::MainWindow *ui);

private:
    const static int START_PAGE = 1;
    const static int USER_NUM_PER_PAGE = 6;

    std::unique_ptr<ApiManager> _apiManager;
    std::unique_ptr<QVBoxLayout> _userLayout;

    int _page;
    int _count;
    bool _hasMorePages;

    void clearUsers();
};
