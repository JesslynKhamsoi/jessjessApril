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
	Word(string newName = "", string newDef = "" );
	//Word(const Word &w);
	//~Word();
	int key(int tableSize, const string &vocab);
	string name;
	string def;
	
};
class Dictionary
{
public:
	Dictionary( int curSize = 101);
	//Dictionary(const Dictionary &d);
	//~Dictionary();
	void parser(string f); //get words to pass into insert
	int counter(); //done
	void insert(Word &vocab); //done
	int findNextPrime(int n);//used gitHub help suggested in assignment
	Word remover (string word); //halp!
	bool contains(string word);
	void rehash();
private:
	int size;

	std::vector<std::vector<Word> > chains; // a vector of vectors of Words
};