# Jetson Vision #
This repository serves as a place to house any code designed to run on the Jetson TX2 board for Team 303.
Currently, the plans for the Jetson TX2 for Team 303 are to run vision processing.

This is accomplished as follows:
	1. Use a PlayStation Eye camera to capture 640x480 @ 60fps video
	2. Configure the webcam using Video4Linux (v4l2-ctl)
	3. Use gstreamer with Video4Linux to acquire an image
	4. Run an OpenCV pipeline on the image to detect retroreflective tape using an LED ring
	5. Send the results to the robot over networktables
	6. Send back the original & processed image to the DriverStation
	
# Setup #
Doing all of this requires a bit of setup on the user end. A lot of instructions, as well as most of the vision boilerplate code,
is taken from the FRC guide on [elinux.org](https://elinux.org/Jetson/FRC_Setup). However, there are a few modifications to the steps required.
Generally, these are the steps to set up the Jetson TX2 for Team 303 use.

### Step 1: OS & JetPack Tool Installation ###
Step 1 is flashing the Jetson with a L4T build, and installing all the JetPack tools. Follow the instructions here: [Orbitty Youtube Installation Video](https://www.youtube.com/watch?v=9uMvXqhjxaQ) to install the drivers for the orbitty board. After that you will need to install the rest of the jetpack tools (start at Installing CUDA and Other Dependencies): [OpenCV Installation](https://github.com/NVIDIA-AI-IOT/jetson-trashformers/wiki/Jetson%E2%84%A2-Flashing-and-Setup-Guide-for-a-Connect-Tech-Carrier-Board). If you use a VM to function as the host computer, use VMWare Workstation Player (any version). VirtualBox did not work for me. 
The Jetson and the host computer need to be connected to the same router for this to happen, and it's easy to accidentally quit the install application.
You can test if this worked correctly by running a CUDA sample ('/home/NVIDIA/NVIDIA_CUDA-8.0_Samples/').

### Step 2: Kernel Rebuilding ###
Step 2 is getting the PlayStation Eye camera to work. It requires a custom driver that is available as part of the linux kernel, but sadly
it is not included by default. Luckily for us, the kernel can be rebuilt on the jetson itself thanks to some clever hacks from jetsonhacks.com.
Kangalow (guy from jetsonhacks.com) has a beautiful guide (and video!) for rebuilding the kernel on the jetson itself. All that you need to do is
follow the guide but instead of installing the ttyACM module, install the 'OV534 OV772x USB Camera Driver' as a module. Select it and hit 'm' to do this. 
Make sure to save the kernel configuration, and build and install the kernel image. Reboot the Jetson afterward.
Follow these links in order: https://www.jetsonhacks.com/2017/07/31/build-kernel-ttyacm-module-nvidia-jetson-tx2/ (build the kernel - make sure it's the correct L4T build - 27.1, 28.1, and 28.2 should all work) and install the module of the playstation eye (https://www.jetsonhacks.com/2016/09/29/sony-playstation-eye-nvidia-jetson-tx1/).  

### Step 3: Install More Tools ###
Step 3 is installing NetworkTables, GStreamer, and Samba. Do the Samba installation first. Follow the elinux instructions for all of these.

NetworkTables is used to transfer data between the Jetson and the RoboRIO. The newest version
doesn't support native aarch64 builds, so you'll have to clone the ntcore repository and build an old version. 

GStreamer is used to stream images over the network as well as get the image from the camera and pass it to OpenCV. It needs to be installed on the Jetson
as well as the driverstation computer. Batch files are used on the driverstation to read the image from the network, and these need to be launched manually.
The SmartDashboard's mjpeg reader won't work because gstreamer is not natively set up to stream mjpeg. It could be with some tweaking, and the example code seems
to provide it but claims it's slower than gstreamer's native way of doing it (which I think is just UDP).

Samba is used to mark a directory on the jetson as a mountable windows drive. This makes development much easier, as you don't need to connect a monitor & keyboard
to the jetson whenever you want to upload files.

### Step 4: Setup the host computer & driverstation ###
In order to manage git repositories on the Jetson, you can use [Git For Windows](https://git-scm.com/) as a gui or through a bash shell over the samba directory.
In order to remotely run commands and build/start/stop code, you'll need an SSH client. My favorite one to use is [PuTTY](https://www.chiark.greenend.org.uk/~sgtatham/putty/latest.html).
As previously mentioned, you'll need [GStreamer for windows](https://gstreamer.freedesktop.org/documentation/installing/on-windows.html) and some sample batch files that are included
[in this repository](https://github.com/Team303/JetsonVision/tree/master/StreamingOnly/ClientSide). 

### Step 5: Setup The Example Code ###
You can compile the example code by going to the example you want's root directory (with the makefile) and running 'make'. Then, you can run it with './gstream_cv'.
You may notice that the build fails when you try to run it. This is because it is looking for NetworkTables in the wrong spot.
To fix this, edit the makefile and replace any instance of "3419" with "303". If it still doesn't build, you installed something wrong or not at all or try to reboot the jetson. Check that OpenCV and CUDA
actually exist on the system. 

Once you have it building and running, you can edit the parameters in main.cpp and vision.cpp as well as the header file vision.hpp to get it working the way you want.
Change the good_settings.sh script to change camera settings. Make sure to recompile after any changes. 
