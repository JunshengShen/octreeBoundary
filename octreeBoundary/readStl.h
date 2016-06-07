#pragma once
#include <vector>
#include <ostream>
using namespace std;
class triganle
{
public:

	double x[3];
	double y[3];
	double z[3];
	double normal[3];
};

ostream & operator<<(ostream & o, const triganle & tir);

class read_stl
{
public:
	float minx, miny, minz, maxx, maxy, maxz;
	vector <triganle> triganles;
	void read(string);
	void read_normal(string);
	void read_vertexs(string);
};
int asc2(char);