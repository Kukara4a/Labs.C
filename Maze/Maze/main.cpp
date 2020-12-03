#include<iostream>
#include "Maze.h"
#include "MTreeNode.h"

using namespace std;

void creatingTree(MTreeNode* currentNode, Maze* maze, int i, int j, int** ar5x5);

int main()
{
	auto maze = new Maze(5, 5);
	int x = 0;
	int y = 1;
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			if ((j == x && x < 4) || (j == y && y < 4))
			{
				maze->makeConnection(i, j, i, j + 1);
				maze->makeConnection(i, j, i + 1, j);
			}
			if (((j == 0 || j == 1) && i < 4) || ((j == 2 || j == 4) && i == 3  ))
				maze->makeConnection(i, j, i + 1, j);
			if ((i == 0 && (j == 3 || j == 2)) || (j == 3 && i == 1))
				maze->makeConnection(i, j, i, j + 1);
		}
		x = x + 1;
		y = y + 1;
	}

	maze->printMaze();
	cout << endl;

	int** treeForPrinting = new int*[5];
	for (int i = 0; i < 5; i++)
		treeForPrinting[i] = new int[5];

	MTreeNode* tree = MTreeNode::beginTree(0, 0);
	creatingTree(tree, maze, 0, 0, treeForPrinting);

	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
			cout << treeForPrinting[i][j] << " ";
		cout << endl;
	}
}

void creatingTree(MTreeNode* currentNode, Maze* maze, int i, int j, int** ar5x5)
{
	ar5x5[i][j] = currentNode->distance();
	if (maze->hasConnection(i, j, i, j + 1))
	{
		currentNode->addChild(i, j + 1);
		creatingTree(currentNode->hasChild(i, j + 1), maze, i, j + 1, ar5x5);
	}

	if (maze->hasConnection(i, j, i + 1, j))
	{
		currentNode->addChild(i + 1, j);
		creatingTree(currentNode->hasChild(i + 1, j), maze, i + 1, j, ar5x5);
	}
}

