#ifndef LOGWINDOW_H
#define LOGWINDOW_H

#include <QMainWindow>
#include"modeswindow.h"
#include <QDesktopWidget>
#include <QUrl>
//要包含下面的两个文件，必须在.pro文件中添加  QT += multimedia  multimediawidgets
//#include <QMediaPlayer>
//#include <QVideoWidget>

namespace Ui {
class LogWindow;
}

class LogWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit LogWindow(QWidget *parent = 0);
    ~LogWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::LogWindow *ui;
    //QMediaPlayer *player;
    //QVideoWidget *videoWidget;
};

#endif // LOGWINDOW_H
