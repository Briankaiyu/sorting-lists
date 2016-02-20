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
void insertionSort(struct county list[], int left, int right);
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
//	SORT DATA USING QUICKSORT
	clock_t begin = clock();
	quicksort(list,0,SIZE-1);
	clock_t end = clock()-begin;

	cout<<"Sorting procedure took " << end << " clicks to complete"<<endl;
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
	
	if(left+20<right)
	{
		struct county pivot=median3(list,left,right);
		
		struct county temp;
		//begin partitioning
		int i=left, j= right-1;
		for( ; ;)
		{
		
			while(list[++i].density < pivot.density){}
		
			while(pivot.density <list[--j].density){}
		
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
	else
	{
		insertionSort(list,left,right);
	}
}
struct county median3 (struct county list[], int left, int right)
{
	int center = (left+right)/2;
	struct county temp;
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

void insertionSort(struct county list[], int left, int right)
{
	
	for(int i=left; i<=right;i++)
	{
		struct county temp=list[i];
		
		int x;
		for(x=i; x>0 && temp.density<list[x-1].density; --x)
			list[x]= list[x-1];
		list[x]=temp;
	}
}
