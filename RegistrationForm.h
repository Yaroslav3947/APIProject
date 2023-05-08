#pragma once

#include <QWidget>
#include <QVBoxLayout>
#include <QRadioButton>

#include "ApiManager.h"
#include "ui_mainwindow.h"

class RegistrationForm : public QObject {
public:
    RegistrationForm();
    void loadRadioButtons(Ui::MainWindow *ui);
    void registerUser(Ui::MainWindow *ui);
    std::unique_ptr<User> getUser();

private:
    std::unique_ptr<User> _user;
    std::unique_ptr<QVBoxLayout> _radioButtonsLayout;
    std::unique_ptr<ApiManager> _apiManager;
    QMap<QString, int> _positions;

private slots:
    void onRadioButtonClicked();

};
