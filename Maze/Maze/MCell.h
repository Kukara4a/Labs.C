#pragma once

class MCell
{
	friend class Maze;
private:
	bool m_down = false;
	bool m_right = false;
	MCell();
public:
	bool right();
	bool down();
};
