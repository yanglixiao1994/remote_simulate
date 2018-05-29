//LiXiao.Yang 
//@Dorabot .Vision Team .
//3.22.2018
//Define the Command and Data header of the autodriver.
#ifndef _AUTODRIVER_COMMAND__
#define _AUTODRIVER_COMMAND__
enum class Command:char
{
	forward_left,
	forward_right,
	forward,
	backward_right,
	backward_left,
	backward,
	reset,
	spawn_box,
	capture_pointcloud,
	capture_ue4_boxs_pos,
};
enum class Data:char
{
	color_img,//capturer -> controller
	segmentaion_img, //capturer -> controller
	depth_img, //capturer -> controller
	score,//capturer -> controller
	pointcloud,
	ue4_box,
	pcl_box,
};

struct pcl_box {
	int id;
	float pos_x, pos_y, pos_z, w, x, y, z, sizex, sizey, sizez;
};

struct ue4_box {
	int id;
	float pos_x, pos_y, pos_z, ue4_rotx, ue4_roty, ue4_rotz, sizex, sizey, sizez;
};

#endif