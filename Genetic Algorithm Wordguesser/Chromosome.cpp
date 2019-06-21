#include "Chromosome.h"

Chromosome::Chromosome(std::string d) : data(d)
{
}

std::string Chromosome::getData() const
{
    return data;
}

Chromosome Chromosome::mutate() const
{
	
	int target = rand() % data.length();
	std::string mstr = data;
	if(rand() % 2 == 0)
	{
		if(mstr[target] == 122)
		{
			mstr[target] = 97;
		}
		else
		{
			++mstr[target];
		}
	}
	else
	{
		if(mstr[target] == 97)
		{
			mstr[target] = 122;
		}
		else
		{
			--mstr[target];
		}
	}
	return Chromosome(mstr);
}

Chromosome Chromosome::crossover(const Chromosome& c) const
{	
	int target = rand() % data.length();
	std::string first = data.substr(0, target);
	std::string second = c.getData().substr(target, data.length());
	std::string composite;
	composite += first;
	composite += second;
	return Chromosome(composite);
}

int Chromosome::fitness(const std::string& target) const
{
    // computes fitness by sum of differences of each character
    // smaller is better (0 is perfect)

    int diff = 0;
    for (int i = 0; i < data.size(); i++)
    {
        int change = std::abs(data[i] - target[i]);
        if (change > 13) // handles wrap around for letters
        {
            change = 26 - change;
        }
        diff += change;
    }
    return diff;
}

std::ostream& operator<<(std::ostream& os, const Chromosome& c)
{
    os << c.getData();
    return os;
}
