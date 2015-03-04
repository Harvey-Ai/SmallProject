#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>
#include "sortFun.h"
using namespace std;

const int testTime = 10;
const int arrSize = 1000;

int main()
{
	srand(time(NULL));
	typedef void (*funPtrType)(vector<int> & a, int &b, int &c);

	int funCnt;
	vector<funPtrType> funs;
	vector<string> funName;
	funs.push_back(bubbleSortTest);
	funName.push_back("bubble sort");
	funs.push_back(insertSortTest);
	funName.push_back("insert sort");
	funs.push_back(selectSortTest);
	funName.push_back("select sort");
	funs.push_back(quickSortTest);
	funName.push_back("quick sort");
	funs.push_back(shellSortTest);
	funName.push_back("shell sort");
	funs.push_back(heapSortTest);
	funName.push_back("heap sort");
	
	funCnt = funs.size();
	vector<int> totalCmp(funCnt, 0);
	vector<int> totalMv(funCnt, 0);

	for(int i = 0;i < testTime;i++)
	{
		int cmpTimes = 0, mvTimes = 0;
		vector<int> arr, tempArr;

		for(int j = 0;j < arrSize;j++)
		{
			int val = rand();
			arr.push_back(val);
			tempArr.push_back(val);
		}

		for(int i = 0;i < funs.size();i++)
		{
			tempArr = arr;
			cmpTimes = mvTimes = 0;
			funs[i](tempArr, cmpTimes, mvTimes);
			
			for(int j = 0;j < tempArr.size() - 1;j++)
				if (tempArr[j] > tempArr[j + 1])
					cout << "find sort function bug!" << endl;
			totalCmp[i] += cmpTimes, totalMv[i] += mvTimes;
		}
	}

	cout << "Statistic:" << endl;
	for(int i = 0;i < funCnt;i++)
		cout << funName[i] << ": " << "compare time: " << totalCmp[i] << ", " <<  "move time: " << totalMv[i] << endl;

	return 0;
}


