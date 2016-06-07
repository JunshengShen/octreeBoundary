#include "overlap.h"
#include <vector>
using namespace std;
bool overlap(coor tri1, coor tri2, coor tri3, float voxel_xn, float voxel_xp, float voxel_yn, float voxel_yp, float voxel_zn, float voxel_zp)
{
	if (tri1.x < voxel_xn&&tri2.x < voxel_xn&&tri3.x < voxel_xn)
		return false;
	if (tri1.x > voxel_xp&&tri2.x > voxel_xp&&tri3.x > voxel_xp)
		return false;
	if (tri1.y < voxel_yn&&tri2.y < voxel_yn&&tri3.y < voxel_yn)
		return false;
	if (tri1.y > voxel_yp&&tri2.y > voxel_yp&&tri3.y > voxel_yp)
		return false;
	if (tri1.z < voxel_zn&&tri2.z < voxel_zn&&tri3.z < voxel_zn)
		return false;
	if (tri1.z > voxel_zp&&tri2.z > voxel_zp&&tri3.z > voxel_zp)
		return false;
	vector<coor> polygon;
	polygon.push_back(tri1);
	polygon.push_back(tri2);
	polygon.push_back(tri3);
	vector <int> point_to_cut;
	vector <int> replace_location;
	vector <coor> replace;
	for (int i = 0; i < polygon.size(); i++)
	{
		//cout << "2";
		if (polygon[i].x >= voxel_xn)//�ж������Ҫ���г����Ǳ���  ������continue  
			continue;
		/*int compare = 0;
		for (int i = 0; i < polygon.size(); i++)
		{
		if (polygon[i].x < voxel_xn)
		compare++;
		}
		if (compare == polygon.size())
		return false;//ȫ������ĸ�����  �ж�Ϊfalse*/

		int location_temp[2];//�����������ڵ�  �ж����ڵ���û�н���  û�н����continue
		if (i == 0)
		{
			location_temp[0] = polygon.size() - 1;
			location_temp[1] = 1;
			if (polygon[location_temp[0]].x < voxel_xn&&polygon[location_temp[1]].x < voxel_xn)
			{
				point_to_cut.push_back(i);
				continue;
			}
		}
		else if (i == polygon.size() - 1)
		{
			location_temp[0] = polygon.size() - 2;
			location_temp[1] = 0;
			if (polygon[location_temp[0]].x < voxel_xn&&polygon[location_temp[1]].x < voxel_xn)
			{
				point_to_cut.push_back(i);
				continue;
			}
		}
		else
		{
			location_temp[0] = i - 1;
			location_temp[1] = i + 1;
			if (polygon[location_temp[0]].x < voxel_xn&&polygon[location_temp[1]].x < voxel_xn)
			{
				point_to_cut.push_back(i);
				continue;
			}
		}//������һ������ ���㽻��  �滻
		if (polygon[i].x == voxel_xn)
			continue;
		//count the intersect coordinate
		if ((polygon[location_temp[0]].x<voxel_xn&&polygon[location_temp[1]].x>voxel_xn) || (polygon[location_temp[1]].x> voxel_xn&&polygon[location_temp[0]].x == voxel_xn))//���һ���н���
		{
			coor replace_temp;
			replace_temp.x = voxel_xn;
			replace_temp.y = polygon[i].y + (voxel_xn - polygon[i].x)
				*(polygon[location_temp[1]].y - polygon[i].y) / (polygon[location_temp[1]].x - polygon[i].x);
			replace_temp.z = polygon[i].z + (voxel_xn - polygon[i].x)
				*(polygon[location_temp[1]].z - polygon[i].z) / (polygon[location_temp[1]].x - polygon[i].x);
			replace.push_back(replace_temp);
			replace_location.push_back(i);
		}
		else if ((polygon[location_temp[0]].x>voxel_xn&&polygon[location_temp[1]].x < voxel_xn) || (polygon[location_temp[0]].x> voxel_xn&&polygon[location_temp[1]].x == voxel_xn))//��ǰһ���н���
		{
			coor replace_temp;
			replace_temp.x = voxel_xn;
			replace_temp.y = polygon[i].y + (voxel_xn - polygon[i].x)
				*(polygon[location_temp[0]].y - polygon[i].y) / (polygon[location_temp[0]].x - polygon[i].x);
			replace_temp.z = polygon[i].z + (voxel_xn - polygon[i].x)
				*(polygon[location_temp[0]].z - polygon[i].z) / (polygon[location_temp[0]].x - polygon[i].x);
			replace.push_back(replace_temp);
			replace_location.push_back(i);
		}
		else//���н���
		{
			coor temp[2];
			//polygon.insert(polygon.begin() + i, temp);

			temp[0].x = voxel_xn;
			temp[0].y = polygon[i].y + (voxel_xn - polygon[i].x)
				*(polygon[location_temp[0]].y - polygon[i].y) / (polygon[location_temp[0]].x - polygon[i].x);
			temp[0].z = polygon[i].z + (voxel_xn - polygon[i].x)
				*(polygon[location_temp[0]].z - polygon[i].z) / (polygon[location_temp[0]].x - polygon[i].x);

			temp[1].x = voxel_xn;
			temp[1].y = polygon[i].y + (voxel_xn - polygon[i].x)
				*(polygon[location_temp[1]].y - polygon[i].y) / (polygon[location_temp[1]].x - polygon[i].x);
			temp[1].z = polygon[i].z + (voxel_xn - polygon[i].x)
				*(polygon[location_temp[1]].z - polygon[i].z) / (polygon[location_temp[1]].x - polygon[i].x);
			polygon[i] = temp[0];
			polygon.insert(polygon.begin() + i + 1, temp[1]);

			//cout << endl;
			for (int i = 0; i < polygon.size(); i++)
			{
				//cout << polygon[i].x << ' ' << polygon[i].y << ' ' << polygon[i].z << endl;
			}
			break;//��������Ѿ����ü����ж���
		}
	}
	//���е��е�  �滻�Ļ���
	if (replace.size() != 0)
	{
		for (int i = 0; i < replace.size(); i++)
		{
			polygon[replace_location[i]] = replace[i];
		}
		replace_location.clear();
		replace.clear();
	}
	for (int i = point_to_cut.size() - 1; i >= 0; i--)
	{
		polygon.erase(polygon.begin() + point_to_cut[i]);
	}
	point_to_cut.clear();


	//cout << endl;
	/*for (int i = 0; i < polygon.size(); i++)
	{
	//cout << polygon[i].x << ' ' << polygon[i].y << ' ' << polygon[i].z << endl;
	}*/


	//cout << '1';





	for (int i = 0; i < polygon.size(); i++)
	{
		//cout << endl << "3";
		if (polygon[i].x <= voxel_xp)//�ж������Ҫ���г����Ǳ���  ������continue  
			continue;
		/*int compare = 0;
		for (int i = 0; i < polygon.size(); i++)
		{
		if (polygon[i].x < voxel_xp)
		compare++;
		}
		if (compare == polygon.size())
		return false;//ȫ������ĸ�����  �ж�Ϊfalse*/

		int location_temp[2];//�����������ڵ�  �ж����ڵ���û�н���  û�н����continue
		if (i == 0)
		{
			location_temp[0] = polygon.size() - 1;
			location_temp[1] = 1;
			if (polygon[location_temp[0]].x > voxel_xp&&polygon[location_temp[1]].x > voxel_xp)
			{
				point_to_cut.push_back(i);
				continue;
			}
		}
		else if (i == polygon.size() - 1)
		{
			location_temp[0] = polygon.size() - 2;
			location_temp[1] = 0;
			if (polygon[location_temp[0]].x > voxel_xp&&polygon[location_temp[1]].x > voxel_xp)
			{
				point_to_cut.push_back(i);
				continue;
			}
		}
		else
		{
			location_temp[0] = i - 1;
			location_temp[1] = i + 1;
			if (polygon[location_temp[0]].x > voxel_xp&&polygon[location_temp[1]].x > voxel_xp)
			{
				point_to_cut.push_back(i);
				continue;
			}
		}//������һ������ ���㽻��  �滻
		if (polygon[i].x == voxel_xp)
		{
			continue;
		}
		//count the intersect coordinate
		if ((polygon[location_temp[0]].x> voxel_xp&&polygon[location_temp[1]].x<voxel_xp) || (polygon[location_temp[1]].x< voxel_xp&&polygon[location_temp[0]].x == voxel_xp))//���һ���н���
		{
			coor replace_temp;
			replace_temp.x = voxel_xp;
			replace_temp.y = polygon[i].y + (voxel_xp - polygon[i].x)
				*(polygon[location_temp[1]].y - polygon[i].y) / (polygon[location_temp[1]].x - polygon[i].x);
			replace_temp.z = polygon[i].z + (voxel_xp - polygon[i].x)
				*(polygon[location_temp[1]].z - polygon[i].z) / (polygon[location_temp[1]].x - polygon[i].x);
			replace.push_back(replace_temp);
			replace_location.push_back(i);
		}
		else if (polygon[location_temp[0]].x<voxel_xp&&polygon[location_temp[1]].x > voxel_xp || (polygon[location_temp[0]].x< voxel_xp&&polygon[location_temp[1]].x == voxel_xp))//��ǰһ���н���
		{
			coor replace_temp;
			replace_temp.x = voxel_xp;
			replace_temp.y = polygon[i].y + (voxel_xp - polygon[i].x)
				*(polygon[location_temp[0]].y - polygon[i].y) / (polygon[location_temp[0]].x - polygon[i].x);
			replace_temp.z = polygon[i].z + (voxel_xp - polygon[i].x)
				*(polygon[location_temp[0]].z - polygon[i].z) / (polygon[location_temp[0]].x - polygon[i].x);
			replace.push_back(replace_temp);
			replace_location.push_back(i);
		}
		else//���н���
		{
			coor temp[2];
			//polygon.insert(polygon.begin() + i, temp);

			temp[0].x = voxel_xp;
			temp[0].y = polygon[i].y + (voxel_xp - polygon[i].x)
				*(polygon[location_temp[0]].y - polygon[i].y) / (polygon[location_temp[0]].x - polygon[i].x);
			temp[0].z = polygon[i].z + (voxel_xp - polygon[i].x)
				*(polygon[location_temp[0]].z - polygon[i].z) / (polygon[location_temp[0]].x - polygon[i].x);

			temp[1].x = voxel_xp;
			temp[1].y = polygon[i].y + (voxel_xp - polygon[i].x)
				*(polygon[location_temp[1]].y - polygon[i].y) / (polygon[location_temp[1]].x - polygon[i].x);
			temp[1].z = polygon[i].z + (voxel_xp - polygon[i].x)
				*(polygon[location_temp[1]].z - polygon[i].z) / (polygon[location_temp[1]].x - polygon[i].x);
			polygon[i] = temp[0];
			polygon.insert(polygon.begin() + i + 1, temp[1]);



			break;//��������Ѿ����ü����ж���
		}
	}

	//���е��е�  �滻�Ļ���
	if (replace.size() != 0)
	{
		for (int i = 0; i < replace.size(); i++)
		{
			polygon[replace_location[i]] = replace[i];
		}
		replace_location.clear();
		replace.clear();
	}
	for (int i = point_to_cut.size() - 1; i >= 0; i--)
	{
		polygon.erase(polygon.begin() + point_to_cut[i]);
	}
	point_to_cut.clear();




	//cout << a;

	//cout << endl;
	/*for (int i = 0; i < polygon.size(); i++)
	{
	//cout << polygon[i].x << ' ' << polygon[i].y << ' ' << polygon[i].z << endl;
	}*/






	//cout << '2';






	int compare = 0;
	for (int i = 0; i < polygon.size(); i++)
	{
		if (polygon[i].y > voxel_yp)
			compare++;
	}
	if (compare == polygon.size())
		return false;
	compare = 0;
	for (int i = 0; i < polygon.size(); i++)
	{
		if (polygon[i].y < voxel_yn)
			compare++;
	}
	if (compare == polygon.size())
		return false;



	for (int i = 0; i < polygon.size(); i++)
	{
		//cout << endl << "4";
		if (polygon[i].y <= voxel_yp)//�ж������Ҫ���г����Ǳ���  ������continue  
			continue;
		/*int compare = 0;
		for (int i = 0; i < polygon.size(); i++)
		{
		if (polygon[i].x < voxel_xp)
		compare++;
		}
		if (compare == polygon.size())
		return false;//ȫ������ĸ�����  �ж�Ϊfalse*/

		int location_temp[2];//�����������ڵ�  �ж����ڵ���û�н���  û�н����continue
		if (i == 0)
		{
			location_temp[0] = polygon.size() - 1;
			location_temp[1] = 1;
			if (polygon[location_temp[0]].y > voxel_yp&&polygon[location_temp[1]].y > voxel_yp)
			{
				point_to_cut.push_back(i);
				continue;
			}
		}
		else if (i == polygon.size() - 1)
		{
			location_temp[0] = polygon.size() - 2;
			location_temp[1] = 0;
			if (polygon[location_temp[0]].y > voxel_yp&&polygon[location_temp[1]].y > voxel_yp)
			{
				point_to_cut.push_back(i);
				continue;
			}
		}
		else
		{
			location_temp[0] = i - 1;
			location_temp[1] = i + 1;
			if (polygon[location_temp[0]].y > voxel_yp&&polygon[location_temp[1]].y > voxel_yp)
			{
				point_to_cut.push_back(i);
				continue;
			}
		}//������һ������ ���㽻��  �滻
		 //count the intersect coordinate
		if ((polygon[location_temp[0]].y> voxel_yp&&polygon[location_temp[1]].y<voxel_yp) || (polygon[location_temp[1]].y<voxel_yp&&polygon[location_temp[0]].y == voxel_yp))//���һ���н���
		{
			coor replace_temp;
			replace_temp.x = polygon[i].x + (voxel_yp - polygon[i].y)
				*(polygon[location_temp[1]].x - polygon[i].x) / (polygon[location_temp[1]].y - polygon[i].y);
			replace_temp.y = voxel_yp;
			replace_temp.z = polygon[i].z + (voxel_yp - polygon[i].y)
				*(polygon[location_temp[1]].z - polygon[i].z) / (polygon[location_temp[1]].y - polygon[i].y);
			replace.push_back(replace_temp);
			replace_location.push_back(i);
		}
		else if (polygon[location_temp[0]].y<voxel_yp&&polygon[location_temp[1]].y > voxel_yp || (polygon[location_temp[0]].y<voxel_yp&&polygon[location_temp[1]].y == voxel_yp))//��ǰһ���н���
		{
			coor replace_temp;
			replace_temp.x = polygon[i].x + (voxel_yp - polygon[i].y)
				*(polygon[location_temp[0]].x - polygon[i].x) / (polygon[location_temp[0]].y - polygon[i].y);
			replace_temp.y = voxel_yp;
			replace_temp.z = polygon[i].z + (voxel_yp - polygon[i].y)
				*(polygon[location_temp[0]].z - polygon[i].z) / (polygon[location_temp[0]].y - polygon[i].y);
			replace.push_back(replace_temp);
			replace_location.push_back(i);
		}
		else//���н���
		{
			coor temp[2];
			//polygon.insert(polygon.begin() + i, temp);

			temp[0].x = polygon[i].x + (voxel_yp - polygon[i].y)
				*(polygon[location_temp[0]].x - polygon[i].x) / (polygon[location_temp[0]].y - polygon[i].y);
			temp[0].y = voxel_yp;
			temp[0].z = polygon[i].z + (voxel_yp - polygon[i].y)
				*(polygon[location_temp[0]].z - polygon[i].z) / (polygon[location_temp[0]].y - polygon[i].y);

			temp[1].x = polygon[i].x + (voxel_yp - polygon[i].y)
				*(polygon[location_temp[1]].x - polygon[i].x) / (polygon[location_temp[1]].y - polygon[i].y);
			temp[1].y = voxel_yp;
			temp[1].z = polygon[i].z + (voxel_yp - polygon[i].y)
				*(polygon[location_temp[1]].z - polygon[i].z) / (polygon[location_temp[1]].y - polygon[i].y);
			polygon[i] = temp[0];
			polygon.insert(polygon.begin() + i + 1, temp[1]);



			break;//��������Ѿ����ü����ж���
		}
	}
	//cout << "456";
	//���е��е�  �滻�Ļ���

	if (replace.size() != 0)
	{
		for (int i = 0; i < replace.size(); i++)
		{
			polygon[replace_location[i]] = replace[i];
		}
		replace_location.clear();
		replace.clear();
	}
	//cout << " "<<point_to_cut.size();
	//cout << polygon.size();
	//cout << endl << point_to_cut[0] << " " << point_to_cut[1];
	if (point_to_cut.size() != 0)
	{
		for (int i = point_to_cut.size() - 1; i >= 0; i--)
		{

			polygon.erase(polygon.begin() + point_to_cut[i]);
			//cout << polygon.size();
		}
		point_to_cut.clear();
	}

	//cout << "3";



	/*for (int i = 0; i < polygon.size(); i++)
	{
	//cout << polygon[i].x << ' ' << polygon[i].y << ' ' << polygon[i].z << endl;
	}*/






	//cout << '3';




	//cout << "123";

	for (int i = 0; i < polygon.size(); i++)
	{
		//cout << endl << "55";
		if (polygon[i].y >= voxel_yn)//�ж������Ҫ���г����Ǳ���  ������continue  
			continue;
		/*int compare = 0;
		for (int i = 0; i < polygon.size(); i++)
		{
		if (polygon[i].x < voxel_xp)
		compare++;
		}
		if (compare == polygon.size())
		return false;//ȫ������ĸ�����  �ж�Ϊfalse*/
		int location_temp[2];//�����������ڵ�  �ж����ڵ���û�н���  û�н����continue
		if (i == 0)
		{
			location_temp[0] = polygon.size() - 1;
			location_temp[1] = 1;
			if (polygon[location_temp[0]].y < voxel_yn&&polygon[location_temp[1]].y < voxel_yn)
			{
				point_to_cut.push_back(i);
				continue;
			}
		}
		else if (i == polygon.size() - 1)
		{
			location_temp[0] = polygon.size() - 2;
			location_temp[1] = 0;
			if (polygon[location_temp[0]].y < voxel_yp&&polygon[location_temp[1]].y < voxel_yn)
			{
				point_to_cut.push_back(i);
				continue;
			}
		}
		else
		{
			location_temp[0] = i - 1;
			location_temp[1] = i + 1;
			if (polygon[location_temp[0]].y < voxel_yn&&polygon[location_temp[1]].y < voxel_yn)
			{
				point_to_cut.push_back(i);
				continue;
			}
		}//������һ������ ���㽻��  �滻
		 //count the intersect coordinate
		if ((polygon[location_temp[0]].y< voxel_yn&&polygon[location_temp[1]].y>voxel_yn) || (polygon[location_temp[1]].y>voxel_yn&&polygon[location_temp[0]].y == voxel_yn))//���һ���н���
		{
			coor replace_temp;
			replace_temp.x = polygon[i].x + (voxel_yn - polygon[i].y)
				*(polygon[location_temp[1]].x - polygon[i].x) / (polygon[location_temp[1]].y - polygon[i].y);
			replace_temp.y = voxel_yn;
			replace_temp.z = polygon[i].z + (voxel_yn - polygon[i].y)
				*(polygon[location_temp[1]].z - polygon[i].z) / (polygon[location_temp[1]].y - polygon[i].y);
			replace.push_back(replace_temp);
			replace_location.push_back(i);
		}
		else if ((polygon[location_temp[0]].y>voxel_yn&&polygon[location_temp[1]].y < voxel_yn) || (polygon[location_temp[0]].y>voxel_yn&&polygon[location_temp[1]].y == voxel_yn))//��ǰһ���н���
		{
			coor replace_temp;
			replace_temp.x = polygon[i].x + (voxel_yn - polygon[i].y)
				*(polygon[location_temp[0]].x - polygon[i].x) / (polygon[location_temp[0]].y - polygon[i].y);
			replace_temp.y = voxel_yn;
			replace_temp.z = polygon[i].z + (voxel_yn - polygon[i].y)
				*(polygon[location_temp[0]].z - polygon[i].z) / (polygon[location_temp[0]].y - polygon[i].y);
			replace.push_back(replace_temp);
			replace_location.push_back(i);
		}
		/*else if (polygon[location_temp[0]].y == voxel_yn&&polygon[location_temp[1]].y == voxel_yn)
		{
		continue;//
		}*/
		else//���н���
		{
			coor temp[2];
			//polygon.insert(polygon.begin() + i, temp);

			temp[0].x = polygon[i].x + (voxel_yn - polygon[i].y)
				*(polygon[location_temp[0]].x - polygon[i].x) / (polygon[location_temp[0]].y - polygon[i].y);
			temp[0].y = voxel_yn;
			temp[0].z = polygon[i].z + (voxel_yn - polygon[i].y)
				*(polygon[location_temp[0]].z - polygon[i].z) / (polygon[location_temp[0]].y - polygon[i].y);

			temp[1].x = polygon[i].x + (voxel_yn - polygon[i].y)
				*(polygon[location_temp[1]].x - polygon[i].x) / (polygon[location_temp[1]].y - polygon[i].y);
			temp[1].y = voxel_yn;
			temp[1].z = polygon[i].z + (voxel_yn - polygon[i].y)
				*(polygon[location_temp[1]].z - polygon[i].z) / (polygon[location_temp[1]].y - polygon[i].y);
			polygon[i] = temp[0];
			polygon.insert(polygon.begin() + i + 1, temp[1]);



			break;//��������Ѿ����ü����ж���
		}
	}
	//cout << '5';
	//���е��е�  �滻�Ļ���
	//cout << "789";
	//cout << endl;
	//cout << replace.size() << endl;
	//cout << polygon.size();
	//cout << replace_location.size();
	if (replace.size() != 0)
	{
		for (int i = 0; i <replace.size(); i++)
		{
			polygon[replace_location[i]] = replace[i];
		}
		replace_location.clear();
		replace.clear();
	}
	//cout << '6';
	if (point_to_cut.size() != 0)
	{
		for (int i = point_to_cut.size() - 1; i >= 0; i--)
		{
			polygon.erase(polygon.begin() + point_to_cut[i]);
		}
		point_to_cut.clear();
	}




	//cout << '4';
	//cout << "10";

	compare = 0;
	for (int i = 0; i < polygon.size(); i++)
	{
		if (polygon[i].z > voxel_zp)
			compare++;
	}
	if (compare == polygon.size())
		return false;
	compare = 0;
	for (int i = 0; i < polygon.size(); i++)
	{
		if (polygon[i].z < voxel_zn)
			compare++;
	}
	if (compare == polygon.size())
		return false;
	//cout << endl;
	/*for (int i = 0; i < polygon.size(); i++)
	{
	//cout << polygon[i].x << ' ' << polygon[i].y << ' ' << polygon[i].z << endl;
	}*/
	return true;
}