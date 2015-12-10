#include "kdtree.h"
#include <iostream>

#define EXAMPLAR_NUM 6
#define EXAMPLAR_DIM 2

int main(int argc, char *argv[])
{
	KDTree::ExamplarSet exm_set;
	exm_set.create(EXAMPLAR_NUM, EXAMPLAR_DIM);
	exm_set.readData("data.txt");

	for(int i=0;i<EXAMPLAR_NUM;i++)
	{
		std::cout << '(' <<exm_set[i][0] << ','
			<< exm_set[i][1] << ')' <<std::endl;
	}

	KDTree::KDTree kdtree;
	kdtree.create(exm_set);
	std::cout<<"Input target point:"<<std::endl;
	KDTree::_Examplar exm(2);
	std::cin>> exm[0] >> exm[1];
	std::pair<KDTree::_Examplar, double> res = kdtree.findNearest(exm);

	std::cout << res.first[0] << ',' << res.first[1] << std::endl;
	std::cout << "distance is " << res.second << std::endl;

	std::vector<std::pair<KDTree::_Examplar, double>> res_result;
	int num = kdtree.findNearest(exm, 4, res_result);

	std::cout<<"range nearest:"<<std::endl;
	for(int i=0;i<num;i++)
	{
		std::cout << res_result[i].first[0] << ',' << res_result[i].first[1] << std::endl;
		std::cout << "distance is " << res_result[i].second << std::endl;
	}
	/*system("PAUSE");*/
	return 0;
}