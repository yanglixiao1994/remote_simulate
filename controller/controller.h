//LiXiao.Yang 
//@Dorabot .Vision Team .
//3.22.2018
//Define the network of controller.
//This class's work is make decision according to the score and images from capturer.
#ifndef _AUTODRIVER_CONTROLLER__
#define _AUTODRIVER_CONTROLLER__
#include "image.h"
#include "command.h"
#include <iostream>
#include <stdio.h>  
#include <sys/types.h>  
#include <sys/socket.h>  
#include <arpa/inet.h>  
#include <stdlib.h>  
#include <string.h>  
#include <unistd.h>  
#include <netinet/in.h>  
#include <errno.h> 

#include <pcl/visualization/cloud_viewer.h>
#include <pcl/visualization/pcl_visualizer.h>
#include <pcl/io/io.h>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <Eigen/Geometry>
#include <Eigen/Dense>
#include <Eigen/Core>

#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define print(A) std::cout<<A<<std::endl
#define error(A) std::cout<<A<<std::endl;std::abort()

class controller {
	pcl::visualization::PCLVisualizer::Ptr viewer_;
public:
	int viewer(const std::string& pcd_name, const std::string& pose_name);


	controller();
	void connect_capturer(const std::string &ip, unsigned int port);
	void reset();
	void handle_data();
	void make_decision();
	void save_to_disk();

	void send_int(int);
	void send_float(float);
	void send_buff(const char*buff, int size);
	void send_command(Command);
	void send_pcl_box(const pcl_box&);//const pcl_box&);

	std::string receive_point_cloud();
	std::string receive_ue4_box();
	Data receive_data_header();
	int receive_int();
	float receive_float();
	void receive_img(image *);
	void send_data_header(Data);

	int countnum(std::string&);
	static int count;
	image color;
	image segmentaion;
	int score;
	// SOCKET conn = INVALID_SOCKET;
	int conn = -1;
};

#endif