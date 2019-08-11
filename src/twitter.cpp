#include <iostream>
#include <sstream>
#include <string>
#include "twiteng.h"
#include "util.h"
#include "tweet.h"
#include "cmdhandler.h"

using namespace std;

Handler* createHandlers();

Handler* createHandlers()
{
  return new AndHandler(
    new OrHandler(
      new TweetHandler(
        new QuitHandler(
          new FollowHandler(
            new SaveHandler(
              new TrendingHandler( 
                new LoginHandler( 
                  new LogoutHandler(
                    new NewUserHandler()
                  )
                )
              )
            )
          )
        )
      )
    )
  );
}

int main(int argc, char* argv[])
{
  TwitEng twit;
  if(argc < 2 || twit.parse(argv[1]))
    cout << endl << "No data provided. Starting fresh ... " << endl << endl;

  // Initialize command handlers
  Handler* handlers = createHandlers();

  cout << "=====================================" << endl;
  cout << "Menu: " << endl;
  cout << "  NEWUSER username password            " << endl;
  cout << "  LOGIN username password            " << endl;
  cout << "  LOGOUT                             " << endl;
  cout << "  TRENDING n (n=top n hashtags)      " << endl;
  cout << "  AND term term ...                  " << endl;
  cout << "  OR term term ...                   " << endl;
  cout << "  TWEET tweet_text" << endl;
  cout << "  FOLLOW user_to_follow              " << endl;
  cout << "  SAVE new_filename                  " << endl;
  cout << "  QUIT (and write feed files)        " << endl;
  cout << "=====================================" << endl;

  Handler::HANDLER_STATUS_T status = Handler::HANDLER_OK;
  while(status != Handler::HANDLER_QUIT && 
        status != Handler::HANDLER_KILL)
  {
    cout << "\nEnter command: " << endl;
    string line;
    getline(cin,line);
    stringstream ss(line);
    string cmd;
    if((ss >> cmd)){
      // convert to upper case
      convUpper(cmd);
      // Invoke the chain of responsibility
      status = handlers->handle(&twit, cmd, ss);
    }

    if(status == Handler::HANDLER_ERROR){
      cout << "Unable to process request." << endl;
      status = Handler::HANDLER_OK;
    }

  }
  delete handlers;
  return 0;
}
