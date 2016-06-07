#pragma once
struct coor {
	float x, y, z;
};
bool overlap(coor, coor, coor,//tri
	float, float, float, float, float, float);//voxel