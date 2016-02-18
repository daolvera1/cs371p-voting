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
    vector<Ballot> ballot_box;
    bool loser = false;
public:
    Candidate (string s){name = s;} //constructor
    void add_ballot(vector<Ballot> v){ballot_box.push_back(v);} //adds ballot to their ballot box
    vector<Ballot> get_box(){return ballot_box;}
    int number_votes(){
        int size = ballot_box.size();
        return size;}
    string get_name(){return name;} //dont know if need this
    bool operator<(const Candidate &other) const{
        return ballot_box.size() < ballot_box.size();
    }
    void make_loser(){loser = true;}
    bool check_loser(){return loser;}
};

vector<int> voting_read (const string& s) {
    vector<int> ballot;
	istringstream sin(s);
    int i;
	while(sin >> i)
		ballot.push_back(i);
    return ballot;
}

class Ballot {
private:
	vector<int> votes;
	int pref = 0;
public: 
	void write_ballot(vector<int>& v){
		votes = v;	
	}
	void get_alternate(){return votes.at(++pref);}
};

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

vector<Candidate*> ballot_counter(vector<Candidate*>& _box, const int total_ballots, 
			vector<Candidate*> & _original_box){
    vector<Candidate*> winners;
    int tied = 1, num_cand=_box.size();
    int index_memory = 0, round = 0;
	cout << "total ballot : " << total_ballots << endl;
    while (1){
        //check if any candidates have over 50%
        int min = _box.at(0)->number_votes(); // set min number votes to max
		tied = 1;
        for(int i = 0; i < num_cand; i++){
            Candidate* cand = _box.at(i);
            cout << double (cand->number_votes())  / total_ballots << 
			" " << _box.at(i)->get_name() << endl;
            if((double (cand->number_votes()) / total_ballots )> .5){
               winners.push_back(cand);
               //cout << "printing winner " << _box.at(i)->get_name()  << endl;
            }
            else if(i > 0 && cand->number_votes() != _box.at(i - 1)->number_votes())
                tied = 0;

            //find min number of votes
            if(cand->number_votes() < min){
                min = cand->number_votes();
                index_memory = i;
            }
        }

        if(!winners.empty()) {return winners;}

        //check if all candidates have equal votes
        else if(tied){return _box;}

        else  //eliminate losers
        {
			//cout << "starting index: " << index_memory <<  " , min " << min << endl;
            for(int i = num_cand - 1; i >=index_memory; --i){
                if(_box.at(i)->number_votes() == min) //remove candidates who meet the min number of votes{
                    {vector<Ballot> removed_ballot = _box.at(i)->get_box(); //get their ballots
                    cout << "removing Candidate " << _box.at(i)->get_name()  << endl;
					_box.at(i) -> make_loser();

                    _box.erase(_box.begin() + i);

					int size = removed_ballot.size();
					//cout << "getting size " << size << endl;
					for(int i = 0; i < size ; i++){
						///assert(0);
						int alternate_vote = removed_ballot.at(i).at(round + 1); //number oging to be 1 bigger

						cout << "printing alt vote " << alternate_vote << " goes to " << 
						_original_box.at(alternate_vote - 1) -> get_name() << "\n\n"; 

						_original_box.at(alternate_vote - 1)->add_ballot(removed_ballot.at(i));
						//assert(_original_box.at(alternate_vote - 1) -> number_votes() == ((_box.at(alternate_vote - 1) -> number_votes()) - 1));

								
							
					}
				}
            }
			
			num_cand = _box.size(); //resize number of candidates
			//cout << "new box size " << num_cand << endl;
			round++;
	
        }

		  //assert(0);
	}
          return winners;
}



void voting_solve (istream& r, ostream& w) {
    string s;
    getline(r, s);
    int count = 0;
    const int number_tests = num_testcases_candidates(s);
    for(int tests = 0; tests < number_tests ; tests++){
			count = 0;
            if (tests == 0)
				getline(r,s); //skip empty line

            getline(r,s); //num candidates

            const int number_candidates = num_testcases_candidates(s);
            vector<Candidate*> _candidates;
            //getting names of candidates
            for (int i = 0;i < number_candidates; i++){

                getline(r,s); // get candidate names
                _candidates.push_back( new Candidate(s)); //add candidate into vector of candidates
            }

			vector<int> ballots;
            while(getline(r,s)){
				if(s.empty())
					break;
				else {
					ballots = voting_read(s); // parse ballot into vector
					//cout << "printing balllot " << s << endl;
                    count++;
                    int candidate_number = ballots.front();

					_candidates.at(candidate_number - 1)->add_ballot(ballots); //add ballot to apprioriate candidate box
				}
          }
			vector<Candidate*> copy_cand;
			for (int i = 0; i < number_candidates; i++){ //make copy to sort 
			
				copy_cand.push_back(_candidates.at(i));	
			}

		    //sort the candidates by votes	
            sort(copy_cand.begin(), copy_cand.end(), [](Candidate* c1, Candidate* c2){
				return c1 -> number_votes() > c2->number_votes();});

            
			//cout << "confirming count " << count << endl;
            vector<Candidate*> winner = ballot_counter(copy_cand,count, _candidates);
            //int num_win = winner.size();
            for(int i = 0; i < number_candidates; i++){
                //cout << "printing winner " << winner.at(i)->get_name() << endl;
				//cout << winner.at(i) -> check_loser() << endl;
				//cout << "testing boolean " << _candidates.at(i) ->check_loser() << endl;
				if (_candidates.at(i) -> check_loser() == false )
                cout <<  _candidates.at(i)->get_name() << endl;
                //cout << i+1 << endl;
            }
            //voting_print();
			cout << "\n";

    }

/* while (getline(r, s)) {
        const pair<int, int> p = voting_read(s);
        const int            i = p.first;
        const int            j = p.second;
        const int            v = voting_eval(i, j);
        voting_print(w, i, j, v);
    }*/
}
