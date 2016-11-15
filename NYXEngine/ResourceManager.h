#pragma once
#include "HashTable.h"
#include <vector>
#include <iostream>
#include "pch.h"

#ifndef RESOURCEMANAGER_H
#define RESOURCEMANGER_H

template<class Resource>
class ResourceHandle
{
private:
	int		index;
public:
	/*
	* Parameterless constructor which creates a NULL resource handle.
	*/
	ResourceHandle() :
		index(-1) {}

	/*
	* Constructor which creates a handle to reference the indicated index.
	* @param idx The index of the resource in the ResourceManager.
	*/
	ResourceHandle(int idx) :
		index(idx) {}

	/**
	* Determines if this is a NULL handle which references nothing.
	* @returns true if this is a NULL handle
	*/
	bool isNull() const
	{
		return index < 0;
	}

	/**
	* Change this handle into a NULL handle which references nothing.
	*/
	void nullify()
	{
		index = -1;
	}

	/**
	* Return the current index value.
	* @returs the current value of the handle index.
	*/
	int getIndex() const
	{
		return index;
	}

	/**
	* The assigment operator.
	*/
	ResourceHandle& operator=(ResourceHandle& other)
	{
		index = other.index;
		return *this;
	}

	/**
	* Equality operator.
	*/
	bool operator==(ResourceHandle& other) const
	{
		return index == other.index;
	}

	/**
	* Inequality operator.
	*/
	bool operator!=(ResourceHandle& other) const
	{
		return index != other.index;
	}

	/**
	* less than operator
	*/
	bool operator<(ResourceHandle& other) const
	{
		return index < other.index;
	}

	friend std::ostream& operator<<(std::ostream& os, ResourceHandle &hndl);
};

template<class Resource>
class ResourceManager
{
private:
	HashTable<std::string, ResourceHandle<Resource>> *table;
	char test = 'a';

public:
	ResourceManager()
	{
		table = new HashTable<std::string, Resource>(1);
		table->insert("Beep", test);
	}
	ResourceManager(int size)
	{
		table = new HashTable<std::string, Resource>(size);
		table->insert("Beep", test);
	}

	~ResourceManager()
	{
		if (*table != NULL)
		{
			delete table;
			table = NULL;
		}
	}
};
#endif // !RESOURCEMANAGER_H