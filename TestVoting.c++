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
#include <algorithm>
#include "gtest/gtest.h"

#include "Voting.h"
using namespace std;

// -----------
// TestVoting
// -----------

// ----
// num_testcases_candidates
// ----

TEST(Ballot_class, get_alt_1){
	vector<int> v = {1,2,3,4};
	Ballot b(v);
	int i = b.get_alternate();
	ASSERT_EQ(i, 2);
}
TEST(Ballot_class, get_alt_2){
	vector<int> v = {1,2,3,4};
	Ballot b(v);
	int i = b.get_alternate();
	i = b.get_alternate();
	ASSERT_EQ(i, 3);
}

TEST(Ballot_class, get_alt_3){
	vector<int> v = {1,2,3,4};
	Ballot b(v);
	int i = b.get_alternate();
	i = b.get_alternate();
	i = b.get_alternate();
	ASSERT_EQ(i, 4);
}


TEST(num_testcases_test, read_0) {
    string s("0\n");
    const int p = num_testcases_candidates(s);
    ASSERT_EQ( p, 0);
}
TEST(num_testcases_test, read_1) {
    string s("1\n");
    const int p = num_testcases_candidates(s);
    ASSERT_EQ( p, 1);
}
TEST(num_testcases_test, read_100) {
    string s("100\n");
    const int p = num_testcases_candidates(s);
    ASSERT_EQ( p, 100);
}


// ----
// voting_read
// ----

TEST(voting_read_test, voting_read_1) {
    string s("1 2 3 4\n");
    vector<int> expect = {1,2,3,4};
    vector<int> actual = voting_read(s);
    for(int i = 0;i < (int) actual.size(); i++)	
        ASSERT_EQ( expect.at(i), actual.at(i));
}
TEST(voting_read_test, voting_read_more_numbers) {
    string s("1 2 3 4 5 6 7 8 9 10\n");
    vector<int> expect = {1,2,3,4,5,6,7,8,9,10};
    vector<int> actual = voting_read(s);
    for(int i = 0;i < (int) actual.size(); i++)	
        ASSERT_EQ( expect.at(i), actual.at(i));
}
TEST(voting_read_test, voting_random_numbers) {
    string s("3 5 2 6 7 1 4\n");
    vector<int> expect = {3,5,2,6,7,1,4};
    vector<int> actual = voting_read(s);
    for(int i = 0;i < (int) actual.size(); i++)	
        ASSERT_EQ( expect.at(i), actual.at(i));
}

// ----
// voting_print
// ----

/*TEST(ballot_counter_test, counter_1) {
	int ballots = 1;
	vector<Candidate*> original;

	vector<string> names ={"bob", "mary", "gary"};

	for (int i = 0; i < 3;i++)
		original.push_back(new Candidate(names.at(i)));

	vector<int> vec = {1,2,3};
	original.at(0) -> add_ballot(new Ballot(vec));
	vector<Candidate*> temp;
	
	for(int i = 0; i < 3; i++){
		temp.push_back(original.at(i));
	}
	sort(temp.begin(), temp.end(), [](Candidate* c1, Candidate* c2){
				return c1 -> number_votes() > c2->number_votes();});


    vector<Candidate*> actual = ballot_counter(temp, ballots, original);
     ASSERT_EQ("bob", actual.at(0) -> get_name());
}
*/


/*TEST(ballot_counter_test, counter_2) {
	int ballots = 1;
	vector<Candidate*> original;

	vector<string> names ={"bob", "mary", "gary"};

	for (int i = 0; i < 3;i++)
		original.push_back(new Candidate(names.at(i)));

	vector<int> vec = {1,2,3};
	original.at(1) -> add_ballot(new Ballot(vec));
	vector<Candidate*> temp;
	
	for(int i = 0; i < 3; i++){
		temp.push_back(original.at(i));
	}
	sort(temp.begin(), temp.end(), [](Candidate* c1, Candidate* c2){
				return c1 -> number_votes() > c2->number_votes();});


    vector<Candidate*> actual = ballot_counter(temp, ballots, original);
     ASSERT_EQ("mary",actual.at(0)->get_name());
}

TEST(ballot_counter_test, counter_3) {
	int ballots = 1;
	vector<Candidate*> original;

	vector<string> names ={"bob", "mary", "gary"};

	for (int i = 0; i < 3;i++)
		original.push_back(new Candidate(names.at(i)));

	vector<int> vec = {1,2,3};
	original.at(2) -> add_ballot(new Ballot(vec));
	vector<Candidate*> temp;
	
	for(int i = 0; i < 3; i++){
		temp.push_back(original.at(i));
	}
	sort(temp.begin(), temp.end(), [](Candidate* c1, Candidate* c2){
				return c1 -> number_votes() > c2->number_votes();});


    vector<Candidate*> actual = ballot_counter(temp, ballots, original);
     ASSERT_EQ("gary",actual.at(0)->get_name());
}*/


/*TEST(voting_print_test, print_name) {
    ostringstream w;
    voting_print(w, "Daniel Olvera");
    ASSERT_EQ("Daniel Olvera\n", w.str());
}*/
TEST(voting_solve_test, voting_solve_1) {
    ostringstream w;
    istringstream r ("1\n\n2\nA\nB\n1 2\n1 2\n1 2");
    voting_solve(r,w);
    ASSERT_EQ("A", w.str());
}

TEST(voting_solve_test, voting_solve_2) {
    ostringstream w;
    istringstream r ("1\n\n1\nA\n1\n1\n1");
    voting_solve(r,w);
    ASSERT_EQ("A", w.str());
}

TEST(voting_solve_test, voting_solve_3) {
    ostringstream w;
    istringstream r ("1\n\n2\nA\nB\n2 1\n1 2\n2 1");
    voting_solve(r,w);
    ASSERT_EQ("B", w.str());
}



// ----
// ballot_counter
// ----

TEST(voting_print_test, print_1) {
    ostringstream w;
    voting_print(w, "a", false);
    ASSERT_EQ("a\n", w.str());
}
TEST(voting_print_test, print_name) {
    ostringstream w;
    voting_print(w, "Daniel Olvera", false);
    ASSERT_EQ("Daniel Olvera\n", w.str());
}
TEST(voting_print_test, print_long_name) {
    ostringstream w;
    voting_print(w, "testing voting_print_test", false);
    ASSERT_EQ("testing voting_print_test\n", w.str());
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
