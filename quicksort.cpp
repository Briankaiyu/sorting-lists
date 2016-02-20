/***************
Name: Brian Yu
Course: CSCE 3110
Assignment: Program 2
Due Date: 2/20/16
***************/
#include <iostream>
#include <fstream>
#include <sstream>
#include "header.h"//also includes string
#include <ctime>

#define SIZE 74000
//SORT BY DENSITY VALUE OF STRUCTURE
using namespace std;

void quicksort(struct county list[], int left, int right);
struct county median3(struct county list[], int left,  int right);
int main()
{
	ofstream output;
	string input;
	string token;
	struct county list[SIZE];
	struct county temp;

	int counter=0;
//PARSE DATA AND FILL ARRAY
	output.open("pop_density_sorted.txt");
	while(getline(cin,input))
	{
		//create string stream
		istringstream ss(input);
		getline(ss,token,'|');//retrieve name
		temp.name=token;
		ss>>temp.area;//get value
		getline(ss,token,'|');//remove marker
		ss>>temp.population;
		getline(ss,token,'|');
		ss>>temp.density;		

		list[counter]=temp;
		counter++;
	}
//	SORT DATA USING QUICKSORT AND TIME CLICKS
	clock_t begin=clock();
	quicksort(list,0,SIZE-1);
	clock_t end = clock()-begin;

	cout<<"Sorting procedure took "<<end<< " clicks to complete"<<endl;
	//copy array into file
	for(int i=0;i <SIZE;i++)
	{
		output<<list[i].name<<'|'<<list[i].area<<'|'<<list[i].population<<'|';
		output<<list[i].density<<endl;
	}
	output.close();
	return 0;
}
void quicksort(struct county list[], int left, int right)
{
	//this is just regular quicksort
	//normally would have an if(left + 20 <=right) to lead into insertion Sort
	if(left<right)
	{
		//set pivot by median of 3
		struct county pivot=median3(list,left,right);
		
		struct county temp;
		//begin partitioning
		int i=left, j= right-1;
		for( ; ;)
		{
		
			//increment counters
			while(list[++i].density < pivot.density){}
		
			while(pivot.density <list[--j].density){}
		
			//sort until not needed then break
			if(i<j)
			{
				temp=list[i];
				list[i]=list[j];
				list[j]=temp;
			}
			else
				break;
		}
		//restore pivot
		temp=list[i];
		list[i]=list[right-1];
		list[right-1]=temp;
	
		quicksort(list,left,i-1);
		quicksort(list,i+1,right);
	}
}
//sort and then pick median
struct county median3 (struct county list[], int left, int right)
{
	//determine center and set up temp
	int center = (left+right)/2;
	struct county temp;

	//place first middle last in appropriate sorted spots
	if(list[center].density<list[left].density)
	{	
		temp=list[center];
		list[center]=list[left];
		list[left]=temp;
	}
	if(list[right].density<list[left].density)
	{
		temp=list[right];
		list[right]=list[left];	
		list[left]=temp;
	}
	if(list[right].density<list[center].density)
	{
		temp=list[right];
		list[right]=list[center];
		list[center]=temp;
	}
	//place pivot at right -1

	temp=list[center];
	list[center]=list[right-1];
	list[right-1]=list[center];
	
	return list[right-1];
}
