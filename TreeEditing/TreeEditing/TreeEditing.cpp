#include "stdafx.h"
#include <iostream>
#include <string>
#include <fstream>
#include <windows.h>

using namespace std;

struct Node //Звено дерева
{
	string nodeName = ""; // Имя узла
	int nodeLevel; //То, что записываем в дерево
	Node *parent, *leftChild, *rightChild; //Это указатели на новые звенья
};

//Читаем уровень и имя, если уровень равен - в правую ветку, запись общего родителя
//Если больше - в левую ветку закидываем

void PrintTree(Node *&Tree) //Функция обхода
{
	if (Tree != NULL) //Пока не встретится пустое звено
	{
		PrintTree(Tree->leftChild); //Рекурсивная функция для вывода левого поддерева
		cout << Tree->nodeName << endl; //Отображаем корень дерева
		PrintTree(Tree->rightChild); //Рекурсивная функци для вывода правого поддерева
	}
}

void MoveVariants(Node *&Tree)
{
	if (Tree != NULL) //Пока не встретится пустое звено
	{
		MoveVariants(Tree->rightChild); //Рекурсивная функци для вывода правого поддерева
		cout << ">"<< Tree->nodeName << endl; //Отображаем корень дерева
	}
}

void AddNode(string nodeName, int nodeLevel, Node *&MyTree) //Функция добавления звена в дерево
{
	if (NULL == MyTree)  //Если дерева нет, то сеем семечко
	{
		MyTree = new Node; //Выделяем память под звено дерева
		MyTree->nodeName = nodeName; //Записываем данные в звено
		MyTree->parent = MyTree->leftChild = MyTree->rightChild = NULL; //Подзвенья инициализируем пустотой во избежание ошибок
		MyTree->nodeLevel = 0;
		return;
	}

	if (nodeLevel > MyTree->nodeLevel)   //Если нововведенный элемент x меньше чем элемент x из семечка дерева, уходим влево
	{
		if (MyTree->leftChild != NULL)
		{
			AddNode(nodeName, nodeLevel, MyTree->leftChild); //При помощи рекурсии заталкиваем элемент на свободный участок
		}
		else //Если элемент получил свой участок, то
		{
			MyTree->leftChild = new Node;  //Выделяем память левому подзвену. Именно подзвену, а не просто звену
			MyTree->leftChild->parent = MyTree;
			MyTree->leftChild->leftChild = MyTree->leftChild->rightChild = NULL; //У левого подзвена будут свои левое и правое подзвенья, инициализируем их пустотой
			MyTree->leftChild->nodeName = nodeName; //Записываем в левое подзвено записываемый элемент 
			MyTree->leftChild->nodeLevel = nodeLevel;
			return;
		}
	}
	
	if (nodeLevel == MyTree->nodeLevel)   //Если нововведенный элемент x больше чем элемент x из семечка дерева, уходим вправо
	{
		if (MyTree->rightChild != NULL)
		{
			AddNode(nodeName, nodeLevel, MyTree->rightChild); //При помощи рекурсии заталкиваем элемент на свободный участок
		} 
		else //Если элемент получил свой участок, то
		{
			MyTree->rightChild = new Node;  //Выделяем память правому подзвену. Именно подзвену, а не просто звену
			MyTree->rightChild->parent = MyTree;
			MyTree->rightChild->leftChild = MyTree->rightChild->rightChild = NULL; //У правого подзвена будут свои левое и правое подзвенья, инициализируем их пустотой
			MyTree->rightChild->nodeName = nodeName; //Записываем в правое подзвено записываемый элемент 
			MyTree->rightChild->nodeLevel = nodeLevel;
			return;
		}
	}
	return;
}

void DeleteTreee(Node *&Tree) {
	if (Tree != NULL) //Пока не встретится пустое звено
	{
		DeleteTreee(Tree->leftChild); //Рекурсивная функция прохода по левому поддереву
		DeleteTreee(Tree->rightChild); //Рекурсивная функци для прохода по правому поддереву
		delete Tree; //Убиваем конечный элемент дерева
		Tree = NULL; //Может и не обязательно, но плохого не будет
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