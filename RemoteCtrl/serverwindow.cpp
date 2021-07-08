#include "serverwindow.h"
#include "ui_serverwindow.h"



ServerWindow::ServerWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ServerWindow)
{
    ui->setupUi(this);
    m_pProc = new ServerProcess(this);
    connect(m_pProc, SIGNAL(RecvImage(QImage)), this, SLOT(ImageShow(QImage)));
}


ServerWindow::~ServerWindow()
{
    disconnect(m_pProc, SIGNAL(RecvImage(QImage)), this, SLOT(ImageShow(QImage)));
    delete m_pProc;
    m_pProc = NULL;
    delete ui;
}

void ServerWindow::on_WButton_clicked()
{
//    RecvLoop();
}

void ServerWindow::on_SButton_clicked()
{

}

void ServerWindow::on_AButton_clicked()
{

}

void ServerWindow::on_DButton_clicked()
{

}

void ServerWindow::on_QButton_clicked()
{

}

void ServerWindow::on_EButton_clicked()
{

}

void ServerWindow::on_WButton_pressed()
{
    m_pProc->ChangeDir('w');
}

void ServerWindow::on_WButton_released()
{
    m_pProc->ChangeDir('p');
}

void ServerWindow::ImageShow(QImage QImg){
    if (ui->lblSharedScreen->size() != ui->scrollAreaWidgetContents->size()) {
        ui->lblSharedScreen->resize(ui->scrollAreaWidgetContents->size());
    }
    //刷新Label显示，显示放缩后的图片
    ui->lblSharedScreen->setPixmap(QPixmap::fromImage(QImg.scaled(ui->lblSharedScreen->size())));
}

void ServerWindow::on_SButton_pressed()
{
    m_pProc->ChangeDir('s');
}

void ServerWindow::on_SButton_released()
{
    m_pProc->ChangeDir('p');
}

void ServerWindow::on_AButton_pressed()
{
    m_pProc->ChangeDir('a');
}

void ServerWindow::on_AButton_released()
{
    m_pProc->ChangeDir('p');
}

void ServerWindow::on_DButton_pressed()
{
    m_pProc->ChangeDir('d');
}

void ServerWindow::on_DButton_released()
{
    m_pProc->ChangeDir('p');
}

void ServerWindow::on_QButton_pressed()
{
    m_pProc->ChangeDir('q');
}

void ServerWindow::on_QButton_released()
{
    m_pProc->ChangeDir('p');
}

void ServerWindow::on_EButton_pressed()
{
    m_pProc->ChangeDir('e');
}

void ServerWindow::on_EButton_released()
{
    m_pProc->ChangeDir('p');
}
