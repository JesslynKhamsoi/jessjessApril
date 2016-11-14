#pragma once
//***************************************************************************//
//**
//**  Simple Heap implementation - With solution
//**    Copyright 2016 - Aaron S. Crandall
//**
//**
//***************************************************************************//

#ifndef HEAP_H
#define HEAP_H

#include <vector>
#include <stdexcept>      // std::out_of_range
using namespace std;

template<typename T>
class Heap
{
private:
	vector<T> _items;

	void buildHeap()
	{
		for (int i = _items.size() / 2; i >= 0; i--)
		{
			adjustHeap(i);
		}
	}


	//MA TODO: Implement adjustHeap!
	//Percolates the item specified at by index down into its proper location within a heap.
	// Used for dequeue operations and array to heap conversions
	void adjustHeap(int index)
	{
		int size = _items.size();
		if (size == 0) // if vector is empty return
		{
			return;
		}
		int child = 0;
		T temp = std::move(_items[index]);
		for (; size > index * 2 + 1; index = child) //children of each element is = to it's index *2 +1
		{
			child = index * 2 + 1;
			if ((child != size - 1)&&(_items[child] > _items[child + 1])) 
				//if current child is not the last in the vector & its value is greater than its sibling, its sibling becomes the child
			{
				child++;
			}
			if (temp > _items[child])
			{
				_items[index] = std::move(_items[child]); //percolate down one step
			}
			else { break; } //if no swap was needed break the loop
		}
		_items[index] = std::move(temp); //setting the last swap of the downwards percolation
	
		// The ONLY code you'd need to do for this MA would be in this function call
	}


public:
	Heap()
	{
	}

	Heap(const vector<T> &unsorted)
	{
		for (int i = 0; i < unsorted.size(); i++)
		{
			_items.push(unsorted[i]);
		}
		buildHeap();
	}

	//Adds a new item to the heap
	void insert(T item)
	{ 

		//calculate positions
		int current_position = _items.size() ;
		int parent_position = (current_position - 1) / 2;

		//insert element (note: may get erased if we hit the WHILE loop)
		_items.push_back(item);
		
		//get parent element if it exists
		T *parent = nullptr;
		if (parent_position >= 0)
		{
			parent = &_items[parent_position];
		}

		//only continue if we have a non-null parent
		if (parent != nullptr)
		{
			//bubble up
			while (current_position > 0 && item < *parent)
			{
				_items[current_position] = *parent;
				current_position = parent_position;
				parent_position = (current_position - 1) / 2;
				if (parent_position >= 0)
				{
					parent = &_items[parent_position];
				}
			}

			//after finding the correct location, we can finally place our item
			_items[current_position] = item;
		}
	}


	//Returns the top-most item in our heap without actually removing the item from the heap
	T& getFirst()
	{
		if (size() > 0)
			return _items[0];
		else
			throw std::out_of_range("No elements in Heap.");
	}


	//Removes the top-most item from the heap and returns it to the caller
	T deleteMin()
	{
		int last_position = _items.size() - 1;
		T last_item = _items[last_position];
		T top = _items[0];
		_items[0] = last_item;
		_items.erase(_items.begin() + last_position);

		//percolate down
		adjustHeap(0);
		return top;
	}


	// Returns true if heap is empty, false otherwise
	bool isEmpty() const
	{
		return _items.size() == 0;
	}


	// Return size (N) of the Heap
	int size() const
	{
		return _items.size();
	}

	// Simple debugging print out
	void printAll() const
	{
		for (int i = 0; i < _items.size(); i++)
		{
			cout << "  [x] Heap element [" << i << "]. key=" << _items[i] << endl;
		}
	}
};

#endif
