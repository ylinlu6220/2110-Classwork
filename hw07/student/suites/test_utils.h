#ifndef TEST_UTILS_H
#define TEST_UTILS_H

#include <check.h>
#include <stddef.h>
#include <stdio.h>

#include "../my_string.h"
#include "../pkmn_gym.h"

#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)

// Useful macro of taking the size of an array
#define ARR_SIZE(xs) (sizeof(xs) / sizeof((xs)[0]))

#define RETURN_ERROR_VALUE -100

#define EXPECTED_RETVAL_MSG "%s - Expected return value: %d, was: %d"
#define EXPECTED_STR_MSG "%s - Expected string: %s, was: %s"
#define EXPECTED_CHAMPION_MSG "Expected returned champion: %s, was: %s"

// Suites
extern Suite *pkmn_gym_suite(void);
extern Suite *my_string_suite(void);
extern struct Gym gym; // gym that is referred from student code

#define tcase_add(suite, setup_fixture, teardown_fixture, func)     \
  {                                                                 \
    TCase *tc = tcase_create(STRINGIFY(func));                      \
    tcase_add_checked_fixture(tc, setup_fixture, teardown_fixture); \
    tcase_add_test(tc, func);                                       \
    suite_add_tcase(s, tc);                                         \
  }

// my_string_helpers.c functions
void generate_duplicated_string(char *str, int len);
void generate_random_string(char *str, int len);
void generate_random_palindrome(char *str, int len);

void s_caesar_shift(char *str, int shift);
void s_deduplicate_str(char *str);
void s_swap_strings(char **s1, char **s2);
int s_is_palindrome_ignore_case(const char *str);

// pkmn_gym_helpers.c functions
void construct_party(char **pokemonSpecies, int *pokemonLevels, int numPokemon,
                     struct Pokemon *outParty);
void construct_trainer(char *trainerName, char **pokemonSpecies,
                       int *pokemonLevels, int numPokemon, int numWins,
                       struct Trainer *outTrainer);

void assert_gyms_equal(struct Gym *gym_expected, struct Gym *gym_actual,
                       char *test_desc);
void assert_trainers_equal(struct Trainer *trainer_expected,
                           struct Trainer *trainer_actual, char *test_desc);
void assert_pokemon_equal(struct Pokemon *pokemon_expected,
                          struct Pokemon *pokemon_actual, char *test_desc);

int s_register_trainer_with_party(struct Gym *g, const char *name,
                                  struct Pokemon *party, int party_size);
int s_register_trainer(struct Gym *g, const char *name);
int s_unregister_trainer(struct Gym *g, const char *name);
int s_catch_pokemon(struct Trainer *trainer, const char *species, int level);
int s_release_pokemon(struct Trainer *trainer, const char *species,
                      struct Pokemon *released_pokemon);

int s_count_species(struct Gym *g, const char *species);
int s_trade_pokemon(struct Trainer *t0, int party_index_0, struct Trainer *t1,
                    int party_index_1);
int s_battle_trainer(struct Trainer *challenger, struct Trainer *opponent);
struct Trainer *s_find_champion(struct Gym *g);

#endif
