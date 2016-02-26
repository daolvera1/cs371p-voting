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
# define DEBUG 0


    Ballot::Ballot(vector<int>& v){
        votes = v;
    }
    int Ballot::get_alternate(){return votes.at(++pref);}



    Candidate::Candidate (string s){name = s;} //constructor
    void Candidate::add_ballot(Ballot* v){ballot_box.push_back(v);} //adds ballot to their ballot box
    vector<Ballot*> Candidate::get_box(){return ballot_box;}
    int Candidate::number_votes(){
        int size = ballot_box.size();
        return size;}
    string Candidate::get_name(){return name;} //dont know if need this
    void Candidate::make_loser(){loser = true;}
    bool Candidate::check_loser(){return loser;}
    bool Candidate::check_winner(){return wins;}
    void Candidate::make_winner(){wins = true;}




vector<int> voting_read (const string& s) {
    vector<int> ballot;
	istringstream sin(s);
    int i;
	while(sin >> i)
		ballot.push_back(i);
    return ballot;
}


// -------------
// voting_print
// -------------

void voting_print (ostream& w, string s, bool last) {
    if(!last)
    w << s << endl;
    else 
    w << s;
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
    #if(DEBUG)
	cout << "total ballot : " << total_ballots << endl;
    #endif
    while (1){
        //check if any candidates have over 50%
        int min = _box.at(0)->number_votes(); // set min number votes to max
		tied = 1;
        cout << "\n\nnew round:\n";
        for(int i = 0; i < num_cand; i++){
            
            Candidate* cand = _box.at(i);
            cout << "getting votes: " << cand->number_votes() << endl;
            #if(DEBUG)
            cout << double (cand->number_votes())  / total_ballots << 
			" " << _box.at(i)->get_name() << endl;
            #endif

            if((double (cand->number_votes()) / total_ballots )> .5){ //check if there is winner
               cand -> make_winner();
               winners.push_back(cand);

               #if(DEBUG)
               cout << "getting pushed to winner " << _box.at(i)->get_name()  << endl;
               #endif

            }
			//check if a virtual tie doesn't exist
            else if(i > 0 && cand->number_votes() != _box.at(i - 1)->number_votes()){
                tied = 0;}

            //find min number of votes
            if(cand->number_votes() < min){
                min = cand->number_votes();
                index_memory = i;
            }
        }
		//check if somebody won
        if(!winners.empty()) {return winners;}

        //check if all candidates have equal votes
        else if(tied){

            for(int i = 0; i < (int)_box.size(); i++){
                _box.at(i) -> make_winner();
            }

            return _box;}

        else  //eliminate losers
        {
			//----------skip to end of list and only iterate over elements that are smallest -------------
            for(int i = num_cand - 1; i >=index_memory; --i){
                if(_box.at(i)->number_votes() == min) //remove candidates who meet the min number of votes{
                    {vector<Ballot*> removed_ballot = _box.at(i)->get_box(); //geting ballots of elimiated candidates
                    #if(DEBUG)
                    cout << "removing Candidate " << _box.at(i)->get_name()  << endl;
                    #endif
					_box.at(i) -> make_loser(); 

                    _box.erase(_box.begin() + i);

					int size = removed_ballot.size();
					//iterate through their ballots
					for(int i = 0; i < size ; i++){
						int alternate_vote = removed_ballot.at(i) -> get_alternate(); //number oging to be 1 bigger than ballot number
                        //loop thorugh voter ballot while next choice is loser
                        while(_original_box.at(alternate_vote - 1) -> check_loser() == true || 
                           _original_box.at(alternate_vote - 1) -> number_votes() == min ){
                               alternate_vote = removed_ballot.at(i) -> get_alternate();}
                        #if(DEBUG)
						cout << "val of alt vote: " << alternate_vote << " goes to " << 
						_original_box.at(alternate_vote - 1) -> get_name() << "\n\n"; 
                        #endif
						_original_box.at(alternate_vote - 1)->add_ballot(removed_ballot.at(i));

								
							
					}
				}
            }
			
			num_cand = _box.size(); //resize number of candidates
			round++;
	
        }

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
            else 
                cout << "\n";

            getline(r,s); //num candidates

            const int number_candidates = num_testcases_candidates(s);
            vector<Candidate*> _candidates;
			vector<Candidate*> copy_cand;
	        _candidates.reserve(number_candidates);
	        copy_cand.reserve(number_candidates);// wont have to readjust size of array
            //getting names of candidates
            for (int i = 0;i < number_candidates; i++){

                getline(r,s); // get candidate names
                _candidates.push_back( new Candidate(s)); //add candidate into vector of candidates
				copy_cand.push_back(_candidates.at(i));	
            }

			vector<int> ballots;
            while(getline(r,s)){
				if(s.empty())
					break;
				else {
					ballots = voting_read(s); // parse ballot into vector
                    count++;
                    int candidate_number = ballots.front(); //get first preference

                    //add ballot to apprioriate candidate box
					_candidates.at(candidate_number - 1)->add_ballot(new Ballot(ballots)); 
				}
            }

		    //sort the candidates by votes	
            sort(copy_cand.begin(), copy_cand.end(), [](Candidate* c1, Candidate* c2){
				return c1 -> number_votes() > c2->number_votes();});

            vector<Candidate*> winner = ballot_counter(copy_cand,count, _candidates);
            for(int i = 0; i < number_candidates; i++){
				if (_candidates.at(i) -> check_winner() == true )
                    voting_print(w, _candidates.at(i) -> get_name(), tests == number_tests - 1);
            }
       

			

    }
}
