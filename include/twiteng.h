#ifndef TWITENG_H
#define TWITENG_H
#include <map>
#include <string>
#include <set>
#include <vector>
#include <stack>
#include "user.h"
#include "tweet.h"
#include "datetime.h"
#include "util.h"
#include "heap.h"
#include "tagdata.h"

class TwitEng
{
 public:
  TwitEng();
  ~TwitEng();
  bool parse(char* filename);
  bool addUser(std::string username, std::string password);
  void addTweet(const std::string& username, const DateTime& time, const std::string& text);
  bool login(std::string username, std::string password);
  void logout();
  void trending(int n);
  std::vector<Tweet*> search(std::vector<std::string>& terms, int strategy);
  bool tweet(const std::string& text);
  bool follow(std::string target);
  void save(std::string filename);
  void scc();
  void strongconnect(User* u, int& i);

  void dumpFeeds();
  void dumpMentions();

  /* You may add other member functions */
 private:
  std::string currentuser;
  std::map<std::string, std::set<Tweet*> > hashmap;
  Heap<TagData, TagStringEqual, TagIntGreater, TagStringHasher> trending_;
  std::map<std::string,User*> users;
  std::set<Tweet*> alltweets;
  std::stack<User*> S; 
};


#endif
