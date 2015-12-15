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

#include "factory_repository.h"
//#include "sound_factory_ds8.h"
#include "sound_factory_openal.h"

namespace Shared{ namespace Platform{

// =====================================================
//	class FactoryRepository
// =====================================================

FactoryRepository &FactoryRepository::getInstance() {
	static FactoryRepository factoryRepository;
	return factoryRepository;
}

GraphicsFactory *FactoryRepository::getGraphicsFactory(const std::string &name) {
	if(name == "OpenGL") {
		return &graphicsFactoryGl;
	}

	throw std::runtime_error("Unknown graphics factory: " + name);
}

SoundFactory *FactoryRepository::getSoundFactory(const std::string &name) {
    return _soundFactory;
	//throw std::runtime_error("Unknown sound factory: " + name);
}

FactoryRepository::FactoryRepository()
{
    _soundFactory = new Shared::Sound::OpenAL::SoundFactoryOpenAL;
}

FactoryRepository::~FactoryRepository()
{
    delete _soundFactory;
}

}}//end namespace
