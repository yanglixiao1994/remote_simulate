﻿#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include"controller.h"
#include <thread>
#include <stdlib.h>
#include <string>
int controller::count = 0;
controller::controller(){
	WSADATA wsData;
	WORD wr = MAKEWORD(2, 2);
	if (WSAStartup(wr, &wsData) != 0)
	{
		//std::cout << "create ws32 failed." << std::endl;
		std::abort();
	}
}
int controller::countnum(std::string&str) {
	int count = 0;
	for (auto&x : str) {
		if (x == '\n')
			count++;
	}
	return count;
}
void controller::connect_capturer(const std::string &ip, unsigned int port) {
	conn = socket(AF_INET, SOCK_STREAM, 0);
	if (conn == INVALID_SOCKET)
	{
		//std::cout << "create socket failed." << std::endl;
		std::abort();
	}
	sockaddr_in saServer;
	saServer.sin_family = AF_INET;
	saServer.sin_addr.S_un.S_addr = inet_addr(ip.c_str());
	saServer.sin_port = htons(port);
	if (connect(conn, (sockaddr*)&saServer, sizeof(sockaddr_in)) == SOCKET_ERROR)
	{
		//std::cout << "connect fail." << WSAGetLastError() << std::endl;
		closesocket(conn);
		std::abort();
	}
	//std::cout << "connect success." << std::endl;
}
void controller::reset() {
	send_command(Command::reset);
}
void controller::send_int(int data) {
	if (send(conn, (char*)&data, sizeof(data), 0) == SOCKET_ERROR)
	{
		//std::cout << "send int fail." << WSAGetLastError() << std::endl;
		std::abort();
	}
}
void controller::send_float(float data) {
	if (send(conn, (char*)&data, sizeof(data), 0) == SOCKET_ERROR)
	{
		//std::cout << "send float fail." << WSAGetLastError() << std::endl;
		std::abort();
	}
}
void controller::send_buff(const char*buff, int size) {
	if (send(conn, buff, size, 0) == SOCKET_ERROR) {
		//std::cout << "send buff error." << std::endl;
		std::abort();
	}
}
void controller::send_command(Command cmd) {
	if (send(conn, (char*)&cmd, sizeof(Command), 0) == SOCKET_ERROR)
	{
		//std::cout << "send int fail." << WSAGetLastError() << std::endl;
		std::abort();
	}
}
void controller::send_pcl_box(const pcl_box&box) {//const pcl_box&box
	send_command(Command::spawn_box);
	send_data_header(Data::pcl_box);
	send_int(box.id);
	send_float(box.pos_x);
	send_float(box.pos_y);
	send_float(box.pos_z);
	send_float(box.w);
	send_float(box.x);
	send_float(box.y);
	send_float(box.z);
	send_float(box.sizex);
	send_float(box.sizey);
	send_float(box.sizez);
	//std::ifstream ifs(file,std::ios::binary);
	//ifs.seekg(0, std::ios_base::end);
	//int size = ifs.tellg();
	//char *pcl = new char[size];
	//ifs.seekg(0, ifs.beg);
	//ifs.read(pcl, size);
	////size -= countnum(std::string(pcl));
	//send_int(size);
	//send_buff(pcl, size);
	//print("Send pcl boxes.");
}
std::string controller::receive_point_cloud() {
	send_command(Command::capture_pointcloud);
	if (Data::pointcloud != receive_data_header()) {
		error("No recv pointcloud header.");
		//std::cout << "Not Receive PointCloud." << std::endl;
		//std::abort();
	}
	int size = receive_int();
	std::string buff;
	buff.resize(size);
	if (size != recv(conn, &buff[0], size, 0)) {
		error("Recving pointcloud Error.");
		//std::cout << "Receive Point Cloud Failed." << std::endl;
		//std::abort();
	}
	print("Already recved pointcloud.");
	return buff;
}
std::string controller::receive_ue4_box() {
	send_command(Command::capture_ue4_boxs_pos);
	if (Data::ue4_box != receive_data_header()) {
		//std::cout << "Receive ue4_box Failed." << std::endl;
		print("No recving ue4_box");
		//std::abort();
	}
	//receive_int();
	//box->pos_x = receive_float();
	//box->pos_y = receive_float();
	//box->pos_z = receive_float();
	//box->ue4_rotx = receive_float();
	//box->ue4_roty = receive_float();
	//box->ue4_rotz = receive_float();
	//box->sizex = receive_float();
	//box->sizey = receive_float();
	//box->sizez = receive_float();
	int size = receive_int();
	std::string buff;
	buff.reserve(size);
	if (size != recv(conn, &buff[0], size, 0)) {
		error("Recving pointcloud Error.");
		//std::cout << "Receive Point Cloud Failed." << std::endl;
		//std::abort();
	}
	print("Already recved ue4boxes.");
	return buff;
}
Data controller::receive_data_header() {
	char buff[sizeof(Data)];
	if (recv(conn, buff, sizeof(Data), 0) <= 0) {
		//std::cout << "recv data failed." << std::endl;
		std::abort();
	}
	Data data = *(Data*)buff;
	return data;
}
int  controller::receive_int() {
	char buff[sizeof(int)];
	if (recv(conn, buff, sizeof(int), 0) <= 0) {
		//std::cout << "recv int failed." << std::endl;
		std::abort();
	}
	//std::cout << "Received int."<< *(int*)buff << std::endl;
	return *(int*)buff;
}
float  controller::receive_float() {
	char buff[sizeof(int)];
	if (recv(conn, buff, sizeof(int), 0) <= 0) {
		//std::cout << "recv int failed." << std::endl;
		std::abort();
	}
	//std::cout << "Received int." << *(float*)buff << std::endl;
	return *(float*)buff;
}
void controller::receive_img(image *img) {
	img->width = receive_int();
	img->height = receive_int();
	int size = img->width * img->height * 4;
	//std::cout << img->width << " "<< img->height  << std::endl;
	//std::cout << "Receive Img Size." << size<<std::endl;
	int len = 0;
	while (len < size) {
		int r = recv(conn, &img->buff[len], size - len, 0);
		//int r = recv(conn, test, img->size - len, 0);
		if (r <= 0) {
			//std::cout << "Receive img failed." << WSAGetLastError()<< std::endl;
			std::abort();
		}
		len += r;
		////std::cout << "len " << len << std::endl;
	}
	//std::cout << "Receive Img Buffer." << size << std::endl;
}
void controller::handle_data() {
	bool Bcimg = false, Bscore = false;//Bsimg = false, 
	for (;;) {
		if (Bcimg && Bscore) {//Bsimg && 
			make_decision();
			save_to_disk();
			Bcimg = false;
			//Bsimg = false;
			Bscore = false;
		}
		switch (receive_data_header()) {
		case Data::color_img:
			//std::cout << "Receive Color_Img_Header." << std::endl;
			receive_img(&color);
			Bcimg = true;
			break;
		case Data::segmentaion_img:
			//std::cout << "Receive Segmentation_Img_Header." << std::endl;
			receive_img(&segmentaion);
			//Bsimg = true;
			break;
		case Data::score:
			//std::cout << "Receive Score_Img_Header." << std::endl;
			score = receive_int();
			//std::cout << "Receive Score." <<score<< std::endl;
			Bscore = true;
			break;
		}
	}
}
void controller::save_to_disk() {
	color.save_to_file(std::to_string(count)+ "test");
}
void controller::make_decision() {
	switch(rand() % 4){
		//switch (0) {
		case 0:
			//std::cout << "Decision_Forward." << std::endl;
			send_command(Command::forward);
			break;
		case 1:
			//std::cout << "Decision_Backward." << std::endl;
			send_command(Command::backward);
			break;
		case 2:
			//std::cout << "Decision_Forward_Left." << std::endl;
			send_command(Command::forward_left);
			break;
		case 3:
			//std::cout << "Decision_Forward_Right." << std::endl;
			send_command(Command::forward_right);
			break;
	}
}
void controller::send_data_header(Data d) {
	if (send(conn, (char*)&d, sizeof(Data), 0) == SOCKET_ERROR)
	{
		//std::cout << "send data header fail." << WSAGetLastError() << std::endl;
		std::abort();
	}
}