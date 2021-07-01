#ifndef AUTOTOURISTWINDOW_H
#define AUTOTOURISTWINDOW_H

#include <QMainWindow>
#include "datuimage.h"
#include "modeswindow.h"
#include <QDesktopWidget>

namespace Ui {
class AutoTouristWindow;
}

class AutoTouristWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit AutoTouristWindow(QWidget *parent = 0);
    ~AutoTouristWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_joyCtrl_clicked();

    void on_felloMe_clicked();

private:
    Ui::AutoTouristWindow *ui;
};

#endif // AUTOTOURISTWINDOW_H
