#include "MTreeNode.h"
#include <vector>

using namespace std;

MTreeNode::MTreeNode(MTreeNode* parent = nullptr)
{
	m_parent = parent;
	m_distance = parent == nullptr ? 0 : parent->distance() + 1;
}

bool MTreeNode::addChild(int i, int j)
{
	for (int k = 0; k < childCount(); k++)
	{
		MTreeNode* child = m_children[k];
		if (child -> m_i == i && child -> m_j == j)
			return false;
	}

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
		auto& curNode = m_children[k];
		if (curNode->m_i == i && curNode->m_j == j)
			return curNode;
	}
	return nullptr;
}

MTreeNode* MTreeNode::beginTree(int i, int j)
{
	MTreeNode* tree = new MTreeNode();
	tree->m_j = j;
	tree->m_i = i;
	return tree;
}

bool elementInVector(vector<int> vect, int element)
{
	for (int i = 0; i < vect.size(); i++)
		if (vect[i] == element)
			return true;

	return false;
}

MTreeNode* MTreeNode::searchNode(MTreeNode& tree, const int i, const int j)
{
	auto currentNode = &tree;			//у меня тут была рекурсия, посторался переделать её в цикл
	auto visitedP = vector<int>();		

	if (tree.m_i == i && tree.m_j == j) 
		return &tree;

	bool flag;
	while (true)
	{
		flag = false;
		if (currentNode->childCount() > 0)
		{
			auto result = currentNode->hasChild(i, j);
			if (result != nullptr)
				return result;

			for (auto node : currentNode->m_children)
				if (!elementInVector(visitedP, node->m_i * 100 + node->m_j))
				{
					visitedP.push_back(node->m_i * 100 + node->m_j);
					currentNode = node;
					flag = true;
					break;
				}
			if (flag) continue;
		}
		currentNode = currentNode->parent();
	}
}
