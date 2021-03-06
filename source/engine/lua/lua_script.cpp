

#include "lua_script.h"

#include <stdexcept>

#include "conversion.h"






namespace Glest {

// =====================================================
//	class LuaScript
// =====================================================

LuaScript::LuaScript(){
	luaState= luaL_newstate();

	luaL_openlibs(luaState);

	if(luaState==NULL){
		throw std::runtime_error("Can not allocate lua state");
	}

	argumentCount= -1;
}

LuaScript::~LuaScript(){
	lua_close(luaState);
}

void LuaScript::loadCode(const std::string &code, const std::string &name){
	int errorCode= luaL_loadbuffer(luaState, code.c_str(), code.size(), name.c_str());
	if(errorCode!=0){
		throw std::runtime_error("Error loading lua code: " + errorToString(errorCode));
	}

	//run code
	errorCode= lua_pcall(luaState, 0, 0, 0)!=0;
	if(errorCode!=0){
		throw std::runtime_error("Error initializing lua: " + errorToString(errorCode));
	}
}

void LuaScript::beginCall(const std::string& functionName){
	lua_getglobal(luaState, functionName.c_str());
	argumentCount= 0;
}

void LuaScript::endCall(){
	lua_pcall(luaState, argumentCount, 0, 0);
}

void LuaScript::registerFunction(LuaFunction luaFunction, const std::string &functionName){
    lua_pushcfunction(luaState, luaFunction);
	lua_setglobal(luaState, functionName.c_str());
}

std::string LuaScript::errorToString(int errorCode){

	std::string error;
		
	switch(errorCode){
		case LUA_ERRSYNTAX: 
			error+= "Syntax error"; 
			break;
		case LUA_ERRRUN: 
			error+= "Runtime error"; 
			break;
		case LUA_ERRMEM: 
			error+= "Memory allocation error"; 
			break;
		case LUA_ERRERR: 
			error+= "Error while running the error handler"; 
			break;
		default:
			error+= "Unknown error";
	}

    error += std::string(": ") + luaL_checkstring(luaState, -1);

	return error;
}

// =====================================================
//	class LuaArguments
// =====================================================

LuaArguments::LuaArguments(lua_State *luaState){
	this->luaState= luaState;
	returnCount= 0;
}

int LuaArguments::getInt(int argumentIndex) const{
	if(!lua_isnumber(luaState, argumentIndex)){
		throwLuaError("Can not get int from Lua state");
	}
	return luaL_checkint(luaState, argumentIndex);
}

std::string LuaArguments::getString(int argumentIndex) const{
	if(!lua_isstring(luaState, argumentIndex)){
		throwLuaError("Can not get std::string from Lua state");
	}
	return luaL_checkstring(luaState, argumentIndex);
}

Vec2i LuaArguments::getVec2i(int argumentIndex) const{
	Vec2i v;
	
	if(!lua_istable(luaState, argumentIndex)){
		throwLuaError("Can not get vec2i from Lua state, value on the stack is not a table");
	}

	if(luaL_getn(luaState, argumentIndex)!=2){
		throwLuaError("Can not get vec2i from Lua state, array size not 2");
	}

	lua_rawgeti(luaState, argumentIndex, 1);
	v.x= luaL_checkint(luaState, argumentIndex);
	lua_pop(luaState, 1);

	lua_rawgeti(luaState, argumentIndex, 2);
	v.y= luaL_checkint(luaState, argumentIndex);
	lua_pop(luaState, 1);

	return v;
}

void LuaArguments::returnInt(int value){
	++returnCount;
	lua_pushinteger(luaState, value);
}

void LuaArguments::returnString(const std::string &value){
	++returnCount;
	lua_pushstring(luaState, value.c_str());
}

void LuaArguments::returnVec2i(const Vec2i &value){
	++returnCount;

	lua_newtable(luaState);

	lua_pushnumber(luaState, value.x);
	lua_rawseti(luaState, -2, 1);

	lua_pushnumber(luaState, value.y);
	lua_rawseti(luaState, -2, 2);
}

void LuaArguments::throwLuaError(const std::string &message) const{
	std::string stackString;
	int stackSize = lua_gettop(luaState);

	//build stack std::string
	for(int i= 1; i<=stackSize; ++i){
		stackString+= "-" + intToStr(i) + ": ";
		if(lua_isnumber(luaState, -i)){
			stackString+= "Number: " + doubleToStr(luaL_checknumber(luaState, -i ));
		}
		else if(lua_isstring(luaState, -i)){
            stackString += "String: " + std::string(luaL_checkstring(luaState, -i));
		}
		else if(lua_istable(luaState, -i)){
			stackString+= "Table (" + intToStr(luaL_getn(luaState, -i)) + ")";
		}
		else
		{
			stackString+= "Unknown";
		}
		stackString+= "\n";
	}
	
	throw std::runtime_error("Lua error: " + message + "\n\nLua Stack:\n" + stackString);
}

}//end namespace
