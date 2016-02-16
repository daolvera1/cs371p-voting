// ----------------------------
// projects/voting/Collatz.c++
// Copyright (C) 2016
// Glenn P. Downing
// ----------------------------

// --------
// includes
// --------


#include <iterator>  // iterate vector
#include <algorithm>  // print vector
#include <cassert>  // assert
#include <iostream> // endl, istream, ostream
#include <fstream> // endl, istream, ostream
#include <sstream>  // istringstream
#include <string>   // getline, string
#include <utility>  // make_pair, pair
#include <vector>   //vector
#include "Voting.h"

using namespace std;
//vecto> names;
// ------------
// voting_read
// ------------

class Candidate 
{
private:
    string name;
    vector<vector<int>> ballot_box;
public:
    Candidate (string s){name = s;} //constructor
    void add_ballot(vector<int> v){ballot_box.push_back(v);} //adds ballot to their ballot box
    vector<vector<int>> get_box(){return ballot_box;}
    string get_name(){return name;} //dont know if need this

};

vector<int> voting_read (const string& s) {
    vector<int> ballot;
	istringstream sin(s);
    /*int i;
    int j;
    int k;
    int l;
    sin >> i >> j >> k >> l;
	ballot.push_back(i);
	ballot.push_back(j);
	ballot.push_back(k);
	ballot.push_back(l);*/
    int i;	
	while(sin >> i)
		ballot.push_back(i);
    return ballot;
}
/*
// ------------
// get_length
// ------------
int get_length(int n){
    assert(n > 0);

    int cycle = 1;
        while ( n > 1 ){

            #ifdef fast
    		if( n < 1000000 && cache.at(n) > 0){
                return cache.at(n) + cycle -1;
            }
            #endif

            if(n % 2 == 0){
                n=n/2;
            }
    		else {
                n=3*n+1;
            }
            cycle++;

        }

    assert(cycle > 0);

    return cycle;
}
*/
// ------------
// voting_eval
// ------------
int voting_eval (int i, int j) {
    // <your code>

    int max = 1, val = 0;
    int low = 0, high = 0;
    if(i < j){
        low = i;
        high = j;
    } else {
        low = j;
        high = i;}
    for (int temp = low ; temp <= high; temp++){ //iterate through the range of values (i.e. 1 10)

       #ifdef fast
        if (cache.at(temp) > 0){ //if value previously cached, do lookup
			val = cache.at(temp);
        }
        else { //if value isn't in cache, find cycle length and cache it
            val = get_length(temp);
            cache.at(temp)=val;
        }
        #endif

        #ifndef fast
       // val = get_length(temp);
        #endif


        if(val > max){ //finding max cycle length
            max = val;
        }
	}
    return max;

}



// -------------
// voting_print
// -------------

void voting_print (ostream& w, int i, int j, int v) {
    w << i << " " << j << " " << v << endl;
}

// -------------
// voting_solve
//

int num_testcases_candidates(const string& s){

    istringstream sin(s);
    int num_testcases;
    sin >> num_testcases;
    return num_testcases;

}



void voting_solve (istream& r, ostream& w) {
    string s;
    getline(r, s);
    const int number_tests = num_testcases_candidates(s);
    for(int tests = 0; tests < number_tests ; tests++){
            
            if (tests == 0) 
				getline(r,s); //skip empty line

            getline(r,s); //num candidates

            const int number_candidates = num_testcases_candidates(s);
            vector<Candidate> _candidates;
            //getting names of candidates
            for (int i = 0;i < number_candidates; i++){

                getline(r,s); // get candidate names
				//names.push_back(s);	
                Candidate cand(s);	
                _candidates.push_back(cand); //add candidate into vector of candidates	
            } 
            
			vector<int> ballots;
            while(getline(r,s)){
				if(s.empty()) 
					break;
				else { 
					ballots = voting_read(s); // parse ballot into vector
                    int candidate_number = ballots.front();

					_candidates.at(candidate_number - 1).add_ballot(ballots); //add ballot to apprioriate candidate box
				}
            }


    }



/* while (getline(r, s)) {
        const pair<int, int> p = voting_read(s);
        const int            i = p.first;
        const int            j = p.second;
        const int            v = voting_eval(i, j);
        voting_print(w, i, j, v);
    }*/
}
