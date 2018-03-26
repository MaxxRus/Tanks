#include <iostream>

#include <windows.h>
#include <map>
#include <wincon.h>
#include "main.h"


using namespace std;




class Deskard
{
private:
	int X;
	int Y;
	COORD key;
public:
	Deskard() 
	{
		key.X = 0;
		X = 0;
		Y = 0;
		key.Y = 0;
	}
	
	COORD getCoord()
	{
		return key;
	}

	/*COORD getCoordConsol() 
	{
		COORD temp;
		temp.X = key.Y;
		temp.Y = key.X;
		return temp;
	}*/

	
	void setCoord(int X, int Y)
	{
		key.X = X;
		key.Y = Y;
		this->X = X;
		this->Y = Y;
	}

	
	bool operator ==(const Deskard & other) 
	{
		return (this->X == other.X && this->Y == other.Y);
	}

	void Print() 
	{
		cout << X << ' ' << Y;
	}

	bool operator < (const Deskard& _Right) const
	{
		return (this->X < _Right.X || this->X == _Right.X  && this->Y < _Right.Y);
	}

	inline bool isInRange(Deskard & _Right, int range) const 
	{
		if (pow(_Right.X - this->X, 2) + pow(_Right.Y - this->Y, 2) <= range * range)
			return true;
		return false;
	}
};

class GameStatus
{
private:
	int sizeBoardX = 20;
	int sizeBoardY;
public:
	int getSizeBoard() 
	{
		return sizeBoardX;
	}
};


class GameObj 
{
private:
	Deskard key;
	char view;
public:
	char show() 
	{
		return view;
	}

	
	GameObj(Deskard value, char img) 
	{
		key = value;
		view = img;
	}
};

int main()
{
	HANDLE handl;
	map <Deskard, GameObj> myMap;
	GameStatus game;
	handl = GetStdHandle(STD_OUTPUT_HANDLE);

	for (int i = 0; i < game.getSizeBoard(); i++)
	{
		for (int j = 0; j < game.getSizeBoard(); j++)
		{
			if ((i == 0) || (i == (game.getSizeBoard() - 1)) || (j == 0) || (j == (game.getSizeBoard() - 1)))
			{
				Deskard temp;
				temp.setCoord(i,j);
				GameObj item(temp, '#');

				myMap.insert(pair<Deskard, GameObj>(temp, item));
			}
		}
	}
	for (auto it = myMap.begin(); it != myMap.end(); ++it)
	{
		Deskard temp = it->first;
		//temp.Print();
		GameObj test = it->second;
		
		SetConsoleCursorPosition(handl, temp.getCoord());
		
		cout  << test.show();
	}

	system("Pause");
	return 0;
}