/********************************************************************************
 * NAME:        Marcus Overzet (523 00 2848)
 * CLASS:       CSCE 121-514 final project
 * DUE DATE:    Tuesday, April 25, 2017
 * FILE NAME:   mdo_fileio.h
 *
 * DESCRIPTION:
 * -IO system of the project. stores top 5 user initials and scores to a file and
 *      later recieves the top 5 initials/scores.
 *
 * DEPENDENCIES:
 * -std_lib_facilities_4.h
 * -score_file.txt
 *
 *
 * IMPORTANT!!!:
 * -use multiple files to store scores for each difficulty, that way we keep the
 *      scores at every difficulty separate. This requires using many score_ios.
 *
 *
 * HOW TO USE:
 * -initialize the class using the format score_io(String ss, int nn)
 *      where ss is the relative path to the file to read/write our highscores
 *      in, and nn is the maximum possible score for this score_io,
 *      ( = 320 * difficulty level ).
 *
 * -once initialized, use the syntax "score_io.get(int n)" where 1 ≤ n ≤ 5.
 *      "score_io.get(1)" returns the top score (as a user_score),
 *      "score_io.get(n)" returns the nth high score (as a user_score).
 *
 * -use the syntax "score_io.add(String ss,int nn)" or "score_io.add(user_score)"
 *      to attempt to store a new score and initials to our high scores. 
 *      returns true if the score is stored as one of our top 5 high scores, or
 *      returns false if it is not in the top 5 high scores.
 *
 * -user_score is a simple struct. use the syntax user_score.score to call 
 *      the int that represents that user's score, and user_score.name to call
 *      the String that reps that user's initials.
 *
 *
 * ERRORS:
 * -"score_io::bad_file" is thrown when failed to open our score file properly
 * -"score_io::add_args" is thrown when an invalid input is given to the "add"
 *      member of score_io (nn is too large/small, invalid chars in String ss, 
 *      or there are no chars in String ss)
 * -"score_io::get_args" is called when an invalid input is given to the "get"
 *      member of score_io (n is not 1, 2, 3, 4, or 5)
 *
 ********************************************************************************/

/* testing results of score_io:
 * 1: Primer
 *  a: initialize with nothing in our file ................................ [y]
 *  b: input lower than current value ..................................... [y]
 *  c: input higher than all values ....................................... [y]
 *  d: input in between the values ........................................ [y]
 *  e: add in one last value, then read values 0-4 ........................ [y]
 *  f: attempt to write an invalid score .................................. [y]
 *  g: attempt to write an invalid name ................................... [y]
 *  h: attempt to read from an invalid index .............................. [y]
 *  i: attempt to read from invalid index between 0-4 .................. [y][y]
 *  j: attempt to add a too low score ..................................... [y]
 *
 * 2: testing the overloaded functions
 *  a: add overloads .................................................[y][y][y]
 *  b: get overloads .................................................[y][y][y]
 *
 * 3: initialize with an unorganized mess ................................. [~]
 * 4: initialize with an invalid file name ................................ [y]
 */

/* NOTES TO SELF:
 * -test 3 fails if the unorganized mess has the format String Int present, as
 *      it initializes a new user_score.
 *
 * -add(), should use const String& or String?
 *
 * -MAX_SCORE holds the default maximum score for a score_io
 *
 * -add something to be able to open several different difficulty's files?
 */
 
#ifndef MDO_FILEIO_H
#define MDO_FILEIO_H

#include "std_lib_facilities_4.h"
using namespace std;

namespace mdo { // Marcus Overzet's namespace
    const int MAX_SCORE = 320;
	const int MAX_SIZE_NAME = 7;
    
    /* user_score */
    struct user_score {
        int score;
        String name;
    };
	
	// return our rules for if it is a valid username
	bool is_valid_username( string );

    /* score_io */
    class score_io {
        String score_file; // contains path to io text file
        Vector<user_score> scores; // contains our top 5 scores/initials
    
        Vector<user_score> get_scores(); // internal member used to update "scores"
        void reorder(); // internal member to put "scores" in ascending order again
        void write(); // write our "scores" to the file
    
        int max_score; // to change based on difficulty.
        const int max_size_name = MAX_SIZE_NAME; // maximum number of characters for a username
        const int num_high_scores = 5; // maximum number of scores to store
        const String default_score_file = "score_file.txt"; // default file to rw
    
    public:
        class bad_file {}; // error for failed ifstream/ofstream
        class add_args {}; // error for invalid arguments to add() member
        class get_args {}; // error for invalid arguments to get() member
    
        // return constant members of score_io, and max_score.
        int get_max_score() const { return max_score; };
        const int get_max_size_name() const { return max_size_name; };
        const int get_num_high_scores() const { return num_high_scores; };
        int get_num_read_scores() const { return scores.size(); };
        const String get_default_score_file() const { return default_score_file; };
	
        // default constructor uses default_score_file as our new score_file
        // alternative constructor allows user to input our new score_file
        score_io();
        score_io(const String&);
        score_io(const String&, int);
  
        // attempt to write a new scores to our high scores. overloaded.
        bool add(String, int);
        bool add(user_score us) { return add(us.name, us.score); };
        bool add(int nn, String ss) { return add(ss,nn); };
    
        // get the nth high score. overloaded.
        void const get(int, String&, int&);
        void const get(int n, int& nn, String& ss) { get(n,ss,nn); return; };
        void const get(int n, user_score& us) { get(n,us.name,us.score); return; };
        user_score const get(int n) { user_score us; get(n,us.name,us.score); return us;};
    };

} // end of namespace mdo

// overloading operators for iostreams so that I can input/output user_scores
istream& operator>>(istream&, mdo::user_score&);
ostream& operator<<(ostream&, const mdo::user_score&);

#endif
