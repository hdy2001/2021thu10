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
    //setWindowOpacity(0.7);//增加透明度
    /*
     //当机器人在语音播报过程中，无法点击停止导航和停止语音按钮
    while(){
        ui->pushButton->setEnabled(false);
        ui->pushButton_2->setEnabled(false);
    }
    */
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
    system("gnome-terminal -x bash -c 'sudo reboot'");
}

//点击“初始位置调整”按钮后的自动调整位置函数（补充内容）
void DATUimage::on_pushButton_place_clicked()
{

}

//停止语音交互，可退出导航
void DATUimage::on_pushButton_2_clicked()
{
    ui->pushButton->setEnabled(true);
    ui->pushButton_2->setEnabled(false);
    ui->pushButton_voice->setEnabled(true);

}
