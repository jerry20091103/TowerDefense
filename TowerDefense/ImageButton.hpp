#ifndef IMAGEBUTTON_HPP
#define IMAGEBUTTON_HPP
#include <allegro5/bitmap.h>
#include <functional>
#include <memory>
#include <string>

#include "IControl.hpp"
#include "Image.hpp"
#include "Label.hpp"

namespace Engine {
	/// <summary>
	/// A clickable button, changes image when mouse move.
	/// </summary>
	class ImageButton: public Image, public IControl {
	protected:
		// The smart pointer that points to bitmap for mouse-out display.
		std::shared_ptr<ALLEGRO_BITMAP> imgOut;
		// The smart pointer that points to bitmap for mouse-in display.
		std::shared_ptr<ALLEGRO_BITMAP> imgIn;
		// The callback function to call when button clicked.
		std::function<void()> OnClickCallback;
	public:
		// The Label text it is binded to
		Engine::Label* label;
		// Determines whether mouse is in the button.
		bool mouseIn = false;
		// Whether the button can be pressed.
		bool Enabled = true;
		/// <summary>
		/// Construct a image object.
		/// </summary>
		/// <param name="img">The mouse-out image path in 'resources/images/'</param>
		/// <param name="imgIn">The mouse-in image path in 'resources/images/'</param>
		/// <param name="x">X-coordinate.</param>
		/// <param name="y">Y-coordinate.</param>
		/// <param name="w">Width of the image, 0 indicates original size.</param>
		/// <param name="h">Height of the image, 0 indicates original size.</param>
		/// <param name="anchorX">The centerX of the object. (0, 0) means top-left, while (1, 0) means top-right.</param>
		/// <param name="anchorY">The centerY of the object. (0, 1) means bottom-left, while (1, 1) means bottom-right.</param>
		/// <param name="label">bind the button to a label.</param>
		explicit ImageButton(std::string img, std::string imgIn, float x, float y, float w = 0, float h = 0, float anchorX = 0, float anchorY = 0, Engine::Label* label = nullptr);
		/// <summary>
		/// Set the callback function when clicked.
		/// </summary>
		/// <param name="onClickCallback"></param>
		void SetOnClickCallback(std::function<void(void)> onClickCallback);
		/// <summary>
		/// Set the Label the button is binded to.
		/// </summary>
		/// <param name="label"></param>
		void SetLabelBinding(Engine::Label* label);
		/// <summary>
		/// Delegated from scene when mouse button down.
		/// </summary>
		/// <param name="button">The button pressed.</param>
		/// <param name="mx">Mouse x coordinate in window space.</param>
		/// <param name="my">Mouse y coordinate in window space.</param>
		void OnMouseDown(int button, int mx, int my) override;
		/// <summary>
		/// Delegated from scene when mouse move.
		/// </summary>
		/// <param name="mx">Mouse x coordinate in window space.</param>
		/// <param name="my">Mouse y coordinate in window space.</param>
		void OnMouseMove(int mx, int my) override;
	};
}
#endif // IMAGEBUTTON_HPP
