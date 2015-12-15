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

#ifndef _SHARED_PLATFORM_FACTORYREPOSITORY_H_
#define _SHARED_PLATFORM_FACTORYREPOSITORY_H_

#include <string>

#include "graphics_factory.h"
#include "sound_factory.h"

#include "graphics_factory_gl.h"








namespace Glest {

// =====================================================
//	class FactoryRepository
// =====================================================

class FactoryRepository{
private:
	FactoryRepository();
    ~FactoryRepository();

	void operator=(const FactoryRepository& );

private:
	GraphicsFactoryGl graphicsFactoryGl;
	SoundFactory* _soundFactory;

public:
	static FactoryRepository &getInstance();

	GraphicsFactory *getGraphicsFactory(const std::string &name);
	SoundFactory *getSoundFactory(const std::string &name);
};

}//end namespace

#endif
