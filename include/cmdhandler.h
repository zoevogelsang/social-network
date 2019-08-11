#ifndef CMDHANDLER_H
#define CMDHANDLER_H
#include "handler.h"

/**
 * Handles the QUIT command
 */
class QuitHandler : public Handler
{
public:
	QuitHandler();
	QuitHandler(Handler* next);

protected:

	virtual bool canHandle(const std::string& cmd) const;
	virtual HANDLER_STATUS_T process(TwitEng* eng, std::istream& instr) const;
};
 
/**
 * Handles the AND command
 */
class AndHandler : public Handler
{
public:
	AndHandler();
	AndHandler(Handler* next);

protected:

	virtual bool canHandle(const std::string& cmd) const;
	virtual HANDLER_STATUS_T process(TwitEng* eng, std::istream& instr) const;
};

/**
 * Handles the OR command
 */
class OrHandler : public Handler
{
public:
	OrHandler();
	OrHandler(Handler* next);

protected:

	virtual bool canHandle(const std::string& cmd) const;
	virtual HANDLER_STATUS_T process(TwitEng* eng, std::istream& instr) const;
};

/**
 * Handles the TWEET command
 */
class TweetHandler : public Handler
{
public:
	TweetHandler();
	TweetHandler(Handler* next);

protected:

	virtual bool canHandle(const std::string& cmd) const;
	virtual HANDLER_STATUS_T process(TwitEng* eng, std::istream& instr) const;
};

/**
 * Handles the FOLLOW command
 */
class FollowHandler : public Handler
{
public:
    FollowHandler();
    FollowHandler(Handler* next);
    
protected:
    
    virtual bool canHandle(const std::string& cmd) const;
    virtual HANDLER_STATUS_T process(TwitEng* eng, std::istream& instr) const;
};

/**
 * Handles the SAVE command
 */
class SaveHandler : public Handler
{
public:
    SaveHandler();
    SaveHandler(Handler* next);
    
protected:
    
    virtual bool canHandle(const std::string& cmd) const;
    virtual HANDLER_STATUS_T process(TwitEng* eng, std::istream& instr) const;
};


/**
 * Handles the SCC command
 */
class SCCHandler : public Handler
{
public:
    SCCHandler();
    SCCHandler(Handler* next);
    
protected:
    
    virtual bool canHandle(const std::string& cmd) const;
    virtual HANDLER_STATUS_T process(TwitEng* eng, std::istream& instr) const;
};

/**
 * Handles the SCC command
 */
class TrendingHandler : public Handler
{
public:
    TrendingHandler();
    TrendingHandler(Handler* next);
    
protected:
    
    virtual bool canHandle(const std::string& cmd) const;
    virtual HANDLER_STATUS_T process(TwitEng* eng, std::istream& instr) const;
};

/**
 * Handles the Login command
 */
class LoginHandler : public Handler
{
public:
    LoginHandler();
    LoginHandler(Handler* next);
    
protected:
    
    virtual bool canHandle(const std::string& cmd) const;
    virtual HANDLER_STATUS_T process(TwitEng* eng, std::istream& instr) const;
};

/**
 * Handles the Logout command
 */
class LogoutHandler : public Handler
{
public:
    LogoutHandler();
    LogoutHandler(Handler* next);
    
protected:
    
    virtual bool canHandle(const std::string& cmd) const;
    virtual HANDLER_STATUS_T process(TwitEng* eng, std::istream& instr) const;
};


/**
 * Handles the NEWUSER command
 */
class NewUserHandler : public Handler
{
public:
    NewUserHandler();
    NewUserHandler(Handler* next);
    
protected:
    
    virtual bool canHandle(const std::string& cmd) const;
    virtual HANDLER_STATUS_T process(TwitEng* eng, std::istream& instr) const;
};


/**
 * Handles the FEED command
 */
class FeedHandler : public Handler
{
public:
    FeedHandler();
    FeedHandler(Handler* next);
    
protected:
    
    virtual bool canHandle(const std::string& cmd) const;
    virtual HANDLER_STATUS_T process(TwitEng* eng, std::istream& instr) const;
};

#endif
