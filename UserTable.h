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
    ~UserTable();

    bool getHasMorePages() const;
    void clearUsers();
    void loadUsers(Ui::MainWindow *ui);
    void loadMoreUsers(Ui::MainWindow *ui);

private:
    const static int START_PAGE = 1;
    constexpr const static double USER_NUM_PER_PAGE = 6;

    std::unique_ptr<ApiManager> _apiManager;
    std::unique_ptr<QVBoxLayout> _userLayout;

    int _page;
    double _count;
    bool _hasMorePages;
    void loadUsersToLayout(const QList<User> &users, Ui::MainWindow *ui);

};
