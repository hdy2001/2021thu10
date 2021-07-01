#include "modeswindow.h"
#include "ui_modeswindow.h"

ModesWindow::ModesWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ModesWindow)
{
    ui->setupUi(this);
    //this->setWindowFlags(Qt::FramelessWindowHint);//去掉标题栏
    QDesktopWidget *desktop = QApplication::desktop();//位于中央
    move((desktop->width()-this->width())/2,(desktop->height()-this->height())/2);
}

ModesWindow::~ModesWindow()
{
    delete ui;
}

void ModesWindow::on_pushButton_2_clicked()
{
    AutoTouristWindow *m = new AutoTouristWindow;
    //这个用来查看机器人的位置
    system("bash -c 'source /opt/ros/kinect/setup.bash;source ~/catkin_ws/devel/setup.bash; roslaunch wpb_home_tutorials nav.launch ;bash'&");
    m->show();
    this->close();
}
