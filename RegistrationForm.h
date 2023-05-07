#pragma once

#include <QWidget>
#include <QVBoxLayout>
#include <QRadioButton>

#include "ApiManager.h"
#include "ui_mainwindow.h"


class RegistrationForm : public QObject {
public:
    RegistrationForm();
    ~RegistrationForm();
    void loadRadioButtons(Ui::MainWindow *ui);
    void registerUser(Ui::MainWindow *ui);
    User *getUser();
private:
    User *_user;
    QVBoxLayout *_radioButtonsLayout;
    ApiManager *_apiManager;
    QMap<QString, int> _positions;
private slots:
    void onRadioButtonClicked();

};
