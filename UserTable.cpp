#include "UserTable.h"

UserTable::UserTable(QWidget *parent):
    QWidget(parent),
    _apiManager(std::make_unique<ApiManager>()),
    _userLayout(nullptr),
    _page(START_PAGE),
    _count(USER_NUM_PER_PAGE) {
}

UserTable::~UserTable() {
    clearUsers();
}

bool UserTable::getHasMorePages() const {
    return _hasMorePages;
}

void UserTable::loadUsers(Ui::MainWindow *ui) {
    _userLayout = std::make_unique<QVBoxLayout>(ui->usersListFrame);
    _userLayout->setContentsMargins(0, 0, 0, 0);

    QList<User> users = _apiManager->getUsers(_page, _count);
    loadUsersToLayout(users, ui);

    // Determine whether to show the "show more" button
    _hasMorePages = _apiManager->hasMorePages(_page);
}

void UserTable::loadUsersToLayout(const QList<User> &users, Ui::MainWindow *ui) {
    for (const auto &user: users) {
        UserWidget *userWidget = new UserWidget(user, ui->usersListFrame);
        userWidget->setFixedSize(640, 117);
        _userLayout->addWidget(userWidget);
    }
}

void UserTable::loadMoreUsers(Ui::MainWindow *ui) {

    clearUsers();

    _page++;

    QList<User> users = _apiManager->getUsers(_page, _count);
    loadUsersToLayout(users, ui);

    // Determine whether to show the "show more" button
    _hasMorePages = _apiManager->hasMorePages(_page);
}

void UserTable::clearUsers() {
    // Remove all user widgets

    if (!_userLayout) {
        return;
    }

    QLayoutItem *child;
    while((child = _userLayout->takeAt(0)) != nullptr) {
        delete child->widget();
        delete child;
    }
}
