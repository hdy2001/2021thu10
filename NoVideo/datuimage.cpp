#include <unistd.h>
#include "datuimage.h"
#include "ui_datuimage.h"



DATUimage::DATUimage(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DATUimage)
{
    ui->setupUi(this);
    //this->setWindowFlags(Qt::FramelessWindowHint);//去掉标题栏
    QDesktopWidget *desktop = QApplication::desktop();//位于中央
    move((desktop->width()-this->width())/2,(desktop->height()-this->height())/2);
    ui->pushButton_2->setEnabled(false);
}

DATUimage::~DATUimage()
{
    delete ui;
}

void DATUimage::on_pushButton_clicked()
{
    this->close();
}

//点击“语音交互”按钮后的语音交互函数（补充内容），不可退出导航
void DATUimage::on_pushButton_voice_clicked()
{
    ui->pushButton_2->setEnabled(true);
    ui->pushButton->setEnabled(false);
    ui->pushButton_voice->setEnabled(false);
    system("  bash -c 'source /opt/ros/kinect/setup.bash;source ~/catkin_ws/devel/setup.bash; roslaunch xfyun_waterplus sr_tts_cn.launch ;bash'&");
    system("  bash -c 'source /opt/ros/kinect/setup.bash;source ~/catkin_ws/devel/setup.bash; rosrun sr_pkg sr_node ;bash'&");
}

//点击“开始导游”按钮后的自动调整位置函数（补充内容）
void DATUimage::on_pushButton_place_clicked()
{
    system("  bash -c 'source /opt/ros/kinect/setup.bash;source ~/catkin_ws/devel/setup.bash; killall -9 bash ;bash'&");
    sleep(1);
    system("  bash -c 'source /opt/ros/kinect/setup.bash;source ~/catkin_ws/devel/setup.bash; roslaunch wpb_home_tutorials nav_cruise.launch ;bash'&");
}

//停止语音交互，可退出导航
void DATUimage::on_pushButton_2_clicked()
{
    ui->pushButton->setEnabled(true);
    ui->pushButton_2->setEnabled(false);
    ui->pushButton_voice->setEnabled(true);
    system("  bash -c 'source /opt/ros/kinect/setup.bash;source ~/catkin_ws/devel/setup.bash; killall -9 roslaunch ;bash'&");
    system("  bash -c 'source /opt/ros/kinect/setup.bash;source ~/catkin_ws/devel/setup.bash; killall -9 sr_node ;bash'&");
    system("  bash -c 'source /opt/ros/kinect/setup.bash;source ~/catkin_ws/devel/setup.bash; killall -9 bash ;bash'&");
}
