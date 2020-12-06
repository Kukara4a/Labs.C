#include<iostream>
#include "Maze.h"
#include "MTreeNode.h"
#include <vector>

using namespace std;

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

	MTreeNode* currentNode = MTreeNode::beginTree(0, 0);
	auto remembNodes = vector<MTreeNode*>(5);
	bool flag = true;

	for (int i = 0; i < 5; i++)	
		for (int j = 0; j < 5; j++)
		{
			if (flag && (i != 0 || j != 0)) currentNode = currentNode->hasChild(i, j);
			else if (i != 0 || j != 0) currentNode = remembNodes[j];
			treeForPrinting[i][j] = currentNode->distance();
			flag = false;
			if (maze->hasConnection(i, j, i, j + 1))
			{
				currentNode->addChild(i, j + 1);
				flag = true;
			}

			if (maze->hasConnection(i, j, i + 1, j))
			{
				currentNode->addChild(i + 1, j);
				remembNodes[j] = currentNode->hasChild(i + 1, j);
			}
		}	
	
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
			cout << treeForPrinting[i][j] << " ";
		cout << endl;
	}
}
