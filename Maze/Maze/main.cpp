#include "Maze.h"

int main()
{
	auto maze = new Maze(5, 5);
	int x = 0;
	int y = 1;
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			if (j == x)
				maze->makeConnection(i, j, i, j + 1);
			if (j == y)
				maze->makeConnection(i, j, i + 1, j);
		}
		x = x + 1;
		y = y + 1;
	}

	maze->printMaze();	
}
