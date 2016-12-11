#include "stdafx.h"
#include <windows.h>
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <iterator>
#include <list>

using namespace std;

struct Vertex
{
	int vertexNumber = 0;

	// ������ � ������� 1 �������� - �������, ���� ����� ������
	// 2 �������� - ���������� �� ���� �������
	vector<pair<int, int>> ways;
	int mark = INT_MAX;

	bool visited = false;
};

// ����, �� ����, ������������ ����� ����� ������, � ������� ���� �����, ���� �� ����
struct Graph
{
	vector<Vertex> vertexes;

	// ������, � ������� ��������� ������� ������ �� ������� ���� ����� ����� ��������
	vector<int> shortWay;
};

int ReadVertexOne(istream &input)
{
	string vertexOne = "";

	char ch = NULL;
	while (ch != '-' && !input.eof())
	{
		input.get(ch);
		vertexOne += ch;
	}

	return stoi(vertexOne);
}

int ReadVertexTwo(istream &input)
{
	string vertexTwo = "";

	char ch = NULL;
	while (ch != ' ' && !input.eof())
	{
		input.get(ch);
		vertexTwo += ch;
	}

	return stoi(vertexTwo);
}

int ReadDensity(istream &input)
{
	string density = "";

	char ch = NULL;
	while (ch != '\n' && !input.eof())
	{
		ch = NULL;
		input.get(ch);
		density += ch;
	}
	return stoi(density);
}

void InitGraph(istream &input, Graph &graph)
{
	// �.�. ���� � ��� �� ���������������, �� �� 1 ������ ����������� 2 �������
	// ������ � � �������-�����
	while (!input.eof())
	{
		Vertex vertex;
		bool found = false;

		int vertexOne = ReadVertexOne(input);
		int vertexTwo = ReadVertexTwo(input);
		int density = ReadDensity(input);

		for (auto it = graph.vertexes.begin(); it != graph.vertexes.end(); it++)
		{
			if (it->vertexNumber == vertexOne)
			{
				// ������ ��� ������� ��� ���� � ���� �������� ������ ������
				// � ������ �������
				it->ways.push_back(make_pair(vertexTwo, density));
				found = true;
				break;
			}
		}

		if (!found)
		{
			// ���� ������� ����� - ��������� � � ����
			vertex.vertexNumber = vertexOne;
			vertex.ways.push_back(make_pair(vertexTwo, density));
			graph.vertexes.push_back(vertex);
		}

		found = false;

		vertex.ways.clear();
		for (auto it = graph.vertexes.begin(); it != graph.vertexes.end(); it++)
		{
			if (it->vertexNumber == vertexTwo)
			{
				// ������ ��� ������� ��� ���� � ���� �������� ������ ������
				// � ������ �������
				it->ways.push_back(make_pair(vertexOne, density));
				found = true;
				break;
			}
		}

		if (!found)
		{
			vertex.vertexNumber = vertexTwo;
			vertex.ways.push_back(make_pair(vertexOne, density));
			graph.vertexes.push_back(vertex);
		}
	}
}

void PrintInfo(Graph const &graph)
{
	
	for (auto it = graph.vertexes.begin(); it != graph.vertexes.end(); it++)
	{
		cout << it->vertexNumber << ":";
		cout << ">>" << it->mark << endl;
	}
}

Vertex *FindVertex(Graph &graph, int vertexNumber)
{
	Vertex vertex;
	for (auto it = graph.vertexes.begin(); it != graph.vertexes.end(); it++)
	{
		if (vertexNumber == it->vertexNumber)
		{
			return &*it;
		}
	}	
}

int FindVertexWithMinDistance(Graph &graph, Vertex const &vertex)
{
	int vertexNumber = 0;

	int minDistance = INT_MAX;
	for (auto it = vertex.ways.begin(); it != vertex.ways.end(); it++)
	{
		if (it->second < minDistance && !FindVertex(graph, it->first)->visited)
		{
			minDistance = it->second;
			vertexNumber = it->first;
		}
	}

	return vertexNumber;
}

void ChangeVertexesMarks(ostream &output, Graph &graph, Vertex &vertex, bool step)
{
	// ������� ������, ���� ���������� �� ������� ������� �� ���� < 
	// ��� �����, ��������� ����� �� ��� ����������
	cout << "������� ������, ���� ���������� �� ������� ������� �� ����" << endl
		<< "������ ��� �����, ��������� ����� �� ��� ��������" << endl << endl;

	output << "������� ������, ���� ���������� �� ������� ������� �� ����" << endl
		<< "������ ��� �����, ��������� ����� �� ��� ��������" << endl << endl;
	for (auto it = vertex.ways.begin(); it != vertex.ways.end(); it++)
	{
		Vertex *newVertex = FindVertex(graph, it->first);
		// ���� ����� ����� ������� ������� � ���������� �� ������ ������ ����� ������
		// �� ������ ����� ������ �� ��� ��������
		if (step)
		{
			cin.get();
		}

		if (vertex.mark + it->second < newVertex->mark)
		{
			cout << "����� ������� " << it->first << " ����� �������� �� " << vertex.mark + it->second << endl;
			output << "����� ������� " << it->first << " ����� �������� �� " << vertex.mark + it->second << endl;
			newVertex->mark = vertex.mark + it->second;
		}
		else
		{
			cout << "����� ������� " << it->first << " ������ " 
				<< vertex.mark + it->second << ", ������ � ������ �� �����" << endl;
			output << "����� ������� " << it->first << " ������ "
				<< vertex.mark + it->second << ", ������ � ������ �� �����" << endl;
		}
	}
	cout << endl;
	output << endl;
}

void PrintMarks(ostream &output, Graph const &graph)
{
	output << "������� �������� �����:" << endl;
	for (auto it = graph.vertexes.begin(); it != graph.vertexes.end(); it++)
	{
		// ����� �������� ������� ���������� ���� ��������� �������� �� ������� ���� � �����
		output << "|" << it->vertexNumber;
		for (size_t i = 1; i < to_string(it->mark).size(); i++)
		{
			output << ' ';
		}
		output << "|";
	}

	output << endl;

	for (auto it = graph.vertexes.begin(); it != graph.vertexes.end(); it++)
	{
		output << "|" << it->mark << "|";
	}

	output << endl << endl;
}

void PrintEndResult(ostream &output, Graph const &graph)
{
	for (auto it = graph.vertexes.begin(); it != graph.vertexes.end(); it++)
	{
		if (it->mark != 0)
		{
			output << "���� �� ������� " << it->vertexNumber << " �����: " << it->mark << endl;
		}
	}
}

void PrintGeneralInformation(ostream &output)
{
	output << "�������� �������� ��������� ����� ����������" << endl
		<< "���������� �� �������� ������� ����� ��" << endl
		<< "��������� ������ ����� �����." << endl;
	output << endl;
}

int main(int argc, char* argv[])
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	ifstream initFile(argv[1]);
	ofstream logFile("log.txt");

	Graph graph;

	bool allVisited = false;

	InitGraph(initFile, graph);

	cout << "� ����� ������ ��������� ���������?" << endl;
	cout << "1. ������� �����." << endl << "2. ��������� �����" << endl;

	char answer;
	cin >> answer;

	bool step = false;
	if (answer == '2')
	{
		cout << endl;
		cout << "��������� �������� � ��������� ������.\n������ ��� ����� ������������ ����� ������� Enter" << endl;
		cout << endl;
		step = true;
	}
	else
	{
		cout << endl;
		cout << "��������� �������� � ������� ������." << endl;
		cout << endl;
	}

	PrintGeneralInformation(cout);
	PrintGeneralInformation(logFile);
	cout << "�� ����� ������� ���� ����?" << endl;
	logFile << "�� ����� ������� ���� ����?" << endl;
	int startVertexNumber;
	cin >> startVertexNumber;

	cout << "��������� �������: " << startVertexNumber << endl;
	logFile << "��������� �������: " << startVertexNumber << endl;

	// ����� ��� �������, �� ������� ���� ���� ����� 0
	Vertex *currVertex = FindVertex(graph, startVertexNumber);
	currVertex->mark = 0;

	cout << "����� ��������� ������� ��������� �� 0, ����� ���� ��������� - ����������� ������� �����." << endl;
	logFile << "����� ��������� ������� ��������� �� 0, ����� ���� ��������� - ����������� ������� �����." << endl;

	if (step)
	{
		cin.get();
	}

	PrintMarks(cout, graph);
	PrintMarks(logFile, graph);
	if (step)
	{
		cin.get();
	}
	// ���������� ����� ���� ��� ������� �� ����� visited
	cout << "���� �� �� ������ ��� ������� ��:" << endl << endl;
	logFile << "���� �� �� ������ ��� ������� ��:" << endl << endl;
	if (step)
	{
		cin.get();
	}
	while (!allVisited)
	{
		allVisited = true;
		if (!currVertex->visited)
		{
			allVisited = false;
			// ������ ����� �������� �� ������ ������� � ���������� ������� �����
			// � �� ����������� �� ����� ������� �������
			ChangeVertexesMarks(logFile, graph, *currVertex, step);

			if (step)
			{
				cin.get();
			}

			PrintMarks(cout, graph);
			PrintMarks(logFile, graph);
			// �������� ������� ��� ����������, ������ ����� ������� � ���������
			currVertex->visited = true;

			if (step)
			{
				cin.get();
			}

			// ������� ������� - ��������� � ����������
			cout << "������� ��������� � ������� ������� � ������ � ��� �� �� �����" << endl;
			logFile << "������� ��������� � ������� ������� � ������ � ��� �� �� �����" << endl;
			int closestVertex = FindVertexWithMinDistance(graph, *currVertex);
			currVertex = FindVertex(graph, closestVertex);

			if (currVertex->ways.size() == 1)
			{
				// ���� � ������� ��� ������ ������� - ����� ��� ���������� � ������ � ����������
				currVertex->visited = true;
				auto it = currVertex->ways.begin();
				currVertex = FindVertex(graph, it->first);
			}
		}
	}

	cout << "�� ������ ��� ������� � ����� ���������� ���������� �� ��������� ������� �� ���� ������" << endl;
	logFile << "�� ������ ��� ������� � ����� ���������� ���������� �� ��������� ������� �� ���� ������" << endl;
	
	PrintEndResult(cout, graph);
	PrintEndResult(logFile, graph);
    return 0;
}