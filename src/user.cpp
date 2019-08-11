#include "user.h"
#include "tweet.h"
#include <algorithm>
using namespace std;

/**
 * Constructor 
 */
User::User(string name, unsigned int pass)
:name_(name), pass_(pass) {
  index = -1;
  lowlink = -1; 
  onstack = false;
}
/**
 * Destructor
 */
User::~User(){
  list<Tweet*>::iterator i;
  for (i = tweets_.begin(); i != tweets_.end(); i++){
    delete *i;
  }
}
/**
 * Gets the name of the user 
 * 
 * @return name of the user 
 */
string User::name() const{
  return this->name_;
}




/**
 * Gets all the followers of this user  
 * 
 * @return Set of Users who follow this user
 */
set<User*> User::followers() const{
  return followers_;
}

/**
 * Gets all the users whom this user follows  
 * 
 * @return Set of Users whom this user follows
 */
set<User*> User::following() const{
  return following_;
}

/**
 * Gets all the tweets this user has posted
 * 
 * @return List of tweets this user has posted
 */
list<Tweet*> User::tweets() const{
  return tweets_;
}

/**
 * Adds a follower to this users set of followers
 * 
 * @param u User to add as a follower
 */
void User::addFollower(User* u){
  followers_.insert(u);
}

/**
 * Adds another user to the set whom this User follows
 * 
 * @param u User that the user will now follow
 */
void User::addFollowing(User* u){
  following_.insert(u);
}

/**
 * Adds the given tweet as a post from this user
 * 
 * @param t new Tweet posted by this user
 */
void User::addTweet(Tweet* t){
  tweets_.push_front(t);
}

void User::addMention(Tweet*t){
  mentions_.insert(t);
}


void User::setPass(unsigned int pass){
  pass_ = pass;
}

unsigned int User::getPass() const {
  return pass_;
}



/**
 * Produces the list of Tweets that represent this users feed/timeline
 *  It should contain in timestamp order all the tweets from
 *  this user and all the tweets from all the users whom this user follows
 *
 * @return vector of pointers to all the tweets from this user
 *         and those they follow in timestamp order
 */
vector<Tweet*> User::getFeed(){
  
  vector<Tweet*> feed;
  list<Tweet*>::iterator it;
  for(it = tweets_.begin(); it != tweets_.end(); it++){
    feed.push_back(*it);
  }
  set<User*>::iterator u; 
  for(u = following_.begin(); u != following_.end(); u++){
      list<Tweet*> ftweets = (*u)->tweets();
      for(it = ftweets.begin(); it != ftweets.end(); it++){
        if((*it)->text()[0] != '@'){
          feed.push_back(*it);
        }
      }
  }

  sort(feed.begin(), feed.end(), TweetComp());
  return feed;
}


vector<Tweet*> User::getMentions(){
  vector<Tweet*> mvec;
  set<Tweet*>::iterator it; 
  for(it = mentions_.begin(); it != mentions_.end(); it++){
    mvec.push_back(*it);
  }

  sort(mvec.begin(), mvec.end(), TweetComp());
  return mvec;
}

