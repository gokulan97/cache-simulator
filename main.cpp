#include <iostream>
#include <stdio.h>
#include <map>
#include <set>
#include <vector>

using namespace std;

int BLOCK_SIZE;
bool INCLUSIVE;

class Block
{
	public:
		int tag;
		vector<bool> bits;

		Block()
		{
			this->tag = 0;
		}
};

class CacheSet
{
	public:
		int index;
		set<Block> blocks;
		int capacity;
		vector<bool> bits;

		CacheSet(int index, int count)
		{
			this->index = index;
			this->capacity = count;
		}
};

class CacheLevel
{
	public:
		long size;
		int assoc;
		bool replace, write;
		map<int, CacheSet> sets;

		CacheLevel(int size, int assoc, bool replace, bool write)
		{
			this->size = size;
			this->assoc = assoc;
			this->replace = replace;
			this->write = write;

			int setno = size / (assoc * BLOCK_SIZE);

			for(int i=0; i<setno; i++)
			{
				CacheSet s(i, assoc);
				this->sets[i] = s;
			}
		}
};

int main(int argc, char* argv[])
{
	FILE *fp = fopen(argv[1], "r");
	if(fp == NULL)
	{
		cout<<"Error opening file\n";
		return 0;
	}

	int num, incl, block;
	vector<CacheLevel> caches;

	fscanf(fp, "%d %d %d", &num, &incl, &block);
	
	BLOCK_SIZE = block;
	INCLUSIVE = incl;

	long size;
	int assoc, replace, write;

	for(int i=0; i<num; i++)
	{
		fscanf(fp, "%ld %d %d %d", &size, &assoc, &replace, &write);
		caches.push_back(*(new CacheLevel(size, assoc, replace, write)));
	}

	fclose(fp);

	for(int i=0; i<num; i++)
	{
		cout<<caches[i].size<<" ";
	}

}