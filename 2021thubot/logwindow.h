#ifndef LOGWINDOW_H
#define LOGWINDOW_H

#include <QMainWindow>
#include"modeswindow.h"
#include <QDesktopWidget>

namespace Ui {
class LogWindow;
}

class LogWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit LogWindow(QWidget *parent = 0);
    ~LogWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::LogWindow *ui;
};

#endif // LOGWINDOW_H
