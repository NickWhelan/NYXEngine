#pragma once
#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <cstddef>
#include <iostream>
#include <string>
#include "pch.h"


using namespace std;

template <class Value, class Key>
class HashTable
{

	struct Node
	{
		Key key;
		Value value;
		Node *next;
		Node *prev;

		Node(const Key& key, const Value& value) : key(key), value(value), next(NULL), prev(NULL) {}
	};

public:

	// An Entry object is returned as the result of a find operation
	class Entry
	{
		friend class HashTable;

		Node *node;

		Entry(Node *node) : node(node) { }

	public:

		Entry() : node(NULL) { }

		bool isValid() const { return node != NULL; }
		const Key getKey() const { return node->key; }
		const Value getValue() const { return node->value; }
		void setValue(const Value& value) { node->value = value; }
	};


	HashTable(size_t sz = 0) : size(0), totalItems(0)
	{
		if (sz > 0)
		{
			//Resize to a prime number
			//Optimized to prevent collision
			size = getNextPrimeNum(sz);
		}

		table = new Node*[size]();
	}

	~HashTable()
	{
		purge();

		delete[] table;
	}

	//Insert value into Hash Table
	Entry insert(const Key& key, const Value& value)
	{
		//Find the hash value
		size_t index = hash(key);
		Node *iter = table[index];
		Node *prev_iter = NULL;

		//No Collision
		if (!iter) {
			table[index] = new Node(key, value);
			++totalItems;

			return table[index];
		}

		//Collision Resolution
		for (; iter; iter = iter->next) {
			if (iter->key >= key) {
				if (key == iter->key) {
					// iter is the node with same key as new key;
					// just update the node's value
					iter->value = value;
					return iter;
				}
				else {
					// iter is the first node with key greater than new key;
					// insert new node before iter
					Node *tmp = new Node(key, value);
					tmp->next = iter;
					tmp->prev = iter->prev;
					// is iter the head?
					if (!iter->prev)
						table[index] = tmp;
					else
						iter->prev->next = tmp;
					iter->prev = tmp;

					++totalItems;

					return tmp;
				}
			}
			// keep track of last non-NULL node visited
			prev_iter = iter;
		}

		// if we get here, than all existing keys were smaller than new key;
		// insert new node at end of list
		Node *tmp = new Node(key, value);
		tmp->prev = prev_iter;
		prev_iter->next = tmp;
		++totalItems;

		return tmp;
	}

	//Remove key entry from Hash Table
	void remove(const Key& key)
	{
		size_t index = hash(key);
		Node *iter;

		// find the entry with this key
		for (iter = table[index]; iter; iter = iter->next) {
			if (iter->key == key)
				// key found
				break;
			else if (iter->key > key)
				// key not found
				return;
		}

		// is this iterator valid?
		if (!iter)
			return;

		//Head of the list
		if (!iter->prev)
			table[index] = iter->next;
		//Tail of list
		else if (!iter->next)
			iter->prev->next = NULL;
		//Middle of list
		else
		{
			iter->next->prev = iter->prev;
			iter->prev->next = iter->next;
		}

		--totalItems;

		delete iter;
	}

	//Search for a key in the Hash Table
	Entry find(const Key& key)
	{
		size_t index = hash(key);
		Node *iter;

		for (iter = table[index]; iter; iter = iter->next) {
			if (iter->key == key)
				return iter;
			else if (iter->key > key)
				return NULL;
		}
		return NULL;
	}

	//Implement the resize member function
	// ENTER CODE IN THIS METHOD
	void resize()
	{
		//Copy current table
		Node** copy = table;

		//Keep track of old size
		size_t oldSize = getSize();

		//Resize to double the old size
		size = getNextPrimeNum(oldSize * 2);

		//Create table with new size
		table = new Node*[size]();

		//Insert old entries into new table
		for (size_t i = 0; i < oldSize; i++) {
			for (Node* iter = copy[i]; iter != NULL; iter = iter->next) {
				insert(iter->key, iter->value);
			}
		}

		//Delete all nodes for each table index
		for (size_t i = 0; i < oldSize; i++) {
			for (Node* iter = copy[i]; iter != NULL;) {
				Node* tmp = iter;
				iter = iter->next;
				delete tmp;
			}
		}

		//Delete old table
		delete[] copy;
	}

	void purge()
	{
		for (size_t i = 0; i<size; i++) {
			Node *iter = table[i];
			while (iter) {
				Node *tmp = iter;
				iter = iter->next;
				delete tmp;
			}
			table[i] = NULL;
		}

		size = 0;
		totalItems = 0;
	}

	//Prints all entries
	void print() const
	{
		for (size_t i = 0; i<size; i++)
			for (Node *iter = table[i]; iter; iter = iter->next) {
				printEntry(iter);
				cout << endl;
			}
		cout << endl;
	}

	//Prints a single entry
	void printEntry(const Node *entry) const
	{
		if (entry)
			cout << entry->key << ":" << entry->value;
	}

	//Prints the table structure
	void printTable() const
	{
		for (size_t i = 0; i<size; i++) {
			cout << i << ":\t";
			Node *iter = table[i];
			printEntry(iter);
			if (iter) iter = iter->next;
			for (; iter; iter = iter->next) {
				cout << ", ";
				printEntry(iter);
			}
			cout << endl;
		}
		cout << endl;
	}

	size_t getSize()
	{
		return size;
	}

	size_t getTotalItems()
	{
		return totalItems;
	}

private:
	//An array of pointers to Nodes
	Node **table;

	//Number of table slots
	size_t size;

	//Number of items
	size_t totalItems;

	//The hash function
	size_t hash(const Key& str)
	{
		size_t hash = 0;

		//Iterates through each character within the key
		for (size_t i = 0; i<str.length(); i++)
			hash = hash * 256 + str[i];
		return hash % size;
	}

	//Determines whether val is a prime number
	bool isNumPrime(size_t val)
	{
		for (size_t i = 2; (i * i) <= val; i++)
		{
			if ((val % i) == 0)
				return false;
		}

		return true;
	}

	//Determines the next prime number closest to val
	size_t getNextPrimeNum(size_t val)
	{
		size_t i;

		for (i = val + 1; ; i++)
		{
			if (isNumPrime(i))
				break;
		}

		return i;
	}
};

#endif // HASHTABLE_H