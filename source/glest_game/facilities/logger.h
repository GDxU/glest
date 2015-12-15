

#ifndef _SHARED_UTIL_LOGGER_H_
#define _SHARED_UTIL_LOGGER_H_

#include <string>
#include <deque>






namespace Glest {

// =====================================================
//	class Logger  
//
/// Interface to write log files
// =====================================================

class Logger{
private:
	static const int logLineCount;

private:
	typedef std::deque<std::string> Strings;

private:
	std::string fileName;
	std::string state;
	std::string subtitle;
	std::string current;

private:
	Logger();

public:
	static Logger & getInstance();
	
	void setFile(const std::string &fileName)		{this->fileName= fileName;}
	void setState(const std::string &state)			{this->state= state;}
	void setSubtitle(const std::string &subtitle)	{this->subtitle= subtitle;}

	void add(const std::string &str, bool renderScreen= false);
	void renderLoadingScreen();

	void clear();
};

}//end namespace

#endif
