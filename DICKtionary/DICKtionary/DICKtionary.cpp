#include "dictionary.h"
Word::Word(string newName, string newDef) //word class constructor
{
	name = newName;
	def = newDef;
}
int Word:: key(int tableSize, const string &vocab) //finds key value for hasing, reffered to book example
{
	unsigned int key = 0;
	for (char ch : vocab)
	{
		if (ch != 0)
		{
			key = 37 * key +ch;
		}
	}
	return key % tableSize;
}
Dictionary::Dictionary(int newSize) // initializes table with 101 empty vectors, also Dictionary constructor
{
	std::vector<Word> link;
	size = newSize;
	for (int i = 0; i < size; i++)
	{
		chains.push_back (link); 
	}
}
void Dictionary :: insert(Word & vocab) //inserts Words
{
	int index = vocab.key(size, vocab.name); //finds which vector in table to insert to

		chains[index].push_back(vocab); // pushes word into the correct vector
		if (size / counter() == 1) //rehash if necessary
		{
			rehash();
		}
}
double Dictionary:: counter() //counts words in dictionary
{
	double wordCount = 0;
	
	for (int i = 0; i < size; i++) //goes through all vectors
	{
			int length = chains[i].size(); //counts elements in vector in index i of the hashTable
			wordCount += length;
	}
	return wordCount;
}
void Dictionary::parser(string f) //coded my own .json parser
{
	string line; //word
	string def; //definition
	fstream dictionary_base(f); //.json file

	if (dictionary_base.is_open()) //if file opened
	{
		while (getline(dictionary_base, line, '"')) //while not at end of file read until next '"'
		{
			getline(dictionary_base, line, '"'); //reading in word, not including qoutation marks
			
			getline(dictionary_base, def, '"'); // characters inbetween word and def.
			getline(dictionary_base, def, '}');  //reading in definition
	
			def[def.size() - 1] = '\0'; // adding null to end of definition to take of qoutation marks
		
			Word *pword = new Word(line, def); // creating new word with new word, and def
			insert(*pword); // insert new word into has table
			
		
		}
		//printting out dictionary infor before going into qeuery mode
		cout <<"\nNumber of words: "<< counter(); 
		cout << "\nTable size: " << size;
		cout << "\nLoad factor: " << (counter()/size);
	}

	dictionary_base.close(); //close file
}
bool Dictionary::contains(string word) //returns true if word is found
{
	Word *temp = new Word(word, " "); //create new word with string value of the parameter
	int hashVal = temp->key(size, word); //find index of vector to search
	std::vector <Word> fakeVec = chains[hashVal]; // create copy of vector we are going to search
	for (int i = 0; i < fakeVec.size(); i++)
	{
		if ((fakeVec[i].name).compare(word) == 0) //if words are the same, print definition and return true
		{
			cout << fakeVec[i].def;
			return true;
		}
	}
	
	return false; // word not found
}
int Dictionary::findNextPrime(int n) //finds next prime for rehashing, reffered example provided in assignment
{
	bool isPrime = false;
	while (isPrime == false) 
	{
		n++; // increment n
		isPrime = true; //assume n is the next prime
		for (int i = 2; i < n / 2; i++)
		{ //if n is divisible by number 2 through itself divided by two it is not prime
			if (n % i == 0)
			{
				isPrime = false; //n is now not prime
			}
		}
	}
	return n; //reutrn next prime
}
void Dictionary:: rehash() //resizes and gives values new places in hash table
{
	std::vector <std::vector<Word>> copy = chains; // make copy of hash table
	size = findNextPrime(2 * size); //this will be the new size, twice as large and still prime
	chains.resize(size);
	for (auto & thisVec : chains) //clearing all vectors in hash table
	{
		thisVec.clear();
	}
	for (auto & thisVec : copy)
	{
		for (auto & x : thisVec) //replacing values into larger array
		{
			insert(x);
		}
	}
}

//named this funtion remover instead of delete to not confuse with the already existing delete funtion
Word* Dictionary:: remover(string word) 
{
	
	Word * tmp = new Word(word, " "); //create new Word with same word
	std::vector <Word> fakeVec = chains[tmp->key(size, word)]; //create copy of vector word is in
//find the item

	for (int i = 0; i < fakeVec.size(); i++)
	{
		if ((fakeVec[i].name).compare(word) == 0)
		{
			fakeVec.erase(fakeVec.begin() + i);// if word is found, delete it
			chains[tmp->key(size, word)] = fakeVec; //copy updated vecotr to hash table, swaping the old and new vector
			return tmp;
		}
	}
	return nullptr;
}