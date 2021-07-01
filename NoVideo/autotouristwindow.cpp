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
//手柄控制用来调整机器人初始位置，直到初始位置和Rviz里显示的一致
void AutoTouristWindow::on_joyCtrl_clicked()
{
    system("  bash -c 'source /opt/ros/kinect/setup.bash;source ~/catkin_ws/devel/setup.bash; roslaunch wpb_home_bringup js_ctrl.launch ;bash'&");
}
//这个也是用来调整初始位置的
void AutoTouristWindow::on_felloMe_clicked()
{
        system("  bash -c 'source /opt/ros/kinect/setup.bash;source ~/catkin_ws/devel/setup.bash; roslaunch wpb_home_tutorials follow.launch ;bash'&");
}
