#include <iostream>

#include <windows.h>
#include <map>
#include <wincon.h>
#include <conio.h>
#include "main.h"
#include <ctime>


using namespace std;

enum eDiretion { LEFT = 97, RIGHT = 100, UP = 119, DOWN = 115, GAMEOVER = 0, FIRE};

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

	int getX() 
	{
		return X;
	}

	int getY()
	{
		return Y;
	}

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

//class IMovable 
//{ 
//public: virtual int Drine() = 0; 
//};
//
//class DriveByKey : public IMovable 
//{
//public: 
//	virtual int Drive(); 
//};
//
//class Tank 
//{
//	IMovable drive; 
//public: 
//	Tank(IMovable move) :drive(move) 
//	{
//	}
//	void Move() 
//	{
//		int direction = drive.Drive(); 
//	}
//};

class GameStatus
{
private:
	int sizeBoardX = 20;
	int sizeBoardY;
	int capacity = 40;
	//enum run ()
public:
	int getCapacty() 
	{
		return capacity;
	}
	int getSizeBoard() 
	{
		return sizeBoardX;
	}
};

class GameObj 
{
private:
	Deskard key;
	//char view;
public:
	//virtual GameObj* clone() const = 0;
	Deskard getKey()
	{
		return key;
	}

	Deskard neighbor(eDiretion dir) 
	{
		Deskard iAm = this->getKey();
		Deskard result;
		int kX = iAm.getX();
		int kY = iAm.getY();
		switch (dir)
		{
		case UP:
			result.setCoord(kX, kY--);
			return result;
			break;
		case DOWN:
			result.setCoord(kX, kY++);
			return result;
			break;
		case LEFT:
			result.setCoord(kX--, kY);
			return result;
			break;
		case RIGHT:
			result.setCoord(kX++, kY);
			return result;
			break;
		}
		//return iAm;
	}


		
	GameObj(Deskard value) 
	{
		key = value;
		//view = img;
	}

	

	virtual void show() = 0;
	virtual string iAmObj() = 0;
	/*void show() 
	{
		cout << view;
	};*/
};

class Border : public GameObj
{
public:
	//virtual Border* clone() const { return new Border(); }

	Border(Deskard value, char img): GameObj(value)
	{
	}

	string iAmObj() 
	{
		return "Border";
	}

	void show()
	{
		cout << '#';
	}
	
};

class Area : public GameObj
{
public:
	//virtual Border* clone() const { return new Border(); }

	Area(Deskard value, char img) : GameObj(value)
	{
	}

	string iAmObj()
	{
		return "Area";
	}

	void show()
	{
		cout << ' ';
	}

};

class Wall : public GameObj
{
	int hitpoint;
public:
	//virtual Border* clone() const { return new Border(); }

	Wall(Deskard value, char img, int hit) : GameObj(value)
	{
		hitpoint = hit;
	}

	string iAmObj()
	{
		return "Wall";
	}

	void show()
	{
		cout << '#';
	}

};

class Gold : public GameObj
{
	int hitpoint;
public:
	//virtual Border* clone() const { return new Border(); }

	Gold(Deskard value, char img, int hit) : GameObj(value)
	{
		hitpoint = hit;
	}

	string iAmObj()
	{
		return "Gold";
	}

	void show()
	{
		cout << '@';
	}

};

class kbord
{
public:
	bool runPleyer(eDiretion dir)
	{
		if (_kbhit())
		{
			switch (_getch())
			{
			case 'a':
				dir = LEFT;
				return true;
				break;
			case 'd':
				dir = RIGHT;
				return true;
				break;
			case 'w':
				dir = UP;
				return true;
				break;
			case 's':
				dir = DOWN;
				return true;
				break;
			case ' ':
				dir = FIRE;
				return true;
				break;
			}
			return false;
		}
	}
};


class Tank : public GameObj
{
	int hitpoint;
	eDiretion dir;

public:

	void move(eDiretion dir)
	{
		this->dir = dir;
		//Deskard nextstep;
		//nextstep = this->neighbor(dir);
		
	//	Deskard point = this->getKey;
	//	switch (dir)
	//	{
	//	case UP:

	//		/*SetConsoleCursorPosition(handl, coordTank);
	//		cout << " ";
	//		coordTank.Y--;*/
	//		this->show();
	//		break;
	//	case DOWN:
	//		/*SetConsoleCursorPosition(handl, coordTank);
	//		cout << " ";
	//		coordTank.Y++;*/
	//		this->show();
	//		break;
	//	case LEFT:
	//		/*SetConsoleCursorPosition(handl, coordTank);
	//		cout << " ";
	//		coordTank.X--;*/
	//		this->show();
	//		break;
	//	case RIGHT:
	//		/*SetConsoleCursorPosition(handl, coordTank);
	//		cout << " ";
	//		coordTank.X++;*/
	//		this->show();
	//		break;

	//	}
	}
	

	Tank(Deskard value, char img, int hit) : GameObj(value)
	{
		hitpoint = hit;
	}

	string iAmObj()
	{
		return "Tank";
	}

	void show()
	{
		cout << 'X';
	}

};


class GameController
{
public:
	void createBorder() 
	{
	}
};
int main()
{
	srand(time(NULL));
	HANDLE handl;
	map <Deskard, GameObj*> myMap;
	GameStatus game;
	handl = GetStdHandle(STD_OUTPUT_HANDLE);
	Deskard temp;
	
	//create border and Area
	for (int i = 0; i < game.getSizeBoard(); i++)
	{
		for (int j = 0; j < game.getSizeBoard(); j++)
		{
			
			temp.setCoord(i, j);
			if ((i == 0) || (i == (game.getSizeBoard() - 1)) || (j == 0) || (j == (game.getSizeBoard() - 1)))
			{
				myMap.insert(pair<Deskard, GameObj*> (temp, new Border(temp, '#')));
			}
			else 
			{
				myMap.insert(pair<Deskard, GameObj*>(temp, new Area(temp, ' ')));
			}
		}
	}

	//create wall
	int vector, x, y;
	bool rightOrDown;
		
	for (int k = 0; k < game.getCapacty(); k++)
	{
		rightOrDown = rand() % 2;
		x = rand() % (game.getSizeBoard() - 1);
		y = rand() % (game.getSizeBoard() - 1);
		if (rightOrDown)
		{
			do
			{
				vector = rand() % 5 + 1;
			} while ((x + vector) >= game.getSizeBoard());
			for (int i = x; i < (x + vector); i++)
			{
				
				temp.setCoord(i, y);
				delete myMap[temp];
				myMap.at(temp) =new Wall(temp, '#', 1);
			}
		}
		else
		{
			do
			{
				vector = rand() % 5 + 1;
			} while ((y + vector) >= game.getSizeBoard());
			for (int i = y; i < (y + vector); i++)
			{
				
				temp.setCoord(x, i);
				delete myMap[temp];
				myMap.at(temp) = new Wall(temp, '#', 1);
			}
		}

	}

	//create gold and fortress
	{

		int xGold;
		int yGold;
		xGold = (int)(game.getSizeBoard() / 2);
		yGold = (game.getSizeBoard() - 2);

		temp.setCoord(xGold, yGold);

		delete myMap[temp];
		myMap.at(temp) = new Gold(temp, '@', 1);

		// create fortress
		temp.setCoord(xGold - 1, yGold);
		delete myMap[temp];
		myMap.at(temp) = new Wall(temp, '#', 1);

		temp.setCoord(xGold - 1, yGold - 1);
		delete myMap[temp];
		myMap.at(temp) = new Wall(temp, '#', 1);

		temp.setCoord(xGold, yGold - 1);
		delete myMap[temp];
		myMap.at(temp) = new Wall(temp, '#', 1);

		temp.setCoord(xGold + 1, yGold - 1);
		delete myMap[temp];
		myMap.at(temp) = new Wall(temp, '#', 1);

		temp.setCoord(xGold + 1, yGold);
		delete myMap[temp];
		myMap.at(temp) = new Wall(temp, '#', 1);


		//create tank

		temp.setCoord(xGold-2, yGold);
		GameObj* pTank = new  Tank(temp, 'X', 1);
		delete myMap[temp];
		myMap.at(temp) = pTank;
		//myMap.at(temp) = new Tank(temp, 'X', 1);
		
		
		//debugg
		Deskard nextStep;
		

		Deskard viewDebugging;
		viewDebugging.setCoord(game.getSizeBoard() + 5, game.getSizeBoard());
		SetConsoleCursorPosition(handl, viewDebugging.getCoord());

		cout << endl;
		
		pTank->getKey().Print();

		cout << endl;
		Deskard myTest;
		myTest = pTank->neighbor(RIGHT);
		myTest.Print();
		//pTank->neighbor(RIGHT).Print();
		//sey = pTank->iAmObj();
		//cout << sey << endl;
		//test.Print();
		//pTank->neighbor().Print();
		//pTank->getKey().Print();
		//nextStep.Print();
	}
	
	
	
	// test input	
	for (auto it = myMap.begin(); it != myMap.end(); ++it)
	{
		temp = it->first;
		//temp.Print();
		GameObj* test = it->second;
		
		SetConsoleCursorPosition(handl, temp.getCoord());
		
		test->show();
	}

	system("Pause");
	return 0;
}