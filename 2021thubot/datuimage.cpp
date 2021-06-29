#include "datuimage.h"
#include "ui_datuimage.h"

DATUimage::DATUimage(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DATUimage)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);//去掉标题栏
    QDesktopWidget *desktop = QApplication::desktop();//位于中央
    move((desktop->width()-this->width())/2,(desktop->height()-this->height())/2);
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
