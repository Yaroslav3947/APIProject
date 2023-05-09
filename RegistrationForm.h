#pragma once

#include <QWidget>
#include <QFileDialog>
#include <QMessageBox>
#include <QVBoxLayout>
#include <QRadioButton>
#include <QButtonGroup>

#include "UserTable.h"
#include "ApiManager.h"
#include "ui_mainwindow.h"

class RegistrationForm : public QObject {
public:
    RegistrationForm();
    ~RegistrationForm();
    void selectPhoto(Ui::MainWindow *ui);
    void loadRadioButtons(Ui::MainWindow *ui);
    void registerUser(Ui::MainWindow *ui);
    void addOneMoreUser(Ui::MainWindow *ui);
    void listUsers(Ui::MainWindow *ui);

    std::shared_ptr<User> getUser();

private:
    std::shared_ptr<User> _user;
    QVBoxLayout *_radioButtonsLayout;
    std::unique_ptr<ApiManager> _apiManager;
    QMap<QString, int> _positions;

    void showSuccessfulRegistraion(Ui::MainWindow *ui);

private slots:
    void onRadioButtonClicked();

};
