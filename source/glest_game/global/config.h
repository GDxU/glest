// ==============================================================
//	This file is part of Glest (www.glest.org)
//
//	Copyright (C) 2001-2008 Martiño Figueroa
//
//	You can redistribute this code and/or modify it under 
//	the terms of the GNU General Public License as published 
//	by the Free Software Foundation; either version 2 of the 
//	License, or (at your option) any later version
// ==============================================================

#ifndef _GLEST_GAME_CONFIG_H_
#define _GLEST_GAME_CONFIG_H_

#include "properties.h"

namespace Glest {



// =====================================================
// 	class Config
//
//	Game configuration
// =====================================================

class Config{
private:
	Properties properties;

private:
	Config();

public:
    static Config &getInstance();
	void save(const std::string &path="glest.ini");

	int getInt(const std::string &key) const;
	bool getBool(const std::string &key) const;
	float getFloat(const std::string &key) const;
	const std::string &getString(const std::string &key) const;

	void setInt(const std::string &key, int value);
	void setBool(const std::string &key, bool value);
	void setFloat(const std::string &key, float value);
	void setString(const std::string &key, const std::string &value);

	std::string toString();
};

}//end namespace

#endif
