// ==============================================================
//	This file is part of Glest Shared Library (www.glest.org)
//
//	Copyright (C) 2005 Matthias Braun <matze@braunis.de>
//
//	You can redistribute this code and/or modify it under 
//	the terms of the GNU General Public License as published 
//	by the Free Software Foundation; either version 2 of the 
//	License, or (at your option) any later version
// ==============================================================
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

class PerformanceTimer{
private:
	Uint32 lastTicks;
	Uint32 updateTicks;

	int times;			// number of consecutive times
	int maxTimes;		// maximum number consecutive times

public:
	void init(float fps, int maxTimes= -1);
	
	bool isTime();
	void reset();
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
