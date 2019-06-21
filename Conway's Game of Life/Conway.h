#ifndef CONWAY_H
#define CONWAY_H

#include <string>
#include <fstream>
#include <iostream>
#include <cstdlib>
using namespace std;

class Conway
{
	
private:
bool** board;
int rows;
int cols;

public:
Conway(string fileName);
Conway(const Conway& orig);
~Conway();

Conway& operator=(const Conway right);
bool alive(int row, int col) const;
void flip(int row, int col);
string str() const;
void step();
int getLivingNeighbors(int row, int col);
void play(int n);

};

#endif