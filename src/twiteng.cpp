#include "twiteng.h"
#include "datetime.h"
#include "hsort.h"
#include "hash.h"
#include <sstream>
#include <fstream>
using namespace std;


TwitEng::TwitEng() : trending_(2) {}

TwitEng::~TwitEng(){
  map<string, User*>::iterator i;
  for(i = users.begin(); i != users.end(); i++){
    delete i->second;
  }
}

/**
 * Parses the Twitter database and populates internal structures
 * @param filename of the database file
 * @return true if there is an error, false if successful
 */
bool TwitEng::parse(char* filename){
  ifstream ifile (filename);
  if( ifile.fail() )
      return 1;
  
  int n;
  ifile >> n;

  if( ifile.fail() )
      return 1;

  string line, name;
  unsigned int passnum;
  getline (ifile, line);

  for(int i=0; i<n; i++){
    if( ifile.fail() )
    return 1;

    //checks to make sure line isn't blank:
    getline(ifile, line);
    bool space = true;
    for(unsigned int i=0;i<line.size(); i++){
      if ( !isspace(line[i]) )
        space = false;
    }
    if (space) continue;
    // 


    stringstream s(line);
    s >> name >> passnum; 

    User* u;
    if(users.find(name) == users.end()){ 
      u = new User(name, passnum);
      users.insert(make_pair(name, u));
    }
    else{
      u = users[name];
      u->setPass(passnum);
    }
    
    while (s >> name){
        User* f;
      if(users.find(name) == users.end()){ 
        f = new User(name, 0);
        users[name] = f;
        u->addFollowing(f);
        f->addFollower(u);
      }
      else{
        f = users[name];
        u->addFollowing(f);
        f->addFollower(u);
      }
    }
  }


  //parsing tweets:
  while(getline(ifile, line)){
      bool space = true;
      for(unsigned int i=0;i<line.size(); i++){
          if ( !isspace(line[i]) )
              space = false;
      }
      if (space)
          continue;
    stringstream s(line);
    DateTime time;
    string text;

    s >> time >> name;
    getline(s, text);
    addTweet(name, time, text);
  }

  ifile.close();
  return 0;
}




// TODO: add comment for function

bool TwitEng::addUser(std::string username, std::string password){
  if(password.size() < 4 || password.size() > 8){
    cout << "Password must be 4 to 8 characters long." << endl;
    return false;
  }

  if(users.find(username) != users.end()){ 
    cout << "Username already exists." << endl;
    return false;
  }

  User* u = new User(username, calculateHash(password));      
  users.insert(make_pair(username, u));
  currentuser = username;
  cout << "User " << username << " created. You are logged in. Welcome!" << endl;
  return true;
}


/**
 * Allocates a tweet from its parts and adds it to internal structures
 * @param username of the user who made the tweet
 * @param timestamp of the tweet
 * @param text is the actual text of the tweet as a single string
 */
void TwitEng::addTweet(const std::string& username, const DateTime& time,
                       const std::string& text){
  if (users.find(username) == users.end())
    return;
  User* user = users[username];
  Tweet* t = new Tweet(user, time, text);
  alltweets.insert(t);
  users[username]->addTweet(t);

  stringstream s(text);
  string word;
  bool mentionFound = false;

  s >> word;
  if(word[0] == '#'){
    word = word.substr(1);
    convUpper(word);
    hashmap[word].insert(t);

    TagData oldtweet(word, 0);
    TagData newtweet(word, hashmap[word].size());
    try{
      trending_.decreaseKey(oldtweet, newtweet);
    } catch(int e){
      trending_.push(newtweet);
    }

  }
  else if (word[0] == '@'){
    word = word.substr(1);
    if(users.find(word) != users.end()){
      users[word]->addMention(t);
      mentionFound = true;
    }
  }

  while (s >> word){
    if(word[0] == '#'){
      word = word.substr(1);
      convUpper(word);
      hashmap[word].insert(t);

      TagData oldtweet(word, 0);
      TagData newtweet(word, hashmap[word].size());
      try{
        trending_.decreaseKey(oldtweet, newtweet);
      } catch(int e){
        trending_.push(newtweet);
      }
    }

    else if (word[0] == '@' && !mentionFound){
      word = word.substr(1);
      if(users.find(word) != users.end())
        users[word]->addMention(t);
    }
  }

}



bool TwitEng::login(string username, string password){
  if( users.find(username) != users.end() && users[username]->getPass() == calculateHash(password)){
    currentuser = username;
    return true;
  }
  return false;
}


void TwitEng::logout(){
  currentuser = "";
}

void TwitEng::trending(int n){
  if(n < 0){
    return;
  }
  if(n > int(hashmap.size()))
    n = hashmap.size();

  vector<TagData> v;
  for(int i=0; i<n; i++){
    string txt = trending_.top().tag;
    convLower(txt);
    cout << txt << " : " << trending_.top().num << endl;
    v.push_back(trending_.top());
    trending_.pop();
  }

  for(int i=0; i<n; i++){
    trending_.push(v.back());
    v.pop_back();
  }
}




/**
 * Searches for tweets with the given words and strategy
 * @param words is the hashtag terms in any case without the '#'
 * @param strategy 0=AND, 1=OR
 * @return the tweets that match the search
 */
std::vector<Tweet*> TwitEng::search(std::vector<std::string>& terms, int strategy){
  vector<Tweet*> results;
  if (terms.size() == 0){
    return results;
  }

  set<Tweet*> s = hashmap[terms[0]];
  set<Tweet*>::iterator it;

  
  if(strategy){ //OR case:
    for(unsigned int i=1; i<terms.size(); i++){
      set<Tweet*> h = hashmap[terms[i]];
      for(it = h.begin(); it != h.end(); ++it){
        s.insert(*it); 
      }
    } 
  }
  else{ //AND case:
    for(unsigned int i=1; i<terms.size(); i++){
      set<Tweet*> h = hashmap[terms[i]];
      for(it = s.begin(); it != s.end(); ++it){
        if(h.find(*it)== h.end() && s.find(*it) != s.end())
        s.erase(*it);
      }
    } 
  }

  for(it=s.begin(); it != s.end(); it++){
    results.push_back(*it);
  }
  hsort(results, TweetComp());

  return results;
}

bool TwitEng::tweet(const std::string& text){
  if(currentuser == "" || users.find(currentuser) == users.end()){
    return false;
  }
  DateTime time;
  addTweet(currentuser, time, text);
  return true;
}



bool TwitEng::follow(string target){
  if(currentuser == "" || users.find(currentuser) == users.end()){
    return false;
  }

  if(users.find(target) != users.end()){
    users[target]->addFollower(users[currentuser]);
    users[currentuser]->addFollowing(users[target]);
  }
  return true;
}



void TwitEng::save(string filename){
  ofstream ofile(filename);

  ofile << users.size() << endl;

  map<std::string,User*>::iterator it;

  for(it = users.begin(); it != users.end(); it ++){
    ofile << it->first << " " << it->second->getPass() << " ";
    set<User*> f = it->second->following();
    for( set<User*>::iterator i = f.begin(); i != f.end(); i++){
      ofile << (*i)->name() << " ";
    }
    ofile << endl;
  }


  set<Tweet*>::iterator i; 
  for(i = alltweets.begin(); i != alltweets.end(); i++){
    ofile << **i << endl;
  }

  ofile.close();
}

void TwitEng::scc(){
  int i = 0;
  map<string, User*>::iterator it; 

  for(it = users.begin(); it != users.end(); it++){
    User* u = it->second;
    u->index = -1;
    u->lowlink = -1;
    u->onstack = false;
  }


  for(it = users.begin(); it != users.end(); it++){
    User* u= it->second;
    if(u->index == -1){
      strongconnect(u, i);
    }
  } 
}


void TwitEng::strongconnect(User* u, int& i){
  u->index = i;
  u->lowlink = i;
  i++;
  S.push(u);
  u->onstack = true;
  set<User*> sucessors = u->following();
  for(set<User*>::iterator it = sucessors.begin(); it != sucessors.end(); ++it){
    User* w = *it;
    if(w->index == -1){
      strongconnect(w, i);
      u->lowlink = min(u->lowlink, w->lowlink);
    } 
    else if(w->onstack){
      u->lowlink = min(u->lowlink, w->index);
    }
  }

  if(u->lowlink == u->index){
    cout << "Component" << endl;
    while(S.top() != u){
      User* w = S.top();
      cout << w->name() << endl;
      w->onstack = false;
      S.pop();
    }
    User* w = S.top();
    cout << w->name() << endl;
    w->onstack = false;
    S.pop();
    cout << endl;
  }

}






/**
 * Dump feeds of each user to their own file
 */
void TwitEng::dumpFeeds(){
  map<string, User*>::iterator it;

  for(it = users.begin(); it != users.end(); it++){
    User* u = it->second;
    string name = u->name();
    ofstream ofile;
    ofile.open ("feeds/" + name + ".feed");

    ofile << name << endl;
    vector<Tweet*>::iterator i;
    vector<Tweet*> feed = u->getFeed();
    for(i = feed.begin(); i != feed.end(); i++){
      ofile << **i << endl;
    }

    ofile.close();
  }

  dumpMentions();
}

void TwitEng::dumpMentions(){
  map<string, User*>::iterator it;

  for(it = users.begin(); it != users.end(); it++){
    User* u = it->second;
    string name = u->name();
    ofstream ofile;
    ofile.open ("feeds/" + name + ".mentions");

    ofile << name << endl;
    vector<Tweet*>::iterator i;
    vector<Tweet*> feed = u->getMentions();
    for(i = feed.begin(); i != feed.end(); i++){
      ofile << **i << endl;
    }

    ofile.close();
  }



}

