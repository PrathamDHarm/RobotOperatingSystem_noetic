# RobotOperatingSystem_noetic
This tutorial will help the beginners to learn the ROS aswell as GAZEBO and  both easy to understand and impliment.  

# WHAT IS ROS?

ROS is an open-source, meta-operating system for your robot. It provides the services you would expect from an operating system, including hardware       abstraction, low-level device control, implementation of commonly-used functionality, message-passing between processes, and package management. It       also provides tools and libraries for obtaining, building, writing, and running code across multiple computers.
    
# ROS NOETIC Installation

  1)Go ros official page to install ros noetic in UBUNTU-20.04(focal) ( http://wiki.ros.org/ROS/Installation )

  2)Setup your sources.list
 
   Setup your computer to accept software from packages.ros.org.
    
       •  sudo sh -c 'echo "deb http://packages.ros.org/ros/ubuntu $(lsb_release -sc) main" > /etc/apt/sources.list.d/ros-latest.list'
    
  3)Set up your keys
      
       sudo apt install curl # if you haven't already installed curl
      
       curl -s https://raw.githubusercontent.com/ros/rosdistro/master/ros.asc | sudo apt-key add -
  
  4)Make sure your Debian package index is up-to-date
    
       • sudo apt update

       • sudo apt install ros-noetic-desktop-full
    
  5)Now, in New terminal paste the below command
 
       echo "source /opt/ros/noetic/setup.bash" >> ~/.bashrc
   
       source ~/.bashrc
   
  6)Let's create and build a catkin workspace

       $ mkdir -p ~/catkin_ws/src

       $ cd ~/catkin_ws/

       $ catkin_make
   
  7)Now, 
 
       $ cd ~/catkin_ws/src

       $ git clone https://github.com/PrathamDHarm/RobotOperatingSystem_noetic.git
       
       $ git clone https://github.com/ROBOTIS-GIT/turtlebot3.git
       
       $ git clone https://github.com/ROBOTIS-GIT/turtlebot3_simulations.git

       $ cd  . .

       $ catkin_make
 
       
  # Point Cloud2 shows the 3D projection view of the camera in gazebo
      
       $roslaunch robot two_wheel_robot.launch

  ![Screenshot from 2023-01-07 14-55-36](https://user-images.githubusercontent.com/109065335/211144414-fda5776f-c510-4987-b22b-60273f8cd31c.png)
    
  ![Screenshot from 2023-01-07 14-56-06](https://user-images.githubusercontent.com/109065335/211144421-02c5cbb5-f199-47c2-8cd9-dda430075ad7.png)

