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
    bool loser = false;
public:
    Candidate (string s){name = s;} //constructor
    void add_ballot(vector<int> v){ballot_box.push_back(v);} //adds ballot to their ballot box
    vector<vector<int>> get_box(){return ballot_box;}
    int number_votes(){
        int size = ballot_box.size();
        return size;}
    string get_name(){return name;} //dont know if need this
    bool operator<(const Candidate &other) const{
        return ballot_box.size() < ballot_box.size();
    }
    void make_loser(){loser = true;}
    bool check_lower(){return loser;}
};

vector<int> voting_read (const string& s) {
    vector<int> ballot;
	istringstream sin(s);
    int i;
	while(sin >> i)
		ballot.push_back(i);
    return ballot;
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

vector<Candidate> ballot_counter(vector<Candidate>& _box, const int total_ballots){
    vector<Candidate> winners;
    int tied = 1, num_cand=_box.size(), round = 0;
    for(int i = 0; i < num_cand; i++){

      cout << "Getting number votes: " << _box.at(i).number_votes() << endl;
    }
    while (1){
        //check if any candidates have over 50%
        int min = _box.at(0).number_votes(); // set min number votes to max
        int index_memory = 0;
        for(int i = 0; i < num_cand; i++){
            Candidate cand = _box.at(i);
            cout << double (cand.number_votes())  / total_ballots << endl;
            if((double (cand.number_votes()) / total_ballots )> .5){
               winners.push_back(cand);
            }
            else if(i > 0 && cand.number_votes() != _box.at(i - 1).number_votes())
                tied = 0;

            //find min number of votes
            if(cand.number_votes() < min){
                min = cand.number_votes();
                index_memory = i;
            }
        }

        if(!winners.empty()) {return winners;}

        //check if all candidates have equal votes
        else if(tied){return _box;}

        else  //eliminate losers
        {
            for(int i = index_memory; i < num_cand; ++i){
                if(_box.at(i).number_votes() == min) //remove candidates
                    vector<int> removed_ballot = _box.at(i).get_box();
                    cout << "removing Candidate " << _box.at(i).get_name() << "\n\n" << endl;
                    _box.erase(i);
            }
        }

          return winners;
    }
}



void voting_solve (istream& r, ostream& w) {
    string s;
    getline(r, s);
    int count = 0;
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
                    count++;
                    int candidate_number = ballots.front();

					_candidates.at(candidate_number - 1).add_ballot(ballots); //add ballot to apprioriate candidate box
				}
          }
            sort(_candidates.begin(), _candidates.end());

            vector<Candidate> winner = ballot_counter(_candidates,count);
            int num_win = winner.size();
            for(int i = 0; i < num_win; i++){
                cout << "printing winner " << winner.at(i).get_name();
            }
            //voting_print();

    }

/* while (getline(r, s)) {
        const pair<int, int> p = voting_read(s);
        const int            i = p.first;
        const int            j = p.second;
        const int            v = voting_eval(i, j);
        voting_print(w, i, j, v);
    }*/
}
