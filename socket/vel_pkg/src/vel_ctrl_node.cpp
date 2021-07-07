#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#define QUEUE 20  //连接请求队列
#define PORT 8888
int conn;

void * connect(void *arg)
{
    char *buffer = (char *)arg;  
    // printf("%d\n",AF_INET);  //IPv4协议
    // printf("%d\n",SOCK_STREAM); //字节流套接字
    int ss = socket(AF_INET, SOCK_STREAM, 0);  //若成功则返回一个sockfd (套接字描述符)
    // printf("%d\n", ss);
    struct sockaddr_in server_sockaddr;  //一般是储存地址和端口，用于信息的显示及存储作用

    //下面设置sockaddr_in 结构体中相关参数
    server_sockaddr.sin_family = AF_INET;
    server_sockaddr.sin_port = htons(PORT); //将一个无符号短整型数值转换为网络字节序，即大端模式
    // printf("%d\n", INADDR_ANY);
    //INADDR_ANY就是指定地址为0.0.0.0的地址，这个地址事实上表示不确定地址，或"所有地址"、“任意地址”。
    //一般来说，在各个系统中均定义成为0值。
    server_sockaddr.sin_addr.s_addr = htonl(INADDR_ANY);  //将主机无符号长整型数转换成网络字节顺序。

    if(bind(ss, (struct sockaddr*)&server_sockaddr, sizeof(server_sockaddr)) == -1)
    {
        perror("bind");
        exit(1);
    }

    if(listen(ss, QUEUE) == -1)
    {
        perror("listen");
        exit(1);
    }

    struct sockaddr_in client_addr;
    socklen_t length = sizeof(client_addr);

    //成功返回非负描述字，出错返回-1
    conn = accept(ss, (struct sockaddr*)&client_addr, &length);
    //如果accept成功，那么其返回值是由内核自动生成的一个全新描述符，代表与所返回客户的TCP连接
    //accept之后就会用新的套接字conn
    if( conn < 0 )
    {
        perror("connect");
        exit(1);
    }
   
    // char buffer[1024];
    while(1)
    {
        //这里把send注释掉了，所以这个程序中server只能是接收client端的数据并能给client发送数据，即使不注释掉也没用，因为没有对是否有数据>传入和传入
        //进行判断所以按照下面的代码这样写，每次都要先让server输入后才能输出client传过来的数据，若是server不输入则程序无法向下走就没有client发送过来的输出，
        //而且每次显示也只能是一行，这样显示就全是错的了，所以就需要select和FD_ISSET的判断了
        // memset(buf, 0 ,sizeof(buf));
        // if(fgets(buf, sizeof(buf),stdin) != NULL) {
        //     send(conn, buf, sizeof(buf), 0);   
        // }

        // memset(buffer, 0, sizeof(buffer));
        int len = recv(conn, buffer, sizeof(buffer), 0);   //从TCP连接的另一端接收数据。
        /*该函数的第一个参数指定接收端套接字描述符；
        第二个参数指明一个缓冲区，该缓冲区用来存放recv函数接收到的数据；
        第三个参数指明buf的长度；
        第四个参数一般置0*/
        if(strcmp(buffer, "exit\n") == 0)//如果没有收到TCP另一端发来的数据则跳出循环不输出
        {
            break;
        }
        // printf("%s", buffer);//如果有收到数据则输出数据
        //必须要有返回数据， 这样才算一个完整的请求
        send(conn, buffer, len , 0);//向TCP连接的另一端发送数据。
    }
    close(conn);   //因为accept函数连接成功后还会生成一个新的套接字描述符，结束后也需要关闭
    close(ss);     //关闭socket套接字描述符
}

int main(int argc, char** argv)
{
    ros::init(argc, argv, "vel_ctrl");
    ros::NodeHandle n;
    ros::Publisher vel_pub = n.advertise<geometry_msgs::Twist>("/cmd_vel", 10);

    pthread_t tid;
    char *buffer = (char *)malloc(1024 * sizeof(char)); 
	pthread_create(&tid, NULL, connect, (void *)buffer);
    char state = buffer[0];

    while(ros::ok())
    {
        if(buffer[0] == 'w' || buffer[0] == 'a' || buffer[0] == 's' || buffer[0] == 'd' || buffer[0] == 'q' || buffer[0] == 'e' || buffer[0] == 'p' ||
        buffer[0] == 'W' || buffer[0] == 'A' || buffer[0] == 'S' || buffer[0] == 'D' || buffer[0] == 'Q' || buffer[0] == 'E' || buffer[0] == 'P')
        {
            if(state != buffer[0]){
                state = buffer[0];
                printf("server recive: %c, act!\n", state);
                if(state == 'w'){
                    geometry_msgs::Twist vel_cmd;
        
                    vel_cmd.linear.x = 0.2;
                    vel_cmd.linear.y = 0;
                    vel_cmd.linear.z = 0;
                    
                    vel_cmd.angular.x = 0;
                    vel_cmd.angular.y = 0;
                    vel_cmd.angular.z = 0;
                    vel_pub.publish(vel_cmd);
                }
                else if(state == 'a'){
                    geometry_msgs::Twist vel_cmd;
        
                    vel_cmd.linear.x = 0;
                    vel_cmd.linear.y = 0.2;
                    vel_cmd.linear.z = 0;
                    
                    vel_cmd.angular.x = 0;
                    vel_cmd.angular.y = 0;
                    vel_cmd.angular.z = 0;
                    vel_pub.publish(vel_cmd);
                }
                else if(state == 's'){
                    geometry_msgs::Twist vel_cmd;
        
                    vel_cmd.linear.x = -0.2;
                    vel_cmd.linear.y = 0;
                    vel_cmd.linear.z = 0;
                    
                    vel_cmd.angular.x = 0;
                    vel_cmd.angular.y = 0;
                    vel_cmd.angular.z = 0;
                    vel_pub.publish(vel_cmd);
                }
                else if(state == 'd'){
                    geometry_msgs::Twist vel_cmd;
        
                    vel_cmd.linear.x = 0;
                    vel_cmd.linear.y = -0.2;
                    vel_cmd.linear.z = 0;
                    
                    vel_cmd.angular.x = 0;
                    vel_cmd.angular.y = 0;
                    vel_cmd.angular.z = 0;
                    vel_pub.publish(vel_cmd);
                }
                else if(state == 'q'){
                    geometry_msgs::Twist vel_cmd;
        
                    vel_cmd.linear.x = 0;
                    vel_cmd.linear.y = 0;
                    vel_cmd.linear.z = 0;
                    
                    vel_cmd.angular.x = 0;
                    vel_cmd.angular.y = 0;
                    vel_cmd.angular.z = 0.2;
                    vel_pub.publish(vel_cmd);
                }
                else if(state == 'e'){
                    geometry_msgs::Twist vel_cmd;
        
                    vel_cmd.linear.x = 0;
                    vel_cmd.linear.y = 0;
                    vel_cmd.linear.z = 0;
                    
                    vel_cmd.angular.x = 0;
                    vel_cmd.angular.y = 0;
                    vel_cmd.angular.z = -0.2;
                    vel_pub.publish(vel_cmd);
                }
                else if(state == 'p'){
                    geometry_msgs::Twist vel_cmd;
        
                    vel_cmd.linear.x = 0;
                    vel_cmd.linear.y = 0;
                    vel_cmd.linear.z = 0;
                    
                    vel_cmd.angular.x = 0;
                    vel_cmd.angular.y = 0;
                    vel_cmd.angular.z = 0;
                    vel_pub.publish(vel_cmd);
                }
                else if(state == 'w'){
                    geometry_msgs::Twist vel_cmd;
        
                    vel_cmd.linear.x = 0.5;
                    vel_cmd.linear.y = 0;
                    vel_cmd.linear.z = 0;
                    
                    vel_cmd.angular.x = 0;
                    vel_cmd.angular.y = 0;
                    vel_cmd.angular.z = 0;
                    vel_pub.publish(vel_cmd);
                }
                else if(state == 'A'){
                    geometry_msgs::Twist vel_cmd;
        
                    vel_cmd.linear.x = 0;
                    vel_cmd.linear.y = 0.5;
                    vel_cmd.linear.z = 0;
                    
                    vel_cmd.angular.x = 0;
                    vel_cmd.angular.y = 0;
                    vel_cmd.angular.z = 0;
                    vel_pub.publish(vel_cmd);
                }
                else if(state == 'S'){
                    geometry_msgs::Twist vel_cmd;
        
                    vel_cmd.linear.x = -0.5;
                    vel_cmd.linear.y = 0;
                    vel_cmd.linear.z = 0;
                    
                    vel_cmd.angular.x = 0;
                    vel_cmd.angular.y = 0;
                    vel_cmd.angular.z = 0;
                    vel_pub.publish(vel_cmd);
                }
                else if(state == 'D'){
                    geometry_msgs::Twist vel_cmd;
        
                    vel_cmd.linear.x = 0;
                    vel_cmd.linear.y = -0.5;
                    vel_cmd.linear.z = 0;
                    
                    vel_cmd.angular.x = 0;
                    vel_cmd.angular.y = 0;
                    vel_cmd.angular.z = 0;
                    vel_pub.publish(vel_cmd);
                }
                else if(state == 'Q'){
                    geometry_msgs::Twist vel_cmd;
        
                    vel_cmd.linear.x = 0;
                    vel_cmd.linear.y = 0;
                    vel_cmd.linear.z = 0;
                    
                    vel_cmd.angular.x = 0;
                    vel_cmd.angular.y = 0;
                    vel_cmd.angular.z = 0.5;
                    vel_pub.publish(vel_cmd);
                }
                else if(state == 'E'){
                    geometry_msgs::Twist vel_cmd;
        
                    vel_cmd.linear.x = 0;
                    vel_cmd.linear.y = 0;
                    vel_cmd.linear.z = 0;
                    
                    vel_cmd.angular.x = 0;
                    vel_cmd.angular.y = 0;
                    vel_cmd.angular.z = -0.5;
                    vel_pub.publish(vel_cmd);
                }
                else if(state == 'P'){
                    geometry_msgs::Twist vel_cmd;
        
                    vel_cmd.linear.x = 0;
                    vel_cmd.linear.y = 0;
                    vel_cmd.linear.z = 0;
                    
                    vel_cmd.angular.x = 0;
                    vel_cmd.angular.y = 0;
                    vel_cmd.angular.z = 0;
                    vel_pub.publish(vel_cmd);
                }
                else{
                    geometry_msgs::Twist vel_cmd;
        
                    vel_cmd.linear.x = 0;
                    vel_cmd.linear.y = 0;
                    vel_cmd.linear.z = 0;
                    
                    vel_cmd.angular.x = 0;
                    vel_cmd.angular.y = 0;
                    vel_cmd.angular.z = 0;
                    vel_pub.publish(vel_cmd);
                }
            }
        }   
        ros::spinOnce();
    }
    return 0;
}
