#pragma once

#include <QMainWindow>
#include <QRegularExpression>
#include <QRegularExpressionValidator>

#include "UserTable.h"
#include "ui_mainwindow.h"
#include "RegistrationForm.h"

#include "ui_mainwindow.h"

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
    std::unique_ptr<UserTable> _userTable;
    std::unique_ptr<RegistrationForm> _registrationForm;

    void setupUi();
    void connectSignalsAndSlots();
private slots:
    void loadMoreUsers();
    void regiserUser();
    void selectPhoto();
};

