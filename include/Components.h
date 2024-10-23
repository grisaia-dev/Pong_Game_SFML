#pragma once

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Vector2.hpp>

class CCirShape {
public:
	sf::CircleShape circle;
	CCirShape(float radius = 0, int points = 0, const sf::Color& fill = sf::Color::White, const sf::Color& outline = sf::Color::Transparent, float thickness = 0)
		: circle(radius, points) {
		circle.setFillColor(fill);
		circle.setOutlineColor(outline);
		circle.setOutlineThickness(thickness);
		circle.setOrigin(radius, radius);
	}
};

class CRecShape {
public:
	sf::RectangleShape rectangle;
	CRecShape(const sf::Vector2f& size = sf::Vector2f(0,0), const sf::Color& fill = sf::Color::White, const sf::Color& outline = sf::Color::Transparent, float thickness = 0)
		: rectangle(size) {
		rectangle.setFillColor(fill);
		rectangle.setOutlineColor(outline);
		rectangle.setOutlineThickness(thickness);
		rectangle.setOrigin(size.x / 2.f, size.y / 2.f);
	}
};

class CTransform {
public:
	sf::Vector2f position;
	sf::Vector2f velocity;

	CTransform(const sf::Vector2f& p, const sf::Vector2f& v) : position(p), velocity(v) {}
};

class CInput {
public:
	bool up, left, right, down;
	CInput() : up(false), left(false), right(false), down(false) {}
};