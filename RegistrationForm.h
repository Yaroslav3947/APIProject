#pragma once

#include <QWidget>
#include <QFileDialog>
#include <QMessageBox>
#include <QVBoxLayout>
#include <QRadioButton>
#include <QButtonGroup>


#include "ApiManager.h"
#include "ui_mainwindow.h"

class RegistrationForm : public QObject {
public:
    RegistrationForm();
    void selectPhoto(Ui::MainWindow *ui);
    void loadRadioButtons(Ui::MainWindow *ui);
    void registerUser(Ui::MainWindow *ui);
    std::unique_ptr<User> getUser();

private:
    std::unique_ptr<User> _user;
    QVBoxLayout *_radioButtonsLayout;
    std::unique_ptr<ApiManager> _apiManager;
    QMap<QString, int> _positions;

private slots:
    void onRadioButtonClicked();

};
