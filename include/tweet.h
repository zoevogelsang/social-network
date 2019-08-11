#ifndef TWEET_H
#define TWEET_H
#include <iostream>
#include <string>
#include <string>
#include <vector>
#include <set>
#include "datetime.h"

/* Forward declaration */
class User;

/**
 * Models a tweet and provide comparison and output operators
 */
class Tweet
{
 public:
  Tweet();
  Tweet(User* user, const DateTime& time, const std::string& text);
  User* user() const; 
  DateTime const & time() const;
  std::string const & text() const;
  std::set<std::string> hashTags() const;
  bool operator<(const Tweet& other) const; 
  friend std::ostream& operator<<(std::ostream& os, const Tweet& t);
 private:
  DateTime dt_;
  User* user_;
  std::string txt_;
};

/***********************************/
/* Leave this alone --             */
/*   it will help sort your tweets */
/***********************************/
struct TweetComp
{
  bool operator()(Tweet* t1, Tweet* t2)
  {
    return (*t2 < *t1);
  }
};
#endif
