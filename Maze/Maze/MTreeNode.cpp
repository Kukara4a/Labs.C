#include "MTreeNode.h"

MTreeNode::MTreeNode() {}

MTreeNode::MTreeNode(MTreeNode* parent)
{
	m_parent = parent;
	m_children = new MTreeNode[3];
	if (parent != nullptr)
		m_distance = parent->m_distance + 1;
}

int MTreeNode::i() const
{
	return m_i;
}

int MTreeNode::j() const
{
	return m_j;
}

const MTreeNode* MTreeNode::parent() const
{
	return m_parent;
}

const MTreeNode* MTreeNode::child(int i) const
{
	return &(m_children[i]);
}

int MTreeNode::distance() const
{
	return m_distance;
}

int MTreeNode::childCount() const
{		
	int result = 0;
	for (int i = 0; i < 3; i++)
		if (m_children[i].m_distance != -1)
			result = result + 1;
	return result;
}

bool MTreeNode::addChild(int i, int j)
{
	MTreeNode child = MTreeNode(this);
	child.m_i = i;
	child.m_j = j;	
	m_children[childCount()] = child;
	return true;
}

MTreeNode* MTreeNode::hasChild(int i, int j)
{
	for (int k = 0; k < 3; k++)
	{
		MTreeNode* child = &m_children[k];
		if (child->m_i == i && child->m_j == j)
			return child;
	}
}

MTreeNode* MTreeNode::beginTree(int i, int j)
{
	MTreeNode* Tree = new MTreeNode(nullptr);
	Tree->m_j= j;
	Tree->m_i = i;
	Tree->m_distance = 0;
	return Tree;
}
