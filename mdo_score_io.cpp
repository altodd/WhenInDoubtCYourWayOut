/********************************************************************************
 * NAME:        Marcus Overzet (523 00 2848)
 * CLASS:       CSCE 121-514 final project
 * DUE DATE:    Tuesday, April 25, 2017
 * FILE NAME:   mdo_fileio.h
 * VERSION:     0.1
 ********************************************************************************/
#include "mdo_fileio.h"
#include "std_lib_facilities_4.h"
using namespace std;

// define ifstream >> operator for user_score here
istream& operator>>(istream& is, mdo::user_score& us)
{
    is >> us.name >> us.score;
    return is;
}

// define ofstream << operator for user_score here
ostream& operator<<(ostream& os, const mdo::user_score& us)
{
    os << us.name << ' ' << us.score << '\n';
    return os;
}

namespace mdo {
	/*
	 *
	 */
	bool is_valid_username( string ss ) {
		if(ss=="" || ss.size()>MAX_SIZE_NAME){
            return false;
        }
		for( int i=0; i<ss.size(); i++ ) {
            if(!(isalpha(ss.at(i)) || ( ss.at(i) >= '0' && ss.at(i) <= '9' ))) {
                return false;
            }
        }
		return true;
	}

    /*
     * function to copy the scores from our file onto
     * a Vector of user_score, then returns that Vector
     */
    Vector<user_score> score_io::get_scores() {
        Vector<user_score> v;
        ifstream ifs;
        user_score us;
        int i = 0;
    
        // open our file
        ifs.open(score_file); //score_file is a class member
        if(!ifs.good()) {
            throw bad_file {};
        }
    
        // use the >> operator in ifstream to return userscores
        while( ifs>>us ) {
            if( i > num_high_scores-1 ) {
                // do nothing here. ensures we only have
                // num_high_scores high scores.
            }
            else if(i<v.size()) {
                v.at(i) = us;
            }
            else {
                v.push_back(us);
            }
            i++;
        }
    
        // close connection to our file.
        ifs.close();
    
        return v;
    }

    /*
     * constructor for score_io
     */
    score_io::score_io() {
        max_score = MAX_SCORE;
        score_file = default_score_file;
        scores = get_scores();
    }

    /*
     * constructor with argument for score_io
     */
    score_io::score_io(const String& ss) {
        max_score = MAX_SCORE;
        score_file = ss;
        scores = get_scores();
    }
    
    /*
     * constructor with argument for score_io & for max_score
     */
    score_io::score_io(const String& ss, int nn) {
        max_score = nn;
        score_file = ss;
        scores = get_scores();
    }
    


    /*
     * attempts to find where our score is in our high scores,
     * then writes new scores into our file
     */
    bool score_io::add(String ss, int nn) {
        int i = 0;
        bool is_high_score = false;
        user_score us;
    
        us.score = nn;
        us.name = ss;
    
        // error handling
        if( nn > max_score || nn < 0 ){
            throw add_args {};
        }
        if( !is_valid_username(ss) ){ 				// FIXME 
            throw add_args {};
        }
    
        // update the member 'scores' before reading
        scores = get_scores();
    
        i = 0;
        // test our score against all of the other values
        while( i<scores.size() && !is_high_score ) {
            if( nn > scores.at(i).score ) {
                scores.insert(scores.begin()+i,us);
                is_high_score = true;
            }
        
            i++;
        }
        // if we don't have our top 5 scores yet, start to
        // fill them in with the given value
        if( scores.size() < num_high_scores && !is_high_score ) {
            scores.push_back(us);
            is_high_score = true;
        }

        write();
    
        return is_high_score;
    }
    
    /*
     * implement a bubble sort to make sure that the highest number in scores
     * is at scores.at(0) and the lowest is at scores.at(scores.size()-1)
     */
    void score_io::reorder() {
        int i = 0;
        int j = 0;
        user_score tmp;
    
        for(i=0; i<scores.size()-1; i++ ) {
            for(j=i+1; j<scores.size(); j++) {
                
                if( scores.at(i).score < scores.at(j).score ) {
                    tmp = scores.at(i);
                    scores.at(i) = scores.at(j);
                    scores.at(j) = tmp;
                }
            }
        }
    
        return;
    }
    
    /*
     * Writes the Vector member scores to our file
     */
    void score_io::write() {
        int i=0;
    
        // make sure that our vector is in the correct ascending order
        reorder();
        
        // make sure our scores vector is only at most 5 users long.
        while( scores.size() > num_high_scores ){
            scores.pop_back();
        }
    
        // open file to write
        ofstream ofs(score_file);
    
        if(!ofs.good()) {
            throw bad_file {};
        }
    
        // write to file
        for( i=0; i<scores.size(); i++) {
            ofs<<scores.at(i);
        }
    
        // close file
        ofs.close();
    }

    /*
     * puts the nth highscore username into ss, and the score in
     * nn.
     */
    void const score_io::get(int n, String& ss, int& nn) {
        reorder();
    
        if( n < scores.size() && n >= 0 && n < num_high_scores ) {
            ss = scores.at(n).name;
            nn = scores.at(n).score;
        }
        else {
            throw get_args {};
        }
    
    }

}//out of namespace mdo
