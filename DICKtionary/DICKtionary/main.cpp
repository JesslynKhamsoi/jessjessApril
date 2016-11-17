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
		cout << "\n\nEnter a word to define: ";
	while (getline(cin, str))
	{
		for (auto & c : str)
		{
			c = toupper(c);
		}
		if (!(test.contains(str)))
		{
			cout << "\n\nWord not found.";
		}
		cout << "\n\nEnter a word to define: ";
		str = "";
	}
	
}