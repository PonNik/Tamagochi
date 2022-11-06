#include "form.h"

// GameObject
void form::GameObject::setPosition(float _x, float _y)
{
	x = _x;
	y = _y;
}

// Label
form::Label::Label(float _x, float _y, std::wstring _text)
{
	None.loadFromFile("ttf/FONT.ttf");

	x = _x;
	y = _y;
	text = _text;
	TXT.setFont(None);
	TXT.setCharacterSize(20);
	TXT.setFillColor(Color::White);
	TXT.setPosition(x, y);
}

Text form::Label::displayText()
{
	TXT.setString(text);
	return TXT;
}

// Button
form::Button::Button(float _x, float _y, float _width, float _height, std::wstring _text)
{
	None.loadFromFile("ttf/FONT.ttf");

	x = _x;
	y = _y;
	width = _width;
	height = _height;
	text = _text;

	TXT.setFont(None);
	TXT.setCharacterSize(20);
	TXT.setFillColor(Color::White);
	TXT.setOrigin(text.size() / 2.0f * 10, 0);
	TXT.setPosition(x + width / 2, y);

	BOX.setSize(Vector2f(width, height));
	BOX.setPosition(x, y);
	BOX.setFillColor(Color::Green);
	BOX.setOutlineThickness(2);
	BOX.setOutlineColor(Color(66, 66, 66));
}

bool form::Button::select(Vector2i _mouse)
{
	return ((_mouse.x > x && _mouse.x < x + width) && (_mouse.y > y && _mouse.y < y + height));
}

RectangleShape form::Button::dysplayButton()
{
	return BOX;
}

void form::Button::draw(sf::RenderWindow& window)
{
	window.draw(BOX);
	TXT.setString(text);
	window.draw(TXT);
}


// ImageButton
form::ImageButton::ImageButton(float scale, float _x, float _y, float _width, float _height, std::string _imagePath)
{
	image.loadFromFile(_imagePath);
	image.createMaskFromColor(image.getPixel(0, 0));

	texture.loadFromImage(image);
	sprite.setTexture(texture);
	sprite.setScale(scale, scale);

	x = _x;
	y = _y;
	width = texture.getSize().x * scale;
	height = texture.getSize().y * scale;

	BOX.setSize(Vector2f(texture.getSize().x * scale, texture.getSize().y * scale));
	BOX.setPosition(x, y);
	BOX.setFillColor(Color(33, 33, 33));
	BOX.setOutlineThickness(2);
	BOX.setOutlineColor(Color(66, 66, 66));
}

bool form::ImageButton::select(Vector2i _mouse)
{
	return ((_mouse.x > x && _mouse.x < x + width) && (_mouse.y > y && _mouse.y < y + height));
}

Sprite form::ImageButton::dysplayImage()
{
	return sprite;
}

RectangleShape form::ImageButton::dysplayButton()
{
	return BOX;
}

void form::ImageButton::draw(sf::RenderWindow& window)
{
	window.draw(BOX);
	window.draw(sprite);
}

// PictureBox

form::PictureBox::PictureBox(bool delBackImg, float _scale, float _x, float _y, float _width, float _height, std::string _imagePath)
{
	image.loadFromFile(_imagePath);
	if (delBackImg)
		image.createMaskFromColor(image.getPixel(0, 0));
	scale = _scale;

	texture.loadFromImage(image);
	sprite.setTexture(texture);
	sprite.setScale(scale, scale);

	x = _x;
	y = _y;
	width = texture.getSize().x * scale;
	height = texture.getSize().y * scale;

	BOX.setSize(Vector2f(width, height));
	BOX.setPosition(x, y);
	BOX.setFillColor(Color(33, 33, 33));
	BOX.setOutlineThickness(2);
	BOX.setOutlineColor(Color(66, 66, 66));
	sprite.setPosition(x, y);
}

sf::Sprite form::PictureBox::getSprite()
{
	return sprite;
}

void form::PictureBox::setTextureRect(float x, float y, float w, float h)
{
	sprite.setTextureRect(IntRect(x, y, w, h));
	width = w * scale;
	height = w * scale;
	BOX.setSize(Vector2f(width, height));
}

void form::PictureBox::draw(sf::RenderWindow& window)
{
	window.draw(BOX);
	window.draw(sprite);
}


// CircleProgresBar

form::CircleProgresBar::CircleProgresBar(float _x, float _y, float scale, float radius, float percent)
{
	image.loadFromFile("img/ProgresBar.png");
	image.createMaskFromColor(image.getPixel(0, 0));

	texture.loadFromImage(image);
	sprite.setTexture(texture);
	sprite.setScale(2 * scale, 2 * scale);

	if (percent > 100)
		Percent = 100;
	else
		Percent = percent;
	Radius = radius * scale;

	x = _x;
	y = _y;

	cs.setPosition(x, y);
	rs.setPosition(x, y);
	sprite.setPosition(x, y);

	cs.setRadius(Radius);

	rs.setSize(Vector2f(2 * Radius, 2 * Radius - Radius * 2 / 100 * Percent));

	rs.setFillColor(sf::Color::Black);
	if (Percent > 50)
	{
		cs.setFillColor(sf::Color::Green);
	}
	else if (Percent > 30 && Percent <= 50)
	{
		cs.setFillColor(sf::Color::Yellow);
	}
	else
	{
		cs.setFillColor(sf::Color::Red);
	}
}

void form::CircleProgresBar::updatePercent(float percent) {
	if (percent <= 100 && percent >= 0) {
		Percent = percent;
		rs.setSize(Vector2f(2 * Radius, 2 * Radius - Radius * 2 / 100 * Percent));
		if (Percent > 50)
		{
			cs.setFillColor(sf::Color::Green);
		}
		else if (Percent > 30 && Percent <= 50)
		{
			cs.setFillColor(sf::Color::Yellow);
		}
		else
		{
			cs.setFillColor(sf::Color::Red);
		}
	}
}

void form::CircleProgresBar::draw(sf::RenderWindow& window)
{
	window.draw(cs);
	window.draw(rs);
	window.draw(sprite);
}
