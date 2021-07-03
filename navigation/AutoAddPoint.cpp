#include <stdlib.h>
int main(){
    system("bash -c 'source /opt/ros/kinetic/setup.bash;source ~/catkin_ws/devel/setup.bash;"
    "roslaunch wpb_home_apps add_point.launch ;bash'&");
    return 0;
}