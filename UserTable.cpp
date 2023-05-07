#include "UserTable.h"

#include <UserWidget.h>


UserTable::UserTable(QWidget *parent): QWidget(parent), _page(1), _count(USER_NUM_PER_PAGE) {
    _apiManager = new ApiManager();

}

void UserTable::loadUsers(Ui::MainWindow *ui) {
    _userLayout = new QVBoxLayout(ui->usersListFrame);
    _userLayout->setContentsMargins(0, 0, 0, 0);

    QList<User> users = _apiManager->getUsers(_page, _count);

    for (const auto &user: users) {
        UserWidget *userWidget = new UserWidget(user, ui->usersListFrame);
        userWidget->setFixedSize(640, 117);
        _userLayout->addWidget(userWidget);
    }

    _hasMoreUsers = _apiManager->hasMorePages(_page);
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

    _hasMoreUsers = _apiManager->hasMorePages(_page);

}

void UserTable::clearUsers() {
    QLayoutItem *child;
    while((child = _userLayout->takeAt(0)) != nullptr) {
        delete child->widget();
    }
}

bool UserTable::getHasMoreUsers() {
    return _hasMoreUsers;
}




