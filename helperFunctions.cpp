#include "helperFunctions.h"

vector<string> split(string query){
    vector<string> strings;
    istringstream iss(query);
    string s;
    while (getline(iss, s, ' ')){
        strings.push_back(s);
    }
    return strings;
}

bool equal_to_insensitive( char c1, char c2 )
{
   return  tolower( static_cast<unsigned char>( c1 ) )
         == tolower( static_cast<unsigned char>( c2 ) );
}

int case_insensitive_comparison( const string& s1, const string& s2 )
{
    string::const_iterator short_begin, short_end, long_begin, long_end;

   // set iterators to the beginning and end of the shorter and longer
   // strings
   if( s1.length() <= s2.length() )
   {
      short_begin = s1.begin();
      short_end = s1.end();
      long_begin = s2.begin();
      long_end = s2.end();
   }
   else
   {
      short_begin = s2.begin();
      short_end = s2.end();
      long_begin = s1.begin();
      long_end = s1.end();
   }

   // find the first spot where corresponding characters don't match,
   // ignoring case
   pair<string::const_iterator,string::const_iterator> spot =
      mismatch( short_begin, short_end, long_begin,
         equal_to_insensitive );

   int result;

   // if all characters of shorter string matched corresponding
   // characters of longer string...
   if( spot.first == short_end )

      // if at end of longer string both strings are same length so
      // both strings are the same
      if( spot.second == long_end )
         result = 0; // s1 == s2

      // not at end of longer string so shorter string is less than
      // longer one
      else
         result = -1; // s1 < s2

   // mismatch in short string - examine characters to decide result
   else
   {
      // convert characters to lower case
      int first =
         tolower( static_cast<unsigned char>( *spot.first  ) );
      int second =
         tolower( static_cast<unsigned char>( *spot.second ) );

      // result of routine based on case-insensitive character
      // comparison
      if( first < second )
         result = -1;
      else if( first > second )
         result = 1;
      else
         result = 0;
   }

   // if long string was first string passed, result is opposite of
   // that computed
   if( long_begin == s1.begin() )
      result *= -1;

   return result;
}

bool greedy_phrase_comparison(const string &searchField, const string &query){
    vector<string> fieldTerms = split(searchField);
    vector<string> queryTerms = split(query);
    for (auto x = queryTerms.begin(); x != queryTerms.end(); x++)
        for (auto y = fieldTerms.begin(); y != fieldTerms.end(); y++)
        {
            if (case_insensitive_comparison(*x, *y) == 0)
                return true;
            else
                return false;
        }
}

string upper(const string query){
    string big;
    string letter;
    for (auto itr = query.begin(); itr != query.end(); itr++){
        letter = toupper(*itr);
        big.append(letter);
    }
    return big;
}
