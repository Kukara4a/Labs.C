#pragma once

class MTreeNode
{
private:
	int m_i, m_j;
	MTreeNode* m_parent;
	MTreeNode* m_children;
	int m_distance = -1;
	MTreeNode(MTreeNode* parent);
	MTreeNode();
public:
	int i() const;
	int j() const;
	const MTreeNode* parent() const;
	const MTreeNode* child(int i) const;
	int distance() const;
	int childCount() const;
	bool addChild(int i, int j);
	MTreeNode* hasChild(int i, int j);
	static MTreeNode* beginTree(int i, int j);
};