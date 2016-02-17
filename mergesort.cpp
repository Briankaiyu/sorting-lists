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

	int counter=0;
//PARSE DATA AND FILL ARRAY
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
		list[counter]=temp;
		counter++;

	}
/*	print array for proof of fill
	for(int i=0; i<76000;i++)
	{
		cout<<list[i].name<<endl;
	}
	data.close();
*/

//	SORT DATA USING MERGESORT

	return 0;
}
