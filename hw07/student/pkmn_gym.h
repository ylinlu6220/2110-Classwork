// DO NOT MODIFY THIS FILE
/**
 * @brief Header file for global macros, structures and fields to be used by the
 * user's program.
 */
#ifndef PKMN_GYM_H
#define PKMN_GYM_H

#include <stdio.h>
#include "my_string.h"


#define UNUSED_PARAM(x) ((void) x) // This macro is only used for turning off compiler errors initially

// Sizes for different arrays
#define MAX_NAME_LENGTH 20
#define MAX_PARTY_LENGTH 6
#define MAX_TRAINER_LENGTH 20

// Success and failure codes for function return
#define SUCCESS 0
#define FAILURE -1

// Students should add their structs here
struct Pokemon {
    char species[MAX_NAME_LENGTH];
    int level;
};

struct Trainer {
    char name[MAX_NAME_LENGTH];
    struct Pokemon party[MAX_PARTY_LENGTH];
    int party_size;
    int num_wins;
};

struct Gym {
    struct Trainer trainers[MAX_TRAINER_LENGTH];
    int num_trainers;
};

int register_trainer(const char *name);
int unregister_trainer(const char *name);
int catch_pokemon(struct Trainer *trainer, const char *species, int level);
int release_pokemon(struct Trainer *trainer, const char *species);

int count_species(const char *species);
int trade_pokemon(struct Trainer *t0, int party_index_0, struct Trainer *t1, int party_index_1);
int battle_trainer(struct Trainer *challenger, struct Trainer *opponent);
struct Trainer *find_champion(void);
#endif

