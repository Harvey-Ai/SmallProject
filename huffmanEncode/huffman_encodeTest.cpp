#include <iostream>
#include <fstream>
#include "huffman_encode.h"

int main()
{
	ifstream in;
	in.open("input", ios::in);
	ofstream out;
	out.open("output", ios::out);

	string str, lineStr;
	while(getline(in, lineStr))
	{
		str += lineStr;
		str += '\n';
	}
	if (str.size())
		str = str.substr(0, str.size() - 1);

	string encodeStr;
	enCode_huffman encodeInstance;
	encodeInstance.enCode(str, encodeStr);

	string decodeStr;
	encodeInstance.deCode(encodeStr, decodeStr);
	out << encodeStr;
	
	if (str != decodeStr)
	{
		cout << "bad huffmam" << endl;
		cout << str.size() << endl;
		cout << "Text: " << str << endl;
		cout << "================" << endl;
		cout << "encode Text: "  << " " << encodeStr.size() << endl;
		cout << "===============" << endl;
		cout << "decode Text: "  << " " << decodeStr.size() << endl;
	}
	else
	{
		cout << "huffman works" << endl;
		cout << "Text size = " << str.size() << ", " << "encode Text size = " << encodeStr.size() << endl;
		if (encodeStr.size() > 0)
			cout << "compress ratio = " << str.size() * 1.0 / encodeStr.size() << endl;
	}

	return 0;
}
