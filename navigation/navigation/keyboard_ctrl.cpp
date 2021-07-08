#include <termios.h>
#include <signal.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/poll.h>
 
#include <boost/thread/thread.hpp>
#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
 
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
    c = 'w';
    // double max_tv = walk_vel;
    // double max_rv = yaw_rate_;
    // bool dirty = false;
    // int speed_x = 0;  //x
    // int speed_y = 0;  //y
    // int turn = 0;     //z
    
    // // get the console in raw mode
    // tcgetattr(kfd, &cooked);//获得标准输入的终端参数，将获得的信息保存在cooked变量中
    // memcpy(&raw, &cooked, sizeof(struct termios));//copy cooked to raw
    // raw.c_lflag &=~ (ICANON | ECHO);
    // raw.c_cc[VEOL] = 1;//VEOL(0, NUL) 附加的行尾字符。当设置 ICANON 时可被识别。
    // raw.c_cc[VEOF] = 2;//修改获得的终端信息的结束控制字符,VEOF(004, EOT, Ctrl-D) 文件尾字符。更精确地说，这个字符使得 tty 缓冲中的内容被送到等待输入的用户程序中，而不必等到 EOL。如果它是一行的第一个字符，那么用户程序的read() 将返回 0，指示读到了 EOF。当设置 ICANON 时可被识别，不再作为输入传递。

    // tcsetattr(kfd, TCSANOW, &raw);//使用tcsetattr函数将修改后的终端参数设置到标准输入
    
    // puts("Reading from keyboard");
    // puts("Use W,A,S,D,Q,E keys to control the robot");
    // puts("Press Shift to move faster");
    
    // struct pollfd ufd;
    // ufd.fd = kfd;
    // ufd.events = POLLIN;
    
    // for(;;)
    // {
    //     boost::this_thread::interruption_point();
        
    //     // get the next event from the keyboard
    //     int num;
        
    //     if ((num = poll(&ufd, 1, 250)) < 0)
    //     {
    //         perror("poll():error");
    //         return;
    //     }
    //     else if(num > 0)
    //     {
    //         if(read(kfd, &c, 1) < 0)
    //         {
    //             perror("read():error");
    //             return;
    //         }
    //     }
    //     else
    //     {
    //         //loop
    //         if (dirty == true)
    //         {
    //             stopRobot();
    //             dirty = false;
    //         }
            
    //         continue;
    //     }
        
    //     switch(c)
    //     {
    //         case KEYCODE_W:
    //             max_tv = walk_vel;
    //             speed_x = 1;
    //             speed_y = 0;
    //             turn = 0;
    //             dirty = true;
    //             break;
    //         case KEYCODE_S:
    //             max_tv = walk_vel;
    //             speed_x = -1;
    //             speed_y = 0;
    //             turn = 0;
    //             dirty = true;
    //             break;
    //         case KEYCODE_A:
    //             max_rv = walk_vel;
    //             speed_x = 0;
    //             speed_y = 1;
    //             turn = 0;
    //             dirty = true;
    //             break;
    //         case KEYCODE_D:
    //             max_rv = walk_vel;
    //             speed_x = 0;
    //             speed_y = -1;
    //             turn = 0;
    //             dirty = true;
    //             break;
    //         case KEYCODE_Q:
    //             max_rv = yaw_rate_;
    //             speed_x = 0;
    //             speed_y = 0;
    //             turn = 1;
    //             dirty = true;
    //             break;
    //         case KEYCODE_E:
    //             max_rv = yaw_rate_;
    //             speed_x = 0;
    //             speed_y = 0;
    //             turn = -1;
    //             dirty = true;
    //             break;
            

                
    //         case KEYCODE_W_CAP:
    //             max_tv = run_vel;
    //             speed_x = 1;
    //             speed_y = 0;
    //             turn = 0;
    //             dirty = true;
    //             break;
    //         case KEYCODE_S_CAP:
    //             max_tv = run_vel;
    //             speed_x = -1;
    //             speed_y = 0;
    //             turn = 0;
    //             dirty = true;
    //             break;
    //         case KEYCODE_A_CAP:
    //             max_rv = run_vel;
    //             speed_x = 0;
    //             speed_y = 1;
    //             turn = 0;
    //             dirty = true;
    //             break;
    //         case KEYCODE_D_CAP:
    //             max_rv = run_vel;
    //             speed_x = 0;
    //             speed_y = -1;
    //             turn = 0;
    //             dirty = true;
    //             break;   
    //         case KEYCODE_Q_CAP:
    //             max_rv = yaw_rate_run;
    //             speed_x = 0;
    //             speed_y = 0;
    //             turn = 1;
    //             dirty = true;
    //             break;
    //         case KEYCODE_E_CAP:
    //             max_rv = yaw_rate_run;
    //             speed_x = 0;
    //             speed_y = 0;
    //             turn = -1;
    //             dirty = true;
    //             break;         
    //         default:
    //             max_tv = walk_vel;
    //             max_rv = yaw_rate_;
    //             speed_x = 0;
    //             turn = 0;
    //             dirty = false;
    //     }
    //     cmdvel_.linear.x = speed_x * max_tv;
    //     cmdvel_.linear.y = speed_y * max_tv;
    //     cmdvel_.angular.z = turn * max_rv;
    //     pub_.publish(cmdvel_);
    // }
}