//This file is part of Glest Shared Library (www.glest.org)
//Copyright (C) 2005 Matthias Braun <matze@braunis.de>

//You can redistribute this code and/or modify it under 
//the terms of the GNU General Public License as published by the Free Software 
//Foundation; either version 2 of the License, or (at your option) any later 
//version.
#include "platform_util.h"

#include <iostream>
#include <sstream>
#include <cassert>

//#include <glob.h>
#include <errno.h>
#include <string.h>

#include <SDL.h>

#include "util.h"
#include "conversion.h"
#include "sdl_private.h"
#include "noimpl.h"

#include <Windows.h>
#include <minwinbase.h>
#include <winbase.h>
#include <wtypes.h>
#include "main.h"




SDL_Window* getWindow();


namespace Glest {

namespace Private{

bool shouldBeFullscreen = false;
int ScreenWidth;
int ScreenHeight;

}



static long long HiresTick()
{
#ifdef _WIN32
//     if (HiresTimer::IsSupported())
//     {
        LARGE_INTEGER counter;
        QueryPerformanceCounter(&counter);
        return counter.QuadPart;
//     }
//     else
//         return timeGetTime();
#elif __EMSCRIPTEN__
    return (unsigned)(emscripten_get_now()*1000.0);
#else
    struct timeval time;
    gettimeofday(&time, NULL);
    return time.tv_sec * 1000000LL + time.tv_usec;
#endif
}

// =====================================
//          PerformanceTimer   
// =====================================
long long HiresTimer::frequency = 1000000;

void HiresTimer::Init()
{
    static bool isinit = false;
    if (!isinit)
    {
#ifdef _WIN32
        LARGE_INTEGER frequency;
        if (QueryPerformanceFrequency(&frequency))
        {
            HiresTimer::frequency = frequency.QuadPart;
        }
#endif
    }
}


HiresTimer::HiresTimer()
{
    Init();
}

void HiresTimer::Reset()
{
    startTime_ = HiresTick();
}

long long HiresTimer::GetUSec(bool reset)
{
    long long currentTime = HiresTick();
    long long elapsedTime = currentTime - startTime_;

    // Correct for possible weirdness with changing internal frequency
    if (elapsedTime < 0)
        elapsedTime = 0;

    if (reset)
        startTime_ = currentTime;

    return (elapsedTime * 1000000LL) / frequency;
}


void Time::Sleep(unsigned mSec)
{
#ifdef _WIN32
    ::Sleep(mSec);
#else
    usleep(mSec * 1000);
#endif
}

// =====================================
//         Chrono    
// =====================================

Chrono::Chrono() {
	freq = 1000;
	stopped= true;
	accumCount= 0;
}

void Chrono::start() {
	stopped= false;
	startCount = SDL_GetTicks();
}

void Chrono::stop() {
	Uint32 endCount;
	endCount = SDL_GetTicks();
	accumCount += endCount-startCount;
	stopped= true;
}

int64 Chrono::getMicros() const {
	return queryCounter(1000000);
}

int64 Chrono::getMillis() const {
	return queryCounter(1000);
}

int64 Chrono::getSeconds() const {
	return queryCounter(1);
}

int64 Chrono::queryCounter(int multiplier) const {
	if(stopped) {
		return multiplier*accumCount/freq;
	} else {
		Uint32 endCount;
		endCount = SDL_GetTicks();
		return multiplier*(accumCount+endCount-startCount)/freq;
	}
}

// =====================================
//         Misc    
// =====================================
static std::string getExtension(const std::string& fullname)
{
	int i = fullname.find_last_of('.');

	if (i != -1)
		return fullname.substr(i + 1);
	else
		return "";
}
static std::string getDirectory(const std::string& name)
{
	int i = name.find_last_of("/\\");
	if (i != -1)
		return name.substr(0, i);

	return ".";
}
static void normalizePath(std::string* path)
{
	size_t pos = std::string::npos;
	while ((pos = path->find_first_of("/\\", pos + 1)) != std::string::npos)
	{
		path->replace(pos, 1, "/");
	}

	if (path->operator[](path->size() - 1) != '/')
		path->append("/");
}
//finds all filenames like path and stores them in resultys
void findAll(const std::string &path, std::vector<std::string> &results, bool cutExtension) {
	results.clear();

	std::string mypath = path;
	/** Stupid win32 is searching for all files without extension when *. is
	 * specified as wildcard
	 */
	if(mypath.compare(mypath.size() - 2, 2, "*.") == 0) {
		mypath += "*";
	}

    std::wstring wpath;

    String2WString(mypath, wpath);

	WIN32_FIND_DATAW info;
    HANDLE handle = FindFirstFileW(wpath.c_str(), &info);
	if (handle != INVALID_HANDLE_VALUE)
	{
		do
		{
            std::string filename;
            WString2String(info.cFileName, filename);

			if (!filename.empty() && filename != "." &&filename != "..")
				//!(info.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) &&
				//!(info.dwFileAttributes & FILE_ATTRIBUTE_HIDDEN) &&
			{
				results.push_back(filename);
			}

		} while (FindNextFileW(handle, &info));

		FindClose(handle);
	}

// 	glob_t globbuf;
// 	
// 	int res = glob(mypath.c_str(), 0, 0, &globbuf);
// 	if(res < 0) {
// 		std::stringstream msg;
// 		msg << "Couldn't scan directory '" << mypath << "': " << strerror(errno);
// 		throw std::runtime_error(msg.str());
// 	}
// 
// 	for(size_t i = 0; i < globbuf.gl_pathc; ++i) {
// 		const char* p = globbuf.gl_pathv[i];
// 		const char* begin = p;
// 		for( ; *p != 0; ++p) {
// 			// strip the path component
// 			if(*p == '/')
// 				begin = p+1;
// 		}
// 		results.push_back(begin);
// 	}
// 
// 	globfree(&globbuf);
// 
	if(results.size() == 0) {
		throw std::runtime_error("No files found in: " + mypath);
	}

	if(cutExtension) {
		for (size_t i=0; i<results.size(); ++i){
			results.at(i)=cutLastExt(results.at(i));
		}
	}
}

bool changeVideoMode(int resW, int resH, int colorBits, int ) {
	Private::shouldBeFullscreen = true;
	return true;
}

void restoreVideoMode() {
}

void message(std::string message) {
	std::cerr << "******************************************************\n";
	std::cerr << "    " << message << "\n";
	std::cerr << "******************************************************\n";
}

bool ask(std::string message) {
	std::cerr << "Confirmation: " << message << "\n";
	int res;
	std::cin >> res;
	return res != 0;
}

void exceptionMessage(const std::exception &excp) {
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Exception", excp.what(), getWindow());
}


int getScreenW() {
    int w, h;
    SDL_GL_GetDrawableSize(getWindow(), &w, &h);
	//return SDL_GetVideoSurface()->w;
    return w;
}

int getScreenH() {
    int w, h;
    SDL_GL_GetDrawableSize(getWindow(), &w, &h);
    //return SDL_GetVideoSurface()->h;
    return h;
}

void sleep(int millis) {
	SDL_Delay(millis);
}

void showCursor(bool b) {
	SDL_ShowCursor(b ? SDL_ENABLE : SDL_DISABLE);
}

bool isKeyDown(int virtualKey) {
	char key = static_cast<char> (virtualKey);
    const Uint8* keystate = SDL_GetKeyboardState(0);
    //const Uint8* keystate = SDL_GetKeyState(0);

	if (strlen((char*)keystate) == 0)
		return false;

	// kinda hack and wrong...
	if(key >= 0) {
		return keystate[key];
	}
	switch(key) {
		case vkAdd:
			return keystate[SDLK_PLUS] | keystate[SDLK_KP_PLUS];
		case vkSubtract:
			return keystate[SDLK_MINUS] | keystate[SDLK_KP_MINUS];
		case vkAlt:
			return keystate[SDLK_LALT] | keystate[SDLK_RALT];
		case vkControl:
			return keystate[SDLK_LCTRL] | keystate[SDLK_RCTRL];
		case vkShift:
			return keystate[SDLK_LSHIFT] | keystate[SDLK_RSHIFT];
		case vkEscape:
			return keystate[SDLK_ESCAPE];
		case vkUp:
			return keystate[SDLK_UP];
		case vkLeft:
			return keystate[SDLK_LEFT];
		case vkRight:
			return keystate[SDLK_RIGHT];
		case vkDown:
			return keystate[SDLK_DOWN];
		case vkReturn:
			return keystate[SDLK_RETURN] | keystate[SDLK_KP_ENTER];
		case vkBack:
			return keystate[SDLK_BACKSPACE];
		default:
			std::cerr << "isKeyDown called with unknown key.\n";
			break;
	}
	return false;
}

}//end namespace
