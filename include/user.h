#ifndef USER_H
#define USER_H

#include <string>
#include <set>
#include <list>
#include <vector>

/* Forward Declaration to avoid #include dependencies */
class Tweet;

class User {
 public:

  User(std::string name, unsigned int pass);
  ~User();
  std::string name() const; 
  std::set<User*> followers() const;
  std::set<User*> following() const;
  std::list<Tweet*> tweets() const; 
  void addFollower(User* u);
  void addFollowing(User* u);
  void addTweet(Tweet* t);
  void addMention(Tweet*t);
  void setPass(unsigned int pass);
  unsigned int getPass() const;
  std::vector<Tweet*> getFeed();
  std::vector<Tweet*> getMentions();

  //TODO: make these private and make scc a friend.
  int index;
  int lowlink;
  bool onstack;

 private:
  
  std::string name_;
  unsigned int pass_;
  std::list<Tweet*> tweets_;
  std::set<Tweet*> mentions_;
  std::set<User*> following_;
  std::set<User*> followers_;

};

#endif
