#include <iostream>
#include <string>
#include <fstream>
using namespace std;

int rmComment(const string &codeStr, string &output)
{
	bool inQuote = false;
	bool inLineComment = false;
	bool inFullComment = false;

	for(int i = 0;i < codeStr.size();i++)
	{
		if (inLineComment)
		{
			if (codeStr[i] == '\n')
				inLineComment = false;
			continue;
		}

		if (inFullComment)
		{
			if (codeStr[i] == '/' && codeStr[i - 1] == '*')
				inFullComment = false;
			continue;
		}

		if (inQuote)
		{
			if (codeStr[i] == '"')
				inQuote = false;
		}
		else
		{
			if (codeStr[i] == '"')
				inQuote = true;
			else if (codeStr[i] == '/' && (i + 1 < codeStr.size()))
			{
				if (codeStr[i + 1] == '*')
					inFullComment = true;
				else if (codeStr[i + 1] == '/')
					inLineComment = true;
			}
		}

		if (!inLineComment && !inFullComment)
			output += codeStr[i];
	}
}

int main()
{
	string codeStr, cleanStr;
	
	ifstream in;
	in.open("input", ios::in);
	ofstream out;
	out.open("output", ios::out);
	
	string lineStr;
	while(getline(in, lineStr))
	{
		codeStr += lineStr;
		codeStr += '\n';
	}

	rmComment(codeStr, cleanStr);
	out << cleanStr;
	return 0;
}
