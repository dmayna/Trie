// Trie.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <string>
using namespace std;
const int ALPHABET_SIZE = 26;


class Node
{
public:
	char getData(void) { return data; };
	void setIsEnd(bool inData) { isEndofWord = inData; };
	bool isEnd(void) { return isEndofWord; };
	bool hasChildren(void) {
		for (int i = 0; i < ALPHABET_SIZE; i++)
		{
			if (children[i] != NULL)
			{
				cout << children[i]->getData() << endl;
				return true;
			}
		}
		return false;
	}
	void setData(char inData) { data = inData; };
	Node * children[ALPHABET_SIZE];
	Node(void) {
		for (int i = 0; i < ALPHABET_SIZE; i++) { children[i] = NULL; }
		isEndofWord = false;
	};
private:
	char data;
	bool isEndofWord;
};

class Trie
{
public:
	Trie() :ptrRoot{ NULL } {};
	Node * ptrRoot;
	bool isEmpty(void);
	void search(string data);
	void insert(string data);
	void remove(string data);
	void printTrie(void);
	Node *getNode(string data);

private:
	void insert(string data, Node * leaf);
	Node *getNode(string data, Node * leaf);
	void remove(Node * leaf, string data);
};



void Trie::remove(string data)
{
	// first check if in tree
	// might need a get node function
	// check last letter of data
	// if the last letter has a childeren node
		// then just mark isEndofWord = false;
	// else
		// delete this node and recursively do this for the rest of the word
	if (data.length() < 1)
	{
		return;
	}
	string origData = data;
	cout << data << " 1"<< endl;
	Node *ptrCurrent = new Node;
	ptrCurrent = ptrRoot;
	Node *tempNode = new Node;
	while (data.length() >= 1/*!ptrCurrent->isEnd()*/) // and same llength of data
		// or while data.length >= 1;
	{
		cout << data << endl;
		int index = data[0] - 'a';
		if (ptrCurrent->children[index] != NULL)
		{
			if (ptrCurrent->children[index]->isEnd())
			{
				tempNode = ptrCurrent;
			}
			ptrCurrent = ptrCurrent->children[index];
			string::iterator it;
			it = data.begin();
			data.erase(it);
		}
	}
	/*if (ptrCurrent->hasChildren())
	{
		cout << "end " << ptrCurrent->getData() <<"\n";
		
		ptrCurrent->setIsEnd(false);
	}
	else
	{*/
		cout << "Before delete : " << ptrCurrent->getData() << endl;
		ptrCurrent = NULL;
		//delete ptrCurrent;
		//cout << "After delete : " << ptrCurrent->getData() << endl;
		tempNode->setIsEnd(true);
		string::iterator it;
		it = origData.end();
		origData.erase(it - 1);
		cout << "Orig: " << origData << endl;;
		remove(origData);
	//}
}

bool Trie::isEmpty()
{
	if (ptrRoot == NULL) 
	{ 
		return true; 
	}
	else
	{
		return false;
	}
}

void Trie::insert(string data)
{
	if (ptrRoot == NULL)
	{
		
		ptrRoot = new Node;
		int index = data[0] - 'a';
		ptrRoot->children[index] = new Node;
		ptrRoot->children[index]->setData(data[0]);
		string::iterator it;
		it = data.begin();
		data.erase(it);
		//cout << ptrRoot->children[index]->getData();
		insert(data,ptrRoot->children[index]);
	}
	else
	{
		insert(data, ptrRoot);
	}
}

void Trie::insert(string data, Node * leaf)
{
	int index = data[0] - 'a';
	if (leaf->children[index] == NULL)
	{
		leaf->children[index] = new Node;
		leaf->children[index]->setData(data[0]);
		if (data.length() == 1)
		{
			//cout << "End of word";
			leaf->children[index]->setIsEnd(true);
		}
		else
		{
			string::iterator it;
			it = data.begin();
			data.erase(it);
			insert(data, leaf->children[index]);
		}
	}
	else
	{
		string::iterator it;
		it = data.begin();
		data.erase(it);
		insert(data, leaf->children[index]);
	}
}

void Trie::printTrie(void)
{
	Node *ptrCurrent = new Node;
	ptrCurrent = ptrRoot;
	int index;
	while (!ptrCurrent->isEnd())
	{
		for (int i = 0; i < ALPHABET_SIZE; i++)
		{
			if (ptrCurrent->children[i] != NULL)
			{
				cout << ptrCurrent->children[i]->getData();
				index = i;
			}
		}
		ptrCurrent = ptrCurrent->children[index];
	}
}

void Trie::search(string inData)
{
	string origData = inData;
	if (isEmpty())
	{
		cout << inData << " is not in the Trie...\n";
		return;
	}
	Node *ptrCurrent = new Node;
	ptrCurrent = ptrRoot;
	int index = inData[0] - 'a';
	if (ptrCurrent->children[index] == NULL)
	{
		cout << origData << " is not in thee Trie... \n";
		return;
	}
	if (ptrCurrent->children[index]->isEnd() && inData.length() > 1)
	{
		ptrCurrent->children[index] = NULL;
		cout << origData << " is not in thee Trie... \n";
		return;
	}
	while (!ptrCurrent->isEnd())
	{
		int index = inData[0] - 'a';
		if (ptrCurrent->children[index] != NULL)
		{
			cout << ptrCurrent->children[index]->getData() << " ttt"<< endl;
			ptrCurrent = ptrCurrent->children[index];
			string::iterator it;
			it = inData.begin();
			inData.erase(it);
		}
		else
		{
			cout << inData << "\n";
			cout << origData << " is not in thee Trie.../n";
			return;
		}
	}
	cout << origData << " is in the Trie...\n";
}


int main()
{
	Trie t;
	t.insert("great");
	//t.printTrie();
	t.insert("greet");
	//t.printTrie();
	//t.search("greet");
	t.insert("blake");
	//t.search("blake");
	t.remove("blake");
	t.printTrie();
	t.search("blake");
	t.search("great");
	t.remove("great");
	//t.remove("greet");
	t.search("greet");

}
