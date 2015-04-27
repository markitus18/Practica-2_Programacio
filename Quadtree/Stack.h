#ifndef __STACK_H__
#define __STACK_H__

#include <stdlib.h>
#include <assert.h>
#include "Globals.h"

#define BLOCK_SIZE 16

template <class DATA>
class Stack
{
private:

	DATA* data;
	unsigned int allocatedMemory;
	unsigned int numElements;

public:

	////////////////
	//Constructors//
	////////////////

	Stack()
	{
		data = new DATA[BLOCK_SIZE];
		allocatedMemory = BLOCK_SIZE + 1;
		numElements = 0;
	}


	///////////////
	//Destructor//
	///////////////

	~Stack()
	{
		delete[] data;
	}

	///////////////////
	//Data Management//
	///////////////////

	void Push(DATA value) //afegir un valor al final
	{
		if (numElements + 1 >= allocatedMemory)
			Reallocate(allocatedMemory + BLOCK_SIZE);
		numElements++;
		data[numElements - 1] = value;
	}

	DATA Pop() //esborra l'ultim valor
	{
		if (numElements > 0)
		{
			DATA value = data[numElements - 1];

			numElements--;

			return value;
		}
		return NULL;
	}

	const DATA Pick(int position) const
	{
		assert(position < numElements);
		return data[position];
	}


private:

	void Reallocate(const unsigned int newMemorySize)
	{
		DATA* newData = new DATA[allocatedMemory + BLOCK_SIZE];

		allocatedMemory += BLOCK_SIZE;

		for (unsigned int i = 0; i < allocatedMemory; i++)
		{
			newData[i] = data[i];
		}

		delete[]data;
		data = new DATA[allocatedMemory];
		data = newData;
	}

};

#endif //__STACK_H__