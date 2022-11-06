#pragma once
#include "form.h"
#include <vector>

namespace game
{
	class scene 
	{
	private:
		std::vector<form::GameObject*> arrObj;
		bool Vision;
	public:
		scene(bool vision = true);

		void setEnable(bool vision);

		void addObj(form::GameObject* obj);
		void draw(sf::RenderWindow& window);
	};

	class Person : public form::GameObject
	{
	private:
	protected:
		float width;
		float height;
		RectangleShape BOX;
		float scale;

		Image image;
		Texture texture;
		Sprite person;
	public:
		float p_hungry = 20;
		float p_fatigue = 20;
		float p_happines = 20;
		bool ani_happines = false;
		bool ani_eat = false;
		bool ani_sleep = false;
		float CurrentFrame = 0;

		Person(std::string _imagePath = "img/button.png", float _x = 0, float _y = 0, float _width = 150, float _height = 30, bool delBackImg = 0, float _scale = 1);

		sf::Sprite* getSprite();

		void setTextureRect(float x, float y, float w, float h);

		void draw(sf::RenderWindow& window);

		void ffun();

		void feat();
		
		void fsleep(form::CircleProgresBar* indicator);

		void flife(form::CircleProgresBar* eat, form::CircleProgresBar* fun, form::CircleProgresBar* sleep);

	};
}