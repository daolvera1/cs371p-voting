// --------------------------
// projects/voting/Voting.h
// Copyright (C) 2016
// Glenn P. Downing
// --------------------------

#ifndef Voting_h
#define Voting_h

// --------
// includes
// --------

#include <iostream> // istream, ostream
#include <string>   // string
#include <utility>  // pair
#include <vector>  // vector


using namespace std;

// ------------
// voting_read
// ------------

/**
 * read two ints
 * @param s a string
 * @return a pair of ints, representing the beginning and end of a range, [i, j]
 */
vector<int> voting_read (const string& s);

// ------------
// voting_eval
// ------------

/**
 * @param i the beginning of the range, inclusive
 * @param j the end       of the range, inclusive
 * @return the max cycle length of the range [i, j]
 */
int voting_eval (int i, int j);

// ------------
// voting_eval
// ------------

/**
 * @param i the beginning of the range, 1 - 1000000
 * @return cycle length of i
 */
//int get_length (int i);

// -------------
// voting_print
// -------------

/**
 * print three ints
 * @param w an ostream
 * @param i the beginning of the range, inclusive
 * @param j the end       of the range, inclusive
 * @param v the max cycle length
 */
void voting_print (ostream& w, int i, int j, int v);

// -------------
// voting_solve
// -------------

/**
 * @param r an istream
 * @param w an ostream
 */
void voting_solve (istream& r, ostream& w);
int num_testcases_candidates(const string& s);
#endif // Voting_h
