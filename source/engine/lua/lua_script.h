

#ifndef _SHARED_LUA_LUASCRIPT_H_
#define _SHARED_LUA_LUASCRIPT_H_

#include <string>

#include <lua.hpp>

#include <vec.h>






namespace Glest {

typedef lua_State LuaHandle;
typedef int(*LuaFunction)(LuaHandle*);

// =====================================================
//	class LuaScript
// =====================================================

class LuaScript{
private:
	LuaHandle *luaState;
	int argumentCount;

public:
	LuaScript();
	~LuaScript();

	void loadCode(const std::string &code, const std::string &name);

    void beginCall(const std::string& functionName);
	void endCall();

	void registerFunction(LuaFunction luaFunction, const std::string &functionName);

private:
	std::string errorToString(int errorCode);
};

// =====================================================
//	class LuaArguments
// =====================================================

class LuaArguments{
private:
	lua_State *luaState;
	int returnCount;

public:
	LuaArguments(lua_State *luaState);

	int getInt(int argumentIndex) const;
	std::string getString(int argumentIndex) const;
	Vec2i getVec2i(int argumentIndex) const;
	int getReturnCount() const					{return returnCount;}

	void returnInt(int value);
	void returnString(const std::string &value);
	void returnVec2i(const Vec2i &value);

private:
	void throwLuaError(const std::string &message) const;
};

}//end namespace

#endif
