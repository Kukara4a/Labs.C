#pragma once
#include <vector>

using namespace std;

class MTreeNode
{
public:
	int i() const { return m_i; }
	int j() const { return m_j; }
	const MTreeNode* parent() const { return m_parent; }
	const MTreeNode* child(int i) const { return m_children[i]; }
	int distance() const { return m_distance; }
	int childCount() const { return m_children.size(); }
	bool addChild(int i, int j);
	MTreeNode* hasChild(int i, int j);
	static MTreeNode* beginTree(int i, int j);
	MTreeNode* searchNode(const MTreeNode& tree, const int i, const int j);
private:
	int m_i = 0, m_j = 0;
	MTreeNode* m_parent = nullptr;
	vector<MTreeNode*> m_children = vector<MTreeNode*>();
	int m_distance = 0;
	MTreeNode(MTreeNode* parent);
};
