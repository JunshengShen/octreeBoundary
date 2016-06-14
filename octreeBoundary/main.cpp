#include "read_stl.h"
#include "oct.h"
#include <iostream>
#include <cmath>
#include <iomanip>
#include <fstream>
#include <sstream>
#include "cache.h"
#include "voxelinfo.h"
#include "generator.h"
#define levelLow 5;
#define voxelsInOneLowLevel 32768;
using namespace std;
/*void coor1(float max_x, float max_y, float max_z, int level)//三个包装盒的尺寸  分割次数
{
	double lines = pow(2, level);//计算每一行有多少体素   dxdydz分别是三个方向上每个体素的尺寸
	double dx = max_x / lines;
	double dy = max_y / lines;
	double dz = max_z / lines;

	fstream outfile;
	outfile.open("D:\\oofem\\build2.3\\Debug\\test1.txt", ios::app);
	int number = 1;
	lines += 1;
	for (int i = 0; i < lines; i++)//输出每个节点的坐标
	{
		for (int j = 0; j < lines; j++)
		{
			for (int k = 0; k < lines; k++)
			{

				if (k == 0)
				{
					outfile << "node   " << number++ << "   coords 3     " << j *dx << "  " << k *dy << "  " << i *dz << "       bc 3 2 2 2" << endl;
				}
				else
					outfile << "node   " << number++ << "   coords 3     " << j *dx << "  " << k *dy << "  " << i *dz << endl;
			}
		}
	}
	outfile.close();
}*/
int main()
{
	/*read_stl a;
	a.read("c:/1.stl");
	int i = a.triganles.size();
	cout << endl;
	cout << "triganles=" << i << endl;*/
	
	//voxels<VoxelInfo> asd_("d:", 2, 2, 64);
	generator asd("d:",1,1);
	asd.generatorOctree();
	system("pause");

	return 0;
}