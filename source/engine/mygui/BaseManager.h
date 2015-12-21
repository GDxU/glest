/*!
	@file
	@author		Albert Semenov
	@date		08/2008
*/

#ifndef BASE_MANAGER_H_
#define BASE_MANAGER_H_

#include <MyGUI.h>
#include <MyGUI_OpenGLPlatform.h>

#include "SDL_InputManager.h"
#include "SDL_PointerManager.h"

namespace base
{

	class BaseManager :
		public input::InputManager,
		public input::PointerManager,
		public MyGUI::OpenGLImageLoader
	{
	public:
		BaseManager();
		virtual ~BaseManager();

		virtual void prepare();
        bool create(int _width, int _height, bool windowed);

        int getW() { return mWidth; }
        int getH() { return mHeight; }

        void destroy();
        void drawOneFrame();
		void quit();

		void setWindowCaption(const std::wstring& _text);
		void makeScreenShot() { }

		const std::string& getRootMedia();
		void setResourceFilename(const std::string& _flename);
		void addResourceLocation(const std::string& _name, bool _recursive = false);

		MyGUI::MapString getStatistic() { return MyGUI::MapString(); }

        static void swapBuffer();

	/*internal:*/
		void _windowResized(int w, int h);
		virtual void* loadImage(int& _width, int& _height, MyGUI::PixelFormat& _format, const std::string& _filename);
		virtual void saveImage(int _width, int _height, MyGUI::PixelFormat _format, void* _texture, const std::string& _filename);

	protected:
		virtual void createScene() { }
		virtual void destroyScene() { }

		virtual void setupResources();

		virtual bool injectMouseMove(int _absx, int _absy, int _absz);
        virtual bool injectMousePress(int _absx, int _absy, MyGUI::MouseButton _id);
        virtual bool injectMouseRelease(int _absx, int _absy, MyGUI::MouseButton _id);
        virtual bool injectKeyPress(MyGUI::KeyCode _key, MyGUI::Char _text);
        virtual bool injectKeyRelease(MyGUI::KeyCode _key);

		virtual void createGui();
		virtual void destroyGui();

		virtual void setWindowMaximized(bool _value);
		virtual bool getWindowMaximized();

		virtual void setWindowCoord(const MyGUI::IntCoord& _value);
		virtual MyGUI::IntCoord getWindowCoord();

	private:
		//void resizeRender(int _width, int _height);
		bool createRender(int _width, int _height, bool _windowed);
		void destroyRender();
		void* convertPixelData(SDL_Surface *_image, MyGUI::PixelFormat& _myGuiPixelFormat);
		void updateSDL_Keycode();

    protected:
		MyGUI::Gui* mGUI;
		MyGUI::OpenGLPlatform* mPlatform;

		bool mExit;
		SDL_Event mEvent;
		SDL_Window* mWindow;
		SDL_GLContext mContext;
		std::string mRootMedia;
		std::string mResourceFileName;
		bool	mWindowOn;
		SDL_Keycode	mKeyCode;
		bool mTextUpdated;

        int mWidth, mHeight;
        bool mFullScreen;
	};

} // namespace base

#endif // BASE_MANAGER_H_
