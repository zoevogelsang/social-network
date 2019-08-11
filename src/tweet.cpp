#include <sstream>
#include <string>
#include "tweet.h"
#include "util.h"
#include "user.h"
using namespace std;

/**
* Default constructor 
*/
Tweet::Tweet(){

  
}

/**
* Constructor 
*/
Tweet::Tweet(User* user, const DateTime& time, const string& text)
: dt_(time), user_(user), txt_(text) 
{
}

/*
* returns user who posted tweet
*/
User* Tweet::user() const{ 
  return user_;
}

/**
* Gets the timestamp of this tweet
*
* @return timestamp of the tweet
*/
DateTime const & Tweet::time() const{
  return dt_;
}

/**
* Gets the actual text of this tweet
*
* @return text of the tweet
*/
string const & Tweet::text() const{
  return txt_;
}

/**
* Returns the hashtagged words without the '#' sign
*
*/
set<string> Tweet::hashTags() const{
  set<string> hashtags;

  stringstream t(txt_);
  string temp;
  while(t >> temp){
  	if(temp[0] == '#'){
  		temp = temp.substr(1);
      convUpper(temp);
  		hashtags.insert(temp);
  	}
  }
  return hashtags;
}

/**
* Return true if this Tweet's timestamp is less-than other's
*
* @return result of less-than comparison of tweet's timestamp
*/
bool Tweet::operator<(const Tweet& other) const{
  return dt_ < other.dt_;
}

/**
* Outputs the tweet to the given ostream in format:
*   YYYY-MM-DD HH::MM::SS username tweet_text
*
* @return the ostream passed in as an argument
*/
ostream& operator<<(ostream& os, const Tweet& t){
  os << t.dt_ << " " << t.user()->name() << t.txt_;
  return os;
}


