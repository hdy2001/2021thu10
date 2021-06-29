#include "logwindow.h"
#include "ui_logwindow.h"

LogWindow::LogWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LogWindow)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);//去掉标题栏
    QDesktopWidget *desktop = QApplication::desktop();//位于中央
    move((desktop->width()-this->width())/2,(desktop->height()-this->height())/2);
}

LogWindow::~LogWindow()
{
    delete ui;
}

void LogWindow::on_pushButton_clicked()
{
   ModesWindow *m = new ModesWindow;// = new ModesWindow();
   m->show();
   this->close();
}

void LogWindow::on_pushButton_2_clicked()
{
   this->close();
}
