#pragma once
#include <iostream>
#include<fstream>
#include "string"
#include <vector>
using std::string;
using std::ifstream;
using namespace std;

class Word
{
public:
	Word(string newName = "", string newDef = "" ); //constructor
	int key(int tableSize, const string &vocab); //finds key value of each Word
	string name; //word
	string def; //definition
	
};
class Dictionary //hashTable
{
public:
	Dictionary( int curSize = 101); //constructor, with original HashTable size 101
	void parser(string f); //get words to pass into insert from .json file
	double counter(); //counts Words in HashTable
	void insert(Word &vocab); //inserts Words into HashTable
	int findNextPrime(int n);//used gitHub help suggested in assignment
	Word* remover (string word); //removes element
	bool contains(string word); //searches for an element
	void rehash(); //rehashes hashTable
private:
	int size; //HashTable size

	std::vector<std::vector<Word> > chains; // a vector of vectors of Words - HashTable
};