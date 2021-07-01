#ifndef DATUIMAGE_H
#define DATUIMAGE_H

#include <QDialog>
#include "autotouristwindow.h"
#include <QDesktopWidget>
#include <sys/stat.h>

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

    void on_pushButton_voice_clicked();

    void on_pushButton_place_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::DATUimage *ui;
};

#endif // DATUIMAGE_H
