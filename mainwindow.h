#pragma once

#include <QMovie>
#include <QTimer>
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
    QMovie *_movie;
    Ui::MainWindow *ui;

    std::unique_ptr<UserTable> _userTable;
    std::unique_ptr<RegistrationForm> _registrationForm;

    const QString LOADING_GIF_PATH = ":/photo/loading.gif";

    void setupUi();
    void connectSignalsAndSlots();
    void clearInputForm(Ui::MainWindow *ui);
    void resetInputForm(Ui::MainWindow *ui);
    QLabel *showLoadingAnimation();
    void hideLoadingAnimation(QLabel *loadingLabel);

private slots:
    void loadMoreUsers();
    void regiserUser();
    void selectPhoto();
    void addOneMoreUser();
    void listUsers();
};

