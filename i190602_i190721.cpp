#pragma once
#include <iostream>
#include <fstream>
#include <string>

using namespace std;


template <typename T>
struct QueueNode
{
public:
	T data;
	QueueNode<T>* next;
};


template <typename T>
struct Node
{
public:
	T data;
	Node<T>* next;
};

template <typename T>
class Queue
{
private:
	QueueNode<T>* Front;
	QueueNode<T>* Rear;
	int size;
public:
	Queue()
	{
		Front = nullptr;
		Rear = nullptr;
		size = 0;
	}
	void enqueue(T k)
	{
		if (Front == nullptr)
		{
			Front = new QueueNode<T>;
			Front->data = k;
			Front->next = nullptr;
			Rear = Front;
			size++;
		}
		else
		{
			Rear->next = new QueueNode<T>;
			Rear = Rear->next;
			Rear->data = k;
			Rear->next = nullptr;
			size++;
		}
	}
	T dequeue()
	{
		T temp = Front->data;
		Front = Front->next;
		size--;
		return temp;
	}
	int queueSize()
	{
		return size;
	}
};

template <typename T>
class AdjancencyList
{
private:
	Node<T>* Head;
	Node<T>* Tail;
	int totalneighbors;
public:
	AdjancencyList()
	{
		Head = nullptr;
		Tail = nullptr;
		totalneighbors = 0;
	}
	void insertAtEnd(T k)
	{
		if (Head == nullptr)
		{
			Head = new Node<T>;
			Head->data = k;
			Head->next = nullptr;
			Tail = Head;
			totalneighbors++;
		}
		else
		{
			Tail->next = new Node<T>;
			Tail = Tail->next;
			Tail->data = k;
			Tail->next = nullptr;
			totalneighbors++;
		}
	}
	int get_totalneighbors()
	{
		return totalneighbors;
	}
	bool search(T v)
	{
		bool flag = false;
		Node<T>* temporary = Head;
		while (temporary != nullptr)
		{
			if (temporary->data == v)
			{
				flag = true;
			}
			temporary = temporary->next;

		}
		return flag;
	}
	void print()
	{
		Node<T>* temporary = Head;
		while (temporary != nullptr)
		{
			cout << temporary->data << endl;
			temporary = temporary->next;
		}
	}
	int searchdata(int i)
	{
		Node<T>* temp = Head;
		int j = 0;
		while (j < i)
		{
			temp = temp->next;
			j++;
		}
		T returner = temp->data;
		return returner;
	}


};


template <typename T>
struct node
{
public:
	T value;

	AdjancencyList<T> A;
	node<T>* next;
};

template <typename T>
class Graph
{
private:
	node<T>* Head;
	node<T>* Tail;
	int totalvertices;

public:
	Graph()
	{
		Head = nullptr;
		Tail = nullptr;
		totalvertices = 0;
	}
	void insert(T k)
	{
		if (Head == nullptr)
		{
			Head = new node<T>;
			Head->value = k;
			Head->next = nullptr;
			Tail = Head;
			totalvertices++;
		}
		else
		{
			Tail->next = new node<T>;
			Tail = Tail->next;
			Tail->value = k;
			Tail->next = nullptr;
			totalvertices++;
		}


	}
	void print()
	{
		node<T>* temp = Head;
		//	node<T>* temp2 = temp->A->Head;
		while (temp != nullptr)
		{
			cout << "Vertice : " << temp->value << endl;
			cout << "Neighbours : " << endl;
			temp->A.print();
			temp = temp->next;

		}
	}
	bool search(T v)
	{
		bool flag = false;
		//AdjancencyList<T,R> A;
		node<T>* temp = Head;
		//	node<T>* temp2 = temp->A->Head;
		while (temp != nullptr)
		{
			if (temp->value == v)
			{
				flag = true;
			}
			temp = temp->next;

		}
		return flag;
	}

	void create_edge(T v1, T v2)
	{
		bool flag = false;
		node<T>* temp = Head;
		while (temp != nullptr)
		{
			if (temp->value == v1)
			{
				temp->A.insertAtEnd(v2);
				break;
			}
			temp = temp->next;
		}
	}

	double get_totaledges()
	{
		double count = 0;
		node<T>* temporary = Head;
		while (temporary != nullptr)
		{
			count += temporary->A.get_totalneighbors();
			temporary = temporary->next;

		}
		return count;
	}
	int get_totalVertices()
	{
		return totalvertices;
	}
	int Sink()
	{
		int SinkNodes = 0;
		node<T>* temporary = Head;
		while (temporary != nullptr)
		{
			int neighbours = temporary->A.get_totalneighbors();
			if (neighbours < 1)
			{
				SinkNodes++;

			}
			temporary = temporary->next;
		}
		return SinkNodes;
	}
	int Source()
	{
		int SourceNodes = 0;
		node<T>* temporary = Head;
		while (temporary != nullptr)
		{
			node<T>* temporary2 = Head;
			bool overallFound = false;
			while (temporary2 != nullptr)
			{
				bool found = temporary2->A.search(temporary->value);
				if (found == true)
				{
					overallFound = true;
					break;
				}
				temporary2 = temporary2->next;
			}
			if (overallFound == false)
				SourceNodes++;
			temporary = temporary->next;
		}
		return SourceNodes;
	}
	int Isolated()
	{
		int IsolatedNodes = 0;
		node<T>* temporary = Head;
		while (temporary != nullptr)
		{
			node<T>* temporary2 = Head;
			bool overallFound = false;
			while (temporary2 != nullptr)
			{
				bool found = temporary2->A.search(temporary->value);
				if (found == true)
				{
					overallFound = true;
					break;
				}
				temporary2 = temporary2->next;
			}
			if (overallFound == false)
			{
				int neighbours = temporary->A.get_totalneighbors();
				if (neighbours < 1)
				{
					IsolatedNodes++;

				}
			}
			temporary = temporary->next;
		}
		return IsolatedNodes;
	}
	AdjancencyList<T> BFS(int sourceIndex)
	{
		AdjancencyList<T> returner;
		Queue<T> queue;
		int currentIndex;
		queue.enqueue(sourceIndex);
		node<T>* temporary = Head;
		int count = 0;
		while (count < sourceIndex)
		{
			temporary = temporary->next;
			count++;
		}
		returner.insertAtEnd(temporary->value);
		for (; queue.queueSize() > 0;)
		{
			currentIndex = queue.dequeue();
			temporary = Head;
			count = 0;
			while (count < currentIndex)
			{
				temporary = temporary->next;
				count++;
			}
			for (int i = 0; i < temporary->A.get_totalneighbors(); i++)
			{
				T data = temporary->A.searchdata(i);
				if (returner.search(data) == false)
				{
					node<T>* temporary2 = Head;
					int index = 0;
					while (temporary2 != nullptr)
					{
						if (temporary2->value == data)
						{
							break;
						}
						else
							index++;
						temporary2 = temporary2->next;
					}
					queue.enqueue(index);
					returner.insertAtEnd(data);
				}
			}
		}
		return returner;
	}
	AdjancencyList<T> out(T s)
	{
		AdjancencyList<T> outanswer;
		node <T>* temporary = Head;
		int index = 0;
		while (temporary != nullptr)
		{
			if (temporary->value == s)
				break;
			index++;
			temporary = temporary->next;
		}
		outanswer = BFS(index);
		return outanswer;
	}
	AdjancencyList<T> in(T s)
	{
		node <T>* temporary = Head;
		AdjancencyList<T> inanswer;
		for (int i = 0; i < totalvertices; i++)
		{
			AdjancencyList<T> bfsanswer = BFS(i);
			if (bfsanswer.search(s))
				inanswer.insertAtEnd(temporary->value);
			temporary = temporary->next;
		}
		return inanswer;
	}
	AdjancencyList<T>** unique(AdjancencyList<T>** SCCanswers, int& size)
	{
		AdjancencyList<T>** finalanswers = new AdjancencyList<T>*[totalvertices];
		int added = 0;
		for (int i = 0; i < size - 1; i++)
		{
			bool f = false;
			if (SCCanswers[i]->get_totalneighbors() == SCCanswers[i]->get_totalneighbors())
			{
				for (int j = 0; j < SCCanswers[i]->get_totalneighbors(); j++)
				{
					if (SCCanswers[i + 1]->search(SCCanswers[i]->searchdata(j)) == false)
					{
						f = true;
						break;
					}
				}
			}
			else
				f = true;
			if(f == true)
			{
				finalanswers[added] = SCCanswers[i];
				added++;
			}
			else
			{

			}
			if (f == true && i == size - 2)
			{
				finalanswers[added] = SCCanswers[i];
				added++;
				finalanswers[added] = SCCanswers[i + 1];
				added++;
			}
		}
		size = added;
		return finalanswers;
	}
	void SCC()
	{
		AdjancencyList<T>** SCCanswers = new AdjancencyList<T>*[totalvertices];
		int added = 0;
		node <T>* temporary = Head;
		while (temporary != nullptr)
		{
			SCCanswers[added] = new AdjancencyList<T>;
			AdjancencyList<T> inanswer = in(temporary->value);
			AdjancencyList<T> outanswer = out(temporary->value);
			for (int i = 0; i < inanswer.get_totalneighbors(); i++)
			{
				if (outanswer.search(inanswer.searchdata(i)))
					SCCanswers[added]->insertAtEnd(inanswer.searchdata(i));

			}
			added++;
			temporary = temporary->next;
		}
		SCCanswers = unique(SCCanswers, added);
		for (int i = 0; i < added; i++)
		{
			SCCanswers[i]->print();
			cout << endl << endl << endl;
		}
	}
	int LargestSCCsize()
	{
		AdjancencyList<T>** SCCanswers = new AdjancencyList<T>*[totalvertices];
		int added = 0;
		node <T>* temporary = Head;
		while (temporary != nullptr)
		{
			SCCanswers[added] = new AdjancencyList<T>;
			AdjancencyList<T> inanswer = in(temporary->value);
			AdjancencyList<T> outanswer = out(temporary->value);
			for (int i = 0; i < inanswer.get_totalneighbors(); i++)
			{
				if (outanswer.search(inanswer.searchdata(i)))
					SCCanswers[added]->insertAtEnd(inanswer.searchdata(i));

			}
			added++;
			temporary = temporary->next;
		}
		SCCanswers = unique(SCCanswers, added);
		int max = -1;
		for (int i = 0; i < added; i++)
		{
			if (max < SCCanswers[i]->get_totalneighbors())
			{
				max = SCCanswers[i]->get_totalneighbors();
			}
		}
		return max;
	}
	void pathDistribution()
	{
		node<T>* temporary = Head;
		int i = 0;
		int distribution[10] = {};
		while (temporary != nullptr)
		{
			int* shortesPaths = shortest(i);
			for(int j = 1 ; j <= 10; j++)
			{ 
				for (int k = 0; k < totalvertices; k++)
				{
					if (shortesPaths[k] == j)
						distribution[j - 1]++;
				}
			}
			i++;
			temporary = temporary->next;
		}
		cout << "---------------------------------------------------------------" << endl;
		for (int length = 1; length <= 10; length++)
		{
			cout << "Length of " << length  << " has " << distribution[length - 1] << " paths." << endl;
			cout << "---------------------------------------------------------------" << endl;
		}
	}
	int GraphDiameter()
	{
		node<T>* temporary = Head;
		int graphDiameter = -1;
		int i = 0;
		int distribution[10] = {};
		while (temporary != nullptr)
		{
			int* shortesPaths = shortest(i);
			for (int k = 0; k < totalvertices; k++)
			{
				if (graphDiameter < shortesPaths[k])
					graphDiameter = shortesPaths[k];
			}
			i++;
			temporary = temporary->next;
		}
		return graphDiameter;
	}
	int* shortest(int sourceIndex)
	{
		int* shortestPaths = new int[totalvertices];
		AdjancencyList<T> returner;
		Queue<T> queue;
		int currentIndex;
		queue.enqueue(sourceIndex);
		for (int i = 0; i < totalvertices; i++)
		{
			if(i != sourceIndex)
				shortestPaths[i] = -1;
			else
				shortestPaths[i] = 0;
		}
		node<T>* temporary = Head;
		int count = 0;
		while (count < sourceIndex)
		{
			temporary = temporary->next;
			count++;
		}
		returner.insertAtEnd(temporary->value);
		for (; queue.queueSize() > 0;)
		{
			currentIndex = queue.dequeue();
			temporary = Head;
			count = 0;
			while (count < currentIndex)
			{
				temporary = temporary->next;
				count++;
			}
			for (int i = 0; i < temporary->A.get_totalneighbors(); i++)
			{
				T data = temporary->A.searchdata(i);
				if (returner.search(data) == false)
				{
					node<T>* temporary2 = Head;
					int index = 0;
					while (temporary2 != nullptr)
					{
						if (temporary2->value == data)
						{
							break;
						}
						else
							index++;
						temporary2 = temporary2->next;
					}
					shortestPaths[index] = shortestPaths[currentIndex] + 1;
					queue.enqueue(index);
					returner.insertAtEnd(data);
				}
			}
		}
		return shortestPaths;
	}
	void findIn_degree()
	{
		int i = 0;
		float j;
		int* indegrees = new int[totalvertices] {};
		node<T>* temporary = Head;
		for (int i = 0; i < totalvertices; i++)
		{
			node<T>* temporary2 = Head;
			while (temporary2 != nullptr)
			{
				if (temporary2->A.search(temporary->value))
					indegrees[i]++;
				temporary2 = temporary2->next;
			}
			temporary = temporary->next;
		}
		cout << "Node  |   InDegree Distribution" << endl;
		temporary = Head;
		for (int i = 0; i < totalvertices; i++)
		{
			j = float(indegrees[i]) / (totalvertices);
			cout << temporary->value << "     |         " << j << endl;
			temporary = temporary->next;
		}
	}
	void findOut_degree()
	{
		float j;
		node<T>* temporary = Head;
		cout << "Node  |   OutDegree Distribution" << endl;
		while (temporary != nullptr)
		{
			j = float(temporary->A.get_totalneighbors()) / (totalvertices);
			cout << temporary->value << "     |         "   << j << endl;
			temporary = temporary->next;
		}

	}
};

Graph<int> load_data(string path)
{
	string v1 = "";
	int num1 = 0, num2 = 0;
	ifstream ifile;
	ifile.open(path);
	string line;
	Graph <int> obj;
	while (!ifile.eof())
	{
		getline(ifile, line);
		v1 = "";
		num1 = 0;
		for (int i = 0; line[i] != '\0'; i++)
		{

			if (line[i] != '\t')
			{
				v1 += line[i];
				if (line[i + 1] == '\0')
				{
					if (num1 == 0)
					{
						num1 = stoi(v1);
						num2 = 0;
					}

					else
					{
						num2 = stoi(v1);
					}

					break;
				}

			}
			else
			{
				num1 = stoi(v1);
				v1 = "";

			}

		}


		if (!obj.search(num1))
		{
			obj.insert(num1);
		}
		else if (!obj.search(num2))
		{
			obj.insert(num2);
		}
		if (num2 != 0)
		{
			obj.create_edge(num1, num2);
		}
	}
	return obj;
}


int main()
{
	Graph<int> graph;
	cout << "Enter file path" << endl;
	string file;
	cin >> file;
	graph = load_data(file);
	int choice = -1;
	bool flag = true;
	while (flag)
	{
		cout << endl;
		cout << endl;
		cout << endl;
		cout << endl;
		cout << endl;
		cout << "Enter 0 to EXIT:" << endl;
		cout << "Enter 1 to Display the number of nodes:" << endl;
		cout << "Enter 2 to Display the number of edges:" << endl;
		cout << "Enter 3 to Display the number of source nodes:" << endl;
		cout << "Enter 4 to Display the number of sink nodes:" << endl;
		cout << "Enter 5 to Display the number of isolated nodes:" << endl;
		cout << "Enter 6 to Display the number of bridge edges:" << endl;
		cout << "Enter 7 to Display the number of articulation nodes:" << endl;
		cout << "Enter 8 to Display the shortest path length distribution:" << endl;
		cout << "Enter 9 to Display the diameter of the graph:" << endl;
		cout << "Enter 10 to Display the in - degree distribution in the form of a table:" << endl;
		cout << "Enter 11 to Display the out - degree distribution in the form of a table:" << endl;
		cout << "Enter 12 to Display the size of the largest strongly connected component(SCC):" << endl;
		cout << "Enter 13 to Display the size distribution of all SCCs:" << endl;
		cout << "Enter 14 to Display the size of the largest weakly connected component(WCC):" << endl;
		cout << "Enter 15 to  Display the size distribution of all WCCs:" << endl;
		cin >> choice;
		cout << endl;
		cout << endl;
		cout << endl;
		cout << endl;
		cout << endl;
		if (choice == 0)
		{
			flag = false;
		}
		if (choice == 1)
		{
			cout << "Total Nodes = " << graph.get_totalVertices() << endl;
		}
		if (choice == 2)
		{
			cout << "Total Edges = " << graph.get_totaledges() << endl;
		}
		if (choice == 3)
		{
			cout << "Total Source Nodes = " << graph.Source() << endl;
		}
		if (choice == 4)
		{
			cout << "Total Sink Nodes = " << graph.Sink() << endl;
		}
		if (choice == 5)
		{
			cout << "Total isolated Nodes = " << graph.Isolated() << endl;
		}
		if (choice == 6)
		{
			cout << "Not done" << endl;
		}
		if (choice == 7)
		{
			cout << "Not done" << endl;
		}
		if (choice == 8)
		{
			graph.pathDistribution();
		}
		if (choice == 9)
		{
			cout << "Diameter = " << graph.GraphDiameter() << endl;
		}
		if (choice == 10)
		{
			graph.findIn_degree();
		}
		if (choice == 11)
		{
			graph.findOut_degree();
		}
		if (choice == 12)
		{
			cout << "Largest SCC SIZE = " << graph.LargestSCCsize() << endl;;
		}
		if (choice == 13)
		{
			graph.SCC();
		}
		if (choice == 14)
		{
			cout << "Not done" << endl;
		}
		if (choice == 15)
		{
			cout << "Not done" << endl;
		}

	}


}

