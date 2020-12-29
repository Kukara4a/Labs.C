#include<iostream>
#include <ctime>
#include <vector>
#include "Maze.h"
#include "MTreeNode.h"

using namespace std;

void buildFullMaze(Maze& iMaze, MTreeNode& tree);
void printTree(int sizeY, int sizeX, int** treeForPrinting);

int main()
{
	setlocale(LC_ALL, "Russian");
	srand(time(NULL));

	int sizeX, sizeY;																	//setting the size of the maze
	cout << "Enter the dimensions of the maze, first the width, then the height: "; 
	cin >> sizeX >> sizeY;

	int i = rand() % sizeY, j;															//generate random coordinates of the entrance to maze
	if (i == 0 || i == sizeY - 1) j = rand() % sizeX;
	else if (rand() % 2 == 0)j = 0;
	else j = sizeX - 1;

	Maze iMaze = Maze(sizeX, sizeY);													//creating a maze and a tree
	MTreeNode tree = *MTreeNode::beginTree(i, j);

	buildFullMaze(iMaze, tree);															//building a random maze and tree

	iMaze.printMaze();																	//output maze to the console
	printf("\n");

	int** treeForPrinting = new int* [sizeY];											//creating an array 
	for (int k = 0; k <= sizeY; k++)													//to output tree weights to the console
		treeForPrinting[k] = new int[sizeX];

	int maxDist = -1;																	//count the maximum weight and the average weight
	int sumAllNode = 0;

	for (int y = 0; y < sizeY; y++)
		for (int x = 0; x < sizeX; x++)
		{
			auto curNode = tree.searchNode(tree, y, x);
			treeForPrinting[y][x] = curNode->distance();
			int dist = curNode->distance();
			sumAllNode = sumAllNode + dist;
			if (maxDist < dist)
				maxDist = dist;
		}

	printTree(sizeY, sizeX, treeForPrinting);											//output tree to the console

	cout << endl << "Maximum weight of the node = " << maxDist << endl;					//output maximum weight and average weight on the console
	cout << "Average weight of the node = " << (sumAllNode / (sizeX * sizeY)) << endl;
}

void printTree(int sizeY, int sizeX, int** treeForPrinting)
{
	const char* indent;
	if (sizeX * sizeY <= 100) indent = "%3d";
	else  indent = "%4d";

	for (int i = 0; i < sizeY; i++)
	{
		for (int j = 0; j < sizeX; j++)
			printf(indent, treeForPrinting[i][j]);
		printf("\n");
	}
}

void buildFullMaze(Maze& iMaze, MTreeNode& tree)
{
	MTreeNode* currentNode = &tree;

	while (currentNode != nullptr)
	{
		int i = currentNode->i();
		int j = currentNode->j();
		auto possibleDirections = new vector<int>(); //0 - up, 1 - right, 2 - down, 3 - left

		if (!(!iMaze.cellInMaze(i - 1, j)										
			|| iMaze.hasConnection(i - 1, j, i - 2, j) || iMaze.hasConnection(i - 1, j, i, j)
			|| iMaze.hasConnection(i - 1, j, i - 1, j - 1) || iMaze.hasConnection(i - 1, j, i - 1, j + 1)))
			possibleDirections->push_back(0);
		if (!(!iMaze.cellInMaze(i, j + 1)
			|| iMaze.hasConnection(i, j + 1, i - 1, j + 1) || iMaze.hasConnection(i, j + 1, i + 1, j + 1)
			|| iMaze.hasConnection(i, j + 1, i, j) || iMaze.hasConnection(i, j + 1, i, j + 2)))
			possibleDirections->push_back(1);
		if (!(!iMaze.cellInMaze(i + 1, j)
			|| iMaze.hasConnection(i + 1, j, i, j) || iMaze.hasConnection(i + 1, j, i + 2, j)
			|| iMaze.hasConnection(i + 1, j, i + 1, j - 1) || iMaze.hasConnection(i + 1, j, i + 1, j + 1)))
			possibleDirections->push_back(2);
		if (!(!iMaze.cellInMaze(i, j - 1)
			|| iMaze.hasConnection(i, j - 1, i - 1, j - 1) || iMaze.hasConnection(i, j - 1, i + 1, j - 1)
			|| iMaze.hasConnection(i, j - 1, i, j - 2) || iMaze.hasConnection(i, j - 1, i, j)))
			possibleDirections->push_back(3);

		if (!possibleDirections->empty())
		{
			int randomDirection = possibleDirections->at(rand() % possibleDirections->size());

			switch (randomDirection)
			{
			case 0:
				currentNode->addChild(i - 1, j);
				currentNode = currentNode->hasChild(i - 1, j);
				iMaze.makeConnection(i, j, i - 1, j);
				continue;
			case 1:
				currentNode->addChild(i, j + 1);
				currentNode = currentNode->hasChild(i, j + 1);
				iMaze.makeConnection(i, j, i, j + 1);
				continue;
			case 2:
				currentNode->addChild(i + 1, j);
				currentNode = currentNode->hasChild(i + 1, j);
				iMaze.makeConnection(i, j, i + 1, j);
				continue;
			case 3:
				currentNode->addChild(i, j - 1);
				currentNode = currentNode->hasChild(i, j - 1);
				iMaze.makeConnection(i, j, i, j - 1);
				continue;
			default:
				break;
			}
		}
		else currentNode = (MTreeNode*)currentNode->parent();
	}
}