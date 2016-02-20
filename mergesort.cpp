/****************
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

void mergesort(struct county list[], int first, int last);
void merge(struct county list[], int first, int mid, int last);
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
		//create stringstream from input
		istringstream ss(input);
		getline(ss,token,'|');//retrieve name
		temp.name=token;
		ss>>temp.area;//get area
		getline(ss,token,'|');//remove marker
		ss>>temp.population;//get population
		getline(ss,token,'|');//remove marker
		ss>>temp.density;		

		list[counter]=temp;//add to list and increment
		counter++;
	}
//	SORT DATA AND TIME SORTING PROCEDURE
	clock_t begin=clock();
	mergesort(list,0,SIZE-1);
	clock_t end=clock()-begin;

	cout<< "Sorting procedure took " <<end<< " clicks to complete"<<endl;
//	Save to file
	for(int i=0;i <SIZE;i++)
	{
		output<<list[i].name<<'|'<<list[i].area<<'|'<<list[i].population<<'|';
		output<<list[i].density<<endl;
	}
	output.close();
	return 0;
}
void mergesort(struct county list[], int first, int last)
{
	//if done sorting, done
	if(first==last)
	{
		return;//do nothing
	}
	else
	{
		//find mid, split, sort both halves
		int mid=(first+last)/2;
		mergesort(list,first,mid);
		mergesort(list,mid+1,last);
		merge(list, first, mid, last);
	}
}
void merge(struct county list[],int first, int mid, int last)
{
	int first_index=first;
	int last_index=mid+1;
	int total_index=first;
	struct county temp[74002];//hold merged result	

	//reassemble array together in sorted order
	while(first_index <= mid && last_index<=last)
	{
		if(list[first_index].density <= list[last_index].density)
		{
			temp[total_index++]=list[first_index++];		
		}
		else
		{
			temp[total_index++]=list[last_index++];
		}

	}
	
	//if leftovers, insert them back into the temp array
	if(first_index==mid+1)
	{
		while(last_index<=last)
		{
			temp[total_index++]=list[last_index++];
		}
	}
	else
	{		
		while(first_index<=mid)
		{
			temp[total_index++]=list[first_index++];
		}
	}
//transfer temp to actual array
	for(int i=first; i<=last;i++)
	{
		list[i]=temp[i];
	}
}
