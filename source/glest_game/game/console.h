

#ifndef _GLEST_GAME_CONSOLE_H_
#define _GLEST_GAME_CONSOLE_H_

#include <utility>
#include <string>
#include <vector>








namespace Glest {

// =====================================================
// 	class Console
//
//	In-game console that shows various types of messages
// =====================================================

class Console{
private:
	static const int consoleLines= 5;

public:
	typedef std::pair<std::string, float> StringTimePair;
	typedef std::vector<StringTimePair> Lines;
	typedef Lines::const_iterator LineIterator;

private:
	float timeElapsed; 
	Lines lines;

	//this should be deleted from here someday
	bool won, lost;

	//config
	int maxLines;
	float timeout;

public:
	Console();
	
	int getLineCount() const		{return lines.size();}
	std::string getLine(int i) const		{return lines[i].first;}


	void addStdMessage(const std::string &s);
	void addLine(std::string line, bool playSound= false);
	void update();
	bool isEmpty();
};

}//end namespace

#endif
