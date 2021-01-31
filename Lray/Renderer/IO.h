#pragma once
#include <vector>
#include <iostream>
#include <fstream>
#include <cmath>

inline void writeppm(int _sizex, int _sizey, std::vector<int> _data, std::string _name) {
	std::ofstream myfile;
	std::string filename = _name + ".ppm";
	std::cout << "writing to " << filename << std::endl;
	myfile.open(filename);
	myfile << "P3\n" << _sizex << " " << _sizey << "\n255\n";
	for (int i = 0; i < _sizey; i++) {
		for (int j = 0; j < _sizex; j++) {
			myfile << _data.at(j*3 + i * _sizex*3) << " " << _data.at(j*3 + i * _sizex*3 + 1) << " " << _data.at(j*3 + i * _sizex*3 + 2) << "\n";
		}
	}
	std::cout << "finished writing to " << filename << std::endl;
	myfile.close();
}
