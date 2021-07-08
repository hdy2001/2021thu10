#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <serverwindow.h>
#include <QMainWindow>
#include <QMessageBox>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_login_clicked();

    void on_exit_clicked();

    void on_ZHIip_returnPressed();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
