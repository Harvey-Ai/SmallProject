#include <map>
#include <queue>
#include <string>
#include <vector>
#include <cstring>
using namespace std;

struct treeNode
{
	int val;
	int weight;
	string encodeStr;
	treeNode *left, *right, *parent;

	treeNode(int v = -1, int w = -1, string str = "", treeNode *l = NULL, treeNode *r = NULL, treeNode *p = NULL)
	{
		val = v;
		weight = w;
		encodeStr = str;
		left = l, right = r, parent = p;
	}

	bool operator()(treeNode *&a, treeNode *&b)
	{
		return a->weight > b->weight;
	}
};

class enCode_huffman {
private:
	treeNode *root;
	map<char, string> encodeMap;
	map<string, char> decodeMap;
	string encodeStr;
	
	void buildTree(const string &str);
	void getEncodeMap();
	int doEncode(const string &str);
public:
	enCode_huffman();
	~enCode_huffman();
	int enCode(const string &str, string &output);
	int deCode(const string &str, string &output);
};

enCode_huffman::enCode_huffman()
{
	root = NULL;
	encodeMap.clear();
	decodeMap.clear();
	encodeStr = "";
}

enCode_huffman::~enCode_huffman()
{
	if (root == NULL)
		return;

	queue<treeNode *> walkQ;
	walkQ.push(root);
	while(!walkQ.empty())
	{
		treeNode *p = walkQ.front();
		walkQ.pop();

		if (p->left)
			walkQ.push(p->left);
		if (p->right)
			walkQ.push(p->right);
		delete p;
	}
}

void enCode_huffman::buildTree(const string &str)
{
	root = NULL;

	int cnt[256];
	memset(cnt, 0, sizeof(cnt));
	for(int i = 0;i < str.size();i++)
		cnt[(unsigned char)str[i]]++;

	priority_queue<treeNode *, vector<treeNode *>, treeNode> maxQ;	
	for(int i = 0;i < 256;i++)
		if (cnt[i])
			maxQ.push(new treeNode(i, cnt[i]));
	
	while(maxQ.size() >= 2)
	{
		treeNode *node1 = maxQ.top();
		maxQ.pop();
		treeNode *node2 = maxQ.top();
		maxQ.pop();

		treeNode *newNode = new treeNode(-1, node1->weight + node2->weight, "",	node1, node2);
		node1->parent = node2->parent = newNode;
		maxQ.push(newNode);
	}
	if (!maxQ.empty())
	{
		root = maxQ.top();
		maxQ.pop();
	}
}

void enCode_huffman::getEncodeMap()
{
	if (root == NULL)
		return;

	encodeMap.clear();
	decodeMap.clear();

	queue<treeNode *> walkQ;
	walkQ.push(root);
	root->encodeStr = "";

	int num = 0;
	while(!walkQ.empty())
	{
		num++;
		treeNode *curNode = walkQ.front();
		walkQ.pop();
		if (curNode->val >= 0)
		{
			encodeMap[curNode->val] = curNode->encodeStr;
			decodeMap[curNode->encodeStr] = curNode->val;
		}

		if (curNode->left)
		{
			curNode->left->encodeStr = curNode->encodeStr + '0';
			walkQ.push(curNode->left);
		}
		if (curNode->right)
		{
			curNode->right->encodeStr = curNode->encodeStr + '1';
			walkQ.push(curNode->right);
		}
	}
}

int  enCode_huffman::doEncode(const string &str)
{
	encodeStr = "";
	string encodeBuff;

	// prefix is the str size
	unsigned int len = str.size();
	unsigned int bitMask = 0xFF;
	encodeStr += (unsigned char)((len >> 24) & bitMask);
	encodeStr += (unsigned char)((len >> 16) & bitMask);
	encodeStr += (unsigned char)((len >> 8) & bitMask);
	encodeStr += (unsigned char)(len & bitMask);
	
	//
	for(int i = 0;i < str.size();i++)
	{
		if (encodeMap.find(str[i]) == encodeMap.end())
			return -1;

		encodeBuff += encodeMap[str[i]];
		while(encodeBuff.size() >= 8)
		{
			int encodeChar = 0;
			for(int j = 0;j < 8;j++)
			{
				encodeChar *= 2;
				encodeChar += encodeBuff[j] - '0';
			}
			encodeStr += (char)encodeChar;
			encodeBuff = encodeBuff.substr(8);
		}
	}

	if (encodeBuff.size())
	{
		int encodeChar = 0;
		for(int i = 0;i < 8;i++)
		{
			encodeChar *= 2;
			if (i < encodeBuff.size())
				encodeChar += encodeBuff[i] - '0';
		}
		encodeStr += (char)encodeChar;
	}
}

int enCode_huffman::enCode(const string &str, string &output)
{
	buildTree(str);
	getEncodeMap();
	doEncode(str);

	output = encodeStr;
	return 0;
}

int enCode_huffman::deCode(const string &str, string &output)
{
	string deCodeBuff = "";
	output = "";
	while(str == "")
		return 0;
	
	unsigned int len = 0;
	len |= (unsigned char)str[0] << 24;
	len |= (unsigned char)str[1] << 16;
	len |= (unsigned char)str[2] << 8;
	len |= (unsigned char)str[3];

	// cout << "decode len:" << len << endl;
	for(int i = 4;i < str.size();i++)
	{
		for(int j = 7;j >= 0;j--)
		{
			if (str[i] & (1 << j))
				deCodeBuff += '1';
			else
				deCodeBuff += '0';
			
			if (len && decodeMap.find(deCodeBuff) != decodeMap.end())
			{
				output += decodeMap[deCodeBuff];
				deCodeBuff = "";
				len--;
			}
		}
	}

	if (len != 0)
		return -1;

	return 0;
}
