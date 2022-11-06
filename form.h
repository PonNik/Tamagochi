#pragma once
#include "Header.h"

using namespace sf;

namespace form 
{
	class GameObject 
	{
	protected:
		float x = 0;
		float y = 0;
	public:
		virtual void draw(sf::RenderWindow& window) = 0;

		void setPosition(float _x = 0, float _y = 0);
	};

	class Label : public GameObject
	{
	public: 
		std::wstring text;

		Text TXT;

		Font None;
	public:
		Label(float _x = 0, float _y = 0, std::wstring _text = L"TExt");

		Text displayText();

	};

	class Button : public Label 
	{
	protected:
		float width;
		float height;
		RectangleShape BOX;
	public:
		Button(float _x = 0, float _y = 0, float _width = 150, float _height = 30, std::wstring _text = L"button");

		bool select(Vector2i _mouse);

		RectangleShape dysplayButton();

		void draw(sf::RenderWindow& window);

	};

	class ImageButton : public GameObject
	{
	protected:
		float width;
		float height;
		RectangleShape BOX;

		Image image;
		Texture texture;
		Sprite sprite;
	public:
		ImageButton(float scale = 1, float _x = 0, float _y = 0, float _width = 150, float _height = 30, std::string _imagePath = "img/button.png");

		bool select(Vector2i _mouse);

		Sprite dysplayImage();

		RectangleShape dysplayButton();

		void draw(sf::RenderWindow& window);
	};

	class PictureBox : public GameObject
	{
	protected:
		float width;
		float height;
		RectangleShape BOX;
		float scale;

		Image image;
		Texture texture;
		Sprite sprite;
	public:
		PictureBox(bool delBackImg = 0, float _scale = 1, float _x = 0, float _y = 0, float _width = 150, float _height = 30, std::string _imagePath = "img/button.png");
		sf::Sprite getSprite();

		void setTextureRect(float x, float y, float w, float h);

		void draw(sf::RenderWindow& window);
	};

	class CircleProgresBar : public GameObject
	{
	public:
		sf::RectangleShape rs;
		sf::CircleShape cs;

		Image image;
		Texture texture;
		Sprite sprite;
	public:
		float Radius;
		float Percent;

		CircleProgresBar(float _x = 0, float _y = 0, float scale = 1, float radius = 50, float percent = 50);

		void updatePercent(float percent);

		void draw(sf::RenderWindow& window);

	};
}

