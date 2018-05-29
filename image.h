//Define the image buffer for transfer.
#ifndef _AUTODRIVER_IMG__
#define _AUTODRIVER_IMG__
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<fstream>
#define IMG_MAX_SIZE 50000000
struct image {
	unsigned int width,height;
	char *buff;
	image():width(1),height(1) {
		//image size should be controled below 5M
		buff = new char[IMG_MAX_SIZE];
	}
	void save_to_file(const std::string filename) {
		::std::string s = filename + ".ppm";
		FILE *f = fopen(s.c_str(), "w");
		fprintf(f, "P3\n%d %d\n%d\n", width, height, 255);
		for (int i = 0; i <width; i++) {
			//buff is empty
			//std::cout <<"*********"<< buff[i] << std::endl;
			for (int j = 0; j <  height; j++) {
				unsigned char b = buff[(i * height + j) * 4 + 0];
				unsigned char g = buff[(i * height + j) * 4 + 1];
				unsigned char r = buff[(i * height + j) * 4 + 2];
				//std::cout << r << " " << g << " " << b << std::endl;
				fprintf(f, "%d %d %d ", r, g, b);
			}
		}
		fclose(f);
	}
	void load_from_file(const std::string filename) {
		std::ifstream t;
		int length;
		t.open(filename);
		t.seekg(0, std::ios::end);
		length = t.tellg();
		if (length > IMG_MAX_SIZE)
			std::abort();
		t.seekg(0, std::ios::beg);
		t.read((char *)buff, length);
		t.close();
	}
	//void copy_from_mem(unsigned char*begin, unsigned int length) {
	//	if (length > IMG_MAX_SIZE)
	//		std::abort();
	//	size = length;
	//	for (int i = 0; i < length; i++) {
	//		buff[i] = begin[i];
	//	}
	//}
};
#endif