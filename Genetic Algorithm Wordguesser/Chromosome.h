#ifndef CHROMOSOME_H
#define CHROMOSOME_H

#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <algorithm>

class Chromosome
{
private:
    std::string data;
public:
    Chromosome(std::string d);
    
    std::string getData() const;
    Chromosome mutate() const;
    Chromosome crossover(const Chromosome& other) const;
    int fitness(const std::string& target) const;
};

std::ostream& operator<<(std::ostream& os, const Chromosome& c);

#endif