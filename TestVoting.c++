// --------------------------------
// projects/voting/TestVoting.c++
// Copyright (C) 2016
// Glenn P. Downing
// --------------------------------

// https://code.google.com/p/googletest/wiki/V1_7_Primer#Basic_Assertions

// --------
// includes
// --------

#include <iostream> // cout, endl
#include <sstream>  // istringtstream, ostringstream
#include <string>   // string
#include <utility>  // pair

#include "gtest/gtest.h"

#include "Voting.h"

using namespace std;

// -----------
// TestVoting
// -----------

// ----
// read
// ----

/*TEST(VotingFixture, read_1) {
    string s("1 10\n");
    const pair<int, int> p = voting_read(s);
    ASSERT_EQ( 1, p.first);
    ASSERT_EQ(10, p.second);}

TEST(VotingFixture, read_2) {
    string s("252 525\n");
    const pair<int, int> p = voting_read(s);
    ASSERT_EQ(252, p.first);
    ASSERT_EQ(525, p.second);}

TEST(VotingFixture, read_3) {
    string s("1 100\n");
    const pair<int, int> p = voting_read(s);
    ASSERT_EQ( 1, p.first);
    ASSERT_EQ(100, p.second);}

TEST(VotingFixture, read_4) {
    string s("555 565\n");
    const pair<int, int> p = voting_read(s);
    ASSERT_EQ( 555, p.first);
    ASSERT_EQ(565, p.second);}

// ----
// eval
// ----

TEST(VotingFixture, eval_1) {
    const int v = voting_eval(1, 10);
    ASSERT_EQ(20, v);}

TEST(VotingFixture, eval_2) {
    const int v = voting_eval(100, 200);
    ASSERT_EQ(125, v);}

TEST(VotingFixture, eval_3) {
    const int v = voting_eval(201, 210);
    ASSERT_EQ(89, v);}

TEST(VotingFixture, eval_4) {
    const int v = voting_eval(900, 1000);
    ASSERT_EQ(174, v);}

TEST(VotingFixture, eval_5) {
    const int v = voting_eval(10, 1);
    ASSERT_EQ(20, v);}

TEST(VotingFixture, eval_6) {
    const int v = voting_eval(1, 1);
    ASSERT_EQ(1, v);}

TEST(VotingFixture, eval_7) {
    const int v = voting_eval(5, 4);
    ASSERT_EQ(6, v);}


// -----
// get_length
// -----

TEST(VotingFixture, len_1) {
    const int v = get_length(10);
    ASSERT_EQ(7, v);}

TEST(VotingFixture, len_2) {
    const int v = get_length(1);
    ASSERT_EQ(1, v);}

TEST(VotingFixture, len_3) {
    const int v = get_length(232);
    ASSERT_EQ(22, v);}


// -----
// print
// -----

TEST(VotingFixture, print_1) {
    ostringstream w;
    voting_print(w, 1, 10, 20);
    ASSERT_EQ("1 10 20\n", w.str());}

TEST(VotingFixture, print_2) {
    ostringstream w;
    voting_print(w, 3, 4, 8);
    ASSERT_EQ("3 4 8\n", w.str());}

TEST(VotingFixture, print_3) {
    ostringstream w;
    voting_print(w, 2, 100, 119);
    ASSERT_EQ("2 100 119\n", w.str());}

TEST(VotingFixture, print_4) {
    ostringstream w;
    voting_print(w, 5, 4, 6);
    ASSERT_EQ("5 4 6\n", w.str());}*/

// -----
// solve
// -----
/*
TEST(VotingFixture, solve_1) {
   // istringstream r("1 10\n100 200\n201 210\n900 1000\n1000 1632");
    istringstream r("1 10\n100 200\n201 210\n900 1000");
    ostringstream w;
    voting_solve(r, w);
    ASSERT_EQ("1 10 20\n100 200 125\n201 210 89\n900 1000 174\n", w.str());}

 TEST(VotingFixture, solve_2) {
   // istringstream r("1 10\n100 200\n201 210\n900 1000\n1000 1632");
    istringstream r("2 2\n3 3\n2 100\n4 5");
    ostringstream w;
    voting_solve(r, w);
    ASSERT_EQ("2 2 2\n3 3 8\n2 100 119\n4 5 6\n", w.str());}
TEST(VotingFixture, solve_3) {
   // istringstream r("1 10\n100 200\n201 210\n900 1000\n1000 1632");
    istringstream r("621 126\n423 621\n333 333\n1 100");
    ostringstream w;
    voting_solve(r, w);
    ASSERT_EQ("621 126 144\n423 621 142\n333 333 113\n1 100 119\n", w.str());}
TEST(VotingFixture, solve_4) {
   // istringstream r("1 10\n100 200\n201 210\n900 1000\n1000 1632");
    istringstream r("100 1\n123 256\n741 6\n845 963");
    ostringstream w;
    voting_solve(r, w);
    ASSERT_EQ("100 1 119\n123 256 128\n741 6 171\n845 963 179\n", w.str());}   */

/*
% g++ -fprofile-arcs -ftest-coverage -pedantic -std=c++11 -Wall Voting.c++ TestVoting.c++ -o TestVoting -lgtest -lgtest_main -lpthread
% valgrind TestVoting                                         >  TestVoting.out 2>&1
% gcov -b Voting.c++     | grep -A 5 "File 'Voting.c++'"     >> TestVoting.out
% gcov -b TestVoting.c++ | grep -A 5 "File 'TestVoting.c++'" >> TestVoting.out
% cat TestVoting.out
==14225== Memcheck, a memory error detector
==14225== Copyright (C) 2002-2011, and GNU GPL'd, by Julian Seward et al.
==14225== Using Valgrind-3.7.0 and LibVEX; rerun with -h for copyright info
==14225== Command: TestVoting
==14225==
Running main() from gtest_main.cc
[==========] Running 7 tests from 1 test case.
[----------] Global test environment set-up.
[----------] 7 tests from Voting
[ RUN      ] Voting.read
[       OK ] Voting.read (31 ms)
[ RUN      ] Voting.eval_1
[       OK ] Voting.eval_1 (5 ms)
[ RUN      ] Voting.eval_2
[       OK ] Voting.eval_2 (3 ms)
[ RUN      ] Voting.eval_3
[       OK ] Voting.eval_3 (3 ms)
[ RUN      ] Voting.eval_4
[       OK ] Voting.eval_4 (3 ms)
[ RUN      ] Voting.print
[       OK ] Voting.print (17 ms)
[ RUN      ] Voting.solve
[       OK ] Voting.solve (10 ms)
[----------] 7 tests from Voting (88 ms total)
[----------] Global test environment tear-down
[==========] 7 tests from 1 test case ran. (132 ms total)
[  PASSED  ] 7 tests.
==14225==
==14225== HEAP SUMMARY:
==14225==     in use at exit: 0 bytes in 0 blocks
==14225==   total heap usage: 495 allocs, 495 frees, 70,302 bytes allocated
==14225==
==14225== All heap blocks were freed -- no leaks are possible
==14225==
==14225== For counts of detected and suppressed errors, rerun with: -v
==14225== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 2 from 2)
File 'Voting.c++'
Lines executed:100.00% of 17
Branches executed:100.00% of 18
Taken at least once:61.11% of 18
Calls executed:89.47% of 19
Creating 'Voting.c++.gcov'
File 'TestVoting.c++'
Lines executed:100.00% of 26
Branches executed:57.14% of 224
Taken at least once:28.57% of 224
Calls executed:54.07% of 209
Creating 'TestVoting.c++.gcov'
*/