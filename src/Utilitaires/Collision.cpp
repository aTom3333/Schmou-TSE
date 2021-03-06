#include "Collision.h"
#include <cmath>


const double PI = acos(-1);

sf::Vector2f centre_transforme(const sf::CircleShape& c)
{
    const double theta = c.getRotation() / 180 * PI;
    auto z = sf::Vector2f{c.getRadius(), c.getRadius()} - c.getOrigin();
    z.x *= c.getScale().x;
    z.y *= c.getScale().y;
    const sf::Vector2f transform(z.x*cos(theta) - z.y*sin(theta), z.x*sin(theta) + z.y*cos(theta));

    return c.getPosition() + transform;
}

sf::Vector2f point_transforme(const sf::Shape& s, size_t index)
{
    const double theta = s.getRotation() / 180 * PI;
    auto z = s.getPoint(index) - s.getOrigin();
    z.x *= s.getScale().x;
    z.y *= s.getScale().y;
    const sf::Vector2f transform(z.x*cos(theta) - z.y*sin(theta), z.x*sin(theta) + z.y*cos(theta));

    return s.getPosition() + transform;
}

bool is_point_in(const sf::Vector2f& C, const sf::Shape& s)
{
    const size_t N = s.getPointCount();

    bool direct = true;
    if(N > 2)
    {
        const auto A = point_transforme(s, 0);
        const auto B = point_transforme(s, 1);
        const auto C = point_transforme(s, 2);
        const auto AB = B - A;
        const auto AC = C - A;
        // Norme du produit vectoriel de AB par AC (pas vraiment en fait, ça peut être négatif)
        const double AB_v_AC_n = AB.x*AC.y - AB.y*AC.x;
        direct = AB_v_AC_n > 0;
    }

    for(size_t i = 0; i < N; ++i)
    {
        // Point A
        const auto A = point_transforme(s, i);
        // Point B
        const auto B = point_transforme(s, (i + 1) % N);
        // Vecteur AB
        const auto AB = B - A;
        // Vecteur AC
        const auto AC = C - A;
        // Norme du produit vectoriel de AB par AC (pas vraiment en fait, ça peut être négatif)
        const double AB_v_AC_n = AB.x * AC.y - AB.y * AC.x;

        if((AB_v_AC_n <= 0) == direct)
            return false;
    }

    return true;
}

bool collision(const sf::Shape& s1, const sf::Shape& s2)
{
    const bool is_circle1 = (dynamic_cast<const sf::CircleShape*>(&s1) != nullptr && s1.getScale().x == s1.getScale().y);
    const bool is_circle2 = (dynamic_cast<const sf::CircleShape*>(&s2) != nullptr && s2.getScale().x == s2.getScale().y);

    if(is_circle1 && is_circle2)
        return collision_impl(dynamic_cast<const sf::CircleShape&>(s1), dynamic_cast<const sf::CircleShape&>(s2));
    if(is_circle1)
        return collision_impl(dynamic_cast<const sf::CircleShape&>(s1), s2);
    if(is_circle2)
        return collision_impl(s1, dynamic_cast<const sf::CircleShape&>(s2));
    return collision_impl(s1, s2);
}

bool collision_impl(const sf::CircleShape& c1, const sf::CircleShape& c2)
{
    const auto c1c = centre_transforme(c1);
    const auto c2c = centre_transforme(c2);
    const auto diff = c1c - c2c;
    // On suppose que pour les cercle, scale.x et scale.y sont égaux
    const float dist = c1.getRadius() * c1.getScale().x + c2.getRadius() * c2.getScale().x;
    return diff.x*diff.x + diff.y*diff.y < dist*dist;
}

bool collision_impl(const sf::CircleShape& c, const sf::Shape& co)
{
    // Point C
    const auto C = centre_transforme(c);
    // Rayon du cercle
    const double R = c.getRadius() * c.getScale().x;

    const size_t N = co.getPointCount();

    bool direct = true;
    if(N > 2)
    {
        const auto A = point_transforme(co, 0);
        const auto B = point_transforme(co, 1);
        const auto C = point_transforme(co, 2);
        const auto AB = B - A;
        const auto AC = C - A;
        // Norme du produit vectoriel de AB par AC (pas vraiment en fait, ça peut être négatif)
        const double AB_v_AC_n = AB.x*AC.y - AB.y*AC.x;
        direct = AB_v_AC_n > 0;
    }

    bool dedans = true;

    for(size_t i = 0; i < N; ++i)
    {
        // Point A
        const auto A = point_transforme(co, i);
        // Point B
        const auto B = point_transforme(co, (i+1) % N);
        // Vecteur AB
		const auto AB = B - A;
        // Norme de AB au carré
		const double AB_n_c = AB.x*AB.x + AB.y*AB.y;
        // Vecteur AC
		const auto AC = C - A;
        // Norme de AC au carré
		const double AC_n_c = AC.x*AC.x + AC.y*AC.y;
        // Norme du produit vectoriel de AB par AC (pas vraiment en fait, ça peut être négatif)
		const double AB_v_AC_n = AB.x*AC.y - AB.y*AC.x;
        // Norme du vecteur IC au carré
		const double IC_n_c = AB_v_AC_n*AB_v_AC_n / (AB.x*AB.x + AB.y*AB.y);
        // Norme de AI au carré
		const double AI_n_c = AC_n_c - IC_n_c;
        // Produit scalaire de AB et AC
		const double AB_scal_AC = AB.x*AC.x + AB.y*AC.y;

        dedans = dedans && ((AB_v_AC_n > 0) == direct);

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

bool collision_impl(const sf::Shape& co, const sf::CircleShape& c)
{
    return collision_impl(c, co);
}

bool collision_impl(const sf::Shape& s1, const sf::Shape& s2)
{
    for(size_t i = 0; i < s1.getPointCount(); ++i)
    {
        if(is_point_in(point_transforme(s1, i), s2))
            return true;
    }
    for(size_t i = 0; i < s2.getPointCount(); ++i)
    {
        if(is_point_in(point_transforme(s2, i), s1))
            return true;
    }

    return false;
}
