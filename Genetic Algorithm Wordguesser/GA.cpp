#include "Chromosome.h"
std::string target;

Chromosome randomChromosome(int size)
{
    std::ostringstream sout;
    for (int i = 0; i < size; i++)
    {
        sout << (char) ((rand() % 26) + 97);
    }
    return Chromosome(sout.str());
}

bool chromosomeCompare(Chromosome t1, Chromosome t2)
{
	return t1.fitness(target) < t2.fitness(target);
}

Chromosome runGA(std::string tar, int popSize, double mr, double cr)
{
	std::ofstream tofile;
	std::string filename(tar);
	filename += ".txt";
	tofile.open(filename.c_str());
	
	std::vector<Chromosome> pop;
	int i;
	for(i = 0; i < popSize; ++i)
	{
		pop.push_back(randomChromosome(tar.length()));
	}
	std::vector<Chromosome> pop2;
	double r;
	int t = 0;
	int t2 = 0;
	int it = 0;
	while(pop[0].fitness(tar) != 0)
	{
		r = ((double) rand() / (RAND_MAX));
		for(i = 0; i < popSize*2; ++i)
		{
			t = rand() % popSize;
			if(popSize == 1)
				t2 = t;
			else
				while(t2 == t)
					t2 = rand() % popSize;
			if(r <= mr && r <= cr)
				pop2.push_back((rand() % 2 == 0) ? pop[t].mutate() : pop[t].crossover(pop[t2]));
			else if( r <= mr)
				pop2.push_back(pop[t].mutate());
			else if( r <= cr)
				pop2.push_back(pop[t].crossover(pop[t2]));
			else
				pop2.push_back(pop[t]);
		}
		std::sort(pop2.begin(), pop2.end(), chromosomeCompare);
		pop.clear();
		for(i = 0; i < popSize; ++i)
		{
			pop.push_back(pop2[i]);
		}
		pop2.clear();
		it++;
		std::cout << "Generation " << it << "'s best candidate: " << pop[0] << std::endl;
		tofile << "Generation " << it << "'s best candidate: " << pop[0] << std::endl;
	}
	tofile.close();
	return pop[0];
}

int main(int argc, char **argv)
{

    srand(time(0));
    target = argv[1];
    int popSize = atoi(argv[2]);
    double mr = atof(argv[3]);
    double cr = atof(argv[4]);
	
    Chromosome answer = runGA(target, popSize, mr, cr);

    std::cout << "Solution found: " << answer << std::endl;
}
