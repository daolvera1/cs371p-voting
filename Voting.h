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

class Ballot {
private:
    vector<int> votes;
    int pref = 0;
public: 
    Ballot(vector<int>& v);
    int get_alternate();};
class Candidate
{
private:
    string name;
    vector<Ballot*> ballot_box;
    bool loser = false;
    bool wins = false;
public:
    Candidate (string s); //constructor
    void add_ballot(Ballot* v); //adds ballot to their ballot box
    vector<Ballot*> get_box();
    int number_votes();
    string get_name(); //dont know if need this
    void make_loser();
    bool check_loser();
    bool check_winner();
    void make_winner();
};

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
void voting_print (ostream& w, string s, bool last);

// -------------
// voting_solve
// -------------

/**
 * @param r an istream
 * @param w an ostream
 */
void voting_solve (istream& r, ostream& w);
int num_testcases_candidates(const string& s);
vector<Candidate*> ballot_counter(vector<Candidate*>& _box, const int total_ballots, 
			vector<Candidate*> & _original_box);
#endif // Voting_h
