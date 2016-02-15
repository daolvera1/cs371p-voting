// ----------------------------
// projects/voting/Collatz.c++
// Copyright (C) 2016
// Glenn P. Downing
// ----------------------------

// --------
// includes
// --------

#include <cassert>  // assert
#include <iostream> // endl, istream, ostream
#include <sstream>  // istringstream
#include <string>   // getline, string
#include <utility>  // make_pair, pair
#include <vector>
#include "Voting.h"

using namespace std;

// ------------
// voting_read
// ------------


pair<int, int> voting_read (const string& s) {
    istringstream sin(s);
    int i;
    int j;
    sin >> i >> j;
    return make_pair(i, j);
}

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
        val = get_length(temp);
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
// -------------

void voting_solve (istream& r, ostream& w) {
    string s;
    getline(r, s);
    istringstream sin(s); //get test cases
    int test_cases;
    sin >> test_cases;
    cout  << "number of test cases: " << test_cases <<endl;



/* while (getline(r, s)) {
        const pair<int, int> p = voting_read(s);
        const int            i = p.first;
        const int            j = p.second;
        const int            v = voting_eval(i, j);
        voting_print(w, i, j, v);
    }*/
}