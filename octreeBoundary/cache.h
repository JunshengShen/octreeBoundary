//缓存类
#pragma once
#include <string>
#include <deque>
#include <sstream>
#include <fstream>
using namespace std;
template <class T>//要重载==  =(liangge)  !=  < >运算符     必须是一个类       T=-1要重载成标记次单元不存在-
class voxels {//向外可以只提供两个函数 getCode和saveOne   其他都能作为private
private:
	string address;
	int levelL, levelH;//levelL是每一块的分割次数    levelH是总的分割次数
public://！！！size要小于等于levelL次数下一个文件中的数目    函数中加了一个检查  如果大于 就改小   没有检查会错 我也不知道为什么  可能是测试时候只有一个文件  第二个文件打不开就出错了  多文件测试时候要注意
	deque<T> voxel;
	voxels(string address_, int levelL_, int levelH_, int size = 4096);//构造函数需要知道去哪里读文件(目录)，赋值给address  并且读入前size个值    输入是address和deque的大小,还有两个划分次数   
	voxels(string address_, int levelL_, int levelH_, string sth, int size = 4096);//覆盖原文件的构造函数
	typename deque<T>::iterator getCode(unsigned long long mortonCode);//查找deque中有无所需的代码  如果有返回其迭代器  如果没有就去读一个
	typename deque<T>::iterator readOneCode(T needed);//输入为需要的   输出返回一个迭代器 如果没有找到就返回end()
	typename deque<T>::iterator readOneToUpdate(unsigned long long lordCommander);//输入为需要读的  读一个删除一个  删除时候要对文件中的进行修改  返回读入的数据的迭代器
	T readOneFromFile(unsigned long long monica);//读出monica编号的数据
	void saveOne(T oneToSave);//保存这个到队列中  队列中应该有这个  没有的话说不定会爆炸
	void updateOne(T & lokTar);
	~voxels() {
		for (int i = 0;i < voxel.size();i++) {
			updateOne(voxel[i]);
		}
	}
};

template<class T>
inline void voxels<T>::updateOne(T & lokTar)
{
	string fileAddress;
	unsigned long long fileNum = lokTar / (1 << 3 * levelL);
	cout << "!!!!!" << fileNum;
	stringstream ss;
	ss << fileNum;
	ss >> fileAddress;
	fileAddress = address + "\\outOfCore" + fileAddress + ".bat";
	fstream write;
	write.open(fileAddress, ios::out |ios::in| ios::binary);
	unsigned long long location;
	location = lokTar % (1 << 3 * levelL);
	cout << "!!!!!" << location << ' ' << lokTar;
	write.seekp(sizeof(T)*location, ios::beg);
	write.write((char*)&lokTar, sizeof(T));
	write.close();


	ifstream readIn;
	readIn.open(fileAddress, ios::in | ios::binary);
	T majnun;
	for (int i = 0;i < 64;i++) {
		readIn.seekg(sizeof(T)*i, ios::beg);

		readIn.read((char *)&majnun, sizeof(T));
		cout << ' ' << majnun << endl;
	}
	readIn.close();



}


template<class T>
inline void voxels<T>::saveOne(T oneToSave) {
	typename deque<T>::iterator temp = readOneCode(oneToSave);
	*temp = oneTosave;
}
template<class T>
inline T voxels<T>::readOneFromFile(unsigned long long monica) {
	string fileAddress;
	unsigned long long fileNum = monica / (1 << (3 * levelL));
	stringstream ss;
	ss << fileNum;
	ss >> fileAddress;
	fileAddress = address + "\\outOfCore" + fileAddress + ".bat";
	ifstream readIn;
	readIn.open(fileAddress, ios::in | ios::binary);
	T majnun;
	monica %= (1 << (3 * levelL));
	readIn.seekg(sizeof(T)*monica, ios::beg);
	
	readIn.read((char *)&majnun, sizeof(T));
	
	readIn.close();
	return majnun;
}
template<class T>
inline typename deque<T>::iterator voxels<T>::readOneToUpdate(unsigned long long lordCommander) {
	T majnun = readOneFromFile(lordCommander);
	updateOne(voxel[0]);//upadte the file
	voxel.pop_front();
	voxel.push_back(majnun);
	return (voxel.end() - 1);
}
template<class T>
inline typename deque<T>::iterator voxels<T>::getCode(unsigned long long mortonCode) {
	unsigned long long findThisOne = mortonCode;
	T temp_;
	temp_.morton = mortonCode;
	deque<T>::iterator temp = readOneCode(temp_);
	if (temp != voxel.end())
		return temp;
	else
		return readOneToUpdate(findThisOne);
}
template<class T>
inline voxels<T>::voxels(string address_, int levelL_, int levelH_, int size = 4096) {
	address = address_;
	levelL = levelL_;
	levelH = levelH_;
	size = size < 1 << (3 * levelL) ? size : 1 << (3 * levelL);
	for (int i = 0; i < size; i++) {
		voxel.push_back(readOneFromFile(i));
		cout << voxel[i] << endl;
	}
	cout << voxel.size();
}

template<class T>
inline voxels<T>::voxels(string address_, int levelL_, int levelH_, string sth, int size=4096)
{
	address = address_;
	levelL = levelL_;
	levelH = levelH_;
	size = size < 1 << (3 * levelL) ? size : 1 << (3 * levelL);
	int files = 1 << (3 * (levelH - levelL));
	for (int i = 0;i < files;i++) {		
		stringstream ss;
		ss << i;
		string fileNum;
		ss >> fileNum;
		string fileAddress = address + "\\outOfCore" + fileNum + ".bat";
		fstream newfiles;
		newfiles.open(fileAddress, ios::out | ios::binary);
		VoxelInfo temp;
		for (int j = 0;j < (1 << (levelL * 3));j++) {
			newfiles.write((char *)&temp, sizeof(VoxelInfo));
		}
		newfiles.close();
	}
	for (int i = 0; i < size; i++) {
		voxel.push_back(readOneFromFile(i));
		cout << voxel[i] << endl;
	}
	cout << voxel.size();
}


template<class T>
inline typename deque<T>::iterator voxels<T>::readOneCode(T needed) {
	deque<T>::iterator temp = voxel.begin();
	for (; temp != voxel.end();temp++) {
		if (*temp == needed) {
			return temp;
		}
	}
	return voxel.end();
}