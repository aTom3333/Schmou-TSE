#include "Collision.h"
#include <cmath>
#include <iostream>


bool collision(const sf::Shape& s1, const sf::Shape& s2);

bool collision(const sf::CircleShape& c1, const sf::CircleShape& c2)
{
	// TODO Prendre en compte les transformations

	auto c1c = c1.getPosition() - c1.getOrigin() + sf::Vector2f{c1.getRadius(), c1.getRadius()};
	auto c2c = c2.getPosition() - c2.getOrigin() + sf::Vector2f{c2.getRadius(), c2.getRadius()};
	auto diff = c1c - c2c;
	return diff.x*diff.x + diff.y*diff.y < (c1.getRadius()+c2.getRadius()) * (c1.getRadius()+c2.getRadius());
}

bool collision(const sf::CircleShape& c, const sf::RectangleShape& r);
bool collision(const sf::RectangleShape& r, const sf::CircleShape& c);

bool collision(const sf::CircleShape& c, const sf::ConvexShape& co)
{
	// TODO Découper cette fonction, c'est trop dégueulasse

	// Point C
	auto C = c.getPosition() - c.getOrigin() + sf::Vector2f{c.getRadius(), c.getRadius()};
	// Rayon du cercle
	double R = c.getRadius();

	size_t N = co.getPointCount();

	bool direct = true;
	if(N > 2)
	{
		double theta = co.getRotation() / 180 * acos(-1);
		auto zA = co.getPoint(0) - co.getOrigin();
		zA.x *= co.getScale().x;
		zA.y *= co.getScale().y;
		sf::Vector2f transformA(zA.x*cos(theta) - zA.y*sin(theta), zA.x*sin(theta) + zA.y*cos(theta));
		auto A = co.getPosition() + transformA;
		auto zB = co.getPoint(1) - co.getOrigin();
		zB.x *= co.getScale().x;
		zB.y *= co.getScale().y;
		sf::Vector2f transformB(zB.x*cos(theta) - zB.y*sin(theta), zB.x*sin(theta) + zB.y*cos(theta));
		auto B = co.getPosition() + transformB;
		auto zC = co.getPoint(2) - co.getOrigin();
		zC.x *= co.getScale().x;
		zC.y *= co.getScale().y;
		sf::Vector2f transformC(zC.x*cos(theta) - zC.y*sin(theta), zC.x*sin(theta) + zC.y*cos(theta));
		auto C = co.getPosition() + transformC;
		auto AB = B - A;
		auto AC = C - A;
		// Norme du produit vectoriel de AB par AC (pas vraiment en fait, ça peut être négatif)
		double AB_v_AC_n = AB.x*AC.y - AB.y*AC.x;
		direct = AB_v_AC_n > 0;
	}

	bool dedans = true;

	for(int i = 0; i < N; ++i)
	{
		double theta = co.getRotation() / 180 * acos(-1);

		auto zA = co.getPoint(i) - co.getOrigin();
		zA.x *= co.getScale().x;
		zA.y *= co.getScale().y;
		sf::Vector2f transformA(zA.x*cos(theta) - zA.y*sin(theta), zA.x*sin(theta) + zA.y*cos(theta));
		// Point A
		auto A = co.getPosition() + transformA;

		auto zB = co.getPoint((i+1) % N) - co.getOrigin();
		zB.x *= co.getScale().x;
		zB.y *= co.getScale().y;
		sf::Vector2f transformB(zB.x*cos(theta) - zB.y*sin(theta), zB.x*sin(theta) + zB.y*cos(theta));
		// Point B
		auto B = co.getPosition() + transformB;
		// Vecteur AB
		auto AB = B - A;
		// Norme de AB au carré
		double AB_n_c = AB.x*AB.x + AB.y*AB.y;
		// Vecteur AC
		auto AC = C - A;
		// Norme de AC au carré
		double AC_n_c = AC.x*AC.x + AC.y*AC.y;
		// Norme du produit vectoriel de AB par AC (pas vraiment en fait, ça peut être négatif)
		double AB_v_AC_n = AB.x*AC.y - AB.y*AC.x;
		// Norme du vecteur IC au carré
		double IC_n_c = AB_v_AC_n*AB_v_AC_n / (AB.x*AB.x + AB.y*AB.y);
		// Norme de AI au carré
		double AI_n_c = AC_n_c - IC_n_c;
		// Produit scalaire de AB et AC
		double AB_scal_AC = AB.x*AC.x + AB.y*AC.y;

		dedans = dedans && AB_v_AC_n > 0;

		// Si collision entre le cercle et le segment
		if((AB_scal_AC < 0 && AC_n_c < R*R)
			|| (AB_scal_AC > 0 && (
				(AI_n_c <= AB_n_c && IC_n_c < R*R)
				|| (IC_n_c > AB_n_c && AC_n_c < R*R)
			))
		)
			return true;
	}
	return dedans;
}

bool collision(const sf::ConvexShape& co, const sf::CircleShape& c)
{
	return collision(c, co);
}

bool collision(const sf::RectangleShape& r1, const sf::RectangleShape& r2);
bool collision(const sf::RectangleShape& r, const sf::ConvexShape& co);
bool collision(const sf::ConvexShape& co, const sf::RectangleShape& r);
bool collision(const sf::ConvexShape& co1, const sf::ConvexShape& co2);