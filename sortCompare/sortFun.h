#ifndef _SORTFUN_H_
#define _SORTFUN_H_

#include <vector>
using namespace std;

void bubbleSortTest(vector<int> &arr, int &cmpTimes, int &mvTimes);
void insertSortTest(vector<int> &arr, int &cmpTimes, int &mvTimes);
void selectSortTest(vector<int> &arr, int &cmpTimes, int &mvTimes);
void quickSortTest(vector<int> &arr, int &cmpTimes, int &mvTimes);
void shellSortTest(vector<int> &arr, int &cmpTimes, int &mvTimes);
void heapSortTest(vector<int> &arr, int &cmpTimes, int &mvTimes);

#endif
