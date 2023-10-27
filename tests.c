#include <stdio.h>
#include <assert.h>
#include <time.h>
#include "./evaluator/kev_eval.h"
#include "royalty_calculator.h"

void test_score()
{
    // test pairs
    short score_AA = kev_eval_5cards(50, 49, 2, 5, 10);
    assert(score_AA == 3545);
    short score_22 = kev_eval_5cards(2, 1, 14, 5, 10);
    assert(score_22 == 6185);
    short score_99_low = kev_eval_5cards(30, 29, 2, 5, 10);
    assert(score_99_low == 4645);
    short score_99_high = kev_eval_5cards(30, 29, 50, 45, 42);
    assert(score_99_high == 4426);

    // test 2 pairs
    short score_2_pairs_low = kev_eval_5cards(2, 1, 6, 5, 10);
    assert(score_2_pairs_low == 3325);
    short score_2_pairs_high = kev_eval_5cards(50, 49, 46, 45, 42);
    assert(score_2_pairs_high == 2468);

    // test sets
    short score_set_low = kev_eval_5cards(2, 1, 3, 5, 10);
    assert(score_set_low == 2467);
    short score_set_high = kev_eval_5cards(50, 49, 51, 45, 42);
    assert(score_set_high == 1610);

    // test flushes and straights
    short score_flush = kev_eval_5cards(50, 26, 18, 10, 14);
    assert(score_flush == 792);
    short score_str_high = kev_eval_5cards(50, 46, 42, 38, 35);
    assert(score_str_high == 1600);
    short score_str_low = kev_eval_5cards(50, 2, 6, 10, 15);
    assert(score_str_low == 1609);

    // test 4oak
    short score_foak_low = kev_eval_5cards(2, 3, 1, 0, 7);
    assert(score_foak_low == 166);
    short score_foak_high = kev_eval_5cards(50, 51, 49, 48, 47);
    assert(score_foak_high == 11);

    // test Straight and Royal Flushes
    short score_SF = kev_eval_5cards(50, 2, 6, 10, 14);
    assert(score_SF == 10);
    short score_RF = kev_eval_5cards(50, 46, 42, 38, 34);
    assert(score_RF == 1);

    printf("Score test passed.\n");
}

void test_royalty()
{
    // test straight
    char royalti_str_mid_high = get_fantasy_score_mid(1600);
    assert(royalti_str_mid_high == 4);
    char royalti_str_mid_low = get_fantasy_score_mid(1609);
    assert(royalti_str_mid_low == 4);
    
    // test flushes
    char royalti_flush_mid_low = get_fantasy_score_mid(1599);
    assert(royalti_flush_mid_low == 8);
    char royalti_flush_mid_high = get_fantasy_score_mid(323);
    assert(royalti_flush_mid_high == 8);

    // test sets
    char royalti_set_mid_low = get_fantasy_score_mid(2467);
    assert(royalti_set_mid_low == 2);
    char royalti_set_mid_high = get_fantasy_score_mid(1610);
    assert(royalti_set_mid_high == 2);

    // test front
    char royalti_55_front = get_fantasy_score_front(5306);
    assert(royalti_55_front == 0);
    char royalti_66_front = get_fantasy_score_front(5305);
    assert(royalti_66_front == 1);
    char royalti_AA_front = get_fantasy_score_front(3326);
    assert(royalti_AA_front == 9);
    char royalti_222_front = get_fantasy_score_front(2467);
    assert(royalti_222_front == 10);
    char royalti_AAA_front = get_fantasy_score_front(1610);
    assert(royalti_AAA_front == 22);

    char royalti_2_pairs_front = get_fantasy_score_front(3258);
    assert(royalti_2_pairs_front == 0);
    char royalti_FH_front = get_fantasy_score_front(167);
    assert(royalti_FH_front == 0);
    char royalti_FH_low_front = get_fantasy_score_front(322);
    assert(royalti_FH_low_front == 0);

    printf("Royalty test passed.\n");
}

void test_time()
{
    clock_t start_worst = clock();
    for (int i = 0; i < 100000000; i++){
        get_fantasy_score_mid(2);
    }
    clock_t end_worst = clock();

    double elapsed_worst = (double)(end_worst - start_worst) / CLOCKS_PER_SEC;

    printf("Time test, worst case: %.3f seconds.\n", elapsed_worst);

    clock_t start_best = clock();
    for (int i = 0; i < 100000000; i++){
        get_fantasy_score_mid(5100);
    }
    clock_t end_best = clock();

    double elapsed_best = (double)(end_best - start_best) / CLOCKS_PER_SEC;

    printf("Time test, best case: %.3f seconds.\n", elapsed_best);
}


int main()
{
    test_score();
    test_royalty();
    test_time();    

    return 0;
}