#include <iostream>
#include <sstream>
#include <cctype>
#include <algorithm>
#include <string>
#include <string_view>
#include "util.h"

using namespace std;
std::string convToLower(std::string src)
{
    std::transform(src.begin(), src.end(), src.begin(), ::tolower);
    return src;
}

bool isLetter(string s){
	if (s >= "a" && s <= "z"){return true;}
	return false;
}
/** Complete the code to convert a string containing a rawWord
    to a set of words based on the criteria given in the assignment **/
std::set<std::string> parseStringToWords(string rawWords)
{
  rawWords = convToLower(rawWords);
    std::set<std::string> s;
    string str = "";
    for(size_t i = 0; i < rawWords.length(); ++i)
    {
        std::string segment = rawWords.substr(i,1);
        if(isLetter(segment)){
            str += segment;
        } else if (str.length() >= 2) {
            s.insert(str);
            str = "";
        } else {
            str = ""; 
        }
    }
    //checks to make sure last keyword is inserted
	if(!str.empty()) s.insert(str);

    return s;
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
