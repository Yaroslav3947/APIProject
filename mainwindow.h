#pragma once

#include <QMainWindow>

#include "UserTable.h"
#include "ui_mainwindow.h"
#include "RegistrationForm.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    UserTable *_userTable;
    RegistrationForm *_registrationForm;
private slots:
    void loadMoreUsers();
    void regiserUser();
};

