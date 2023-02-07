#include <iostream>
#include <sstream>
#include <cctype>
#include <algorithm>
#include "util.h"

using namespace std;
std::string convToLower(std::string src)
{
    std::transform(src.begin(), src.end(), src.begin(), ::tolower);
    return src;
}

/** Complete the code to convert a string containing a rawWord
    to a set of words based on the criteria given in the assignment **/
std::set<std::string> parseStringToWords(string rawWords)
{
    std::set<std::string> keywords;
    stringstream ss(rawWords);
    std::string word;

    while(ss >> word){ //put into string stream 
        std::string split;
        for(size_t i = 0; i < word.size(); i++){ //split at those characters
            if(word[i] == '.' || word[i] == ',' || word[i] == '!' || word[i] == '?' || word[i] == '-' || word[i] == '\''){
                split += " ";
            }
            else{
                split += word[i];
            }
        }

        std::string wordsp;
        stringstream splitss(split);

        while(splitss >> wordsp){
            if(wordsp.size() > 1){
                keywords.insert(wordsp);
            }
        }
    }
		return keywords; //return the set of the words that were split and fit the 2 or greater requirement

}

/**************************************************
 * COMPLETED - You may use the following functions
 **************************************************/

// Used from http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
// trim from start
std::string &ltrim(std::string &s) {
    s.erase(s.begin(), 
	    std::find_if(s.begin(), 
			 s.end(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}

// trim from end
std::string &rtrim(std::string &s) {
    s.erase(
	    std::find_if(s.rbegin(), 
			 s.rend(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))).base(), 
	    s.end());
    return s;
}

// trim from both ends
std::string &trim(std::string &s) {
    return ltrim(rtrim(s));
}
