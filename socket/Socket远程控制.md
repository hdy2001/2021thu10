# Socket远程控制

## 1. 运动方向

- 功能说明

远程操控运动，在另一台电脑上用w/s/a/d/p控制运动方向，p是停止。按shift加速。

- 如何配置

~~~
cp vel_pkg ~/catkin_ws
cp keyboard_pkg ~/catkin_ws
~~~

实际上，只需要在小智的机载电脑上配置vel_pkg，远程电脑上配置keyboard_pkg即可。

- 如何运行

首先在机载电脑上启动核心节点

~~~
roslaunch wpb_home_bringup minimal.launch
~~~

查看机载电脑ip

~~~
ifconfig -a
~~~

将该ip写到另一台电脑的~/catkin_ws/Data/Ip.txt里面。

再在机载电脑上开启server

~~~
rosrun vel_pkg vel_ctrl_node
~~~

最后在另一台电脑上开启client

~~~
rosrun keyboard_pkg keyboard_ctrl
~~~

## 2. 图像回传

- 功能说明

将小智拍摄到的图片实时回传，以便远程控制。

- 如何配置

~~~
cp SocketMatTransmissionServer.h ~/catkin_ws/src/wpb_home_apps/include
cp SocketMatTransmissionServer.cpp ~/catkin_ws/src/wpb_home_apps/src/scripts
cp server ~/catkin_ws/src/wpb_home_apps/src
cp server.launch ~/catkin_ws/src/wpb_home_apps/launch
the same for 4 client files
cp take_photo_test ~/catkin_ws/src/wpb_home_apps/src
modify CMakeLists 
~~~

- 如何运行

查看远程电脑ip，并将该ip写到另一台电脑的~/catkin_ws/Data/Ip.txt里面。

在远程电脑上开启server

~~~
roslaunch wpb_home_apps server.launch
~~~

在机载电脑开启take_photo_test

~~~
roslaunch wpb_home_apps take_photo_test.launch
~~~

