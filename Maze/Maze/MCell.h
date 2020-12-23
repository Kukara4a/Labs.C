#pragma once

class MCell
{
	friend class Maze;
public:
	bool right() const { return m_right; }
	bool down() const { return m_down; }
private:
	bool m_down = false;
	bool m_right = false;
	MCell() = default;
};
