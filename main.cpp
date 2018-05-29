#include "controller.h"
#include <vector>
#include <math.h>

int main() {
	controller ctr;

	std::ifstream ifs("D:\\Boxes.txt");
	//ifs.seekg(0, std::ios_base::end);
	//int size = ifs.tellg();
	//char *pcl = new char[size];
	//ifs.seekg(0, ifs.beg);
	//ifs.read(pcl, size);
	//size -= ctr.countnum(std::string(pcl));

	ctr.connect_capturer("10.0.9.222", 8888);
	//ctr.connect_capturer("127.0.0.1", 18381);


	for (int i = 0; i < 20; i++) {
		//pcl_box box{ 0, (float)-500, (float)0 ,(float)1000 ,(float)0.854 ,(float)0.146 ,(float)0.354 ,(float)0.354,(float)200,(float)100,(float)300 };
		//ctr.send_pcl_box(box);
		//box = { 1 ,(float)-100, (float)100, (float)700, (float)0.924,  (float)0 ,(float)0.383, (float)0 ,(float)200 ,(float)100, (float)300 };
		//ctr.send_pcl_box(box);
		//box = { 2 ,(float)300 ,(float)500 ,(float)1500 ,(float)0.750 ,(float)0.433 ,(float)-0.250 ,(float)0.433 ,(float)200 ,(float)100 ,(float)300 };
		//ctr.send_pcl_box(box);
		//box = { 3 ,(float)500 ,(float)200 ,(float)900  ,(float)0.800 ,(float)0.191 ,(float)0.331  ,(float)0.462 ,(float)200 ,(float)100 ,(float)300 };
		//ctr.send_pcl_box(box);
		pcl_box box{ i ,rand()%1000 - 500 ,rand()%500 ,rand()%1000 + 500 ,(float)(rand()%1000 )/1000 ,(float)(rand() % 1000) / 1000 ,(float)(rand() % 1000) / 1000  ,(float)(rand() % 1000) / 1000 ,rand()%200 ,rand() % 200 ,rand() % 200 };
		ctr.send_pcl_box(box);
	}
	std::string pointcloud = ctr.receive_point_cloud();
	//std::cout << pointcloud.c_str() << std::endl;
	std::ofstream of("D:\\ue4boxes1.pcd");// Yanglixiao\\tools\\ue4boxes.pcd");
	of << pointcloud.c_str() << std::endl;
	of.close();
	std::string pose = ctr.receive_ue4_box();
	of.open("D:\\pose1.txt");// Yanglixiao\\tools\\ue4boxes.pcd");
	of << pose.c_str() << std::endl;
	of.close();
	//std::string ue4boxes = ctr.receive_ue4_box();
	//of.open("D:\\Yanglixiao\\tools\\ue4pose.txt");
	//of << ue4boxes.c_str() << std::endl;


	//for (int i = 0; i < 5; i++) {
	//	int id, px, py, pz, w, x, y, z, sx, sy, sz;
	//	ifs >> id >> px >> py >> pz >> w >> x >> y >> z >> sx >> sy >> sz;
	//	pcl_box box{ id - 1,px,py,pz,w,x,y,z,sx,sy,sz };
	//	ctr.send_pcl_box(box);
	//}
	pcl_box box = { 0,(float)200,(float)350,(float)900,(float)0.800,(float)0.191,(float)0.331,(float)0.462,(float)200,(float)100,(float)300 };
	ctr.send_pcl_box(box);
	box = { 1,(float)500,(float)200,(float)900,(float)0.800,(float)0.191,(float)0.331,(float)0.462,(float)200,(float)100,(float)300 };
	ctr.send_pcl_box(box);
	box = { 2,(float)300,(float)100,(float)700,(float)0.924,(float)0.383,(float)0,(float)0,(float)200,(float)100,(float)300 };

	ctr.send_pcl_box(box);
	pointcloud = ctr.receive_point_cloud();
	//std::cout << pointcloud.c_str() << std::endl;
	of.open("D:\\ue4boxes2.pcd");// Yanglixiao\\tools\\ue4boxes.pcd");
	of << pointcloud.c_str() << std::endl;
	of.close();
	pose = ctr.receive_ue4_box();
	of.open("D:\\pose2.txt");// Yanglixiao\\tools\\ue4boxes.pcd");
	of << pose.c_str() << std::endl;
	of.close();

	//of.close();
	ctr.reset();
	for (;;) {
		//std::vector<pcl_box> boxs;
		//for (int i = 1; i < 10; i++) {
		//	pcl_box pcb = { i,rand()%1000,rand() % 1000,rand() % 1000,1,0,0,0,rand() % 200,rand() % 200,rand() % 200 };
		//	boxs.push_back(pcb);
		//	Sleep(300);
		//}
		//for (auto &b : boxs) {
		//ctr.send_pcl_box("D:\\Yanglixiao\\tools\\pclboxes.txt");
		//}
		std::string pointcloud = ctr.receive_point_cloud();
		//std::cout << pointcloud.c_str() << std::endl;
		std::ofstream of("D:\\Yanglixiao\\tools\\ue4boxes.pcd");
		of << pointcloud.c_str() << std::endl;
		of.close();
		std::string ue4boxes = ctr.receive_ue4_box();
		of.open("D:\\Yanglixiao\\tools\\ue4pose.txt");
		of << ue4boxes.c_str() << std::endl;
		of.close();
		//std::cout << "UE4 box:" << box.pos_x << " " << box.pos_y << " " << box.pos_z << std::endl;
	}
	return 0;
}