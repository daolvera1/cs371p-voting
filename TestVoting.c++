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

TEST(num_testcases_test, read_1) {
    string s("0\n");
    const int p = num_testcases_candidates(s);
    ASSERT_EQ( p, 0);
}
TEST(num_testcases_test, read_2) {
    string s("1\n");
    const int p = num_testcases_candidates(s);
    ASSERT_EQ( p, 1);
}
TEST(num_testcases_test, read_3) {
    string s("100\n");
    const int p = num_testcases_candidates(s);
    ASSERT_EQ( p, 100);
}

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
