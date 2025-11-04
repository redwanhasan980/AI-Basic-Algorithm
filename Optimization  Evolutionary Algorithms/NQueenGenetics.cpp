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
    int n = chromosome.size(), attacks = 0;
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++)
            if (chromosome[i] == chromosome[j] || abs(chromosome[i] - chromosome[j]) == abs(i - j))
                attacks++;
    return n * (n - 1) / 2 - attacks;
}

Individual createIndividual(int n)
{
    Individual ind;
    ind.chromosome.resize(n);
    for (int i = 0; i < n; i++)
        ind.chromosome[i] = rand() % n;
    ind.fitness = calculateFitness(ind.chromosome);
    return ind;
}

vector<Individual> createPopulation(int n)
{
    vector<Individual> population;
    for (int i = 0; i < POPULATION_SIZE; i++)
        population.push_back(createIndividual(n));
    return population;
}

Individual selectParent(vector<Individual> &population)
{
    int idx1 = rand() % POPULATION_SIZE, idx2 = rand() % POPULATION_SIZE;
    return population[idx1].fitness > population[idx2].fitness ? population[idx1] : population[idx2];
}

Individual crossover(Individual &parent1, Individual &parent2)
{
    int n = parent1.chromosome.size(), crossoverPoint = rand() % n;
    Individual child;
    child.chromosome.resize(n);
    for (int i = 0; i < n; i++)
        child.chromosome[i] = i < crossoverPoint ? parent1.chromosome[i] : parent2.chromosome[i];
    child.fitness = calculateFitness(child.chromosome);
    return child;
}

void mutate(Individual &ind)
{
    for (int i = 0; i < ind.chromosome.size(); i++)
        if ((double)rand() / RAND_MAX < MUTATION_RATE)
            ind.chromosome[i] = rand() % ind.chromosome.size();
    ind.fitness = calculateFitness(ind.chromosome);
}

void printSolution(Individual &solution)
{
    int n = solution.chromosome.size();
    cout << "\nSolution Board:" << endl;
    for (int row = 0; row < n; row++)
    {
        for (int col = 0; col < n; col++)
            cout << (solution.chromosome[col] == row ? "Q " : ". ");
        cout << endl;
    }
    cout << "\nQueen positions (col, row): ";
    for (int col = 0; col < n; col++)
        cout << "(" << col << "," << solution.chromosome[col] << ") ";
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

    while (generation < MAX_GENERATIONS)
    {
        sort(population.begin(), population.end(), [](Individual &a, Individual &b)
             { return a.fitness > b.fitness; });

        if (population[0].fitness == maxFitness)
        {
            cout << "\n*** Solution found in generation " << generation << "! ***" << endl;
            printSolution(population[0]);
            return 0;
        }

        if (generation % 100 == 0)
            cout << "Generation " << generation << ": Best Fitness = " << population[0].fitness << " / " << maxFitness << endl;

        vector<Individual> newPopulation;
        for (int i = 0; i < POPULATION_SIZE / 10; i++)
            newPopulation.push_back(population[i]);

        while (newPopulation.size() < POPULATION_SIZE)
        {
            Individual p1 = selectParent(population), p2 = selectParent(population);
            Individual child = crossover(p1, p2);
            mutate(child);
            newPopulation.push_back(child);
        }

        population = newPopulation;
        generation++;
    }

    cout << "\nNo perfect solution found. Best result:" << endl;
    printSolution(population[0]);
    cout << "Fitness: " << population[0].fitness << " / " << maxFitness << endl;
    return 0;
}