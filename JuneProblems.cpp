// JuneProblems.cpp : Defines the entry point for the application.
//

#include "JuneProblems.h"
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>


using namespace std;

class Player
{
public: 
	Player() = default; 
	Player(string name)
		: _name(name)
	{

	}
	char makeMove()
	{
		return _symbol; 
	}

	void setSymbol()
	{
		cout << " enter symbol";
		cin >> _symbol; 
	}

	void displaySymbol()
	{
		cout << " Player: " << _name  << " symbol is " << _symbol << endl;
	}

	void setScore(int newScore)
	{
		score += newScore; 
	}
protected: 
	char _symbol; 
	string _name; 
	int score{ 0 };
	
};

class GameBoard
{
public: 
	GameBoard() = default;
	vector<vector<int>> publicBoard{ {'*','*','*','*'}, {'*','*','*','*'}, {'*','*','*','*'}, {'*','*','*','*'} };

	void displayBoard()
	{
		for (int i = 0; i < publicBoard.size(); i++)
		{
			for (int j = 0; i < publicBoard[0].size(); j++)
			{
				cout << publicBoard[i][j] << " "; 
			}
			cout << endl; 
		}
	}

private:
	vector<vector<char>> privateBoard { {'x','o','x','o'}, {'x','x','o','o'}, {'o','x','o','x'}, {'o','o','x','x'} };

};

class GameManager
{
public:
	GameManager() = default; 

	void GameLoop()
	{

	}

	

	void inputMove(Player& p, GameBoard& gb)
	{
		cout << "choose position on game board" << endl; 
		int row = 0; 
		int col = 0;
		cout << " Choose row position" << endl; 
		cin >> row; 

		cout << "Choose col position" << endl; 
		cin >> col; 

		// update game board 
		gb.publicBoard[row][col] = p.makeMove();

		// update score
		p.setScore(1); 

		// check if player symbol is same as privateBoard symbol
		// if so 
		


		// 


	}

protected:
	

 

};

int main()
{
	/*
	cout << "Hello CMake." << endl;
	Player p1("Wallace");
	p1.setSymbol(); 
	p1.displaySymbol(); 

	Player p2("Quintin"); 
	p2.setSymbol(); 
	p2.displaySymbol(); 
	*/
	/*
	cout << "What food do you want to eat:\n"; 
	string food; 
	cin >> food; 

	ofstream file("Foods.txt"); 
	file << food; 
	file.close(); 
	*/

	vector<string> familyList; 
	ifstream file("Family_List.txt");

	string person; 

	while (file >> person)
	{
		familyList.push_back(person); 
	}
	cout << " From file \n"; 
	for (auto& i : familyList)
	{
		cout << i << "\n"; 
	}
 
	file.close(); 
	return 0;
}
