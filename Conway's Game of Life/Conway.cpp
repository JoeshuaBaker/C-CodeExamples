#include "Conway.h"

Conway::Conway(string fileName)
{
	ifstream fin(fileName.c_str());
	if(!fin)
	{
		cout << "Invalid file name. Could not read from file " << fileName;
		return;
	}
	
	fin >> rows;
	fin >> cols;
	
	board = new bool*[rows];
	for(int i = 0; i < rows; ++i)
	{
		board[i] = new bool[cols];
		for(int j = 0; j < cols; ++j)
		{
			fin >> board[i][j];
		}
	}
}

Conway::Conway(const Conway& orig)
{
	rows = orig.rows;
	cols = orig.cols;
	board = new bool*[rows];
	for(int i = 0; i < rows; ++i)
	{
		board[i] = new bool[cols];
		for(int j = 0; j < cols; ++j)
		{
			board[i][j] = orig.board[i][j];
		}
	}
}

Conway::~Conway()
{
	for( int i = 0; i < rows; ++i)
	{
		delete[] board[i];
	}
	delete[] board;
}

Conway& Conway::operator=(const Conway right)
{
	for(int i = 0; i < rows; ++i)
	{
		delete[] board[i];
	}
	delete[] board;
	
	rows = right.rows;
	cols = right.cols;
	board = new bool*[rows];
	for(int i = 0; i < rows; ++i)
	{
		board[i] = new bool[cols];
		for(int j = 0; j < cols; ++j)
		{
			board[i][j] = right.board[i][j];
		}
	}
	return *this;
}

bool Conway::alive(int row, int col) const
{
	return board[row][col];
}

void Conway::flip(int row, int col)
{
	if(alive(row, col))
		board[row][col] = false;
	else
		board[row][col] = true;
}

string Conway::str() const
{
	string bStr = "";
	for(int i = 0; i < rows; ++i)
	{
		for(int j = 0; j < cols; ++j)
		{
			if(alive(i, j))
				bStr += 'X';
			else
				bStr += '.';
			bStr += ' ';
		}
		bStr += '\n';
	}
	return bStr;
}

void Conway::step()
{
	Conway next = *this;
	int aliveNeighbors = 0;
	for(int i = 0; i < rows; ++i)
	{
		for(int j = 0; j < cols; ++j)
		{
			aliveNeighbors = getLivingNeighbors(i, j);
			if(alive(i, j))
			{
				if(aliveNeighbors < 2 || aliveNeighbors > 3)
					next.flip(i, j);
			}
			else
			{
				if(aliveNeighbors == 3)
					next.flip(i, j);
			}
		}
	}
	*this = next;
}

int Conway::getLivingNeighbors(int row, int col)
{
	int count = 0;
	for(int i = -1; i <= 1; ++i)
	{
		if((row + i) < 0 || (row + i) >= rows)
			continue;
		for(int j = -1; j <= 1; ++j)
		{
			if((col + j) < 0 || (col + j) >= cols)
				continue;
			
			if(i == 0 && j == 0)
				continue;
			
			if(alive((row + i), (col + j)))
			{
				count++;
			}
		}
	}
	return count;
}

void Conway::play(int n)
{
	cout << "the game has started. playing " << n << " times." << endl;
	cout << "starting board: " << endl;
	cout << str() << endl;
	for(int i = 0; i < n; ++i)
	{
		step();
		cout << str() << endl;
	}
}