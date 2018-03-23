#include <iostream>

#include <windows.h>

#include "main.h"


using namespace std;


int main() 
{
	cout << "sdsdsd" << endl;
	COORD descart;
	map <COORD, int> myFirstMap;
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10 j++)
		{
			descart.X = i;
			descart.Y = j;
			myFirstMap.insert(pair<COORD, int>(descart, i));
		}

	}


	
	for (auto it = myFirstMap.begin(); it != myFirstMap.end(); ++it)
	{
		cout <<  it->second << endl;
	}

		
	system("PAUSE");
	return 0;
}