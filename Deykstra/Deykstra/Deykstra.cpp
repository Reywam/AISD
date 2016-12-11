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

	// Вектор в котором 1 значение - вершина, куда можем прийти
	// 2 значение - расстояние до этой вершины
	vector<pair<int, int>> ways;
	int mark = INT_MAX;

	bool visited = false;
};

// Граф, по сути, представляет собой набор вершин, а вершины сами знают, куда им идти
struct Graph
{
	vector<Vertex> vertexes;

	// Вектор, в который запишется порядок вершин по которым путь будет самым коротким
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
	// Т.к. граф у нас не ориентированный, то за 1 проход добавляются 2 вершины
	// первая и её вершина-сосед
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
				// Значит эта вершина уже есть и надо добавить только соседа
				// в вектор соседей
				it->ways.push_back(make_pair(vertexTwo, density));
				found = true;
				break;
			}
		}

		if (!found)
		{
			// Если вершина новая - добавляем её в граф
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
				// Значит эта вершина уже есть и надо добавить только соседа
				// в вектор соседей
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
	// Каждому соседу, если расстояние от текущей вершины до него < 
	// его метки, обновляем метку на это расстояние
	cout << "Каждому соседу, если расстояние от текущей вершины до него" << endl
		<< "меньше его метки, обновляем метку на это значение" << endl << endl;

	output << "Каждому соседу, если расстояние от текущей вершины до него" << endl
		<< "меньше его метки, обновляем метку на это значение" << endl << endl;
	for (auto it = vertex.ways.begin(); it != vertex.ways.end(); it++)
	{
		Vertex *newVertex = FindVertex(graph, it->first);
		// Если сумма метки текущей вершины и расстояния до соседа меньше метки соседа
		// то меняем метку соседа на это значение
		if (step)
		{
			cin.get();
		}

		if (vertex.mark + it->second < newVertex->mark)
		{
			cout << "Метку вершины " << it->first << " можно заменить на " << vertex.mark + it->second << endl;
			output << "Метку вершины " << it->first << " можно заменить на " << vertex.mark + it->second << endl;
			newVertex->mark = vertex.mark + it->second;
		}
		else
		{
			cout << "Метка вершины " << it->first << " меньше " 
				<< vertex.mark + it->second << ", значит её менять не нужно" << endl;
			output << "Метка вершины " << it->first << " меньше "
				<< vertex.mark + it->second << ", значит её менять не нужно" << endl;
		}
	}
	cout << endl;
	output << endl;
}

void PrintMarks(ostream &output, Graph const &graph)
{
	output << "Текущие значения меток:" << endl;
	for (auto it = graph.vertexes.begin(); it != graph.vertexes.end(); it++)
	{
		// Чтобы табличка красиво смотрелась надо выравнять столбики по размеру цифр в метке
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
			output << "Путь до вершины " << it->vertexNumber << " равен: " << it->mark << endl;
		}
	}
}

void PrintGeneralInformation(ostream &output)
{
	output << "Алгоритм Дейкстры позволяет найти кратчайшее" << endl
		<< "расстояние от заданной вершины графа до" << endl
		<< "остальных вершин этого графа." << endl;
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

	cout << "В каком режиме запустить программу?" << endl;
	cout << "1. Обычный режим." << endl << "2. Пошаговый режим" << endl;

	char answer;
	cin >> answer;

	bool step = false;
	if (answer == '2')
	{
		cout << endl;
		cout << "Программа запущена в пошаговом режиме.\nКаждый шаг будет производится после нажатия Enter" << endl;
		cout << endl;
		step = true;
	}
	else
	{
		cout << endl;
		cout << "Программа запущена в обычном режиме." << endl;
		cout << endl;
	}

	PrintGeneralInformation(cout);
	PrintGeneralInformation(logFile);
	cout << "От какой вершины ищем путь?" << endl;
	logFile << "От какой вершины ищем путь?" << endl;
	int startVertexNumber;
	cin >> startVertexNumber;

	cout << "Выбранная вершина: " << startVertexNumber << endl;
	logFile << "Выбранная вершина: " << startVertexNumber << endl;

	// Метка той вершины, от которой ищем путь равна 0
	Vertex *currVertex = FindVertex(graph, startVertexNumber);
	currVertex->mark = 0;

	cout << "Метку выбранной вершины принимаем за 0, метки всех остальных - недостижимо большое число." << endl;
	logFile << "Метку выбранной вершины принимаем за 0, метки всех остальных - недостижимо большое число." << endl;

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
	// Продолжать обход пока все вершины не будут visited
	cout << "Пока мы не обошли все вершины мы:" << endl << endl;
	logFile << "Пока мы не обошли все вершины мы:" << endl << endl;
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
			// Теперь нужно пройтись по списку соседей и расставить соседям метки
			// с их расстоянием до нашей текущей вершины
			ChangeVertexesMarks(logFile, graph, *currVertex, step);

			if (step)
			{
				cin.get();
			}

			PrintMarks(cout, graph);
			PrintMarks(logFile, graph);
			// Отметили вершину как посещённую, теперь нужно перейти в ближайшую
			currVertex->visited = true;

			if (step)
			{
				cin.get();
			}

			// Текущая вершина - ближайшая к предыдущей
			cout << "Находим ближайшую к текущей вершину и делаем с ней то же самое" << endl;
			logFile << "Находим ближайшую к текущей вершину и делаем с ней то же самое" << endl;
			int closestVertex = FindVertexWithMinDistance(graph, *currVertex);
			currVertex = FindVertex(graph, closestVertex);

			if (currVertex->ways.size() == 1)
			{
				// Если у вершины нет других соседей - метим как посещённую и уходим в предыдущую
				currVertex->visited = true;
				auto it = currVertex->ways.begin();
				currVertex = FindVertex(graph, it->first);
			}
		}
	}

	cout << "Мы обошли все вершины и нашли кратчайшие расстояния от выбранной вершины до всех вершин" << endl;
	logFile << "Мы обошли все вершины и нашли кратчайшие расстояния от выбранной вершины до всех вершин" << endl;
	
	PrintEndResult(cout, graph);
	PrintEndResult(logFile, graph);
    return 0;
}