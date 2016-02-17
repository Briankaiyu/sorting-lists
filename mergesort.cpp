#include <iostream>
#include <fstream>
#include <sstream>
#include "header.h"//also includes string

using namespace std;
int main()
{
	ifstream data;
	string input;
	string token;
	//declare array to fill
	struct county list[76000];
	struct county temp;

	data.open("pop_density.txt");
	//fill array
	while(getline(data,input))
	{
		istringstream ss(input);
		getline(ss,token,'|');//retrieve name
		temp.name=token;

		ss>>temp.area;
		getline(ss,token,'|');
			
		ss>>temp.population;
		getline(ss,token,'|');
		
		ss>>temp.density;		
		

	}

	data.close();


	return 0;
}
