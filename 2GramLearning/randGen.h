/*
 * randGen.h
 *
 *  Created on: Aug 24, 2014
 *      Author: ufo008ahw
 */

#ifndef RANDGEN_H_
#define RANDGEN_H_

#include <string>
#include <vector>
using namespace std;

class randGen
{
	private:
		vector<string> inputStr;
		vector<int> suffixArr;

		const int minGenNum = 100;
		const int maxGenNum = 150;
		const char* outputFile = "out.txt";
		int wordNum;

		int sortSuffxArr();
		int findNext(string curStr);

	public:
		randGen(string fileName);
		~randGen();

		bool operator()(int a, int b);
		int readFile(string fileName);
		int outPut();
};



#endif /* RANDGEN_H_ */
