// --------------------------------
// projects/collatz/TestCollatz.c++
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

#include "Collatz.h"

using namespace std;

// -----------
// TestCollatz
// -----------

// ----
// read
// ----

TEST(CollatzFixture, read_1) {
    string s("1 10\n");
    const pair<int, int> p = collatz_read(s);
    ASSERT_EQ( 1, p.first);
    ASSERT_EQ(10, p.second);}

TEST(CollatzFixture, read_2) {
    string s("252 525\n");
    const pair<int, int> p = collatz_read(s);
    ASSERT_EQ(252, p.first);
    ASSERT_EQ(525, p.second);}

TEST(CollatzFixture, read_3) {
    string s("1 100\n");
    const pair<int, int> p = collatz_read(s);
    ASSERT_EQ( 1, p.first);
    ASSERT_EQ(100, p.second);}

TEST(CollatzFixture, read_4) {
    string s("555 565\n");
    const pair<int, int> p = collatz_read(s);
    ASSERT_EQ( 555, p.first);
    ASSERT_EQ(565, p.second);}

// ----
// eval
// ----

TEST(CollatzFixture, eval_1) {
    const int v = collatz_eval(1, 10);
    ASSERT_EQ(20, v);}

TEST(CollatzFixture, eval_2) {
    const int v = collatz_eval(100, 200);
    ASSERT_EQ(125, v);}

TEST(CollatzFixture, eval_3) {
    const int v = collatz_eval(201, 210);
    ASSERT_EQ(89, v);}

TEST(CollatzFixture, eval_4) {
    const int v = collatz_eval(900, 1000);
    ASSERT_EQ(174, v);}

TEST(CollatzFixture, eval_5) {
    const int v = collatz_eval(10, 1);
    ASSERT_EQ(20, v);}

TEST(CollatzFixture, eval_6) {
    const int v = collatz_eval(1, 1);
    ASSERT_EQ(1, v);}

TEST(CollatzFixture, eval_7) {
    const int v = collatz_eval(5, 4);
    ASSERT_EQ(6, v);}


// -----
// get_length
// -----

TEST(CollatzFixture, len_1) {
    const int v = get_length(10);
    ASSERT_EQ(7, v);}

TEST(CollatzFixture, len_2) {
    const int v = get_length(1);
    ASSERT_EQ(1, v);}

TEST(CollatzFixture, len_3) {
    const int v = get_length(232);
    ASSERT_EQ(22, v);}


// -----
// print
// -----

TEST(CollatzFixture, print_1) {
    ostringstream w;
    collatz_print(w, 1, 10, 20);
    ASSERT_EQ("1 10 20\n", w.str());}

TEST(CollatzFixture, print_2) {
    ostringstream w;
    collatz_print(w, 3, 4, 8);
    ASSERT_EQ("3 4 8\n", w.str());}

TEST(CollatzFixture, print_3) {
    ostringstream w;
    collatz_print(w, 2, 100, 119);
    ASSERT_EQ("2 100 119\n", w.str());}

TEST(CollatzFixture, print_4) {
    ostringstream w;
    collatz_print(w, 5, 4, 6);
    ASSERT_EQ("5 4 6\n", w.str());}

// -----
// solve
// -----

TEST(CollatzFixture, solve_1) {
   // istringstream r("1 10\n100 200\n201 210\n900 1000\n1000 1632");
    istringstream r("1 10\n100 200\n201 210\n900 1000");
    ostringstream w;
    collatz_solve(r, w);
    ASSERT_EQ("1 10 20\n100 200 125\n201 210 89\n900 1000 174\n", w.str());}

 TEST(CollatzFixture, solve_2) {
   // istringstream r("1 10\n100 200\n201 210\n900 1000\n1000 1632");
    istringstream r("2 2\n3 3\n2 100\n4 5");
    ostringstream w;
    collatz_solve(r, w);
    ASSERT_EQ("2 2 2\n3 3 8\n2 100 119\n4 5 6\n", w.str());}
TEST(CollatzFixture, solve_3) {
   // istringstream r("1 10\n100 200\n201 210\n900 1000\n1000 1632");
    istringstream r("621 126\n423 621\n333 333\n1 100");
    ostringstream w;
    collatz_solve(r, w);
    ASSERT_EQ("621 126 144\n423 621 142\n333 333 113\n1 100 119\n", w.str());}
TEST(CollatzFixture, solve_4) {
   // istringstream r("1 10\n100 200\n201 210\n900 1000\n1000 1632");
    istringstream r("100 1\n123 256\n741 6\n845 963");
    ostringstream w;
    collatz_solve(r, w);
    ASSERT_EQ("100 1 119\n123 256 128\n741 6 171\n845 963 179\n", w.str());}   

/*
% g++ -fprofile-arcs -ftest-coverage -pedantic -std=c++11 -Wall Collatz.c++ TestCollatz.c++ -o TestCollatz -lgtest -lgtest_main -lpthread
% valgrind TestCollatz                                         >  TestCollatz.out 2>&1
% gcov -b Collatz.c++     | grep -A 5 "File 'Collatz.c++'"     >> TestCollatz.out
% gcov -b TestCollatz.c++ | grep -A 5 "File 'TestCollatz.c++'" >> TestCollatz.out
% cat TestCollatz.out
==14225== Memcheck, a memory error detector
==14225== Copyright (C) 2002-2011, and GNU GPL'd, by Julian Seward et al.
==14225== Using Valgrind-3.7.0 and LibVEX; rerun with -h for copyright info
==14225== Command: TestCollatz
==14225==
Running main() from gtest_main.cc
[==========] Running 7 tests from 1 test case.
[----------] Global test environment set-up.
[----------] 7 tests from Collatz
[ RUN      ] Collatz.read
[       OK ] Collatz.read (31 ms)
[ RUN      ] Collatz.eval_1
[       OK ] Collatz.eval_1 (5 ms)
[ RUN      ] Collatz.eval_2
[       OK ] Collatz.eval_2 (3 ms)
[ RUN      ] Collatz.eval_3
[       OK ] Collatz.eval_3 (3 ms)
[ RUN      ] Collatz.eval_4
[       OK ] Collatz.eval_4 (3 ms)
[ RUN      ] Collatz.print
[       OK ] Collatz.print (17 ms)
[ RUN      ] Collatz.solve
[       OK ] Collatz.solve (10 ms)
[----------] 7 tests from Collatz (88 ms total)
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
File 'Collatz.c++'
Lines executed:100.00% of 17
Branches executed:100.00% of 18
Taken at least once:61.11% of 18
Calls executed:89.47% of 19
Creating 'Collatz.c++.gcov'
File 'TestCollatz.c++'
Lines executed:100.00% of 26
Branches executed:57.14% of 224
Taken at least once:28.57% of 224
Calls executed:54.07% of 209
Creating 'TestCollatz.c++.gcov'
*/