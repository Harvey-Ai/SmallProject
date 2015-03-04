/*
 * randGen.cpp
 *
 *  Created on: Aug 24, 2014
 *      Author: ufo008ahw
 */

#include "randGen.h"
#include <fstream>
#include <cstdio>
#include <string>
#include <cctype>
#include <algorithm>
#include <iostream>
#include <cassert>
using namespace std;

bool randGen::operator()(int a, int b)
{
	if (inputStr[suffixArr[a]] < inputStr[suffixArr[b]])
		return 1;
	else
		return 0;
}

int randGen::sortSuffxArr()
{
	sort(suffixArr.begin(), suffixArr.end(), *this);
}

int randGen::findNext(string curStr)
{
	int low = 0, high = suffixArr.size() - 1;
	while(high > low)
	{
		int mid = (low + high) / 2;

		if (inputStr[suffixArr[mid]] == curStr)
			high = mid;
		else if (inputStr[suffixArr[mid]] < curStr)
			low = mid + 1;
		else
			high = mid - 1;
	}

	assert(inputStr[suffixArr[low]] == curStr);
	int pos = low;
	int nextPos = -1;

	for(int i = pos, k = 0;i < suffixArr.size();i++, k++)
	{
		if (inputStr[suffixArr[i]] != inputStr[suffixArr[pos]])
			break;

		// random choose, but don't choose the last suffix ""
		if (suffixArr[i] == inputStr.size() - 1)
		{
			k--;
			continue;
		}
		if (random() % (k + 1) == 0)
			nextPos = i;
	}
	assert(nextPos != -1);

	return nextPos;
}

randGen::randGen(string fileName)
{
	readFile(fileName);
}

randGen::~randGen()
{
}

int randGen::readFile(string fileNames)
{
	ifstream inputIOS;
	inputIOS.open(fileNames.c_str(), ios::in);

	string oneStr;
	// add a prefix line
	inputStr.push_back("");
	suffixArr.push_back(inputStr.size() - 1);

	while(getline(inputIOS, oneStr))
	{
		// convert to lower case
		for(int i = 0;i < oneStr.size();i++)
			if (oneStr[i] >= 'A' && oneStr[i] <= 'Z')
				oneStr[i] = oneStr[i] - 'A' + 'a';

		// split regular chars and special chars
		int pos = 0;
		while(pos < oneStr.size())
		{
			while(pos < oneStr.size() && oneStr[pos] == ' ')
				pos++;

			int end = pos;
			for(;end < oneStr.size() && isalnum(oneStr[end]);end++);
			if (end == pos)
				end++;
			inputStr.push_back(oneStr.substr(pos, end - pos));
			suffixArr.push_back(inputStr.size() - 1);
			pos = end;
		}

		inputStr.push_back("");
		suffixArr.push_back(inputStr.size() - 1);
	}

	wordNum = suffixArr.size();
	inputIOS.close();

	// sort suffix
	sortSuffxArr();
}

int randGen::outPut()
{
	ofstream outputIOS;
	outputIOS.open(outputFile, ios_base::out);

	srand(unsigned(time(0)));
	int curIndex = findNext("");

	int genedNum = 0;
	int beginFlag = 1;
	while(curIndex != -1)
	{
		if (isalnum(inputStr[suffixArr[curIndex] + 1][0]) && !beginFlag)
			outputIOS << " ";

		if (inputStr[suffixArr[curIndex] + 1] != "")
		{
			if (inputStr[suffixArr[curIndex]] == "." || beginFlag)
			{
				outputIOS << (char)toupper(inputStr[suffixArr[curIndex] + 1][0]);
				outputIOS << inputStr[suffixArr[curIndex] + 1].substr(1);
			}
			else
				outputIOS << inputStr[suffixArr[curIndex] + 1];
			genedNum++;
		}
		else
		{
			if (genedNum >= maxGenNum)
				break;
		}

		beginFlag = 0;
		curIndex = findNext(inputStr[suffixArr[curIndex] + 1]);
	}

	outputIOS << endl;
	outputIOS.close();
}
