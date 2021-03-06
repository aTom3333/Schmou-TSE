#include "utilities.h"
#include <cctype>
#include <random>


int random()
{
	return random(std::numeric_limits<long>::max());
}

int random(int max)
{
	return random(0, max);
}

int random(int min, int max)
{
    #if defined(WIN32) && (defined(__GNUC__) || defined(__GNUG__)) && !defined(_GLIBCXX_USE_DEV_RANDOM)
    static std::mt19937_64 random_engine(std::time(nullptr));
    #else
    static std::default_random_engine random_engine(std::random_device{}());
    #endif
    std::uniform_int_distribution<int> distr(min, max);
    return distr(random_engine);
}

void adapt_viewport(sf::RenderWindow& window)
{
	auto view = window.getView();
	const auto size = window.getSize();

	const float ratio = static_cast<float>(size.x) / size.y;
	const float ratio_normal = ECRAN_L / ECRAN_H;

	if (ratio > ratio_normal)
	{
		const float proportion = ratio_normal / ratio;
		view.setViewport({ (1 - proportion) / 2, 0, proportion, 1 });
	}
	else
	{
		const float proportion = ratio / ratio_normal;
		view.setViewport({ 0, (1 - proportion) / 2, 1, proportion });
	}

	window.setView(view);
}

std::string trim(std::string str)
{
	str.erase(str.begin(), std::find_if(str.begin(), str.end(), [](int ch) {
		return !std::isspace(ch);
	}));
	str.erase(std::find_if(str.rbegin(), str.rend(), [](int ch) {
		return !std::isspace(ch);
	}).base(), str.end());

	return str;
}

std::pair<std::string, std::string> tokenize(const std::string& str, char sep)
{
	const auto pos = str.find(sep);

	if (pos == std::string::npos)
		return { str, "" };

	auto str1 = str.substr(0, pos);
	auto str2 = str.substr(pos + 1);

	return { str1, str2 };
}

double rayon_englobeur(const std::vector<std::unique_ptr<sf::Shape>> & forme, sf::Vector2f origine) {
    double dist_max = 0; //distance du point le plus éloigné de l'origine parmi tous
    for (auto const& shape_ptr : forme) {
        const size_t N = shape_ptr->getPointCount(); //nombre de points de la shape actuelle
        for (size_t i = 0; i < N; i++) {
            const sf::Vector2f point = shape_ptr->getPoint(i);
            if (hypot(point.x - origine.x, point.y - origine.y) > dist_max)
                dist_max = hypot(point.x - origine.x, point.y - origine.y);
        }
    }
	return dist_max;
}

void englobeur_circulaire(Entite& entite)
{
	const float R = rayon_englobeur(entite.getForme(), entite.getOrigin());
	sf::CircleShape cercleEnglobant(R);
	cercleEnglobant.setOrigin(R, R);
	cercleEnglobant.setPosition(entite.getPosition());
	entite.setCercleEnglobant(cercleEnglobant);
}