#include "autotouristwindow.h"
#include "ui_autotouristwindow.h"

AutoTouristWindow::AutoTouristWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AutoTouristWindow)
{
    ui->setupUi(this);
    //this->setWindowFlags(Qt::FramelessWindowHint);//去掉标题栏
    QDesktopWidget *desktop = QApplication::desktop();//位于屏幕中央
    move((desktop->width()-this->width())/2,(desktop->height()-this->height())/2);
}

AutoTouristWindow::~AutoTouristWindow()
{
    delete ui;
}

void AutoTouristWindow::on_pushButton_clicked()
{
    DATUimage *m = new DATUimage();
    m->show();
}

void AutoTouristWindow::on_pushButton_2_clicked()
{
    ModesWindow *w = new ModesWindow;
    w->show();
    this->close();
}
