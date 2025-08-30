// JuneProblems.cpp : Defines the entry point for the application.

#include "JuneProblems.h"
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <queue>

using namespace std;

class Person
{
public: 
	Person() = default; 

	virtual char makeMove() = 0; 
	virtual void setSymbol() = 0;
	virtual void displaySymbol() = 0;
	virtual void setScore(int newScore) = 0; 
};

class Player : public Person
{
public: 
	Player() = default; 
	Player(string name)
		: _name(name)
	{

	}
	char makeMove() override
	{
		return _symbol; 
	}

	void setSymbol() override
	{
		cout << " enter symbol";
		cin >> _symbol; 
	}

	void displaySymbol() override
	{
		cout << " Player: " << _name  << " symbol is " << _symbol << endl;
	}

	void setScore(int newScore)
	{
		score += newScore; 
	}

protected: 
	char _symbol{};
	string _name{};
	int score{ 0 };
	
};



class GameBoard
{
public: 
	GameBoard() = default;

	vector<vector<char>> publicBoard{ {'*','*','*','*'},
									  {'*','*','*','*'},
									  {'*','*','*','*'},
									  {'*','*','*','*'} };

	vector<vector<int>> dir = { {0,1}, {0,-1}, {1,0}, {-1,0} }; 

	bool valid(int row, int col, Player& p)
	{
		return 0 <= row && row < publicBoard.size() && 0 <= col && col < publicBoard[0].size() && privateBoard[row][col] == p.makeMove() && publicBoard[row][col] == '*';
	}

	void displayBoard()
	{
		for (int i = 0; i < publicBoard.size(); i++)
		{
			for (int j = 0; j < publicBoard[0].size(); j++)
			{
				cout << publicBoard[i][j] << " "; 
			}
			cout << endl; 
		}
	}

	void update(int row, int col, Player& p)
	{
		cout << " board before move " << endl; 

		displayBoard(); 

		if (privateBoard[row][col] == p.makeMove()) // if board[row][col] == * && p.makeMove() == *
		{
			// legal move
			publicBoard[row][col] = p.makeMove(); 
			floodFillAlgo(row, col, p); 
		}

		else
		{
			cout << " Wrong symbol try again next move :( \n"; 
		}

		cout << " board after move " << endl;

		displayBoard(); 
	}

	/*
	* Check sto see if we can fill in any other neighboring squares with our symbol
	*/
	void floodFillAlgo(int row, int col, Player& p)
	{
		// breadth first search? 
		vector<vector<bool>> visited(publicBoard.size(), vector<bool>(publicBoard[0].size(), false));
		visited[row][col] = true; 
		queue<vector<int>> que; 

		que.push({ row, col }); 

		while (!que.empty())
		{
			auto curr = que.front(); 
			que.pop(); 

			int currRow = curr[0]; 
			int currCol = curr[1]; 

			publicBoard[currRow][currCol] = p.makeMove(); 
			p.setScore(1); 

			// only stop if all positions have been visited 
			if (row == publicBoard.size() - 1 && col == publicBoard[0].size() - 1)
			{
				cout << " Done with flood fill \n"; 
				return; 
			}

			// visit neighbors
			for (auto& i : dir)
			{
				int nextRow = currRow + i[0]; 
				int nextCol = currCol + i[1]; 

				if (valid(nextRow, nextCol, p) && !visited[nextRow][nextCol])
				{
					visited[nextRow][nextCol] = true;
					que.push({ nextRow, nextCol });
				}
			}
		}
	}

private:
	vector<vector<char>> privateBoard { {'x','o','x','o'},
										{'x','x','o','o'},
										{'o','x','o','x'},
										{'o','o','x','x'} };

};

class GameManager
{
public:
	GameManager() = default; 

	void GameLoop()
	{
		return;
	}

	void inputMove(Player& p, GameBoard& gb)
	{
		cout << endl; 

		std::cout << "Player:\n ";
		p.displaySymbol();


		cout << "choose position on game board" << endl; 
		int row = 0;
		int col = 0;
		cout << " Choose row position" << endl; 
		cin >> row; 

		cout << "Choose col position" << endl; 
		cin >> col; 

		// update game board 
		gb.update(row, col, p); 
	}
};


void displayBoard(vector<vector<char>>& publicBoard)
{
	/*
	for (int i = 0; i < publicBoard.size(); i++)
	{
		for (int j = 0; i < publicBoard[0].size(); j++)
		{
			cout << publicBoard[i][j] << " ";
		}
		cout << endl;
	}
	*/ 

	for (auto& row : publicBoard)
	{
		for (auto& col : row)
		{
			cout << col << " "; 
		}
		cout << endl; 
	}
}

int main()
{
	GameManager gm; 
	GameBoard gb; 

	cout << "Hello CMake." << endl;

	cout << " Player 1 enter info \n"; 
	Player p1("Wallace");
	p1.setSymbol(); 
	p1.displaySymbol(); 

	cout << endl; 
	cout << "Player two enter info \n"; 
	Player p2("Quintin"); 
	p2.setSymbol(); 
	p2.displaySymbol(); 

	cout << endl; 
	int keepGoing = 1; 

	cout << "Loop to keep playing: \n"; 

	while (keepGoing)
	{
		int myRow;
		int myCol;

		if (keepGoing % 2 == 0)
		{
			cout << "It's your turn: " << endl; 
			p1.displaySymbol(); 
			cout << endl; 
		}
		else
		{
			cout << "It's your turn: " << endl;
			p2.displaySymbol();
			cout << endl; 
		}

		cout << "Enter row \n"; 
		cin >> myRow; 

		cout << "Enter col \n"; 
		cin >> myCol;

		if (keepGoing % 2 == 0)
		{
			gb.update(myRow, myCol, p1);
		}
		else
		{
			gb.update(myRow, myCol, p2); 
		}

		cout << " Keep going? Enter 1 for yes and 0 for no" << endl; 
		int answer = 0;

		cin >> answer; 

		if (answer)
		{
			keepGoing++; 
		}
		else
		{
			break; 
		}
	}
	
	int initCol = 4; 
	int initRow = 4;
	vector<vector<bool>> mylist(initRow, vector<bool>(initCol, false));

	mylist[initRow - 1][initCol - 1] = true; 
	
	return 0;
}
