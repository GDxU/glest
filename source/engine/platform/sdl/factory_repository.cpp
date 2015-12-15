

#include "factory_repository.h"
//#include "sound_factory_ds8.h"
#include "sound_factory_openal.h"

namespace Glest {

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
    _soundFactory = new SoundFactoryOpenAL;
}

FactoryRepository::~FactoryRepository()
{
    delete _soundFactory;
}

}//end namespace
