/*
Hafiz Muneeb ur Rehman
BCSF15M030
ASSIGNMENT 01
QQUESTION 1
*/

#include<iostream>
#include<fstream>
using namespace std;


class Node
{
public:
	int data;
	Node* next;
};

class myStack
{
	Node* head;
public:
	int size;
	myStack() { head = NULL; size = 0; }
	void push(int element);
	int pop();
};

void myStack::push(int element)
{
	Node* n = new Node;
	n->data = element;
	n->next = NULL;
	if (head == NULL)
		head = n;
	else
	{
		n->next = head;
		head = n;
	}
	++size;
}

int myStack::pop()
{
	if (size == 0)
	{
		cout << "\nerror! no data exist...\n";
	}
	else
	{
		Node* temp = head->next;
		int num = head->data;
		delete head;
		head = temp;
		--size;
		return num;
	}
}

class Maze
{
	char** maze;
	int* arr;
	int row;
	int col;
	int numOfHurdles;
	bool isBlock;
public:
	myStack stack;
	void readFromFile();
	void drawMaze(bool isAgain);
	void findPath();
	void showCoordinates();
};

void Maze::readFromFile()
{
	ifstream inFile("Input 1.txt");
	if (!inFile)
	{
		cout << "Error opening file.\n";
		exit(1);
	}
	arr = new int[1000];
	int count = 0;
	inFile >> arr[count];
	while (!inFile.eof())
	{
		count++;
		inFile >> arr[count];
	}
	inFile.close();
	row = arr[0];
	col = arr[1];
	numOfHurdles = arr[2];
	maze = new char*[row];
	for (int i = 0; i < row; i++)
		maze[i] = new char[col];
}

void Maze::drawMaze(bool isAgain)
{
	if (isAgain)
	{
		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < col; j++)
			{
				maze[i][j] = NULL;
			}
		}
	}
	int count = 3;
	int rowHurdle = 0;
	int colHurdle = 0;
	for (int i = 0; i < numOfHurdles; i++)
	{
		rowHurdle = arr[count];
		++count;
		colHurdle = arr[count];
		++count;
		maze[rowHurdle][colHurdle] = 49;
	}

	for (int i = 0; i < col * 8 + 1; i++)
		cout << "_";
	cout << "\n";
	for (int i = 0; i < row; i++)
	{
		cout << "|";
		for (int j = 0; j < col; j++)
		{
			cout << maze[i][j] << "\t|";
		}
		cout << "\n";
		for (int k = 0; k < col * 8 + 1; k++)
			cout << "_";
		cout << "\n";
	}
}

void Maze::findPath()
{
	char man = 'M';
	int i = 0, j = 0;
	maze[i][j] = man;
	int max = row*col*row*col;
	int count = 0;
	isBlock = false;
	myStack stack1;
	while (maze[row - 1][col - 1] != man && !isBlock)
	{
		if (j + 1 < col && maze[i][j + 1] != 49 && maze[i][j + 1] != 'B')
		{
			stack1.push(i);
			stack1.push(j);
			++j;
			maze[i][j] = man;
			++count;
		}
		else if (i + 1 < row &&  maze[i + 1][j] != 49 && maze[i + 1][j] != 'B')
		{
			stack1.push(i);
			stack1.push(j);
			++i;
			maze[i][j] = man;
			++count;
		}
		else if (i - 1 >= 0 && maze[i - 1][j] != 49 && maze[i - 1][j] != 'B')
		{
			--i;
			maze[i][j] = man;
			++count;

			if (i + 1 < row && maze[i + 1][j - 1] == 49 && maze[i + 1][j - 1] == 'B')
			{
				maze[i + 1][j] = 'B';
			}
			else
			{
				maze[i + 1][j] = 'B';
			}
		}
		else if (j - 1 >= 0 && maze[i][j - 1] != 49 && maze[i][j - 1] != 'B')
		{
			--j;
			maze[i][j] = man;
			++count;
			if (j + 1 < col)
			{
				maze[i][j + 1] = 'B';
			}
		}
		else
			++count;
		if (count > max)
			isBlock = true;
	}

	if (maze[row - 1][col - 1] == man)
	{
		stack1.push(row - 1);
		stack1.push(col - 1);
	}
	while (stack1.size != 0)
	{
		stack.push(stack1.pop());
		stack.push(stack1.pop());
	}
}

void Maze::showCoordinates()
{
	if (!isBlock)
	{
		cout << "\n\nCoordinates are:\n";

		while (stack.size != 0)
		{
			cout << '(' << stack.pop() << ",";
			cout << stack.pop() << ")\n";
		}
		cout << "\n\n";
	}
	else
		cout << "\n\nPath is Blocked.\n\n";
}

int main()
{
	Maze m;
	m.readFromFile();
	cout << "\n\nMaze\n\n";
	m.drawMaze(true);
	m.findPath();
	cout << "\n\nPath Shown\n\n";
	m.drawMaze(false);
	m.showCoordinates();
	return 0;
}