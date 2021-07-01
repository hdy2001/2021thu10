#ifndef MODESWINDOW_H
#define MODESWINDOW_H

#include <QMainWindow>
#include "autotouristwindow.h"
#include <QDesktopWidget>

namespace Ui {
class ModesWindow;
}

class ModesWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ModesWindow(QWidget *parent = 0);
    ~ModesWindow();

private slots:
    void on_pushButton_2_clicked();

private:
    Ui::ModesWindow *ui;
};

#endif // MODESWINDOW_H
