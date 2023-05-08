#include "UserTable.h"

UserTable::UserTable(QWidget *parent):
    QWidget(parent),
    _apiManager(std::make_unique<ApiManager>()),
    _userLayout(nullptr),
    _page(START_PAGE),
    _count(USER_NUM_PER_PAGE) {
}

void UserTable::loadUsers(Ui::MainWindow *ui) {
    _userLayout = std::make_unique<QVBoxLayout>(ui->usersListFrame);
    _userLayout->setContentsMargins(0, 0, 0, 0);

    QList<User> users = _apiManager->getUsers(_page, _count);

    for (const auto &user: users) {
        UserWidget *userWidget = new UserWidget(user, ui->usersListFrame);
        userWidget->setFixedSize(640, 117);
        _userLayout->addWidget(userWidget);
    }

    //Determine whether to show the button
    _hasMorePages = _apiManager->hasMorePages(_page);
}

void UserTable::loadMoreUsers(Ui::MainWindow *ui) {

    clearUsers();

    _page++;

    QList<User> users = _apiManager->getUsers(_page, _count);

    for (const auto &user: users) {
        UserWidget *userWidget = new UserWidget(user, ui->usersListFrame);
        userWidget->setFixedSize(640, 117);
        _userLayout->addWidget(userWidget);
    }

    //Determine whether to show the button
    _hasMorePages = _apiManager->hasMorePages(_page);
}

void UserTable::clearUsers() {
    if (!_userLayout) {
        return;
    }

    QLayoutItem *child;
    while((child = _userLayout->takeAt(0)) != nullptr) {
        delete child->widget();
    }
}

bool UserTable::getHasMorePages() {
    return _hasMorePages;
}


