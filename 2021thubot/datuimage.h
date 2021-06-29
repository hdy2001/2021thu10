#ifndef DATUIMAGE_H
#define DATUIMAGE_H

#include <QDialog>
#include "autotouristwindow.h"
#include <QDesktopWidget>

namespace Ui {
class DATUimage;
}

class DATUimage : public QDialog
{
    Q_OBJECT

public:
    explicit DATUimage(QWidget *parent = 0);
    ~DATUimage();

private slots:
    void on_pushButton_clicked();

private:
    Ui::DATUimage *ui;
};

#endif // DATUIMAGE_H
