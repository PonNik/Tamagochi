#include "game.h"

// scene

game::scene::scene(bool vision)
{
	Vision = vision;
}

void game::scene::setEnable(bool vision)
{
	Vision = vision;
}


void game::scene::addObj(form::GameObject* obj)
{
	arrObj.push_back(obj);
}
void game::scene::draw(sf::RenderWindow& window)
{
	if (Vision) {
		for (int numObj = 0; numObj < arrObj.size(); numObj++)
		{
			arrObj[numObj]->draw(window);
		}
	}
}

// Person

game::Person::Person(std::string _imagePath, float _x, float _y, float _width, float _height, bool delBackImg, float _scale)
{
	image.loadFromFile(_imagePath);
	if (delBackImg)
		image.createMaskFromColor(image.getPixel(0, 0));
	scale = _scale;

	texture.loadFromImage(image);
	person.setTexture(texture);
	person.setScale(scale, scale);

	x = _x;
	y = _y;
	width = texture.getSize().x * scale;
	height = texture.getSize().y * scale;

	BOX.setSize(Vector2f(width, height));
	BOX.setPosition(x, y);
	BOX.setFillColor(Color(33, 33, 33));
	BOX.setOutlineThickness(2);
	BOX.setOutlineColor(Color(66, 66, 66));
	person.setPosition(x, y);
}

sf::Sprite* game::Person::getSprite()
{
	return &person;
}

void game::Person::setTextureRect(float x, float y, float w, float h)
{
	person.setTextureRect(IntRect(x, y, w, h));
	width = w * scale;
	height = w * scale;
	BOX.setSize(Vector2f(width, height));
}

void game::Person::draw(sf::RenderWindow& window)
{
	window.draw(BOX);
	window.draw(person);
}

void game::Person::ffun()
{
	if (ani_happines)
	{
		if (CurrentFrame > 6)
		{
			CurrentFrame -= 6;
			ani_happines = false;
			getSprite()->setTextureRect(sf::IntRect(0, 0, 64, 64));
		}
		else
		{
			CurrentFrame += 0.005f;
			getSprite()->setTextureRect(sf::IntRect(64 * int(CurrentFrame), 2 * 64, 64, 64));
		}
	}
}

void game::Person::feat()
{
	if (ani_eat)
	{
		if (CurrentFrame > 2)
		{
			ani_eat = false;
			getSprite()->setTextureRect(sf::IntRect(0, 0, 64, 64));
			CurrentFrame -= 2;
		}
		else
		{
			CurrentFrame += 0.005f;
			getSprite()->setTextureRect(sf::IntRect(64 * (4 + int(CurrentFrame)), 3 * 64, 64, 64));
		}
	}
}

void game::Person::fsleep(form::CircleProgresBar* indicator)
{
	if (ani_sleep)
	{
		if (CurrentFrame < 3)
		{
			CurrentFrame += 0.005f;
			getSprite()->setTextureRect(sf::IntRect(64 * int(CurrentFrame), 3 * 64, 64, 64));
		}
		else {
			p_fatigue += 0.005f;
			indicator->updatePercent(p_fatigue);
		}
	}
}

void game::Person::flife(form::CircleProgresBar* eat, form::CircleProgresBar* fun, form::CircleProgresBar* sleep)
{
	if (!ani_eat)
		p_hungry -= 0.0005f;
	if (!ani_happines)
		p_happines -= 0.0005f;
	if (!ani_sleep)
		p_fatigue -= 0.0004f;

	eat->updatePercent(p_hungry);
	fun->updatePercent(p_happines);
	sleep->updatePercent(p_fatigue);

	if (p_fatigue < 0)
		ani_sleep = true;
}