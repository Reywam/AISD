#include "stdafx.h"
#include <iostream>
#include <string>
#include <fstream>
#include <windows.h>

using namespace std;

struct Node //����� ������
{
	string nodeName = ""; // ��� ����
	int nodeLevel; //��, ��� ���������� � ������
	Node *parent, *leftChild, *rightChild; //��� ��������� �� ����� ������
};

//������ ������� � ���, ���� ������� ����� - � ������ �����, ������ ������ ��������
//���� ������ - � ����� ����� ����������

void PrintTree(Node *&Tree) //������� ������
{
	if (Tree != NULL) //���� �� ���������� ������ �����
	{
		PrintTree(Tree->leftChild); //����������� ������� ��� ������ ������ ���������
		cout << Tree->nodeName << endl; //���������� ������ ������
		PrintTree(Tree->rightChild); //����������� ������ ��� ������ ������� ���������
	}
}

void MoveVariants(Node *&Tree)
{
	if (Tree != NULL) //���� �� ���������� ������ �����
	{
		MoveVariants(Tree->rightChild); //����������� ������ ��� ������ ������� ���������
		cout << ">"<< Tree->nodeName << endl; //���������� ������ ������
	}
}

void AddNode(string nodeName, int nodeLevel, Node *&MyTree) //������� ���������� ����� � ������
{
	if (NULL == MyTree)  //���� ������ ���, �� ���� �������
	{
		MyTree = new Node; //�������� ������ ��� ����� ������
		MyTree->nodeName = nodeName; //���������� ������ � �����
		MyTree->parent = MyTree->leftChild = MyTree->rightChild = NULL; //��������� �������������� �������� �� ��������� ������
		MyTree->nodeLevel = 0;
		return;
	}

	if (nodeLevel > MyTree->nodeLevel)   //���� ������������� ������� x ������ ��� ������� x �� ������� ������, ������ �����
	{
		if (MyTree->leftChild != NULL)
		{
			AddNode(nodeName, nodeLevel, MyTree->leftChild); //��� ������ �������� ����������� ������� �� ��������� �������
		}
		else //���� ������� ������� ���� �������, ��
		{
			MyTree->leftChild = new Node;  //�������� ������ ������ ��������. ������ ��������, � �� ������ �����
			MyTree->leftChild->parent = MyTree;
			MyTree->leftChild->leftChild = MyTree->leftChild->rightChild = NULL; //� ������ �������� ����� ���� ����� � ������ ���������, �������������� �� ��������
			MyTree->leftChild->nodeName = nodeName; //���������� � ����� �������� ������������ ������� 
			MyTree->leftChild->nodeLevel = nodeLevel;
			return;
		}
	}
	
	if (nodeLevel == MyTree->nodeLevel)   //���� ������������� ������� x ������ ��� ������� x �� ������� ������, ������ ������
	{
		if (MyTree->rightChild != NULL)
		{
			AddNode(nodeName, nodeLevel, MyTree->rightChild); //��� ������ �������� ����������� ������� �� ��������� �������
		} 
		else //���� ������� ������� ���� �������, ��
		{
			MyTree->rightChild = new Node;  //�������� ������ ������� ��������. ������ ��������, � �� ������ �����
			MyTree->rightChild->parent = MyTree;
			MyTree->rightChild->leftChild = MyTree->rightChild->rightChild = NULL; //� ������� �������� ����� ���� ����� � ������ ���������, �������������� �� ��������
			MyTree->rightChild->nodeName = nodeName; //���������� � ������ �������� ������������ ������� 
			MyTree->rightChild->nodeLevel = nodeLevel;
			return;
		}
	}
	return;
}

void DeleteTreee(Node *&Tree) {
	if (Tree != NULL) //���� �� ���������� ������ �����
	{
		DeleteTreee(Tree->leftChild); //����������� ������� ������� �� ������ ���������
		DeleteTreee(Tree->rightChild); //����������� ������ ��� ������� �� ������� ���������
		delete Tree; //������� �������� ������� ������
		Tree = NULL; //����� � �� �����������, �� ������� �� �����
	}

}

void MoveUp(Node *&Tree)
{
	if (Tree->parent != NULL)
	{
		Tree = Tree->parent;
	}
}

void MoveL(Node *&Tree)
{
	if (Tree->leftChild != NULL)
	{
		Tree = Tree->leftChild;
	}
}

void MoveR(Node *&Tree)
{
	if (Tree->rightChild != NULL)
	{
		Tree = Tree->rightChild;
	}
}

void TreeInitialization(ifstream &input, Node *&tree)
{
	while (!input.eof())
	{
		string line;
		getline(input, line);
		int currLevel = 0;
		string nodeName = "";

		for (size_t i = 0; i < line.size(); i++)
		{
			if (line[i] == '*')
			{
				++currLevel;
				continue;
			}
			nodeName += line[i];
		}
		AddNode(nodeName, currLevel, tree);
	}
}

int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		cout << "Invalid arguements count." << endl;
		return 1;
	}

	ifstream initFile(argv[1]);
	if (!initFile)
	{
		cout << "Opening file error." << endl;
		return 1;
	}

	Node *Tree = NULL; 
	
	TreeInitialization(initFile, Tree);

	Node *currNode = Tree;
	while (!cin.eof())
	{
		cout << "Current detail: " << currNode->nodeName << endl;
		
		if (currNode->leftChild != NULL)
		{
			cout << "Can move L: " << currNode->leftChild->nodeName << endl;
		}
		if (currNode->rightChild != NULL)
		{
			Node *tempNode = currNode;
			while (tempNode->rightChild->rightChild != NULL)
			{
				tempNode = tempNode->rightChild;
				cout << "Can move R: " << tempNode->rightChild->nodeName << endl;
			}
		}

		string command;
		cin >> command;

		if (command == "w")
		{
			MoveUp(currNode);
		}
		if (command == "q")
		{
			MoveL(currNode);
		}
		if (command == "e")
		{
			MoveR(currNode);
		}
		system("cls");
	}

	system("cls");
	return 0;
}