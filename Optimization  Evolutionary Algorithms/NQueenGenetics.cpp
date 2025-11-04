#include <bits/stdc++.h>
using namespace std;

const int POPULATION_SIZE = 100;
const int MAX_GENERATIONS = 10000;
const double MUTATION_RATE = 0.1;

struct Individual
{
    vector<int> chromosome;
    int fitness;
};

int calculateFitness(vector<int> &chromosome)
{
    int n = chromosome.size();
    int attacks = 0;

    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (chromosome[i] == chromosome[j])
                attacks++;
            if (abs(chromosome[i] - chromosome[j]) == abs(i - j))
                attacks++;
        }
    }
    return n * (n - 1) / 2 - attacks;
}

Individual createIndividual(int n)
{
    Individual ind;
    ind.chromosome.resize(n);
    for (int i = 0; i < n; i++)
    {
        ind.chromosome[i] = rand() % n;
    }
    ind.fitness = calculateFitness(ind.chromosome);
    return ind;
}

vector<Individual> createPopulation(int n)
{
    vector<Individual> population;
    for (int i = 0; i < POPULATION_SIZE; i++)
    {
        population.push_back(createIndividual(n));
    }
    return population;
}

Individual selectParent(vector<Individual> &population)
{
    int idx1 = rand() % POPULATION_SIZE;
    int idx2 = rand() % POPULATION_SIZE;
    return (population[idx1].fitness > population[idx2].fitness) ? population[idx1] : population[idx2];
}

Individual crossover(Individual &parent1, Individual &parent2)
{
    int n = parent1.chromosome.size();
    Individual child;
    child.chromosome.resize(n);
    int crossoverPoint = rand() % n;

    for (int i = 0; i < crossoverPoint; i++)
    {
        child.chromosome[i] = parent1.chromosome[i];
    }
    for (int i = crossoverPoint; i < n; i++)
    {
        child.chromosome[i] = parent2.chromosome[i];
    }

    child.fitness = calculateFitness(child.chromosome);
    return child;
}

void mutate(Individual &ind)
{
    int n = ind.chromosome.size();
    for (int i = 0; i < n; i++)
    {
        if ((double)rand() / RAND_MAX < MUTATION_RATE)
        {
            ind.chromosome[i] = rand() % n;
        }
    }
    ind.fitness = calculateFitness(ind.chromosome);
}

void printSolution(Individual &solution)
{
    int n = solution.chromosome.size();
    cout << "\nSolution Board:" << endl;

    for (int row = 0; row < n; row++)
    {
        for (int col = 0; col < n; col++)
        {
            cout << (solution.chromosome[col] == row ? "Q " : ". ");
        }
        cout << endl;
    }

    cout << "\nQueen positions (col, row): ";
    for (int col = 0; col < n; col++)
    {
        cout << "(" << col << "," << solution.chromosome[col] << ") ";
    }
    cout << endl;
}

int main()
{
    srand(time(0));

    int n;
    cout << "Enter N: ";
    cin >> n;

    int maxFitness = n * (n - 1) / 2;
    cout << "N-Queen Genetic Algorithm (Max Fitness: " << maxFitness << ")\n"
         << endl;

    vector<Individual> population = createPopulation(n);

    int generation = 0;
    bool solutionFound = false;

    while (generation < MAX_GENERATIONS && !solutionFound)
    {
        sort(population.begin(), population.end(),
             [](Individual &a, Individual &b)
             { return a.fitness > b.fitness; });

        if (population[0].fitness == maxFitness)
        {
            solutionFound = true;
            break;
        }

        if (generation % 100 == 0)
        {
            cout << "Generation " << generation << ": Best Fitness = "
                 << population[0].fitness << " / " << maxFitness << endl;
        }

        vector<Individual> newPopulation;

        int eliteCount = POPULATION_SIZE / 10;
        for (int i = 0; i < eliteCount; i++)
        {
            newPopulation.push_back(population[i]);
        }

        while (newPopulation.size() < POPULATION_SIZE)
        {
            Individual parent1 = selectParent(population);
            Individual parent2 = selectParent(population);
            Individual child = crossover(parent1, parent2);
            mutate(child);
            newPopulation.push_back(child);
        }

        population = newPopulation;
        generation++;
    }

    if (solutionFound)
    {
        cout << "\n*** Solution found in generation " << generation << "! ***" << endl;
        printSolution(population[0]);
    }
    else
    {
        cout << "\nNo perfect solution found. Best result:" << endl;
        printSolution(population[0]);
        cout << "Fitness: " << population[0].fitness << " / " << maxFitness << endl;
    }

    return 0;
}