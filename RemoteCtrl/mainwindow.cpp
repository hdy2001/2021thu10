#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_login_clicked()
{
    QMessageBox msgBox;
    if(ui->ZHIip->text() != "robot"){
        msgBox.setText("wrong password");
        msgBox.exec();
    }
    else{
        ServerWindow* pServerWindow;
        this->setWindowOpacity(0.0);
        pServerWindow = new ServerWindow(this);
        pServerWindow->exec();
        this->setWindowOpacity(1.0);
        delete pServerWindow;
        pServerWindow = NULL;
    }
}

void MainWindow::on_exit_clicked()
{
    this->close();
}

void MainWindow::on_ZHIip_returnPressed()
{
    QMessageBox msgBox;
    if(ui->ZHIip->text().isEmpty()){
        msgBox.setText("please input XizoZhi ip");
        msgBox.exec();
    }
    else{
        ServerWindow* pServerWindow;
        this->setWindowOpacity(0.0);
        pServerWindow = new ServerWindow(this);
        pServerWindow->exec();
        this->setWindowOpacity(1.0);
        delete pServerWindow;
        pServerWindow = NULL;
    }
}
