#include <stdlib.h>
int main(){
    system("bash -c 'source /opt/ros/kinetic/setup.bash;source ~/catkin_ws/devel/setup.bash;"
    "rosrun waterplus_map_tools wp_saver &&"
    "cd ~ &&" 
    "python3 ~/catkin_ws/src/process_waypoints/process_waypoints.py &&"
    "cp waypoints.txt ~/catkin_ws/src/wpb_home/wpb_home_tutorials &&"
    // "killall roslaunch && killall bash;"
    "bash'&");
    return 0;
}