/*!
	@file
	@author		Albert Semenov
	@date		09/2009
*/

#ifndef INPUT_MANAGER_H_
#define INPUT_MANAGER_H_

#include <MyGUI.h>
#include <SDL.h>

namespace input
{
	class InputManager
	{
	public:
		InputManager();
		virtual ~InputManager();

		void createInput();
		void destroyInput();
		void captureInput();
		void setInputViewSize(int _width, int _height);
		
		// following five methods are to be implemented in BaseManager class
        virtual bool injectMouseMove(int _absx, int _absy, int _absz) = 0;
        virtual bool injectMousePress(int _absx, int _absy, MyGUI::MouseButton _id) = 0;
        virtual bool injectMouseRelease(int _absx, int _absy, MyGUI::MouseButton _id) = 0;
        virtual bool injectKeyPress(MyGUI::KeyCode _key, MyGUI::Char _text) = 0;
        virtual bool injectKeyRelease(MyGUI::KeyCode _key) = 0;

		virtual void onFileDrop(const std::wstring& _filename) { }
		virtual bool onWinodwClose(size_t _handle) { return true; }

		void setMousePosition(int _x, int _y);
		void updateCursorPosition();

	protected:
		void frameEvent(float _time);
		void computeMouseMove();

		void onClipboardChanged(const std::string& _type, const std::string& _data);
		void onClipboardRequested(const std::string& _type, std::string& _data);

		virtual bool mouseMoved(const SDL_MouseMotionEvent &evt);
		virtual bool mousePressed(const SDL_MouseButtonEvent &evt);
		virtual bool mouseReleased(const SDL_MouseButtonEvent &evt);
		virtual bool keyPressed(SDL_Keycode key, const SDL_TextInputEvent* evt);
		virtual bool keyReleased(const SDL_KeyboardEvent &key);
		virtual bool mouseWheelMoved(const SDL_MouseWheelEvent &evt);

		void checkPosition();

		void buildVKeyMap();
		void buildMouseButtonMap();
	private:
		int mMouseX;
		int mMouseY;
		int mMouseZ;
		bool mMouseMove;
		int mWidth;
		int mHeight;
		std::map<int, MyGUI::KeyCode> mSDLVKeyMap;
		std::map<int, MyGUI::MouseButton> mSDLMouseMap;
	};

} // namespace input

#endif // INPUT_MANAGER_H_
