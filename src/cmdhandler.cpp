#include "cmdhandler.h"
#include "util.h"
using namespace std;

QuitHandler::QuitHandler()
{

}

QuitHandler::QuitHandler(Handler* next)
  : Handler(next)
{

}

bool QuitHandler::canHandle(const std::string& cmd) const
{
	return cmd == "QUIT";
}

Handler::HANDLER_STATUS_T QuitHandler::process(TwitEng* eng, std::istream& instr) const
{
	eng->dumpFeeds();
	return HANDLER_QUIT;
}


AndHandler::AndHandler()
{

}

AndHandler::AndHandler(Handler* next)
  : Handler(next)
{

}

bool AndHandler::canHandle(const std::string& cmd) const
{
	return cmd == "AND";

}

Handler::HANDLER_STATUS_T AndHandler::process(TwitEng* eng, std::istream& instr) const
{
	string term;
	vector<string> terms;
	while(instr >> term){
		convUpper(term);
		terms.push_back(term);
	}
	vector<Tweet*> search = eng->search(terms, 0);
	displayHits(search);
	return HANDLER_OK;
}

OrHandler::OrHandler()
{

}

OrHandler::OrHandler(Handler* next)
  : Handler(next)
{

}

bool OrHandler::canHandle(const std::string& cmd) const
{
	return cmd == "OR";

}

Handler::HANDLER_STATUS_T OrHandler::process(TwitEng* eng, std::istream& instr) const
{
	string term;
	vector<string> terms;
	while(instr >> term){
		convUpper(term);
		terms.push_back(term);
	}
	vector<Tweet*> search = eng->search(terms, 1);
	displayHits(search);
	return HANDLER_OK;
}



TweetHandler::TweetHandler()
{

}

TweetHandler::TweetHandler(Handler* next)
  : Handler(next)
{

}

bool TweetHandler::canHandle(const std::string& cmd) const
{
	return cmd == "TWEET";
}

Handler::HANDLER_STATUS_T TweetHandler::process(TwitEng* eng, std::istream& instr) const
{

	string text;
	getline(instr, text);
	if(eng->tweet(text)){
		return HANDLER_OK;
	}
	else{
		cout << "No user logged in." << endl;
		return HANDLER_ERROR;
	}
}


FollowHandler::FollowHandler()
{

}

FollowHandler::FollowHandler(Handler* next)
  : Handler(next)
{

}

bool FollowHandler::canHandle(const std::string& cmd) const
{
	return cmd == "FOLLOW";
}

Handler::HANDLER_STATUS_T FollowHandler::process(TwitEng* eng, std::istream& instr) const
{
	string followed;
	instr >> followed;
	if(eng->follow( followed)){
		return HANDLER_OK;
	}
	else{
		cout << "No user logged in." << endl;
		return HANDLER_ERROR;
	}
}


SaveHandler::SaveHandler()
{

}

SaveHandler::SaveHandler(Handler* next)
  : Handler(next)
{

}

bool SaveHandler::canHandle(const std::string& cmd) const
{
	return cmd == "SAVE";
}

Handler::HANDLER_STATUS_T SaveHandler::process(TwitEng* eng, std::istream& instr) const
{
	string filename;
	instr >> filename;
	eng->save(filename);
	return HANDLER_OK;
}

SCCHandler::SCCHandler()
{

}

SCCHandler::SCCHandler(Handler* next)
  : Handler(next)
{

}

bool SCCHandler::canHandle(const std::string& cmd) const
{
	return cmd == "SCC";
}

Handler::HANDLER_STATUS_T SCCHandler::process(TwitEng* eng, std::istream& instr) const
{
	eng->scc();
	return HANDLER_OK;
}


TrendingHandler::TrendingHandler()
{

}

TrendingHandler::TrendingHandler(Handler* next)
  : Handler(next)
{

}

bool TrendingHandler::canHandle(const std::string& cmd) const
{
	return cmd == "TRENDING";
}

Handler::HANDLER_STATUS_T TrendingHandler::process(TwitEng* eng, std::istream& instr) const
{
	int n;
	instr >> n;
	if(n < 0){
		return HANDLER_ERROR;
	}
	eng->trending(n);
	return HANDLER_OK;
}



LoginHandler::LoginHandler()
{

}

LoginHandler::LoginHandler(Handler* next)
  : Handler(next)
{

}

bool LoginHandler::canHandle(const std::string& cmd) const
{
	return cmd == "LOGIN";
}

Handler::HANDLER_STATUS_T LoginHandler::process(TwitEng* eng, std::istream& instr) const
{
	string user, password;
	instr >> user >> password;
	if(eng->login(user, password)){
		cout << "Login successful." << endl;
		return HANDLER_OK;
	}
	else{
		cout << "Invalid username/password." << endl;
		return HANDLER_ERROR;
	}
}


LogoutHandler::LogoutHandler()
{

}

LogoutHandler::LogoutHandler(Handler* next)
  : Handler(next)
{

}

bool LogoutHandler::canHandle(const std::string& cmd) const
{
	return cmd == "LOGOUT";
}

Handler::HANDLER_STATUS_T LogoutHandler::process(TwitEng* eng, std::istream& instr) const
{
	eng->logout();
	return HANDLER_OK;
}




NewUserHandler::NewUserHandler()
{

}

NewUserHandler::NewUserHandler(Handler* next)
  : Handler(next)
{

}

bool NewUserHandler::canHandle(const std::string& cmd) const
{
	return cmd == "NEWUSER";
}

Handler::HANDLER_STATUS_T NewUserHandler::process(TwitEng* eng, std::istream& instr) const
{
	string username, password;
	instr >> username >> password;

	if(eng->addUser(username, password))
		return HANDLER_OK;

	return HANDLER_ERROR;
}




FeedHandler::FeedHandler()
{

}

FeedHandler::FeedHandler(Handler* next)
  : Handler(next)
{

}

bool FeedHandler::canHandle(const std::string& cmd) const
{
	return cmd == "FEED";
}

Handler::HANDLER_STATUS_T FeedHandler::process(TwitEng* eng, std::istream& instr) const
{
	return HANDLER_OK;
}
