#include "generator.h"
#include <iostream>
generator::generator(string address_, int levelL_, int levelH_)
{
	address = address_;
	levelL = levelL_;
	levelH = levelH_;
	stlIsHere = new read_stl();
	stlIsHere->read("c:/1.stl");
	bounX = abs(stlIsHere->maxx - stlIsHere->minx);
	bounY = abs(stlIsHere->maxy - stlIsHere->miny);
	bounZ = abs(stlIsHere->maxz - stlIsHere->minz);
	int lines = pow(2, levelH);
	dx = bounX / lines;
	dy = bounY / lines;
	dz = bounZ / lines;
}

void generator::generatorOctree()//使用overlap函数判断交叉  使用cache保存
{
	//确定包围盒与dxdydz
	//遍历三角面片 生成交叉的边界使用cache保存



}