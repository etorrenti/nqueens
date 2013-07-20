/*
 * nqueens.h
 *
 *  Created on: Jul 20, 2013
 *      Author: emanuele
 */

#ifndef NQUEENS_H_
#define NQUEENS_H_

#include <gaul.h>

#define N 8
#define POPULATION 30
#define GENERATIONS 1400000
#define ROW_PENALTY 0.8
#define DIAG_PENALTY 0.8
#define PRINT_TOP_N 5

/*
 * Stampa un cromosoma a video
 */
void print_chromosome(population *pop, entity *entity);

/*
 * Misura di fitness della scacchiera. Massimo = 1000.0. Ogni
 * vincolo violato comporta una penalità
 */
boolean fitness(population *pop, entity *entity);

/*
 * Estrae un numero non ancora estratto
 */
int draw(bool* drawn);

/*
 * Genera un cromosoma (scacchiera) casuale
 */
boolean seedCheesboard(population *pop, entity *adam);

/*
 * Invocata ad ogni generazione
 */
boolean my_generation_hook(const int generation, population *pop);

/*
 * Funzioni di adattamento
 */

/*
 * Cambia un allele col valore che permette la miglior fitness
 */
entity *best_adaptation(population *pop, entity *child);

/*
 * Cambia un allele di un valore casuale
 */
entity *slight_adaptation(population *pop, entity *child);

/*
 * Cambia un allele di +1 o -1 cercando un individuo migliore
 */
entity *struggle_adaptation(population *pop, entity *child);

#endif /* NQUEENS_H_ */
