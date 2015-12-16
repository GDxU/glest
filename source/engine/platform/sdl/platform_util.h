
#ifndef _SHARED_PLATFORM_PLATFORMUTIL_H_
#define _SHARED_PLATFORM_PLATFORMUTIL_H_

#include <string>
#include <vector>
#include <stdexcept>

#include <SDL.h>

#include "types.h"










namespace Glest {

// =====================================================
//	class PerformanceTimer
// =====================================================

class HiresTimer
{
private:

    long long startTime_;

    static long long frequency;

    static void Init();

public:

    HiresTimer();

    void Reset();
    long long GetUSec(bool reset);

    static long long GetFrequency() { return frequency; }
};

class Time
{
public:
    static void Sleep(unsigned mSec);
};

// =====================================================
//	class Chrono
// =====================================================

class Chrono {
private:
	Uint32 startCount;
	Uint32 accumCount;
	Uint32 freq;
	bool stopped;

public:
	Chrono();
	void start();
	void stop();
	int64 getMicros() const;
	int64 getMillis() const;
	int64 getSeconds() const;

private:
	int64 queryCounter(int multiplier) const;
};

// =====================================================
//	class PlatformExceptionHandler
// =====================================================

class PlatformExceptionHandler {
public:
	virtual ~PlatformExceptionHandler() {}
	void install(std::string dumpFileName) {}
	virtual void handle()=0;
};

// =====================================================
//	Misc
// =====================================================

void findAll(const std::string &path, std::vector<std::string> &results, bool cutExtension = false);

bool changeVideoMode(int resH, int resW, int colorBits, int refreshFrequency);
void restoreVideoMode();

void message(std::string message);
bool ask(std::string message);
void exceptionMessage(const std::exception &excp);

int getScreenW();
int getScreenH();

void sleep(int millis);

void showCursor(bool b);
bool isKeyDown(int virtualKey);
std::string getCommandLine();

}//end namespace

#endif
