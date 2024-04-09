/**
 * @file pkmn_gym_suite.c
 * @author Richard, Vy, Alex, Prabhav
 * @brief Testing Suites to HW7 - Spring 2024
 * @date 2024-03-07
 */

// Check Docs
// Tutorial : https://libcheck.github.io/check/doc/check_html/check_3.html
// Check API: https://libcheck.github.io/check/doc/doxygen/html/check_8h.html

// System Headers
#include <string.h>
#include <check.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <sys/wait.h> // For grabbing return value of system call

// TA Headers
#include "test_utils.h"

struct Gym gt_gym; // ground-truth gym to be checked against students' gym
char *TA_names[] = {
    "Richard",
    "Vy",
    "Alex",
    "Prabhav"};

///////////////////////////////////////////////////////////////////////////////////////////////////
/******************************************* TESTS ***********************************************/
///////////////////////////////////////////////////////////////////////////////////////////////////

/*
 * register_trainer() test cases
 */

START_TEST(test_register_trainer_null_check)
{
    char *emptyNamePointer = 0;
    ck_assert_msg(FAILURE == register_trainer(emptyNamePointer), "Trainer's name is NULL, should return FAILURE");
    assert_gyms_equal(&gt_gym, &gym, "Ensure gym is unchanged");
}
END_TEST

START_TEST(test_register_trainer_extra_long_name)
{
    char *extraLongName = "12345678901234567890";
    ck_assert_msg(FAILURE == register_trainer(extraLongName), "Trainer's name longer than MAX_NAME_LENGTH, should return FAILURE");
    char *extraLongName2 = "12345678901234567890V";
    ck_assert_msg(FAILURE == register_trainer(extraLongName2), "Trainer's name longer than MAX_NAME_LENGTH, should return FAILURE");
    assert_gyms_equal(&gt_gym, &gym, "Ensure gym is unchanged");
}
END_TEST

START_TEST(test_register_trainer_normal)
{
    char *name = "Prabhav";
    ck_assert_msg(SUCCESS == register_trainer(name), "Trainer %s not successfully added", name);
    s_register_trainer(&gt_gym, name);
    assert_gyms_equal(&gt_gym, &gym, "Ensure gym is changed properly");
}
END_TEST

START_TEST(test_register_trainer_full_gym)
{
    for (int i = 0; i < MAX_TRAINER_LENGTH; i++)
    {
        char name[100];
        sprintf(name, "Richard %d", i);
        ck_assert_int_eq(SUCCESS, s_register_trainer(&gym, name));
        s_register_trainer(&gt_gym, name);
    }
    char *name = "Prabhav";
    ck_assert_msg(FAILURE == register_trainer(name), "Gym is already full");
    assert_gyms_equal(&gt_gym, &gym, "Ensure gym is unchanged");
}
END_TEST

/*
 * unregister_trainer() test cases
 */

START_TEST(test_unregister_trainer_null_check)
{
    char *emptyNamePointer = 0;
    ck_assert_msg(FAILURE == unregister_trainer(emptyNamePointer), "Trainer's name is NULL, should return FAILURE");
    assert_gyms_equal(&gt_gym, &gym, "Ensure gym is unchanged");
}
END_TEST

START_TEST(test_unregister_trainer_extra_long_name)
{
    char *extraLongName = "12345678901234567890";
    ck_assert_msg(FAILURE == unregister_trainer(extraLongName), "Trainer's name longer than MAX_NAME_LENGTH, should return FAILURE");
    char *extraLongName2 = "12345678901234567890V";
    ck_assert_msg(FAILURE == unregister_trainer(extraLongName2), "Trainer's name longer than MAX_NAME_LENGTH, should return FAILURE");
    assert_gyms_equal(&gt_gym, &gym, "Ensure gym is unchanged");
}
END_TEST

START_TEST(test_unregister_trainer_normal)
{
    char *name = TA_names[0];
    // ck_assert_msg(SUCCESS == register_trainer(name), "Trainer %s not successfully added", name);
    s_register_trainer(&gym, name);
    s_register_trainer(&gt_gym, name);
    ck_assert_msg(SUCCESS == unregister_trainer(name), "Trainer %s not successfully removed", name);
    s_unregister_trainer(&gt_gym, name);
    assert_gyms_equal(&gt_gym, &gym, "Make sure your gym unergisters correctly");
}
END_TEST

START_TEST(test_register_unregister_coverage_basic)
{
    char *TA_1 = TA_names[0];
    ck_assert_msg(SUCCESS == register_trainer(TA_1), "Trainer %s not successfully added", TA_1);
    char *TA_2 = TA_names[1];
    ck_assert_msg(SUCCESS == register_trainer(TA_2), "Trainer %s not successfully added", TA_2);

    s_register_trainer(&gt_gym, TA_1);
    s_register_trainer(&gt_gym, TA_2);

    assert_gyms_equal(&gt_gym, &gym, "Make sure your gym registers trainers correctly");

    char *newPokemon = "amogus";
    int pokemonLvl = 69;
    s_catch_pokemon(&gt_gym.trainers[0], newPokemon, pokemonLvl);
    s_catch_pokemon(&gym.trainers[0], newPokemon, pokemonLvl);
    // ck_assert_msg(SUCCESS == catch_pokemon(&gym.trainers[0], newPokemon, pokemonLvl), "Pokemon not successfully caught");

    char *TA_3 = TA_names[2];
    ck_assert_msg(FAILURE == unregister_trainer(TA_3), "Trainer %s doesn't exist in gym", TA_3);
    ck_assert_msg(SUCCESS == unregister_trainer(TA_1), "Trainer %s not successfully removed", TA_1);
    ck_assert_msg(SUCCESS == unregister_trainer(TA_2), "Trainer %s not successfully removed", TA_2);
    s_unregister_trainer(&gt_gym, TA_3);
    s_unregister_trainer(&gt_gym, TA_1);
    s_unregister_trainer(&gt_gym, TA_2);
    assert_gyms_equal(&gt_gym, &gym, "Gyms are equal");
}
END_TEST

/*
 * catch_pokemon() test cases
 */

START_TEST(test_catch_pokemon_null_check)
{
    char *trainerName = "Vy";
    char *pokemonNames[] = {"Pichu", "Amogus"};
    int pokemonLevels[] = {17, 69};
    int numPokemon = 2, numWins = 2;

    struct Trainer vy;
    struct Trainer students_trainer;

    construct_trainer(trainerName, pokemonNames, pokemonLevels, numPokemon, numWins, &vy);
    construct_trainer(trainerName, pokemonNames, pokemonLevels, numPokemon, numWins, &students_trainer);

    ck_assert_msg(FAILURE == catch_pokemon(0, "Pichu", 17), "Trainer is NULL, should return FAILURE");
    ck_assert_msg(FAILURE == catch_pokemon(&students_trainer, 0, 42), "Pokemon's name is NULL, should return FAILURE");
    char *extraLongName = "12345678901234567890";
    ck_assert_msg(FAILURE == catch_pokemon(&students_trainer, extraLongName, 42), "Pokemon's name is too long, should return FAILURE");
    char *extraLongName2 = "12345678901234567890V";
    ck_assert_msg(FAILURE == catch_pokemon(&students_trainer, extraLongName2, 42), "Pokemon's name is too long, should return FAILURE");
    ck_assert_msg(FAILURE == catch_pokemon(&students_trainer, pokemonNames[1], 9000), "Pokemon's level %d is too high, should return FAILURE", 9000);
    ck_assert_msg(FAILURE == catch_pokemon(&students_trainer, pokemonNames[1], 101), "Pokemon's level %d is too high, should return FAILURE", 101);
    ck_assert_msg(FAILURE == catch_pokemon(&students_trainer, pokemonNames[1], 0), "Pokemon's level %d is too low, should return FAILURE", 0);
    ck_assert_msg(FAILURE == catch_pokemon(&students_trainer, pokemonNames[1], -1), "Pokemon's level %d is too low, should return FAILURE", -1);
    ck_assert_msg(FAILURE == catch_pokemon(&students_trainer, pokemonNames[1], -17), "Pokemon's level %d is too low, should return FAILURE", -17);

    char test_desc[400];

    // check valid extrema bounds [1, 100]
    ck_assert_msg(SUCCESS == catch_pokemon(&students_trainer, "Catto", 99), "Pokemon not successfully caught");
    s_catch_pokemon(&vy, "Catto", 99);
    sprintf(test_desc, "catch_pokemon(%s, %s, %d)",
            "Trainer Vy {[Pichu, lvl 17], [Amogus, lvl 69]}", "Catto", 99);
    assert_trainers_equal(&vy, &students_trainer, test_desc);

    ck_assert_msg(SUCCESS == catch_pokemon(&students_trainer, pokemonNames[0], 1), "Pokemon not successfully caught");
    s_catch_pokemon(&vy, pokemonNames[0], 1);
    sprintf(test_desc, "catch_pokemon(%s, %s, %d)",
            "Trainer Vy {[Pichu, lvl 17], [Amogus, lvl 69], [Catto, lvl 99]}", pokemonNames[0], 99);
    assert_trainers_equal(&vy, &students_trainer, test_desc);

    ck_assert_msg(SUCCESS == catch_pokemon(&students_trainer, pokemonNames[1], 100), "Pokemon not successfully caught");
    s_catch_pokemon(&vy, pokemonNames[1], 100);
    sprintf(test_desc, "catch_pokemon(%s, %s, %d)",
            "Trainer Vy {[Pichu, lvl 17], [Amogus, lvl 69], [Catto, lvl 99], [Pichu, lvl 1]}", pokemonNames[1], 100);
    assert_trainers_equal(&vy, &students_trainer, test_desc);

    // assert_gyms_equal(&gt_gym, &gym, "Ensure gym keeps track of trainer's pokemon");
}

START_TEST(test_catch_pokemon_basic)
{
    char *richardsPokemonSpecies[] = {"pikachu", "squirtle"};
    int richardsPokemonLevels[] = {5, 10};
    int numPokemon = 2;
    int numWins = 0;

    struct Trainer richard;
    struct Trainer test_richard;

    // make two identical trainers
    construct_trainer("Richard", richardsPokemonSpecies, richardsPokemonLevels, numPokemon, numWins, &richard);
    construct_trainer("Richard", richardsPokemonSpecies, richardsPokemonLevels, numPokemon, numWins, &test_richard);

    // try to catch a new pokemon
    char *newPokemonSpecies = "snivy";
    int newPokemonLvl = 15;

    s_catch_pokemon(&richard, newPokemonSpecies, newPokemonLvl);
    catch_pokemon(&test_richard, newPokemonSpecies, newPokemonLvl);

    // test description
    char test_desc[400];
    sprintf(test_desc, "catch_pokemon(%s, %s, %d)",
            "Trainer Richard {[pikachu, lvl 5], [squirtle, lvl 10]}", "snivy", 15);

    // trainers should be equal
    assert_trainers_equal(&richard, &test_richard, test_desc);
}
END_TEST

/*
 * release_pokemon() test cases
 */

START_TEST(test_release_pokemon_null_checks)
{
    char *trainerName = "Vy";
    char *pokemonNames[] = {"Pichu", "Amogus"};
    int pokemonLevels[] = {17, 69};
    int numPokemon = 2, numWins = 2;

    struct Trainer vy;
    struct Trainer students_trainer;

    construct_trainer(trainerName, (char *[]){0}, (int[]){0}, 0, numWins, &vy);
    ck_assert_msg(FAILURE == release_pokemon(&vy, "Pichu"), "Trainer's party is empty, should return FAILURE");

    construct_trainer(trainerName, pokemonNames, pokemonLevels, numPokemon, numWins, &vy);
    construct_trainer(trainerName, pokemonNames, pokemonLevels, numPokemon, numWins, &students_trainer);

    ck_assert_msg(FAILURE == release_pokemon(0, "Pichu"), "Trainer is NULL, should return FAILURE");
    ck_assert_msg(FAILURE == release_pokemon(&students_trainer, 0), "Pokemon's name is NULL, should return FAILURE");
    ck_assert_msg(FAILURE == release_pokemon(&students_trainer, "Catto"), "Pokemon doesn't exist in party, should return FAILURE");

    ck_assert_msg(SUCCESS == release_pokemon(&students_trainer, "Pichu"), "Pokemon not released successfully");

    struct Pokemon released_pokemon;
    s_release_pokemon(&vy, "Pichu", &released_pokemon);
    assert_trainers_equal(&vy, &students_trainer, "Ensure trainer's party is updated");
}
END_TEST

START_TEST(test_catch_and_release_coverage_test)
{
    char *firstTrainerName = "Vy";
    char *firstPokemonSet[] = {"Pichu", "Snorlax", "Kirby"};
    int firstPokemonLevels[] = {17, 69, 42};
    int numPokemon = 3, numWins = 4;

    char *secondTrainerName = "Talia";
    char *secondPokemonSet[] = {"Latios", "Bewear", "Porygon2"};
    int secondPokemonLevels[] = {5, 23, 23};

    s_register_trainer(&gym, firstTrainerName);
    s_register_trainer(&gym, secondTrainerName);
    s_register_trainer(&gt_gym, firstTrainerName);
    s_register_trainer(&gt_gym, secondTrainerName);
    // assert_gyms_equal(&gt_gym, &gym, "Ensure gym registers trainers properly");

    struct Trainer vy = gt_gym.trainers[0];
    struct Trainer student_trainer_1 = gym.trainers[0];

    struct Trainer talia = gt_gym.trainers[1];
    struct Trainer student_trainer_2 = gym.trainers[1];

    ck_assert_msg(FAILURE == release_pokemon(&student_trainer_1, "vvvvvVVVVVyyyyyVVVVVVyyyyy"), "Pokemon's name is too long, should return failure");

    construct_trainer(firstTrainerName, firstPokemonSet, firstPokemonLevels, numPokemon, numWins, &vy);
    construct_trainer(firstTrainerName, firstPokemonSet, firstPokemonLevels, numPokemon, numWins, &student_trainer_1);
    construct_trainer(secondTrainerName, secondPokemonSet, secondPokemonLevels, numPokemon, numWins, &talia);
    construct_trainer(secondTrainerName, secondPokemonSet, secondPokemonLevels, numPokemon, numWins, &student_trainer_2);

    char test_desc[400];

    char *pokemonToBeCaught = "Catto";
    int newPokemonLevel = 21;
    ck_assert_msg(SUCCESS == catch_pokemon(&student_trainer_2, pokemonToBeCaught, newPokemonLevel), "Trainer %s did not catch %s successfully", secondTrainerName, pokemonToBeCaught);
    s_catch_pokemon(&talia, pokemonToBeCaught, newPokemonLevel);
    sprintf(test_desc, "Trainer %s did not catch %s successfully", secondTrainerName, pokemonToBeCaught);
    assert_trainers_equal(&talia, &student_trainer_2, test_desc);

    pokemonToBeCaught = "Amogus";
    newPokemonLevel = 19;
    ck_assert_msg(SUCCESS == catch_pokemon(&student_trainer_1, pokemonToBeCaught, newPokemonLevel), "Trainer %s did not catch %s successfully", firstTrainerName, pokemonToBeCaught);
    s_catch_pokemon(&vy, pokemonToBeCaught, newPokemonLevel);
    sprintf(test_desc, "Trainer %s did not catch %s successfully", firstTrainerName, pokemonToBeCaught);
    assert_trainers_equal(&vy, &student_trainer_1, test_desc);

    ck_assert_msg(SUCCESS == release_pokemon(&student_trainer_1, firstPokemonSet[1]), "%s should have been released", firstPokemonSet[1]);
    struct Pokemon Pichu;
    s_release_pokemon(&vy, firstPokemonSet[1], &Pichu);
    sprintf(test_desc, "Trainer %s did not release %s successfully", firstTrainerName, firstPokemonSet[1]);
    assert_trainers_equal(&vy, &student_trainer_1, test_desc);

    // ck_assert_msg(SUCCESS == unregister_trainer(firstTrainerName), "Trainer %s not successfully removed", firstTrainerName);
    // s_unregister_trainer(&gt_gym, firstTrainerName);
    // assert_gyms_equal(&gt_gym, &gym, "Ensure gym removes trainers properly");
}
END_TEST

// count_species
START_TEST(test_count_species_basic)
{
    // first trainer
    char *species1[] = {"squirtle", "charmander"};
    int levels1[] = {1, 1};
    int numPokemon1 = 2;
    struct Pokemon party1[2];
    construct_party(species1, levels1, numPokemon1, party1);
    s_register_trainer_with_party(&gym, "Richard", party1, numPokemon1);
    s_register_trainer_with_party(&gt_gym, "Richard", party1, numPokemon1);

    // second trainer
    char *species2[] = {"snivy"};
    int levels2[] = {15};
    int numPokemon2 = 1;
    struct Pokemon party2[1];
    construct_party(species2, levels2, numPokemon2, party2);
    s_register_trainer_with_party(&gym, "Prabhav", party2, numPokemon2);
    s_register_trainer_with_party(&gt_gym, "Prabhav", party2, numPokemon2);

    int student_answer = count_species("squirtle");
    int ground_truth = s_count_species(&gt_gym, "squirtle");

    ck_assert_msg(student_answer == ground_truth, EXPECTED_RETVAL_MSG,
                  "count_species(\"squirtle\")", ground_truth, student_answer);
}
END_TEST

START_TEST(test_count_species_none)
{
    // first trainer
    char *species1[] = {"squirtle", "charmander"};
    int levels1[] = {1, 1};
    int numPokemon1 = 2;
    struct Pokemon party1[2];
    construct_party(species1, levels1, numPokemon1, party1);
    s_register_trainer_with_party(&gym, "Richard", party1, numPokemon1);
    s_register_trainer_with_party(&gt_gym, "Richard", party1, numPokemon1);

    // second trainer
    char *species2[] = {"snivy"};
    int levels2[] = {15};
    int numPokemon2 = 1;
    struct Pokemon party2[1];
    construct_party(species2, levels2, numPokemon2, party2);
    s_register_trainer_with_party(&gym, "Prabhav", party2, numPokemon2);
    s_register_trainer_with_party(&gt_gym, "Prabhav", party2, numPokemon2);

    int student_answer = count_species("asdf");
    int ground_truth = s_count_species(&gt_gym, "asdf");

    ck_assert_msg(student_answer == ground_truth, EXPECTED_RETVAL_MSG,
                  "count_species(\"asdf\")", ground_truth, student_answer);
}
END_TEST

START_TEST(test_count_species_invalid_string_argument)
{
    char *species1[] = {"squirtle", "charmander"};
    int levels1[] = {1, 1};
    int numPokemon1 = 2;
    struct Pokemon party1[2];
    construct_party(species1, levels1, numPokemon1, party1);
    s_register_trainer_with_party(&gym, "Richard", party1, numPokemon1);

    ck_assert_msg(count_species(NULL) == FAILURE, "count_species(NULL) - Did not return FAILURE");
    ck_assert_msg(count_species("aaaaaaaaaaaaaaaaaaa") != FAILURE,
                  "count_species(\"aaaaaaaaaaaaaaaaaaa\"[length excluding '\n' == MAX_NAME_LENGTH - 1]) - Incorrectly returned FAILURE");
    ck_assert_msg(count_species("aaaaaaaaaaaaaaaaaaaa") == FAILURE,
                  "count_species(\"aaaaaaaaaaaaaaaaaaaa\"[length excluding '\n' == MAX_NAME_LENGTH]) - Did not return FAILURE");
    ck_assert_msg(count_species("qwertyuiopasdfghjklzxcvbnm") == FAILURE,
                  "count_species(\"qwertyuiopasdfghjklzxcvbnm\"[longer than MAX_NAME_LENGTH]) - Did not return FAILURE");
}
END_TEST

START_TEST(test_count_species_duplicate_species_in_party)
{
    // first trainer
    char *species1[] = {"pikachu", "pikachu", "charmander"};
    int levels1[] = {1, 1, 1};
    int numPokemon1 = 3;
    struct Pokemon party1[3];
    construct_party(species1, levels1, numPokemon1, party1);
    s_register_trainer_with_party(&gym, "Richard", party1, numPokemon1);
    s_register_trainer_with_party(&gt_gym, "Richard", party1, numPokemon1);

    // second trainer
    char *species2[] = {"pikachu-pika", "pikachu"};
    int levels2[] = {1, 1};
    int numPokemon2 = 2;
    struct Pokemon party2[2];
    construct_party(species2, levels2, numPokemon2, party2);
    s_register_trainer_with_party(&gym, "Prabhav", party2, numPokemon2);
    s_register_trainer_with_party(&gt_gym, "Prabhav", party2, numPokemon2);

    int student_answer = count_species("pikachu");
    int ground_truth = s_count_species(&gt_gym, "pikachu");

    ck_assert_msg(student_answer == ground_truth, EXPECTED_RETVAL_MSG,
                  "count_species(\"pikachu\")", ground_truth, student_answer);
}
END_TEST

START_TEST(test_count_species_max_trainers)
{
    // make up to MAX_TRAINER_LENGTH trainers
    for (int i = 0; i < MAX_TRAINER_LENGTH; i++)
    {
        char *species1[] = {"squirtle", "squirtle"};
        int levels1[] = {1, 1};
        int numPokemon1 = 2;
        struct Pokemon party1[2];
        construct_party(species1, levels1, numPokemon1, party1);
        s_register_trainer_with_party(&gym, "trainer", party1, numPokemon1);
        s_register_trainer_with_party(&gt_gym, "trainer", party1, numPokemon1);
    }

    int student_answer = count_species("squirtle");
    int ground_truth = s_count_species(&gt_gym, "squirtle");

    ck_assert_msg(student_answer == ground_truth, EXPECTED_RETVAL_MSG,
                  "count_species(\"squirtle\")", ground_truth, student_answer);
}
END_TEST

// trade_pokemon
START_TEST(test_trade_pokemon_basic)
{
    // first trainer
    char *species1[] = {"squirtle", "charmander"};
    int levels1[] = {1, 1};
    int numPokemon1 = 2;
    struct Pokemon party1[2];
    construct_party(species1, levels1, numPokemon1, party1);
    s_register_trainer_with_party(&gym, "Richard", party1, numPokemon1);
    s_register_trainer_with_party(&gt_gym, "Richard", party1, numPokemon1);

    // second trainer
    char *species2[] = {"snivy"};
    int levels2[] = {15};
    int numPokemon2 = 1;
    struct Pokemon party2[1];
    construct_party(species2, levels2, numPokemon2, party2);
    s_register_trainer_with_party(&gym, "Prabhav", party2, numPokemon2);
    s_register_trainer_with_party(&gt_gym, "Prabhav", party2, numPokemon2);

    trade_pokemon(&gym.trainers[0], 1, &gym.trainers[1], 0);
    s_trade_pokemon(&gt_gym.trainers[0], 1, &gt_gym.trainers[1], 0);

    // test description
    char test_desc[400];
    sprintf(test_desc, "trade_pokemon(%s, %d, %s, %d)",
            "Trainer Richard {[squirtle, lvl 1], [charmander, lvl 1]}", 1, "Trainer Prabhav {[snivy, lvl 15]}", 0);

    assert_gyms_equal(&gt_gym, &gym, test_desc);
}
END_TEST

START_TEST(test_trade_pokemon_coverage)
{
    char *trainer_desc[] = {
        "Trainer Richard",
        "Trainer Prabhav",
        "Trainer Vy",
    };

    // first trainer
    char *species1[] = {"squirtle", "charmander", "flareon", "pikachu", "jigglypuff", "greninja"};
    int levels1[] = {1, 1, 5, 10, 15, 40};
    int numPokemon1 = 6;
    struct Pokemon party1[6];
    construct_party(species1, levels1, numPokemon1, party1);
    s_register_trainer_with_party(&gym, "Richard", party1, numPokemon1);
    s_register_trainer_with_party(&gt_gym, "Richard", party1, numPokemon1);

    // second trainer
    char *species2[] = {"snivy", "blastoise", "magikarp", "magikarp", "ivysaur", "charizard"};
    int levels2[] = {15, 33, 1, 100, 23, 98};
    int numPokemon2 = 6;
    struct Pokemon party2[6];
    construct_party(species2, levels2, numPokemon2, party2);
    s_register_trainer_with_party(&gym, "Prabhav", party2, numPokemon2);
    s_register_trainer_with_party(&gt_gym, "Prabhav", party2, numPokemon2);

    // third trainer
    char *species3[] = {"snorlax", "eevee", "tepig", "oshawott", "pichu", "mewtwo"};
    int levels3[] = {100, 10, 5, 6, 25, 49};
    int numPokemon3 = 6;
    struct Pokemon party3[6];
    construct_party(species3, levels3, numPokemon3, party3);
    s_register_trainer_with_party(&gym, "Vy", party3, numPokemon3);
    s_register_trainer_with_party(&gt_gym, "Vy", party3, numPokemon3);

    // start a chain of trades
    char test_desc[400];

    trade_pokemon(&gym.trainers[0], 5, &gym.trainers[2], 0);
    s_trade_pokemon(&gt_gym.trainers[0], 5, &gt_gym.trainers[2], 0);
    sprintf(test_desc, "trade_pokemon(%s, %d, %s, %d)",
            trainer_desc[0], 5, trainer_desc[2], 0);
    assert_gyms_equal(&gt_gym, &gym, test_desc);

    trade_pokemon(&gym.trainers[1], 3, &gym.trainers[2], 4);
    s_trade_pokemon(&gt_gym.trainers[1], 3, &gt_gym.trainers[2], 4);
    sprintf(test_desc, "trade_pokemon(%s, %d, %s, %d)",
            trainer_desc[1], 3, trainer_desc[2], 4);
    assert_gyms_equal(&gt_gym, &gym, test_desc);

    trade_pokemon(&gym.trainers[2], 2, &gym.trainers[0], 1);
    s_trade_pokemon(&gt_gym.trainers[2], 2, &gt_gym.trainers[0], 1);
    sprintf(test_desc, "trade_pokemon(%s, %d, %s, %d)",
            trainer_desc[2], 2, trainer_desc[0], 1);
    assert_gyms_equal(&gt_gym, &gym, test_desc);

    trade_pokemon(&gym.trainers[0], 5, &gym.trainers[1], 4);
    s_trade_pokemon(&gt_gym.trainers[0], 5, &gt_gym.trainers[1], 4);
    sprintf(test_desc, "trade_pokemon(%s, %d, %s, %d)",
            trainer_desc[0], 5, trainer_desc[1], 4);
    assert_gyms_equal(&gt_gym, &gym, test_desc);

    trade_pokemon(&gym.trainers[1], 2, &gym.trainers[0], 3);
    s_trade_pokemon(&gt_gym.trainers[1], 2, &gt_gym.trainers[0], 3);
    sprintf(test_desc, "trade_pokemon(%s, %d, %s, %d)",
            trainer_desc[1], 2, trainer_desc[0], 3);
    assert_gyms_equal(&gt_gym, &gym, test_desc);
}
END_TEST

START_TEST(test_trade_pokemon_index_too_large)
{
    // first trainer
    char *species1[] = {"squirtle", "charmander"};
    int levels1[] = {1, 1};
    int numPokemon1 = 2;
    struct Pokemon party1[2];
    construct_party(species1, levels1, numPokemon1, party1);
    s_register_trainer_with_party(&gym, "Richard", party1, numPokemon1);
    s_register_trainer_with_party(&gt_gym, "Richard", party1, numPokemon1);

    // second trainer
    char *species2[] = {"snivy"};
    int levels2[] = {15};
    int numPokemon2 = 1;
    struct Pokemon party2[1];
    construct_party(species2, levels2, numPokemon2, party2);
    s_register_trainer_with_party(&gym, "Prabhav", party2, numPokemon2);
    s_register_trainer_with_party(&gt_gym, "Prabhav", party2, numPokemon2);

    // test description
    char test_desc[400];
    sprintf(test_desc, "trade_pokemon(%s, %d, %s, %d)",
            "Trainer Richard {[squirtle, lvl 1], [charmander, lvl 1]}", 3, "Trainer Prabhav {[snivy, lvl 15]}", 0);

    // make sure that FAILURE is returned if either index is >= party_size
    ck_assert_msg(trade_pokemon(&gym.trainers[0], 3, &gym.trainers[1], 0) == FAILURE,
                  "%s - Did not return FAILURE on index too large", test_desc);

    sprintf(test_desc, "trade_pokemon(%s, %d, %s, %d)",
            "Trainer Richard {[squirtle, lvl 1], [charmander, lvl 1]}", 0, "Trainer Prabhav {[snivy, lvl 15]}", 1);

    ck_assert_msg(trade_pokemon(&gym.trainers[0], 0, &gym.trainers[1], 1) == FAILURE,
                  "%s - Did not return FAILURE on index too large", test_desc);
}
END_TEST

START_TEST(test_trade_pokemon_invalid_index)
{
    char *species1[] = {"squirtle", "charmander"};
    int levels1[] = {1, 1};
    int numPokemon1 = 2;
    struct Pokemon party1[2];
    construct_party(species1, levels1, numPokemon1, party1);
    s_register_trainer_with_party(&gym, "Richard", party1, numPokemon1);

    char *species2[] = {"snivy"};
    int levels2[] = {15};
    int numPokemon2 = 1;
    struct Pokemon party2[1];
    construct_party(species2, levels2, numPokemon2, party2);
    s_register_trainer_with_party(&gym, "Prabhav", party2, numPokemon2);

    // make sure that FAILURE is returned if either index is negative
    ck_assert_msg(trade_pokemon(&gym.trainers[0], -1, &gym.trainers[1], 0) == FAILURE,
                  "trade_pokemon(Trainer, -1, Trainer, 0) - Did not return FAILURE on negative index");
    ck_assert_msg(trade_pokemon(&gym.trainers[0], 0, &gym.trainers[1], -1) == FAILURE,
                  "trade_pokemon(Trainer, 0, Trainer, -1) - Did not return FAILURE on negative index");
}
END_TEST

START_TEST(test_trade_pokemon_invalid_trainer)
{
    char *species1[] = {"squirtle", "charmander"};
    int levels1[] = {1, 1};
    int numPokemon1 = 2;
    struct Pokemon party1[2];
    construct_party(species1, levels1, numPokemon1, party1);
    s_register_trainer_with_party(&gym, "Richard", party1, numPokemon1);

    char *species2[] = {"snivy"};
    int levels2[] = {15};
    int numPokemon2 = 1;
    struct Pokemon party2[1];
    construct_party(species2, levels2, numPokemon2, party2);
    s_register_trainer_with_party(&gym, "Prabhav", party2, numPokemon2);

    // make sure that FAILURE is returned if either trainer argument is NULL
    ck_assert_msg(trade_pokemon(NULL, 0, &gym.trainers[1], 0) == FAILURE,
                  "trade_pokemon(NULL, 0, Trainer, 0) - Did not return FAILURE on NULL pointer to trainer");
    ck_assert_msg(trade_pokemon(&gym.trainers[0], 0, NULL, 0) == FAILURE,
                  "trade_pokemon(Trainer, 0, NULL, 0) - Did not return FAILURE on NULL pointer to trainer");
}
END_TEST

START_TEST(test_trade_pokemon_same_trainer)
{
    char *species1[] = {"squirtle", "charmander"};
    int levels1[] = {1, 1};
    int numPokemon1 = 2;
    struct Pokemon party1[2];
    construct_party(species1, levels1, numPokemon1, party1);
    s_register_trainer_with_party(&gym, "Richard", party1, numPokemon1);

    // make sure that FAILURE is returned if both trainer pointer arguments point to the same trainer
    ck_assert_msg(trade_pokemon(&gym.trainers[0], 0, &gym.trainers[0], 1) == FAILURE,
                  "trade_pokemon(Trainer Richard, 0, Trainer Richard, 1) - Did not return FAILURE on pointers to identical trainer");
}
END_TEST

// battle_trainer
START_TEST(test_battle_trainer_basic)
{
    // first trainer
    char *species1[] = {"squirtle", "charmander", "eevee"};
    int levels1[] = {1, 10, 15};
    int numPokemon1 = 3;
    struct Pokemon party1[3];
    construct_party(species1, levels1, numPokemon1, party1);
    s_register_trainer_with_party(&gym, "Richard", party1, numPokemon1);
    s_register_trainer_with_party(&gt_gym, "Richard", party1, numPokemon1);

    // second trainer
    char *species2[] = {"snivy", "pikachu", "magikarp"};
    int levels2[] = {15, 9, 50};
    int numPokemon2 = 3;
    struct Pokemon party2[3];
    construct_party(species2, levels2, numPokemon2, party2);
    s_register_trainer_with_party(&gym, "Prabhav", party2, numPokemon2);
    s_register_trainer_with_party(&gt_gym, "Prabhav", party2, numPokemon2);

    // test description
    char test_desc[400];
    sprintf(test_desc, "battle_trainer(%s, %s)",
            "Trainer Richard {[squirtle, lvl 1], [charmander, lvl 10], [eevee, lvl 15]}",
            "Trainer Prabhav {[snivy, lvl 15], [pikachu, lvl 9], [magikarp, lvl 50]}");

    int student_answer = battle_trainer(&gym.trainers[0], &gym.trainers[1]);
    int ground_truth = s_battle_trainer(&gt_gym.trainers[0], &gt_gym.trainers[1]);
    ck_assert_msg(student_answer == ground_truth, EXPECTED_RETVAL_MSG, test_desc, ground_truth, student_answer);

    // assert gyms are the same (num_wins updated properly)
    assert_gyms_equal(&gt_gym, &gym, test_desc);

    // perform battle again, but swap opponent and challenger
    sprintf(test_desc, "battle_trainer(%s, %s)",
            "Trainer Prabhav {[snivy, lvl 15], [pikachu, lvl 9], [magikarp, lvl 50]}",
            "Trainer Richard {[squirtle, lvl 1], [charmander, lvl 10], [eevee, lvl 15]}");
    student_answer = battle_trainer(&gym.trainers[1], &gym.trainers[0]);
    ground_truth = s_battle_trainer(&gt_gym.trainers[1], &gt_gym.trainers[0]);
    ck_assert_msg(student_answer == ground_truth, EXPECTED_RETVAL_MSG, test_desc, ground_truth, student_answer);
    assert_gyms_equal(&gt_gym, &gym, test_desc);
}
END_TEST

START_TEST(test_battle_trainer_no_pokemon)
{
    // first trainer
    s_register_trainer(&gym, "Richard");
    s_register_trainer(&gt_gym, "Richard");

    // second trainer
    s_register_trainer(&gym, "Prabhav");
    s_register_trainer(&gt_gym, "Prabhav");

    // test description
    char test_desc[400];
    sprintf(test_desc, "battle_trainer(%s, %s)", "Trainer Richard {no pokemon}", "Trainer Prabhav {no pokemon}");

    int student_answer = battle_trainer(&gym.trainers[0], &gym.trainers[1]);
    int ground_truth = s_battle_trainer(&gt_gym.trainers[0], &gt_gym.trainers[1]);
    ck_assert_msg(student_answer == ground_truth, EXPECTED_RETVAL_MSG, test_desc, ground_truth, student_answer);

    assert_gyms_equal(&gt_gym, &gym, test_desc);

    // swap opponent and challenger
    sprintf(test_desc, "battle_trainer(%s, %s)", "Trainer Prabhav {no pokemon}", "Trainer Richard {no pokemon}");
    student_answer = battle_trainer(&gym.trainers[1], &gym.trainers[0]);
    ground_truth = s_battle_trainer(&gt_gym.trainers[1], &gt_gym.trainers[0]);
    ck_assert_msg(student_answer == ground_truth, EXPECTED_RETVAL_MSG, test_desc, ground_truth, student_answer);
    assert_gyms_equal(&gt_gym, &gym, test_desc);
}
END_TEST

START_TEST(test_battle_trainer_same_level)
{
    // first trainer
    char *species1[] = {"squirtle", "charmander", "eevee", "pikachu"};
    int levels1[] = {10, 10, 10, 10};
    int numPokemon1 = 4;
    struct Pokemon party1[4];
    construct_party(species1, levels1, numPokemon1, party1);
    s_register_trainer_with_party(&gym, "Richard", party1, numPokemon1);
    s_register_trainer_with_party(&gt_gym, "Richard", party1, numPokemon1);

    // second trainer
    char *species2[] = {"snivy", "pikachu", "magikarp", "charizard"};
    int levels2[] = {10, 10, 10, 10};
    int numPokemon2 = 4;
    struct Pokemon party2[4];
    construct_party(species2, levels2, numPokemon2, party2);
    s_register_trainer_with_party(&gym, "Prabhav", party2, numPokemon2);
    s_register_trainer_with_party(&gt_gym, "Prabhav", party2, numPokemon2);

    // test description
    char test_desc[400];
    sprintf(test_desc, "battle_trainer(%s, %s)",
            "Trainer Richard {4 lvl 10 pokemon}", "Trainer Prabhav {4 lvl 10 pokemon}");

    int student_answer = battle_trainer(&gym.trainers[0], &gym.trainers[1]);
    int ground_truth = s_battle_trainer(&gt_gym.trainers[0], &gt_gym.trainers[1]);
    ck_assert_msg(student_answer == ground_truth, EXPECTED_RETVAL_MSG, test_desc, ground_truth, student_answer);

    assert_gyms_equal(&gt_gym, &gym, test_desc);

    // swap opponent and challenger
    sprintf(test_desc, "battle_trainer(%s, %s)",
            "Trainer Prabhav {4 lvl 10 pokemon}", "Trainer Richard {4 lvl 10 pokemon}");
    student_answer = battle_trainer(&gym.trainers[1], &gym.trainers[0]);
    ground_truth = s_battle_trainer(&gt_gym.trainers[1], &gt_gym.trainers[0]);
    ck_assert_msg(student_answer == ground_truth, EXPECTED_RETVAL_MSG, test_desc, ground_truth, student_answer);
    assert_gyms_equal(&gt_gym, &gym, test_desc);
}
END_TEST

START_TEST(test_battle_trainer_unequal_party_count)
{
    // first trainer
    char *species1[] = {"squirtle", "charmander", "eevee"};
    int levels1[] = {1, 1, 1};
    int numPokemon1 = 3;
    struct Pokemon party1[3];
    construct_party(species1, levels1, numPokemon1, party1);
    s_register_trainer_with_party(&gym, "Richard", party1, numPokemon1);
    s_register_trainer_with_party(&gt_gym, "Richard", party1, numPokemon1);

    // second trainer
    char *species2[] = {"magikarp"};
    int levels2[] = {90};
    int numPokemon2 = 1;
    struct Pokemon party2[1];
    construct_party(species2, levels2, numPokemon2, party2);
    s_register_trainer_with_party(&gym, "Prabhav", party2, numPokemon2);
    s_register_trainer_with_party(&gt_gym, "Prabhav", party2, numPokemon2);

    // test description
    char test_desc[400];
    sprintf(test_desc, "battle_trainer(%s, %s)",
            "Trainer Richard {3 lvl 1 pokemon}", "Trainer Prabhav {[magikarp, lvl 90]}");

    int student_answer = battle_trainer(&gym.trainers[0], &gym.trainers[1]);
    int ground_truth = s_battle_trainer(&gt_gym.trainers[0], &gt_gym.trainers[1]);
    ck_assert_msg(student_answer == ground_truth, EXPECTED_RETVAL_MSG, test_desc, ground_truth, student_answer);

    assert_gyms_equal(&gt_gym, &gym, test_desc);

    // swap opponent and challenger
    sprintf(test_desc, "battle_trainer(%s, %s)",
            "Trainer Prabhav {[magikarp, lvl 90]}", "Trainer Richard {3 lvl 1 pokemon]}");
    student_answer = battle_trainer(&gym.trainers[1], &gym.trainers[0]);
    ground_truth = s_battle_trainer(&gt_gym.trainers[1], &gt_gym.trainers[0]);
    ck_assert_msg(student_answer == ground_truth, EXPECTED_RETVAL_MSG, test_desc, ground_truth, student_answer);
    assert_gyms_equal(&gt_gym, &gym, test_desc);
}
END_TEST

START_TEST(test_battle_trainer_unequal_party_count_lesser_wins)
{
    // first trainer
    char *species1[] = {"squirtle", "charmander", "eevee"};
    int levels1[] = {1, 1, 1};
    int numPokemon1 = 3;
    struct Pokemon party1[3];
    construct_party(species1, levels1, numPokemon1, party1);
    s_register_trainer_with_party(&gym, "Richard", party1, numPokemon1);
    s_register_trainer_with_party(&gt_gym, "Richard", party1, numPokemon1);

    // second trainer
    char *species2[] = {"magikarp", "magikarp"};
    int levels2[] = {90, 90};
    int numPokemon2 = 2;
    struct Pokemon party2[2];
    construct_party(species2, levels2, numPokemon2, party2);
    s_register_trainer_with_party(&gym, "Prabhav", party2, numPokemon2);
    s_register_trainer_with_party(&gt_gym, "Prabhav", party2, numPokemon2);

    // test description
    char test_desc[400];
    sprintf(test_desc, "battle_trainer(%s, %s)",
            "Trainer Richard {3 lvl 1 pokemon}", "Trainer Prabhav {2 lvl 90 pokemon}");

    int student_answer = battle_trainer(&gym.trainers[0], &gym.trainers[1]);
    int ground_truth = s_battle_trainer(&gt_gym.trainers[0], &gt_gym.trainers[1]);
    ck_assert_msg(student_answer == ground_truth, EXPECTED_RETVAL_MSG, test_desc, ground_truth, student_answer);

    assert_gyms_equal(&gt_gym, &gym, test_desc);

    // swap opponent and challenger
    sprintf(test_desc, "battle_trainer(%s, %s)",
            "Trainer Prabhav {[magikarp, lvl 90]}", "Trainer Richard {3 lvl 1 pokemon]}");
    student_answer = battle_trainer(&gym.trainers[1], &gym.trainers[0]);
    ground_truth = s_battle_trainer(&gt_gym.trainers[1], &gt_gym.trainers[0]);
    ck_assert_msg(student_answer == ground_truth, EXPECTED_RETVAL_MSG, test_desc, ground_truth, student_answer);
    assert_gyms_equal(&gt_gym, &gym, test_desc);
}
END_TEST

START_TEST(test_battle_trainer_unequal_party_count_even_tie)
{
    // first trainer
    char *species1[] = {"squirtle", "charmander", "eevee", "pikachu"};
    int levels1[] = {1, 1, 1, 1};
    int numPokemon1 = 4;
    struct Pokemon party1[4];
    construct_party(species1, levels1, numPokemon1, party1);
    s_register_trainer_with_party(&gym, "Richard", party1, numPokemon1);
    s_register_trainer_with_party(&gt_gym, "Richard", party1, numPokemon1);

    // second trainer
    char *species2[] = {"magikarp", "magikarp"};
    int levels2[] = {90, 100};
    int numPokemon2 = 2;
    struct Pokemon party2[2];
    construct_party(species2, levels2, numPokemon2, party2);
    s_register_trainer_with_party(&gym, "Prabhav", party2, numPokemon2);
    s_register_trainer_with_party(&gt_gym, "Prabhav", party2, numPokemon2);

    // test description
    char test_desc[400];
    sprintf(test_desc, "battle_trainer(%s, %s)",
            "Trainer Richard {4 lvl 1 pokemon}", "Trainer Prabhav {[magikarp, lvl 90], [magikarp, lvl 100]}");

    int student_answer = battle_trainer(&gym.trainers[0], &gym.trainers[1]);
    int ground_truth = s_battle_trainer(&gt_gym.trainers[0], &gt_gym.trainers[1]);
    ck_assert_msg(student_answer == ground_truth, EXPECTED_RETVAL_MSG, test_desc, ground_truth, student_answer);

    assert_gyms_equal(&gt_gym, &gym, test_desc);

    // swap opponent and challenger
    sprintf(test_desc, "battle_trainer(%s, %s)",
            "Trainer Prabhav {[magikarp, lvl 90], [magikarp, lvl 100]}", "Trainer Richard {4 lvl 1 pokemon]}");
    student_answer = battle_trainer(&gym.trainers[1], &gym.trainers[0]);
    ground_truth = s_battle_trainer(&gt_gym.trainers[1], &gt_gym.trainers[0]);
    ck_assert_msg(student_answer == ground_truth, EXPECTED_RETVAL_MSG, test_desc, ground_truth, student_answer);
    assert_gyms_equal(&gt_gym, &gym, test_desc);
}
END_TEST

START_TEST(test_battle_trainer_null_input)
{
    // trainer
    char *species1[] = {"squirtle", "charmander", "eevee"};
    int levels1[] = {1, 1, 1};
    int numPokemon1 = 3;
    struct Pokemon party1[3];
    construct_party(species1, levels1, numPokemon1, party1);
    s_register_trainer_with_party(&gym, "Richard", party1, numPokemon1);

    char test_desc[400];
    sprintf(test_desc, "battle_trainer(%s, %s)",
            "Trainer", "NULL");

    ck_assert_msg(battle_trainer(&gym.trainers[0], NULL) == FAILURE, "%s - did not return FAILURE on NULL input", test_desc);

    sprintf(test_desc, "battle_trainer(%s, %s)",
            "NULL", "Trainer");
    ck_assert_msg(battle_trainer(NULL, &gym.trainers[0]) == FAILURE, "%s - did not return FAILURE on NULL input", test_desc);
}
END_TEST

START_TEST(test_find_champion_basic)
{
    char *trainerNames[] = {"Richard", "Prabhav", "Vy", "Alex", "Henry", "Saloni"};
    int trainerWins[] = {1, 2, 3, 1, 5, 4};
    int numTrainers = 6;
    for (int i = 0; i < numTrainers; i++)
    {
        s_register_trainer(&gym, trainerNames[i]);
        s_register_trainer(&gt_gym, trainerNames[i]);
        // artificially set number of wins to each trainer
        gym.trainers[i].num_wins = trainerWins[i];
        gt_gym.trainers[i].num_wins = trainerWins[i];
    }

    // make sure that student finds the correct champion (all names are unique in this example)
    struct Trainer *student_answer = find_champion();
    struct Trainer *ground_truth = s_find_champion(&gt_gym);
    ck_assert_msg(student_answer != NULL && strcmp(student_answer->name, ground_truth->name) == 0,
                  EXPECTED_CHAMPION_MSG, ground_truth->name, student_answer == NULL ? "NULL" : student_answer->name);

    // ensure that they have not modified the trainer before returning pointer to it
    assert_trainers_equal(student_answer, ground_truth,
                          "Checking that trainer of returned pointer isn't modified in find_champion()");
    // ensure gym is unchanged
    assert_gyms_equal(&gt_gym, &gym, "Checking that gym is unchanged");
}
END_TEST

START_TEST(test_find_champion_same_wins)
{
    char *trainerNames[] = {"Richard", "Prabhav", "Vy", "Alex", "Henry", "Saloni"};
    int trainerWins[] = {5, 5, 5, 5, 5, 5};
    int numTrainers = 6;
    for (int i = 0; i < numTrainers; i++)
    {
        s_register_trainer(&gym, trainerNames[i]);
        s_register_trainer(&gt_gym, trainerNames[i]);
        // artificially set number of wins to each trainer
        gym.trainers[i].num_wins = trainerWins[i];
        gt_gym.trainers[i].num_wins = trainerWins[i];
    }

    // make sure that student finds the correct champion (all names are unique in this example)
    struct Trainer *student_answer = find_champion();
    struct Trainer *ground_truth = s_find_champion(&gt_gym);
    ck_assert_msg(student_answer != NULL && strcmp(student_answer->name, ground_truth->name) == 0,
                  EXPECTED_CHAMPION_MSG, ground_truth->name, student_answer == NULL ? "NULL" : student_answer->name);

    // ensure that they have not modified the trainer before returning pointer to it
    assert_trainers_equal(student_answer, ground_truth,
                          "Checking that trainer of returned pointer isn't modified in find_champion()");
    // ensure gym is unchanged
    assert_gyms_equal(&gt_gym, &gym, "Checking that gym is unchanged");
}
END_TEST

START_TEST(test_find_champion_no_wins)
{
    // should act the same as same_wins
    char *trainerNames[] = {"Richard", "Prabhav", "Vy", "Alex", "Henry", "Saloni"};
    int trainerWins[] = {0, 0, 0, 0, 0, 0};
    int numTrainers = 6;
    for (int i = 0; i < numTrainers; i++)
    {
        s_register_trainer(&gym, trainerNames[i]);
        s_register_trainer(&gt_gym, trainerNames[i]);
        // artificially set number of wins to each trainer
        gym.trainers[i].num_wins = trainerWins[i];
        gt_gym.trainers[i].num_wins = trainerWins[i];
    }

    // make sure that student finds the correct champion (all names are unique in this example)
    struct Trainer *student_answer = find_champion();
    struct Trainer *ground_truth = s_find_champion(&gt_gym);
    ck_assert_msg(student_answer != NULL && strcmp(student_answer->name, ground_truth->name) == 0,
                  EXPECTED_CHAMPION_MSG, ground_truth->name, student_answer == NULL ? "NULL" : student_answer->name);

    // ensure that they have not modified the trainer before returning pointer to it
    assert_trainers_equal(student_answer, ground_truth,
                          "Checking that trainer of returned pointer isn't modified in find_champion()");
    // ensure gym is unchanged
    assert_gyms_equal(&gt_gym, &gym, "Checking that gym is unchanged");
}
END_TEST

START_TEST(test_find_champion_empty_gym)
{
    ck_assert_msg(find_champion() == NULL, "find_champion() on an empty gym should return NULL");
}
END_TEST

/**
 * Wipe out the array - since they are globals, it is reasonable for students to expect the array to be zeroed and size to be 0 before each test
 * Also try to detect any funky stuff going on with including <string(s).h>
 */
void init_gym(struct Gym *g)
{
    memset(g->trainers, 0, sizeof(struct Trainer) * MAX_TRAINER_LENGTH);
    g->num_trainers = 0;
}

static void setup(void)
{
    init_gym(&gym);
    init_gym(&gt_gym);
}

Suite *pkmn_gym_suite(void)
{
    Suite *s = suite_create("pkmn_gym_suite");

    // register_trainer
    tcase_add(s, setup, NULL, test_register_trainer_normal);
    tcase_add(s, setup, NULL, test_register_trainer_null_check);
    tcase_add(s, setup, NULL, test_register_trainer_extra_long_name);
    tcase_add(s, setup, NULL, test_register_trainer_full_gym);

    // unregister_trainer
    tcase_add(s, setup, NULL, test_unregister_trainer_normal);
    tcase_add(s, setup, NULL, test_unregister_trainer_null_check);
    tcase_add(s, setup, NULL, test_unregister_trainer_extra_long_name);

    // register & unregister
    tcase_add(s, setup, NULL, test_register_unregister_coverage_basic);

    // catch/release pokemon
    tcase_add(s, setup, NULL, test_catch_pokemon_basic);
    tcase_add(s, setup, NULL, test_catch_pokemon_null_check);
    tcase_add(s, setup, NULL, test_release_pokemon_null_checks);
    tcase_add(s, setup, NULL, test_catch_and_release_coverage_test);

    // count_species
    tcase_add(s, setup, NULL, test_count_species_basic);
    tcase_add(s, setup, NULL, test_count_species_none);
    tcase_add(s, setup, NULL, test_count_species_invalid_string_argument);
    tcase_add(s, setup, NULL, test_count_species_duplicate_species_in_party);
    tcase_add(s, setup, NULL, test_count_species_max_trainers);

    // trade_pokemon
    tcase_add(s, setup, NULL, test_trade_pokemon_basic);
    tcase_add(s, setup, NULL, test_trade_pokemon_coverage);
    tcase_add(s, setup, NULL, test_trade_pokemon_index_too_large);
    tcase_add(s, setup, NULL, test_trade_pokemon_invalid_index);
    tcase_add(s, setup, NULL, test_trade_pokemon_invalid_trainer);
    tcase_add(s, setup, NULL, test_trade_pokemon_same_trainer);

    // battle_trainer
    tcase_add(s, setup, NULL, test_battle_trainer_basic);
    tcase_add(s, setup, NULL, test_battle_trainer_no_pokemon);
    tcase_add(s, setup, NULL, test_battle_trainer_same_level);
    tcase_add(s, setup, NULL, test_battle_trainer_unequal_party_count);
    tcase_add(s, setup, NULL, test_battle_trainer_unequal_party_count_lesser_wins);
    tcase_add(s, setup, NULL, test_battle_trainer_unequal_party_count_even_tie);
    tcase_add(s, setup, NULL, test_battle_trainer_null_input);

    // find_champion
    tcase_add(s, setup, NULL, test_find_champion_basic);
    tcase_add(s, setup, NULL, test_find_champion_same_wins);
    tcase_add(s, setup, NULL, test_find_champion_no_wins);
    tcase_add(s, setup, NULL, test_find_champion_empty_gym);

    // Return Testing Suite
    return s;
}
