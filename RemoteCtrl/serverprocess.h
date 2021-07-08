#ifndef SERVERPROCESS_H
#define SERVERPROCESS_H

#include <SocketMatTransmissionServer.h>
#include <QImage>
#include <signal.h>
#include <string>

#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/shm.h>

const int BUFFER_SIZE = 1024;
const int PORT = 9788;

class ServerProcess : public QObject{
    Q_OBJECT
public:
    explicit ServerProcess(QObject* Parent = NULL);
    ~ServerProcess();
    void ChangeDir(const char dir);
//    void SetIp(const QString ip);
signals:
    void RecvImage(QImage img);
private:
//    std::string m_ZHIip;
    char m_dir;
    pthread_t m_tid, m_tid2;
    SocketMatTransmissionServer socketMat;
    void *RecvImageThread();
    static void* StaticRecvHelper(void *pThis);
    void *SendDirThread();
    static void* StaticSendHelper(void *pThis);
};

#endif // SERVERPROCESS_H
