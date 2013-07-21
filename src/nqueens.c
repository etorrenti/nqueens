/*
 ============================================================================
 Name        : nqueens.c
 Author      : Emanuele Torrenti
 Version     :
 Copyright   : Beerware license

 N-queens problem solver featuring genetic algorithms and libgaul
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <gaul.h>
#include "nqueens.h"

void print_chromosome(population *pop, entity *entity) {
	char* str = NULL;
	size_t slen;
	double f = fmax(0.0, entity->fitness);
	printf("%s (fitness: %f)\n",
			ga_chromosome_integer_to_string(pop, entity, str, &slen), f);
}

boolean fitness(population *pop, entity *entity) {
	entity->fitness = MAX_FITNESS;
	int *chromosome = (int*) (entity->chromosome[0]);

	/* Loop over alleles in chromosome. */
	int i;
	for (i = 0; i < N - 1; i++) {
		int j;
		for (j = i + 1; j < N; j++) {
			int vi = chromosome[i];
			int vj = chromosome[j];

			if (vi == vj) {
				entity->fitness *= PENALTY;
			}

			if (abs(vi - vj) == j - i) {
				entity->fitness *= PENALTY;
			}
		}
	}
	return TRUE;
}

int draw(bool* drawn) {
	int n;
	while (drawn[(n = random_int(N))]) {}
	return n;
}

boolean seedCheesboard(population *pop, entity *adam) {
	int i;
	bool* drawn;
	drawn = calloc(N, sizeof(bool));

	int *chromosome = (int*) (adam->chromosome[0]);
	for (i = 0; i < N; i++) {
		int n = draw(drawn);
		drawn[n] = TRUE;
		chromosome[i] = n;
	}

	printf("Generated: ");
	print_chromosome(pop, adam);

	free(drawn);
	return TRUE;
}

boolean my_generation_hook(const int generation, population *pop) {
	printf("Best individuals at generation #%d:\n", generation);
	int i;
	for (i = 0; i < PRINT_TOP_N; ++i) {
		entity *e = ga_get_entity_from_rank(pop, i);
		printf("#%d: ", i + 1);
		print_chromosome(pop, e);
	}
	printf("---------------------\n\n");
	return ga_get_entity_from_rank(pop, 0)->fitness < MAX_FITNESS;
}

entity *adaptation(population *pop, entity *child) {
	entity *adult = ga_entity_clone(pop, child);
	int allele = random_int(N);
	int val = random_int(N);

	((int *) adult->chromosome[0])[allele] = val;
	fitness(pop, adult);

	if (adult->fitness > child->fitness)
		return adult;

	return child;
}

int main(void) {
	population *pop = NULL; /* The population of solutions. */
	/* initialize random seed: */
	random_seed(time(NULL)); /* Random seed requires any integer parameter. */

	pop = ga_genesis_integer(POPULATION, /* const int              population_size */
	1, /* const int              num_chromo */
	N, /* const int              len_chromo */
	my_generation_hook, /* GAgeneration_hook      generation_hook */
	NULL, /* GAiteration_hook       iteration_hook */
	NULL, /* GAdata_destructor      data_destructor */
	NULL, /* GAdata_ref_incrementor data_ref_incrementor */
	fitness, /* GAevaluate             evaluate */
	seedCheesboard, /* GAseed                 seed */
	adaptation, /* GAadapt                adapt */
	ga_select_one_roulette, /* GAselect_one           select_one */
	ga_select_two_roulette, /* GAselect_two           select_two */
	ga_mutate_integer_singlepoint_drift, /* GAmutate  mutate */
	ga_crossover_integer_allele_mixing, /* GAcrossover     crossover */
	NULL, /* GAreplace              replace */
	NULL /* void *                 userdata */
	);

	ga_population_set_parameters(pop, /* population              *pop */
	GA_SCHEME_LAMARCK_ALL, /* const ga_class_type     class */
	GA_ELITISM_PARENTS_DIE, /* const ga_elitism_type   elitism */
	0.9, /* double                  crossover */
	0.1, /* double                  mutation */
	0.0 /* double                  migration */
	);

	pop->allele_max_integer = N - 1;
	pop->allele_min_integer = 0;

	int iterations = ga_evolution(pop, GENERATIONS);

	printf(
			"The best solution after %d iterations with Lamarckian evolution was:\n",
			iterations);
	print_chromosome(pop, ga_get_entity_from_rank(pop, 0));

	ga_extinction(pop);
	exit(EXIT_SUCCESS);
}
