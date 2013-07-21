/*
 ============================================================================
 Name        : nqueens.h
 Author      : Emanuele Torrenti
 Version     :
 Copyright   : Beerware license

 N-queens problem solver featuring genetic algorithms and libgaul
 ============================================================================
 */

#ifndef NQUEENS_H_
#define NQUEENS_H_

#include <gaul.h>

/*
 * Chessboard size
 */
#define N 8
/*
 * Initial population size
 */
#define POPULATION 50
/*
 * Maximum iterations
 */
#define GENERATIONS 10000

/*
 * Penalties to be used in fitness function
 */
#define PENALTY 0.8

/*
 * For debug purposes
 */
#define PRINT_TOP_N 3

/*
 * Maximum fitness
 */
#define MAX_FITNESS 1000.0

/*
 * Print a chromosome
 */
void print_chromosome(population *pop, entity *entity);

/*
 * Fitness measurement. Perfect individuals have a fitness
 * value of 1000.0
 */
boolean fitness(population *pop, entity *entity);

/*
 * Draw a not yet drawn number according to *drawn array
 */
int draw(bool* drawn);

/*
 * Generate a random chessboard / chromosome
 */
boolean seedCheesboard(population *pop, entity *adam);

/*
 * To be invoked by gaul at each generation
 */
boolean my_generation_hook(const int generation, population *pop);

/*
 * Change a random allele with a random value
 */
entity *adaptation(population *pop, entity *child);

#endif /* NQUEENS_H_ */
