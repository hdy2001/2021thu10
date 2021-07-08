#ifndef SERVERWINDOW_H
#define SERVERWINDOW_H

#include <QDialog>
#include <serverprocess.h>
#include <QImage>
#include <pthread.h>
#include <QMessageBox>

namespace Ui {
class ServerWindow;
}



class ServerWindow : public QDialog
{
    Q_OBJECT

public:
    explicit ServerWindow(QWidget *parent = 0);
    ~ServerWindow();

private slots:
    void on_WButton_clicked();

    void on_SButton_clicked();

    void on_AButton_clicked();

    void on_DButton_clicked();

    void on_QButton_clicked();

    void on_EButton_clicked();

    void on_WButton_pressed();

    void on_WButton_released();

    void ImageShow(QImage img);

    void on_SButton_pressed();

    void on_SButton_released();

    void on_AButton_pressed();

    void on_AButton_released();

    void on_DButton_pressed();

    void on_DButton_released();

    void on_QButton_pressed();

    void on_QButton_released();

    void on_EButton_pressed();

    void on_EButton_released();

private:
    Ui::ServerWindow *ui;
    ServerProcess* m_pProc;
    QMessageBox m_Msg;


};

#endif // SERVERWINDOW_H
