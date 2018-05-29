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
#include <winsock2.h>
#include <ws2tcpip.h>
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define print(A) std::cout<<A<<std::endl
#define error(A) std::cout<<A<<std::endl;std::abort()
#pragma comment(lib,"Ws2_32.lib") 
class controller {
public:
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
	SOCKET conn = INVALID_SOCKET;
};
#endif