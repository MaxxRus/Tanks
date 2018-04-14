#include <iostream>

#include <windows.h>
#include <map>
#include <wincon.h>
#include <conio.h>
#include "main.h"
#include <ctime>


using namespace std;

enum eDiretion { LEFT = 97, RIGHT = 100, UP = 119, DOWN = 115, GAMEOVER = 0, FIRE = 32, start = 1};

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
	Deskard(int valueX, int valueY)
	{
		key.X = valueX;
		X = valueX;
		Y = valueY;
		key.Y = valueY;
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

class IMovable 
{ 
public: virtual eDiretion Drive() = 0; 
};

class Pleyer : public IMovable
{
	eDiretion dir;
public:
	Pleyer()
	{
		dir = start;
	}

	eDiretion Drive()
	{
		eDiretion dir=start;
		if (_kbhit())
		{
			switch (_getch())
			{
			case 'a':
				dir = LEFT;
				break;
			case 'd':
				dir = RIGHT;
				break;
			case 'w':
				dir = UP;
				break;
			case 's':
				dir = DOWN;
				break;
			case ' ':
				dir = FIRE;
			break;
			}
			
		}
		return dir;
	}


};

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
	virtual eDiretion move() { return start; };
	Deskard getKey()
	{
		return key;
	}

	void setKey(Deskard value)
	{
		this->key = value;
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
			result.setCoord(kX, --kY);
			return result;
			break;
		case DOWN:
			result.setCoord(kX, ++kY);
			return result;
			break;
		case LEFT:
			result.setCoord(--kX, kY);
			return result;
			break;
		case RIGHT:
			result.setCoord(++kX, kY);
			return result;
			break;
		case start:
			return iAm;
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

class Tank : public GameObj
{
	int hitpoint;
	eDiretion dir;
	HANDLE handl;
	IMovable *tankMan;

public:
	/*Tank(IMovable move) :drive(move)
	{
	}
	void Move()
	{
		int direction = drive.Drive();
	}*/

	eDiretion move()
	{
		dir = this->tankMan->Drive();
		return dir;
	}
	

	Tank(Deskard value, char img, int hit, HANDLE handl, IMovable *tankMan) : GameObj(value)
	{
		hitpoint = hit;
		this->handl = handl;
		this->tankMan = tankMan;
	}

	string iAmObj()
	{
		return "Tank";
	}

	void show()
	{
		SetConsoleCursorPosition(handl, this->getKey().getCoord());
		cout << 'X';
	}

};


class GameController
{
	
	
public:
	
	void createBorder(map <Deskard, GameObj*>& myMap, int sizeBoard)
	{
		Deskard temp;
		for (int i = 0; i < sizeBoard; i++)
		{
			for (int j = 0; j < sizeBoard; j++)
			{

				temp.setCoord(i, j);
				if ((i == 0) || (i == (sizeBoard - 1)) || (j == 0) || (j == (sizeBoard - 1)))
				{
					myMap.insert(pair<Deskard, GameObj*>(temp, new Border(temp, '#')));
				}
				else
				{
					myMap.insert(pair<Deskard, GameObj*>(temp, new Area(temp, ' ')));
				}
			}
		}
	}

	void createWall(map <Deskard, GameObj*>& myMap, int sizeBoard, int capacty)
	{
		Deskard temp;
		int vector, x, y;
		bool rightOrDown;

		for (int k = 0; k < capacty; k++)
		{
			rightOrDown = rand() % 2;
			x = rand() % (sizeBoard - 1);
			y = rand() % (sizeBoard - 1);
			if (rightOrDown)
			{
				do
				{
					vector = rand() % 5 + 1;
				} while ((x + vector) >= sizeBoard);
				for (int i = x; i < (x + vector); i++)
				{

					temp.setCoord(i, y);
					delete myMap[temp];
					myMap.at(temp) = new Wall(temp, '#', 1);
				}
			}
			else
			{
				do
				{
					vector = rand() % 5 + 1;
				} while ((y + vector) >= sizeBoard);
				for (int i = y; i < (y + vector); i++)
				{

					temp.setCoord(x, i);
					delete myMap[temp];
					myMap.at(temp) = new Wall(temp, '#', 1);
				}
			}

		}
	}

	Deskard createGoldFortres(map <Deskard, GameObj*>& myMap, int sizeBoard)
	{
		int xGold;
		int yGold;
		Deskard temp;
		xGold = (int)(sizeBoard / 2);
		yGold = (sizeBoard - 2);

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

		return Deskard(xGold, yGold);
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


	GameController startGame;
	startGame.createBorder(myMap, game.getSizeBoard());
	startGame.createWall(myMap, game.getSizeBoard(), game.getCapacty());
	Deskard newPoint = startGame.createGoldFortres(myMap, game.getSizeBoard());
	for (auto it = myMap.begin(); it != myMap.end(); ++it)
	{
		temp = it->first;
		//temp.Print();
		GameObj* test = it->second;

		SetConsoleCursorPosition(handl, temp.getCoord());

		test->show();
	}
	
	temp.setCoord(newPoint.getX() - 2, newPoint.getY());
	Pleyer tankman;
	GameObj* pTank = new  Tank(temp, 'X', 1, handl, &tankman);
	
	delete myMap[temp];
	myMap.at(temp) = pTank;
	pTank->show();

	

	Deskard viewDebugging;
	Deskard nextStep;

	while (true)
	{
		viewDebugging.setCoord(game.getSizeBoard() + 5, game.getSizeBoard());
		SetConsoleCursorPosition(handl, viewDebugging.getCoord());
		
		
		eDiretion key = pTank->move();
		//Sleep(1000);
		bool go = false;
		if (key != 1)
		{
			go = (myMap[pTank->neighbor(key)]->iAmObj() == "Area");
		}
		
		if (go)
		{
			temp = pTank->getKey();
			nextStep = pTank->neighbor(key);
			
			pTank->setKey(nextStep);
			

			swap(myMap[nextStep], myMap[temp]);
			myMap[nextStep]->show();
			myMap[temp]->show();
			/*myMap[temp] = new Area(temp, ' ');
			myMap[temp]->show();*/
		}

	};

	system("Pause");
	return 0;
}
	
	
	
