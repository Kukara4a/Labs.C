#include "MTreeNode.h"

MTreeNode::MTreeNode(MTreeNode* parent)
{
	m_i = 0;
	m_j = 0;
	m_parent = parent;
	m_children = vector<MTreeNode*>();
	m_distance = parent == nullptr ? 0 : parent->distance() + 1;
}

bool MTreeNode::addChild(int i, int j)
{
	MTreeNode* child = new MTreeNode(this);
	child->m_i = i;
	child->m_j = j;
	m_children.push_back(child);
	return true;
}

MTreeNode* MTreeNode::hasChild(int i, int j)
{
	for (int k = 0; k < childCount(); k++)
	{
		auto curNode = m_children[k];
		if (curNode->m_i == i && curNode->m_j == j)
			return curNode;
	}
	return nullptr;
}

MTreeNode* MTreeNode::beginTree(int i, int j)
{
	MTreeNode* tree = new MTreeNode(nullptr);
	tree->m_j = j;
	tree->m_i = i;
	return tree;
}

MTreeNode* MTreeNode::searchNode(const MTreeNode& tree, const int i, const int j)
{
	if (i == tree.m_i && j == tree.m_j)
		return &(MTreeNode)tree;

	if (tree.childCount() > 0)
	{
		auto result = ((MTreeNode)tree).hasChild(i, j);
		if (result != nullptr)
			return result;

		for (auto node : tree.m_children)
		{
			auto result = searchNode(*node, i, j);
			if (result != nullptr)
				return result;
		}
	}

	return nullptr;
}
