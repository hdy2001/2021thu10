#include "serverprocess.h"

QImage cvMat2QImage(const cv::Mat& mat)
{
    // 8-bits unsigned, NO. OF CHANNELS = 1
    if(mat.type() == CV_8UC1)
    {
        QImage image(mat.cols, mat.rows, QImage::Format_Indexed8);
        // Set the color table (used to translate colour indexes to qRgb values)
        image.setColorCount(256);
        for(int i = 0; i < 256; i++)
        {
            image.setColor(i, qRgb(i, i, i));
        }
        // Copy input Mat
        uchar *pSrc = mat.data;
        for(int row = 0; row < mat.rows; row ++)
        {
            uchar *pDest = image.scanLine(row);
            memcpy(pDest, pSrc, mat.cols);
            pSrc += mat.step;
        }
        return image;
    }
    // 8-bits unsigned, NO. OF CHANNELS = 3
    else if(mat.type() == CV_8UC3)
    {
        // Copy input Mat
        const uchar *pSrc = (const uchar*)mat.data;
        // Create QImage with same dimensions as input Mat
        QImage image(pSrc, mat.cols, mat.rows, mat.step, QImage::Format_RGB888);
        return image.rgbSwapped();
    }
    else if(mat.type() == CV_8UC4)
    {
//        qDebug() << "CV_8UC4";
        // Copy input Mat
        const uchar *pSrc = (const uchar*)mat.data;
        // Create QImage with same dimensions as input Mat
        QImage image(pSrc, mat.cols, mat.rows, mat.step, QImage::Format_ARGB32);
        return image.copy();
    }
    else
    {
//        qDebug() << "ERROR: Mat could not be converted to QImage.";
        return QImage();
    }
}
cv::Mat QImage2cvMat(QImage image)
{
    cv::Mat mat;
//    qDebug() << image.format();
    switch(image.format())
    {
    case QImage::Format_ARGB32:
    case QImage::Format_RGB32:
    case QImage::Format_ARGB32_Premultiplied:
        mat = cv::Mat(image.height(), image.width(), CV_8UC4, (void*)image.constBits(), image.bytesPerLine());
        break;
    case QImage::Format_RGB888:
        mat = cv::Mat(image.height(), image.width(), CV_8UC3, (void*)image.constBits(), image.bytesPerLine());
        cv::cvtColor(mat, mat, CV_BGR2RGB);
        break;
    case QImage::Format_Indexed8:
        mat = cv::Mat(image.height(), image.width(), CV_8UC1, (void*)image.constBits(), image.bytesPerLine());
        break;
    }
    return mat;
}

ServerProcess::ServerProcess(QObject* Parent): QObject(Parent)
{
    m_dir = 'p';
    pthread_create(&m_tid, NULL, StaticRecvHelper,(void *)this);
    pthread_create(&m_tid2, NULL, StaticSendHelper,(void *)this);
}

ServerProcess::~ServerProcess()
{
    pthread_kill(m_tid, SIGUSR2);
    pthread_kill(m_tid2, SIGUSR2);
}

void ServerProcess::ChangeDir(const char dir){
    m_dir = dir;
}

void* ServerProcess::SendDirThread(){
//        int conn;
        //?????? sockfd
        int sock_cli = socket(AF_INET, SOCK_STREAM, 0);

        //??????sockaddr_in
        struct sockaddr_in servaddr;
        servaddr.sin_family = AF_INET;
        servaddr.sin_port = htons(PORT);  //???????????????
        servaddr.sin_addr.s_addr = inet_addr("183.173.201.245");  //?????????ip??? inet_addr??????IPv4???IP??????(???????????????????????????)
        //127.0.0.1?????????????????????
        //?????????????????? ????????????0??? ???????????? -1
        if(::connect(sock_cli, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
        {
            perror("connect");
            printf("socket error!");
            exit(1);
        }

        char sendbuf[BUFFER_SIZE];
        char recvbuf[BUFFER_SIZE];

        while(1)
        {
            sendbuf[0] = m_dir;
            sendbuf[1] = '\n';
            //?????????????????????????????????????????????buf???????????????????????????????????????????????????????????? buf
            send(sock_cli, sendbuf, strlen(sendbuf), 0); //??????
            if(strcmp(sendbuf, "exit\n") == 0)
                    break;
            recv(sock_cli, recvbuf, sizeof(recvbuf), 0);  //??????

            fputs(recvbuf, stdout);

            memset(sendbuf, 0, sizeof(sendbuf));  //??????????????????????????????????????????????????????????????? ??? 0
            memset(recvbuf, 0, sizeof(recvbuf));
        }
        close(sock_cli);
}

void* ServerProcess::StaticSendHelper(void *pThis){
    static_cast<ServerProcess *>(pThis)->SendDirThread();
}

//StaticRecvHelper???????????????StaticRecvImage?????????????????????
void* ServerProcess::StaticRecvHelper(void* pThis)
{
    static_cast<ServerProcess *>(pThis)->RecvImageThread();
}


void* ServerProcess::RecvImageThread()
{
    if (socketMat.socketConnect(6666) < 0)
    {
        printf("failed to open socket!\n");
    }
    else {
        printf("open socket!\n");
    }
    cv::Mat image;
    while(1)
    {
        if(socketMat.receive(image) > 0)
        {
            QImage QImg = cvMat2QImage(image);
            //require GUI to update Image
            emit RecvImage(QImg);
            //cv::waitKey(10);
        }
        else
        {
            printf("no image recv!\n");
        }
    }
    socketMat.socketDisconnect();
}
