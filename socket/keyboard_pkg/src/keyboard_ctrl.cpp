#include <termios.h>
#include <signal.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/poll.h>
 
#include <boost/thread/thread.hpp>
#include <ros/ros.h>
#include <geometry_msgs/Twist.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include <fcntl.h>
#define QUEUE 20  //连接请求队列
#define PORT 8888
#define BUFFER_SIZE 1024
int conn;
 
#define KEYCODE_W 0x77
#define KEYCODE_A 0x61
#define KEYCODE_S 0x73
#define KEYCODE_D 0x64
#define KEYCODE_Q 0x71
#define KEYCODE_E 0x65
 

//shift to accelerate by the method of CAP
#define KEYCODE_A_CAP 0x41
#define KEYCODE_D_CAP 0x44
#define KEYCODE_S_CAP 0x53
#define KEYCODE_W_CAP 0x57
#define KEYCODE_Q_CAP 0x51
#define KEYCODE_E_CAP 0x45

//pause
#define KEYCODE_PAUSE 0x40

#define BUFFSIZE 1024

std::string ServerIp = "127.0.0.1";

typedef struct buffer{
    char sendbuff[BUFFSIZE];
    char recvbuff[BUFFSIZE];
}buff;

void * connect(void *arg)
{
    buff *b= (buff*)arg;
    //定义 sockfd
    int sock_cli = socket(AF_INET, SOCK_STREAM, 0);

    //定义sockaddr_in
    struct sockaddr_in servaddr;
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);  //服务器端口
    servaddr.sin_addr.s_addr = inet_addr(ServerIp.c_str());  //服务器ip， inet_addr用于IPv4的IP转换(十进制转换为二进制)
    //127.0.0.1是本地预留地址
    //连接服务器， 成功返回0， 错误返回 -1
    int n;
    
    if(connect(sock_cli, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
    {
        perror("connect");
        exit(1);
    }

    while(fgets(b->sendbuff, sizeof(b->sendbuff), stdin) != NULL)
    {
        //每次读取一行，读取的数据保存在buf指向的字符数组中，成功，则返回第一个参数 buf
        send(sock_cli, b->sendbuff, strlen(b->sendbuff), 0); //发送
        if(strcmp(b->sendbuff, "exit\n") == 0)
                break;
        recv(sock_cli, b->recvbuff, sizeof(b->recvbuff), 0);  //接收

        // fputs(b->recvbuff, stdout);

        memset(b->sendbuff, 0, sizeof(b->sendbuff));  //接受或者发送完毕后把数组中的数据全部清空。 置 0
        memset(b->recvbuff, 0, sizeof(b->recvbuff));
    }
    close(sock_cli);
}

class KeyboardNode
{
    private:
        double walk_vel;
        double run_vel;
        double yaw_rate_;
        double yaw_rate_run;
        
        geometry_msgs::Twist cmdvel_;
        ros::NodeHandle n_;
        ros::Publisher pub_;
 
    public:
        char buffer[BUFFER_SIZE];
        KeyboardNode()
        {
            pub_ = n_.advertise<geometry_msgs::Twist>("cmd_vel", 1);
            
            ros::NodeHandle n_private("~");
            n_private.param("walk_vel", walk_vel, 0.5);
            n_private.param("run_vel", run_vel, 1.0);
            n_private.param("yaw_rate", yaw_rate_, 1.0);
            n_private.param("yaw_rate_run", yaw_rate_run, 1.5);
        }
        
        ~KeyboardNode() { }
        void keyboardLoop();
        
        void stopRobot()
        {
            cmdvel_.linear.x = 0.0;
            cmdvel_.linear.y = 0.0;
            cmdvel_.angular.z = 0.0;
            pub_.publish(cmdvel_);
        }
};
 
KeyboardNode* tbk;
int kfd = 0;
struct termios cooked, raw;
bool done;
 
int main(int argc, char** argv)
{
    ros::init(argc,argv,"tbk", ros::init_options::AnonymousName | ros::init_options::NoSigintHandler); //rosrun several same nodes by "ros::init_options::AnonymousName"
    KeyboardNode tbk;
    //multithreading
    boost::thread t = boost::thread(boost::bind(&KeyboardNode::keyboardLoop, &tbk));

    pthread_t tid;
    buff *b = (buff *)malloc(sizeof(buff));
    pthread_create(&tid, NULL, connect, (void *)b);

    while(1){
        printf("send: %s\n",b->sendbuff);
        printf("recv: %s\n",b->recvbuff);
        sleep(0.1);
    }

    ros::spin();
    
    t.interrupt();
    t.join();
    tbk.stopRobot();
    tcsetattr(kfd, TCSANOW, &cooked);//TCSANOW：不等数据传输完毕就立即改变属性
    
    return(0);
}
 
void KeyboardNode::keyboardLoop()
{
    char c;
    double max_tv = walk_vel;
    double max_rv = yaw_rate_;
    bool dirty = false;
    int speed_x = 0;  //x
    int speed_y = 0;  //y
    int turn = 0;     //z
    
    // get the console in raw mode
    tcgetattr(kfd, &cooked);//获得标准输入的终端参数，将获得的信息保存在cooked变量中
    memcpy(&raw, &cooked, sizeof(struct termios));//copy cooked to raw
    raw.c_lflag &=~ (ICANON | ECHO);
    raw.c_cc[VEOL] = 1;//VEOL(0, NUL) 附加的行尾字符。当设置 ICANON 时可被识别。
    raw.c_cc[VEOF] = 2;//修改获得的终端信息的结束控制字符,VEOF(004, EOT, Ctrl-D) 文件尾字符。更精确地说，这个字符使得 tty 缓冲中的内容被送到等待输入的用户程序中，而不必等到 EOL。如果它是一行的第一个字符，那么用户程序的read() 将返回 0，指示读到了 EOF。当设置 ICANON 时可被识别，不再作为输入传递。

    tcsetattr(kfd, TCSANOW, &raw);//使用tcsetattr函数将修改后的终端参数设置到标准输入
    
    puts("Reading from keyboard");
    puts("Use W,A,S,D,Q,E keys to control the robot");
    puts("Press Shift to move faster");
    
    struct pollfd ufd;
    ufd.fd = kfd;
    ufd.events = POLLIN;
    
    for(;;)
    {
        boost::this_thread::interruption_point();
        // get the next event from the keyboard
        int num;
        
        if ((num = poll(&ufd, 1, 250)) < 0)
        {
            perror("poll():error");
            return;
        }
        else if(num > 0)
        {
            if(read(kfd, &c, 1) < 0)
            {
                perror("read():error");
                return;
            }
        }
        else
        {
            // //loop
            // if (dirty == true)
            // {
            //     // stopRobot();w
            //     // dirty = false;
            // }
            continue;
        }
        switch(c)
        {
            case KEYCODE_W:
                buffer[0] = 'w';
                break;
            case KEYCODE_S:
                buffer[0] = 's';
                break;
            case KEYCODE_A:
                buffer[0] = 'a';
                break;
            case KEYCODE_D:
                buffer[0] = 'd';
                break;
            case KEYCODE_Q:
                buffer[0] = 'q';
                break;
            case KEYCODE_E:
                buffer[0] = 'e';
                break;   
            case KEYCODE_W_CAP:
                buffer[0] = 'W';
                break;
            case KEYCODE_S_CAP:
                buffer[0] = 'S';
                break;
            case KEYCODE_A_CAP:
                buffer[0] = 'A';
                break;
            case KEYCODE_D_CAP:
                buffer[0] = 'D';
                break;   
            case KEYCODE_Q_CAP:
                buffer[0] = 'Q';
                break;
            case KEYCODE_E_CAP:
                buffer[0] = 'E';
                break;         
            default:
                buffer[0] = 'p';
                break;
        }
        buffer[1] = '\n';
    }
}