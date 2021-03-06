#ifndef __TREE_H__
#define __THREE_H__

#include "DList.h"
#include "Stack.h"

///Balanced Tree: de cada node en surten dos->cerques m�s �ptimes dintre dels arbres



//crear "VisitAllNodes" en recursiu i iteratiu, en tots els tipus d'ordre; en iteratiu s'utilitza una pila de crides
template <class DATA>
struct treeNode
{
	DATA data;
	treeNode* parent;
	DList<treeNode<DATA>*> children;
	bool halfDone = false;

	treeNode(DATA _data)
	{
		data = _data;
	}

	void Node_PreorderRecursive(DList<DATA>* list) const
	{
		list->Add(data);
		for (unsigned int i = 0; i < children.NodeCounter(); i++)
			children.GetPointer(i)->atr->PreorderRecursive(list);
	}

	void Node_PostorderRecursive(DList<DATA>* list) const
	{

		for (unsigned int i = 0; i < children.NodeCounter(); i++)
			children.GetPointer(i)->atr->Node_PostorderRecursive(list);
		list->Add(data);
	}

	void Node_InorderRecursive(DList<DATA>* list) const
	{
		for (unsigned int i = 0; i < children.NodeCounter() / 2; i++)
			children.GetPointer(i)->atr->Node_InorderRecursive(list);
		list->Add(data);
		for (unsigned int i = children.NodeCounter() / 2; i < (children.NodeCounter()); i++)
			children.GetPointer(i)->atr->Node_InorderRecursive(list);
	}
};

template <class DATA>
class Tree
{
private:
	treeNode<DATA>* rootNode;

public:

	///////////////
	//Constructor//
	///////////////

	Tree(const DATA& dataGiven)
	{
		rootNode = new treeNode<DATA>(dataGiven);
		rootNode->data = dataGiven;
		rootNode->parent = NULL;
	}

	treeNode<DATA>* Add(const DATA& dataGiven)
	{
		treeNode<DATA>* newNode = new treeNode<DATA>(dataGiven);
		rootNode->children.Add(newNode);
		newNode->parent = rootNode;
		return newNode;
	}

	treeNode<DATA>* Add(DATA dataGiven, treeNode<DATA>* parentGiven)
	{
		treeNode<DATA>* newNode = new treeNode<DATA>(dataGiven);
		parentGiven->children.Add(newNode);
		newNode->parent = parentGiven;
		return newNode;
	}

	void Clear(treeNode<DATA>* tmp = NULL)
	{
		if (tmp == NULL)
			tmp = rootNode;

		if (tmp != NULL)
		{
			for (int i = 0; i < tmp->children.NodeCounter(); i++)
			{
				Clear(tmp->children.GetPointer(i)->atr);
			}

			delete tmp;
		}

	}

	//Cerca "Pre-Order: pares->fills"  F B A D C E G I H
	//		"In-Order:	meitat fills->pare->meitat fill	A B C D E F G I H
	//		"Post-Order: fills->pare"	A C E D B H I G F

	//Recursive functions
	void Tree_PreorderRecursive(DList<DATA>* list) const
	{
		rootNode->Node_PreorderRecursive(list);
	}

	void Tree_PostorderRecursive(DList<DATA>* list) const
	{
		rootNode->Node_PostorderRecursive(list);
	}

	void Tree_InorderRecursive(DList<DATA>* list) const
	{
		rootNode->Node_InorderRecursive(list);
	}

	//Iterative functions
	void Tree_PreorderIterative(DList<DATA>* list) const
	{
		Stack<treeNode<DATA>*> newStack;
		treeNode<DATA>* newNode = rootNode;
		while (newNode)
		{
			list->Add(newNode->data);
			for (int i = newNode->children.NodeCounter(); i > 0; i--)
			{
				newStack.Push(newNode->children.GetPointer(i - 1)->atr);
			}
			newNode = newStack.Pop();
		}
	}

	void Tree_PostorderIterative(DList<DATA>* list) const
	{
		Stack<treeNode<DATA>*> primaryStack;
		Stack<treeNode<DATA>*> auxiliarStack;

		treeNode<DATA>* newNode = rootNode;

		while (newNode)
		{
			primaryStack.Push(newNode);

			for (int i = 0; i < newNode->children.NodeCounter(); i++)
			{
				auxiliarStack.Push(newNode->children.GetPointer(i)->atr);
			}

			newNode = auxiliarStack.Pop();
		}

		do
		{
			newNode = primaryStack.Pop();
			if (newNode)
				list->Add(newNode->data);
		} while (newNode);

	}

	void Tree_InorderIterative(DList<DATA>* list) const
	{
		Stack<treeNode<DATA>*> newStack;
		treeNode<DATA>* newNode = rootNode;

		while (newNode)
		{
			if (newNode->halfDone == false)
			{
				for (int i = newNode->children.NodeCounter(); i > newNode->children.NodeCounter() / 2; i--)
				{
					newStack.Push(newNode->children.GetPointer(i - 1)->atr);
				}

				newStack.Push(newNode);
				newNode->halfDone = true;

				for (int i = newNode->children.NodeCounter() / 2 - 1; i >= 0; i--)
				{
					newStack.Push(newNode->children.GetPointer(i)->atr);
				}
			}

			else
			{
				list->Add(newNode->data);
			}

			newNode = newStack.Pop();
		}
	}


};

#endif //__TREE_H__