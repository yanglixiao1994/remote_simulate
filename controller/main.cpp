#include "controller.h"
#include <vector>
#include <math.h>
#include <string>
#include <stdio.h>

int main(int argc, char *argv[]) {
	controller ctr;
	ctr.connect_capturer("10.0.9.222", 8888);
	std::string pcd_name{"./ue4boxes.pcd"}, pose_name{"./pose.txt"};
	int id{-1};
	float position_x,position_y,position_z,quat_w,quat_x,quat_y,quat_z,size_x,size_y,size_z;
	std::cout << "-h, --help" << std::endl << "-s, --send single box, " << std::endl << "-f, --send a file with box data" << std::endl;
	int cnt = 0;
	while(strcmp(argv[1],"-s") == 0){
		std::cout << "box id begins with 0"<<std::endl;
		while(true){
			std::cout<<"input a box as following format : id position_x position_y position_z quat_w quat_x quat_y quat_z size_x size_y size_z"<<std::endl;
			std::cin>>id;
			if(id == -1){
				std::cout<<"capturing..."<<std::endl;
				break;
			}
			std::cin>>position_x>>position_y>>position_z>>quat_w>>quat_x>>quat_y>>quat_z>>size_x>>size_y>>size_z;
			pcl_box box{id,position_x,position_y,position_z,quat_w,quat_x,quat_y,quat_z,size_x,size_y,size_z};
        	ctr.send_pcl_box(box);
			int resultid = ctr.receive_int();
			if(ctr.receive_int() == 0){
				std::cout<<id<<" "<<"can not be spawned."<<std::endl;
			}
			else {
				std::cout<<id<<" "<<"has been spawned."<<std::endl;
			}
		}

		std::string pointcloud = ctr.receive_point_cloud();
		std::ofstream of(pcd_name);
		of << pointcloud.c_str() << std::endl;
		of.close();
		std::string pose = ctr.receive_ue4_box();
		of.open(pose_name);
		of << pose.c_str() << std::endl;
		of.close();
		if(!ctr.viewer(pcd_name, pose_name)){
			std::cout << "pcd error" << std::endl;
			return -1;
		}
	}

	if(strcmp(argv[1],"-f") == 0){
		std::string filename(argv[2]);	
		while(filename.compare("-1") != 0){
			std::ifstream inf(filename);
			while(!inf.eof()){
        		inf >> id >> position_x >> position_y >> position_z >> quat_w >> quat_x >> quat_y >> quat_z >> size_x >> size_y >> size_z;
				pcl_box box{id,position_x,position_y,position_z,quat_w,quat_x,quat_y,quat_z,size_x,size_y,size_z};
        		ctr.send_pcl_box(box);
				int id = ctr.receive_int();
				if(ctr.receive_int() == 0){
					std::cout<<id<<" "<<"can not be spawned."<<std::endl;
				}
				else {
					std::cout<<id<<" "<<"has been spawned."<<std::endl;
				}
        	}
        	inf.close();
			std::cout << "capturing..." << std::endl;
			std::ofstream of(pcd_name);
			of << ctr.receive_point_cloud().c_str() << std::endl;
			of.close();
			of.open(pose_name);
			of << ctr.receive_ue4_box().c_str() << std::endl;
			of.close();
			if(!ctr.viewer(pcd_name, pose_name)){
				std::cout << "pcd error" << std::endl;
				return -1;
			}
			std::cout<<"Input boxes file name:"<<std::endl;
			std::cin>>filename;
		}
	}

	if(strcmp(argv[1],"-h") == 0){
		//--help
	}

	else{
		std::cout << "require one argument" << std::endl;
	}
	ctr.reset();
	return 0;
}