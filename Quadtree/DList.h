#ifndef __DLIST_H__
#define __DLIST_H__

#include <stdlib.h>
#include <Windows.h>

#include "Globals.h"

template <class TYPE>
struct dnode
{
	TYPE atr;
	dnode* previous;
	dnode* next;
};

template <class TYPE>
class DList
{
public:

	dnode<TYPE>* start;
	dnode<TYPE>* end;

public:

	DList()
	{
		start = NULL;
		end = NULL;
	}

	~DList(){ DelList(); }


	unsigned int NodeCounter()
	{
		int counter = 0;
		if (start != NULL && end != NULL)
		{
			dnode<TYPE>* tmp = new dnode<TYPE>;
			tmp = start;
			counter = 1;
			while (tmp->next != NULL)
			{
				counter++;
				tmp = tmp->next;
			}
		}

		return counter;
	}

	void Add(TYPE atrToAdd)
	{
		dnode < TYPE >* dnodeX = new dnode < TYPE >;

		if (start != NULL && end != NULL)
		{
			end->next = dnodeX;
		}
		else
		{
			start = dnodeX;
		}
		dnodeX->previous = end;
		dnodeX->next = NULL;
		end = dnodeX;
		dnodeX->atr = atrToAdd;
	}


	dnode<TYPE>* GetPointer(int dnodeN)
	{
		if (start != NULL && end != NULL)
		{
			int counter = 0;
			dnode<TYPE>* tmp = new dnode<TYPE>;
			tmp = start;
			while (tmp->next != NULL && counter < dnodeN)
			{
				tmp = tmp->next;
				counter++;
			}
			if (counter == dnodeN)
				return tmp;
		}
	}

	void DelNode(dnode<TYPE>* del)
	{
		if (del != NULL && start != NULL && end != NULL)
		{
			if (del->previous != NULL)
			{
				del->previous->next = del->next;
			}
			else
				start = del->next;
			if (del->next != NULL)
			{
				del->next->previous = del->previous;
			}
			else
				end = del->previous;
		}
	}

	unsigned int DelNodes(const int position, const int nodes)
	{
		if (start != NULL && end != NULL)
		{
			if (position < NodeCounter())
			{
				int counter;
				for (counter = 0; counter < MIN(nodes, NodeCounter()); counter++)
				{
					DelNode(GetPointer(position + counter));
				}
				return counter + 1;
			}

		}
		return 0;
	}

	void DelList()
	{
		while (start != NULL && end != NULL)
		{
			end = start;
			start = start->next;
			delete[]end;
		}
		end = start;
	}
};

#endif //__SLIST_H__