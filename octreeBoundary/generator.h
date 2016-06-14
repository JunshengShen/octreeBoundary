#pragma once
//
#include "read_stl.h"
class generator {
private:
	string address;
	int levelL, levelH;
	read_stl * stlIsHere;
	double bounX, bounY, bounZ;
	double dx, dy, dz;
public:
	generator(string address_,int levelL_,int levelH_);
	void generatorOctree();
};