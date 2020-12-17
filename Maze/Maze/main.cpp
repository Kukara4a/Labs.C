#include<iostream>
#include "Maze.h"
#include "MTreeNode.h"
#include <ctime>
#include <vector>
#include <map>
#include <stack>

using namespace std;

void buildFullMaze(Maze& iMaze, MTreeNode& tree);

int main()
{
	srand(time(NULL));

	int sizeX, sizeY;
	cout << "Enter the dimensions of the maze, first the width, then the height: ";
	cin >> sizeX >> sizeY;

	int i = rand() % sizeY, j;
	if (i == 0 || i == sizeY - 1) j = rand() % sizeX;
	else if (rand() % 2 == 0)j = 0;
	else j = sizeX - 1;

	Maze* iMaze = new Maze(sizeX, sizeY);
	MTreeNode* tree = MTreeNode::beginTree(i, j);

	buildFullMaze(*iMaze, *tree);

	iMaze->printMaze();
	printf("\n");

	int** treeForPrinting = new int* [sizeY];
	for (int k = 0; k <= sizeY; k++)
		treeForPrinting[k] = new int[sizeX];

	int maxDist = -1;
	int sumAllNode = 0;

	for(int y = 0; y < sizeY; y++)
		for (int x = 0; x < sizeX; x++)
		{			
			auto curNode = *(tree->searchNode(*tree, y, x));
			treeForPrinting[y][x] = curNode.distance();
			int dist = curNode.distance();
			sumAllNode = sumAllNode + dist;
			if (maxDist < dist)
				maxDist = dist;
		}

	const char* indent;
	if (sizeX * sizeY <= 100) indent = "%3d";
	else  indent = "%4d";

	for (int i = 0; i < sizeY; i++)
	{
		for (int j = 0; j < sizeX; j++)
			printf(indent, treeForPrinting[i][j]);
		printf("\n");
	}

	cout << endl <<"Maximum weight of the node = " << maxDist << endl;
	cout << "Average weight of the node = " << (sumAllNode/(sizeX*sizeY)) << endl;
}

void buildFullMaze(Maze& iMaze, MTreeNode& tree)
{
	map <tuple<int, int>, bool> pVisit;
	stack <tuple<int, int>> prevPoints;

	int n = iMaze.getN();
	int m = iMaze.getM();

	int i = tree.i(), j = tree.j();
	auto currentNode = &tree;

	while (true)
	{
		if (pVisit.size() == n * m)
			break;

		pVisit[tuple<int, int>(j, i)] = true;

		vector<tuple<int, int>> unvisitedNeighbors;
		for (int y = -1; y <= 1; y++)
			for (int x = -1; x <= 1; x++)
				if (((x == -1 && y == 0) || (x == 1 && y == 0) || (x == 0 && y == 1) || (x == 0 && y == -1)) &&
					j + x >= 0 && i + y >= 0 && j + x < n && i + y < m && pVisit.count(tuple<int, int>(j + x, i + y)) == 0)
					unvisitedNeighbors.push_back(tuple<int, int>(j + x, i + y));
						
		if (unvisitedNeighbors.size() == 0)
		{
			tuple<int, int> point = prevPoints.top();
			prevPoints.pop();
			j = get<0>(point);
			i = get<1>(point);
			currentNode = (MTreeNode*)currentNode->parent();
			continue;
		}

		auto rndpoint = unvisitedNeighbors[rand() % unvisitedNeighbors.size()];

		iMaze.makeConnection(i, j, get<1>(rndpoint), get<0>(rndpoint));		
		prevPoints.push(tuple<int, int>(j, i));
		j = get<0>(rndpoint);
		i = get<1>(rndpoint);

		currentNode->addChild(i, j);
		currentNode = currentNode->hasChild(i, j);
	}
}