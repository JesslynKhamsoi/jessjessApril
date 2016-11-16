#include "dictionary.h"
Word::Word(string newName, string newDef)
{
	name = newName;
	def = newDef;
}
int Word:: key(int tableSize, const string &vocab)
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
Dictionary::Dictionary(int newSize)
{
	std::vector<Word> link;
	size = newSize;
	for (int i = 0; i < size; i++)
	{
		chains.push_back (link); //setting vector or "hashtable" to number of size pointers
	}
}
void Dictionary :: insert(Word & vocab)
{
	int index = vocab.key(size, vocab.name);

		chains[index].push_back(vocab);
		if (size / counter() == 1)
		{
			rehash();
		}
}
int Dictionary:: counter() //counts words in dictionary
{
	int wordCount = 0;
	
	for (int i = 0; i < size; i++)
	{
	
			int length = chains[i].size();
			wordCount += length;
		
	}
	return wordCount;
}
void Dictionary::parser(string f)
{
	string line;
	string def;
	fstream dictionary_base(f);

	if (dictionary_base.is_open())
	{
		cout << "dictionary is opened bish.\n";
		while (getline(dictionary_base, line, '"'))
		{
			getline(dictionary_base, line, '"');
			//line[line.size() - 1] = '\0'; // changes last index to null character instead of '"'
			getline(dictionary_base, def, '"');
			getline(dictionary_base, def, '}');
			//def = def.substr[def.begin(), def.length() - 1];
			//getline(dictionary_base, def, '"'); //qoutes are cut off.
			def[def.size() - 1] = '\0';
		
			Word *pword = new Word(line, def);
			insert(*pword);
			
			//bool has = contains("CHILOSTOMATOUS");// testing contains - works af;
			//if(has == true)
			//{
			//	cout << "the word exists";
			//}
		}
		cout <<"Number of words: "<< counter();
		cout << "Table size: " << size;
		cout << "Load factor: " << (size / counter());
	}

	dictionary_base.close();
}
bool Dictionary::contains(string word)
{
	Word *temp = new Word(word, " ");
	int hashVal = temp->key(size, word); //find index of vector to search
	std::vector <Word> fakeVec = chains[hashVal];
	for (int i = 0; i < fakeVec.size(); i++)
	{
		
		int k = (fakeVec[i].name).compare(word);
		if ((fakeVec[i].name).compare(word) == 0)
		{
			cout << fakeVec[i].def;
			return true;
		}
	}
	
	return false;
}
int Dictionary::findNextPrime(int n)
{
	bool isPrime = false;
	while (isPrime == false)
	{
		n++;
		isPrime = true;
		for (int i = 2; i < n / 2; i++)
		{
			if (n % i == 0)
			{
				isPrime = false;
			}
		}
	}
	cout << "The next prime is " << n;
	return n;
}
void Dictionary:: rehash()
{
	std::vector <std::vector<Word>> copy = chains;
	size = findNextPrime(2 * size);
	chains.resize(size);
	for (auto & thisVec : chains)
	{
		thisVec.clear();
	}
	for (auto & thisVec : copy)
	{
		for (auto & x : thisVec)
		{
			insert(x);
		}
	}
}

//named this funtion remover instead of delete to not confuse with the already existing delete funtion
Word* Dictionary:: remover(string word) // help with this one
{
	
	Word * tmp = new Word(word, " ");
	std::vector <Word> fakeVec = chains[tmp->key(size, word)];
//find the item

	for (int i = 0; i < fakeVec.size(); i++)
	{
		if ((fakeVec[i].name).compare(word) == 0)
		{
			fakeVec.erase(fakeVec.begin() + i);// :( why
			return tmp;
		}
	}
	return nullptr;
}