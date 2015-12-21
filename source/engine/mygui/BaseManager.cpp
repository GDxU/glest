
#include "Precompiled.h"
#include "BaseManager.h"
#include "MyGUI_Diagnostic.h"

//#include "SDL_image.h"

#include "GL/glew.h"
#include "stb_image.h"

#ifdef MYGUI_CHECK_MEMORY_LEAKS
#	undef new
#	undef delete
#endif


static SDL_Window* s_window = NULL;

SDL_Window* getWindow() {
    return s_window;
}

namespace base
{
	BaseManager::BaseManager() :
		mGUI(nullptr),
		mPlatform(nullptr),
		mWindow(nullptr),
		mContext(nullptr),
		mExit(false),
		mWindowOn(false),
		mResourceFileName("MyGUI_Core.xml")
	{
		// initialize SDL
		//MYGUI_ASSERT(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_AUDIO | SDL_INIT_EVENTS) == 0, "Failed initializing SDL.");
		// initialize SDL_image
		//MYGUI_ASSERT(IMG_Init(~0) != 0, "Failed to initializing SDL_image");
	}

	BaseManager::~BaseManager()
	{
		//SDL_GL_DeleteContext(mContext);
		//IMG_Quit();
		//SDL_Quit();
	}

	void BaseManager::_windowResized( int w, int h )
{
		if (mPlatform)
			mPlatform->getRenderManagerPtr()->setViewSize(w, h);

		setInputViewSize(w, h);
	}

    bool BaseManager::create(int _width, int _height, bool windowed)
	{
        mWidth = _width;
        mHeight = _height;
        mFullScreen = !windowed;

        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
        // 	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 1);
        // 	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 1);
        // 	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 1);
        // 	SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, stencilBits);
        SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

        int flags = SDL_WINDOW_OPENGL;
#if 0
        if (mFullScreen)
            flags |= SDL_WINDOW_FULLSCREEN;
#endif
        SDL_Window* screen = SDL_CreateWindow("Cocos2d SDL ", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, _width, _height, flags);

        SDL_GL_CreateContext(screen);

        if (glewInit() != GLEW_OK)
            std::cout << "GLEW init false";

        if (GLEW_ARB_vertex_shader && GLEW_ARB_fragment_shader)
        {
            std::cout << "Ready for GLSL\n";
        }
        else
        {
            std::cout << "Not totally ready :(\n";
        }

        if (glewIsSupported("GL_VERSION_2_0"))
        {
            std::cout << "Ready for OpenGL 2.0\n";
        }
        else
        {
            std::cout << "OpenGL 2.0 not supported\n";
        }

        SDL_GL_SetSwapInterval(1);

        s_window = screen;

        if (screen == 0) {
            std::ostringstream msg;
            msg << "Couldn't set video mode " << _width << "x" << _height << " depth-buffer). SDL Error is: " << SDL_GetError();
            throw std::runtime_error(msg.str());
        }

		mWindowOn = true;

		if (!createRender(mWidth, mHeight, windowed))
		{
			return false;
		}

		createGui();

		createInput();

		createPointerManager();

		// this needs to be called before createScene() since some demos require
		// screen size to properly position the widgets
		_windowResized(mWidth, mHeight);

		createScene();

		return true;
	}

    void BaseManager::swapBuffer()
    {
        glFlush();
        SDL_GL_SwapWindow(s_window);
    }

    void BaseManager::drawOneFrame()
    {
        if (mPlatform)
            mPlatform->getRenderManagerPtr()->drawOneFrame();

        swapBuffer();
    }

	void BaseManager::destroy()
	{
		destroyScene();

		destroyPointerManager();

		destroyInput();

		destroyGui();

		destroyRender();

	}

	void BaseManager::setupResources()
	{
		MyGUI::xml::Document doc;

		if (!doc.open(std::string("resources.xml")))
			doc.getLastError();

		MyGUI::xml::ElementPtr root = doc.getRoot();
		if (root == nullptr || root->getName() != "Paths")
			return;

		MyGUI::xml::ElementEnumerator node = root->getElementEnumerator();
		while (node.next())
		{
			if (node->getName() == "Path")
			{
				if (node->findAttribute("root") != "")
				{
					bool root = MyGUI::utility::parseBool(node->findAttribute("root"));
					if (root)
						mRootMedia = node->getContent();
				}
				addResourceLocation(node->getContent(), false);
			}
		}

		addResourceLocation(getRootMedia() + "/Common/Base");
	}

	void BaseManager::createGui()
	{
		mPlatform = new MyGUI::OpenGLPlatform();
		mPlatform->initialise(this);

		setupResources();

		mGUI = new MyGUI::Gui();
		mGUI->initialise(mResourceFileName);

		SDL_StartTextInput();
	}

	void BaseManager::destroyGui()
	{
		SDL_StopTextInput();
		if (mGUI)
		{
			mGUI->shutdown();
			delete mGUI;
			mGUI = nullptr;
		}

		if (mPlatform)
		{
			mPlatform->shutdown();
			delete mPlatform;
			mPlatform = nullptr;
		}
	}

	void BaseManager::setWindowMaximized(bool _value)
	{
		if (mWindow != nullptr && _value)
		{
			SDL_MaximizeWindow(mWindow);
		}
	}

	bool BaseManager::getWindowMaximized()
	{
		Uint32 windowState = SDL_GetWindowFlags(mWindow);
		return windowState & SDL_WINDOW_MAXIMIZED || windowState & SDL_WINDOW_FULLSCREEN;
	}

	void BaseManager::setWindowCoord(const MyGUI::IntCoord& _value)
	{
		if (_value.empty())
			return;

		MyGUI::IntCoord coord = _value;

		SDL_SetWindowPosition(mWindow, coord.left, coord.top);
	}

	MyGUI::IntCoord BaseManager::getWindowCoord()
	{
		int left, top, width, height;
		SDL_GetWindowPosition(mWindow, &left, &top);
		SDL_GetWindowSize(mWindow, &width, &height);
		return MyGUI::IntCoord(left, top, width, height);
	}

	void BaseManager::setWindowCaption(const std::wstring& _text)
	{
		MyGUI::UString title(_text);
		SDL_SetWindowTitle(mWindow, title.asUTF8_c_str());
	}

	void BaseManager::prepare()
	{
	}

	void BaseManager::addResourceLocation(const std::string& _name, bool _recursive)
	{
		mPlatform->getDataManagerPtr()->addResourceLocation(_name, _recursive);
	}

    bool BaseManager::injectMouseMove(int _absx, int _absy, int _absz)
	{
		if (!mGUI)
			return false;

        return MyGUI::InputManager::getInstance().injectMouseMove(_absx, _absy, _absz);
	}

	bool BaseManager::injectMousePress(int _absx, int _absy, MyGUI::MouseButton _id)
	{
		if (!mGUI)
            return false;

        return MyGUI::InputManager::getInstance().injectMousePress(_absx, _absy, _id);
	}

    bool BaseManager::injectMouseRelease(int _absx, int _absy, MyGUI::MouseButton _id)
	{
		if (!mGUI)
            return false;

		return MyGUI::InputManager::getInstance().injectMouseRelease(_absx, _absy, _id);
	}

    bool BaseManager::injectKeyPress(MyGUI::KeyCode _key, MyGUI::Char _text)
	{
		if (!mGUI)
			return false;

// 		if (_key == MyGUI::KeyCode::Escape)
// 		{
// 			mExit = true;
// 			return false;
// 		}

		return MyGUI::InputManager::getInstance().injectKeyPress(_key, _text);
	}

    bool BaseManager::injectKeyRelease(MyGUI::KeyCode _key)
	{
		if (!mGUI)
			return false;

		return MyGUI::InputManager::getInstance().injectKeyRelease(_key);
	}

	bool BaseManager::createRender(int _width, int _height, bool _windowed)
	{
		return true;
	}

	void BaseManager::destroyRender()
	{
	}

	void* BaseManager::convertPixelData(SDL_Surface *_image, MyGUI::PixelFormat& _myGuiPixelFormat)
	{
		void* ret = nullptr;
		SDL_PixelFormat *format = _image->format;
		unsigned int bpp = format->BytesPerPixel;
		switch (bpp) {
		case 1:
			_myGuiPixelFormat = MyGUI::PixelFormat::L8;
			break;
		case 2:
			_myGuiPixelFormat = MyGUI::PixelFormat::L8A8;
			break;
		case 3:
			_myGuiPixelFormat = MyGUI::PixelFormat::R8G8B8;
			break;
		case 4:
			_myGuiPixelFormat = MyGUI::PixelFormat::R8G8B8A8;
			break;
		default:
			break;
		}
		SDL_LockSurface(_image);

		int pitchSrc = _image->pitch;	//the length of a row of pixels in bytes
		int bppSrc = pitchSrc / _image->w;
		size_t size = _image->h * pitchSrc;
		ret = new unsigned char[size];
		unsigned char* ptr_source = (unsigned char*)_image->pixels;
		unsigned char* ptr_dst = (unsigned char*)ret;
		int pitchDst = _image->w * bpp;
		if (pitchSrc == pitchDst)
		{
			memcpy(ret, _image->pixels, size);
		}
		else
		{
			for (unsigned int y = 0; y < (unsigned int)_image->h; ++y)
			{
				memcpy(ptr_dst, ptr_source, pitchDst);
				ptr_dst += pitchDst;
				ptr_source += pitchSrc;
			}
		}

		SDL_UnlockSurface(_image);
		return ret;
	}

	void* BaseManager::loadImage(int& _width, int& _height, MyGUI::PixelFormat& _format, const std::string& _filename)
	{
		std::string fullname = MyGUI::OpenGLDataManager::getInstance().getDataPath(_filename);

		int bpp = 0, w, h;
		stbi_uc* image = stbi_load(fullname.c_str(), &w, &h, &bpp, 0);

		size_t size = w*h*bpp;
		unsigned char* ret = new unsigned char[size];
		memcpy(ret, image, size);

		_width = w;
		_height = h;
		switch (bpp) {
		case 1: _format = MyGUI::PixelFormat::L8; break;
		case 2: _format = MyGUI::PixelFormat::L8A8; break;
		case 3: _format = MyGUI::PixelFormat::R8G8B8; break;
		case 4: _format = MyGUI::PixelFormat::R8G8B8A8; break;
		}

        if (bpp == 4 || bpp == 3)
        {
            char c;//rgb[a] -> bgr[a]
            for (unsigned int i = 0; i < w * h; i++)
            {
                c = ret[i * bpp];
                ret[i * bpp] = ret[i * bpp + 2];
                ret[i * bpp + 2] = c;
            }
        }

        stbi_image_free(image);

		return ret;
#if sdl_img
		void* result = nullptr;
		SDL_Surface *image = nullptr;
		SDL_Surface *cvtImage = nullptr;		// converted surface with RGBA/RGB pixel format
		image = IMG_Load(fullname.c_str());
		if (image != nullptr) {
			_width = image->w;
			_height = image->h;

			int bpp = image->format->BytesPerPixel;
			if (bpp < 3)
			{
				result = convertPixelData(image, _format);
			}
			else
			{
				Uint32 pixelFmt = bpp == 3 ? SDL_PIXELFORMAT_BGR24 : SDL_PIXELFORMAT_ARGB8888;
				cvtImage = SDL_ConvertSurfaceFormat(image, pixelFmt, 0);
				result = convertPixelData(cvtImage, _format);
				SDL_FreeSurface(cvtImage);
			}
			SDL_FreeSurface(image);
		}
		MYGUI_ASSERT(result != nullptr, "Failed to load image.");
		return result;
#endif
	}

	void BaseManager::saveImage(int _width, int _height, MyGUI::PixelFormat _format, void* _texture, const std::string& _filename)
	{

	}

	void BaseManager::quit()
	{
		mExit = true;
	}

	const std::string& BaseManager::getRootMedia()
	{
		return mRootMedia;
	}

	void BaseManager::setResourceFilename(const std::string& _flename)
	{
		mResourceFileName = _flename;
	}

} // namespace base
