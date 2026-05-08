#include <iostream>
#include <math.h>
int e[9][3] = {{60,0,0},{0,20,0},{-20,0,0},{0,20,0},{-20,0,0},{0,-20,0},{-20,0,0},{0,-20,0},{60,0,0}};
bool icbukey_check = 0;
int vector_m[8][3];
int main ()
{
	for(int i =0;i<8;i++)
	{
		vector_m[i][0] = e[i][1]*e[i+1][2] - e[i][2]*e[i+1][1];
		vector_m[i][1] = e[i][2]*e[i+1][0] - e[i][0]*e[i+1][2];
		vector_m[i][2] = e[i][0]*e[i+1][1] - e[i][1]*e[i+1][0];
	}
	for(int i =0;i<8;i++)
	{
		std::cout << "---d" << i << " \n";
		std::cout << vector_m[i][0] << " \n";
		std::cout << vector_m[i][1] << "\n";
		if (vector_m[i][2] > 0) icbukey_check =1; std::cout << vector_m[i][2] << " | <180 \n \n";
		if (vector_m[i][2] <= 0) std::cout << vector_m[i][2] << " | >180 \n \n";
	}
	if(icbukey_check)	std::cout << "ic bukey" << " \n";
	 else std::cout << "dis bukey" << " \n";
}


	

