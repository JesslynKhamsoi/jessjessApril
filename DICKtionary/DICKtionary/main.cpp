//int main(const char *argv []) 
//{
//	return 0;
//}

#include "dictionary.h"

int main(int argc,char *argv [])
{
	string file = argv[1];
	
	Dictionary test;
	test.parser(file);
	string str;
	char c;
	do
	{
		cout << "\nEnter a word to define: ";
		//getline(cin, val);
		while (cin.get(c) && c != '\n')
		{
			if (cin.eof())
			{
				break;
			}
			
				str += c;
		}
		if (c == '\n')
		{
			for (auto & s : str)
			{
				s = toupper(s);
			}
			if (!(test.contains(str)))
			{
				cout << "Word not found.\n";
			}
		}
	} while (!(cin.eof()));//does this work?
}