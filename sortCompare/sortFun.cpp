#include "sortFun.h"
#include <vector>
#include <cstdlib>
#include <iostream>
using namespace std;

void bubbleSortTest(vector<int> &arr, int &cmpTimes, int &mvTimes)
{
	cmpTimes = mvTimes = 0;
	for(int i = arr.size() - 2;i >= 0;i--)
	{
		for(int j = i;j < arr.size() - 1;j++)
		{
			cmpTimes++;
			if (arr[j] > arr[j + 1])
			{
				mvTimes++;
				swap(arr[j], arr[j + 1]);
			}
			else
				break;
		}
	}
}


void insertSortTest(vector<int> &arr, int &cmpTimes, int &mvTimes)
{
	cmpTimes = mvTimes = 0;
	for(int i = 1;i < arr.size();i++)
	{
		int pos = i;
		for(int j = 0;j < i;j++)
		{
			cmpTimes++;
			if (arr[j] >= arr[i])
			{
				pos = j;
				break;
			}
		}

		int insertVal = arr[i];
		for(int j = i - 1;j >= pos;j--)
		{
			mvTimes++;
			arr[j + 1] = arr[j];
		}
		mvTimes++;
		arr[pos] = insertVal;
	}
}

void selectSortTest(vector<int> &arr, int &cmpTimes, int &mvTimes)
{
	cmpTimes = mvTimes = 0;
	for(int i = 0;i < arr.size();i++)
	{
		int minVal = arr[i];
		int minPos = i;
		for(int j = i + 1;j < arr.size();j++) 
		{
			cmpTimes++;
			if (minVal > arr[j])
			{
				minVal = arr[j];
				minPos = j;
			}
		}
		mvTimes++;
		swap(arr[minPos], arr[i]);
	}
}

void quickSort(int *arr, int n, int &cmpTimes, int &mvTimes)
{
	if (n < 2)
		return;

	int startPos = 1, endPos = n - 1;
	int keyVal = arr[0];
	while(1)
	{
		while(startPos < n && arr[startPos] <= keyVal)
		{
			cmpTimes++;
			startPos++;
		}
		while(endPos > 0 && arr[endPos] >= keyVal)
		{
			cmpTimes++;
			endPos--;
		}
		if (startPos < endPos)
		{
			swap(arr[startPos], arr[endPos]);
			startPos++, endPos--;
			mvTimes++;
		}
		else
			break;
	}
	mvTimes++;
	swap(arr[endPos], arr[0]);

	quickSort(arr, endPos, cmpTimes, mvTimes);
	quickSort(arr + endPos + 1, n - endPos - 1, cmpTimes, mvTimes);
}


void quickSortTest(vector<int> &arr, int &cmpTimes,int &mvTimes)
{
	int *newArr = (int *)malloc(arr.size() * sizeof(int));
	for(int i = 0;i < arr.size();i++)
		newArr[i] = arr[i];
	cmpTimes = mvTimes = 0;
	quickSort(newArr, arr.size(), cmpTimes, mvTimes);
	
	for(int i = 0;i < arr.size();i++)
		arr[i] = newArr[i];
}


void shellSortTest(vector<int> &arr, int &cmpTimes, int &mvTimes)
{
	int step = arr.size() - 1;
	cmpTimes = mvTimes = 0;

	while(step)
	{
		for(int i = 0;i < step;i++)
			for(int pos = i + step;pos < arr.size();pos += step)
				for(int j = pos;j >= step;j -= step)
				{
					cmpTimes++;
					if (arr[j] < arr[j - step])
					{
						mvTimes++;
						swap(arr[j], arr[j - step]);
					}
					else
						break;
				}
		step /= 2;
	}
}



void shiftDown(vector<int> &arr, int index, int &cmpTimes, int &mvTimes)
{
	int pos = index;

	while(pos < arr.size())
	{
		cmpTimes += 2, mvTimes++;
		int minVal = arr[pos], minIndex = pos;

		if (pos * 2 + 1 < arr.size() && arr[pos * 2 + 1] < arr[pos])
		{
			minIndex = pos * 2 + 1;
			minVal = arr[pos * 2 + 1];
		}
		if (pos * 2 + 2 < arr.size() && arr[pos * 2 + 2] < minVal)
		{
			minIndex = pos * 2 + 2;
			minVal = arr[pos * 2 + 2];
		}

		swap(arr[pos], arr[minIndex]);
		if (pos == minIndex)
			break;
		else
			pos = minIndex;
	}
}


void heapSortTest(vector<int> &arr, int &cmpTimes, int &mvTimes)
{
	cmpTimes = mvTimes = 0;
	for(int i = arr.size() / 2 - 1;i >= 0;i--)
		shiftDown(arr, i, cmpTimes, mvTimes);

	vector<int> tempArr(arr.size());
	for(int i = 0;i < tempArr.size();i++)
	{
		tempArr[i] = arr[0];
		mvTimes++;
		swap(arr[0], arr[arr.size() - 1]);
		arr.pop_back();
		shiftDown(arr, 0, cmpTimes, mvTimes);
	}
	arr = tempArr;
}

