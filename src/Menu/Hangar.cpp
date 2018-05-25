#include "Hangar.h"
#include "../Vaisseau/_vaisseaux.h"

Hangar::Hangar(sf::RenderWindow & window) : Ecran(window)
{
	fond_.setTexture(*chargeur_.getTexture("hangar.fond"));
	selection_.setTexture(*chargeur_.getTexture("hangar.selection"));
	
	description_.setSize({ 140, 20 });
	description_.setFillColor({ 255, 255, 255, 25 });

	nom_.setFont(polices_["hemi"]);
	nom_.setFillColor({ 255, 255, 255 });
	nom_.setCharacterSize(68);
	nom_.setPosition(75, 40);

	titreDescription_.setFont(polices_["hemi"]);
	titreDescription_.setFillColor({ 255, 255, 255 });
	titreDescription_.setCharacterSize(13);

	for (size_t i = 0; i < NB_STATS; i++)
	{
		stats_[i].setFont(polices_["hemi"]);
		stats_[i].setFillColor({ 255, 255, 255 });
		stats_[i].setCharacterSize(20);
		stats_[i].setPosition(70, 230 + i*62);

		barres_[i].setFillColor({ 255, 255, 255, 100});
		barres_[i].setPosition(55, 243 + i * 62);
	}

	positionModeleX_ = milieuX;
	positionModeleY_ = milieuY;
}

ecran_t Hangar::executer(std::vector<std::unique_ptr<Ecran>>& vectEtats, sf::Texture & derniereFenetre)
{
	while (window_.isOpen())
	{
		sf::Event event;
		while (window_.pollEvent(event))
		{
			auto retour = gestionEvent(event);
			if(retour) {
				derniereFenetre.update(window_);
				if(retour == PARTIE)
					fade(window_, derniereFenetre);
				return *retour;
			}
		}

		move();

		window_.clear();

		window_.draw(fond_);

		nom_.setString(vaisseau_->getNom());
		window_.draw(nom_);

		drawStats();
		drawOverview();

		window_.display();
	}

	return PARTIE;
}

std::unique_ptr<Ecran> Hangar::factory()
{
	return std::unique_ptr<Ecran>(std::make_unique<Hangar>(window_));
}

void Hangar::drawStats()
{
	std::string temp[NB_STATS];
	temp[0] = std::to_string(static_cast<int>(vaisseau_->getPvMax())) + "(+" + std::to_string(static_cast<int>(vaisseau_->getPvRegen())) + "/sec)";
	temp[1] = std::to_string(static_cast<int>(vaisseau_->getArmureMax())) + "(+" + std::to_string(static_cast<int>(vaisseau_->getArmureRegen())) + "/sec)";
	temp[2] = std::to_string(static_cast<int>(vaisseau_->getBouclierMax())) + "(+" + std::to_string(static_cast<int>(vaisseau_->getBouclierRegen())) + "/sec)";
	temp[3] = std::to_string(static_cast<int>(vaisseau_->getatqM()));
	temp[4] = std::to_string(static_cast<int>(vaisseau_->getVitMax()));

	float ratio[NB_STATS];
	ratio[0] = vaisseau_->getPvMax() > MAX_PV ? 1.f : vaisseau_->getPvMax() / MAX_PV;
	ratio[1] = vaisseau_->getArmureMax() > MAX_ARMURE ? 1.f : vaisseau_->getArmureMax() / MAX_ARMURE;
	ratio[2] = vaisseau_->getBouclierMax() > MAX_BOUCLIER ? 1.f : vaisseau_->getBouclierMax() / MAX_BOUCLIER;
	ratio[3] = vaisseau_->getatqM() > MAX_ATK ? 1.f : vaisseau_->getatqM() / MAX_ATK;
	ratio[4] = vaisseau_->getVitMax() > MAX_VITESSE ? 1.f : vaisseau_->getVitMax() / MAX_VITESSE;

	for (size_t i = 0; i < NB_STATS; i++)
	{
		stats_[i].setString(temp[i]);
		window_.draw(stats_[i]);

		barres_[i].setSize({ ratio[i] * BARRE_STATS_W, BARRE_STATS_H });
		window_.draw(barres_[i]);
	}
}

void Hangar::drawOverview()
{
	vaisseau_->setModelePosition(positionModeleX_, positionModeleY_);
	window_.draw(vaisseau_->getModele());

	if (posSelection_.x != 0 && posSelection_.y != 0)
	{

		if (positionModeleX_ > milieuX)
		{
			sf::Vertex line[] =
			{
				sf::Vertex(sf::Vector2f(posSelection_.x + 40, posSelection_.y + 40)),
				sf::Vertex(sf::Vector2f(600, 300)),
				sf::Vertex(sf::Vector2f(520, 300))
			};

			window_.draw(line, 3, sf::LineStrip);

			description_.setPosition(520 - 140, 300 - description_.getGlobalBounds().height/3.f);
			titreDescription_.setPosition(520 - 140 + 2, 300 - description_.getGlobalBounds().height / 3.f + 2);
		}
		else
		{
			sf::Vertex line[] =
			{
				sf::Vertex(sf::Vector2f(posSelection_.x + 40, posSelection_.y + 40)),
				sf::Vertex(sf::Vector2f(700, 300)),
				sf::Vertex(sf::Vector2f(800, 300))
			};

			window_.draw(line, 3, sf::LineStrip);

			description_.setPosition(800, 300 - description_.getGlobalBounds().height / 3.f);
			titreDescription_.setPosition(800 + 2, 300 - description_.getGlobalBounds().height / 3.f + 2);
		}
		
		window_.draw(description_);
		window_.draw(titreDescription_);
		selection_.setPosition(posSelection_.x, posSelection_.y);
		window_.draw(selection_);
	}

	for (auto mod : vaisseau_->getModules())
	{
		mod.setPositionModules(positionModeleX_, positionModeleY_);
		window_.draw(mod.getSprite());
	}
}

void Hangar::move()
{
	if (animation_)
	{
		sf::Time t = horloge_.getElapsedTime();
		if (t.asSeconds() < TEMPS_ANIMATION)
		{
		    const float D = destinationX_ - departX_;
			float delta = positionModeleX_;
			positionModeleX_ = - D / (TEMPS_ANIMATION*TEMPS_ANIMATION) * t.asSeconds() *  t.asSeconds() + 2 * D / TEMPS_ANIMATION * t.asSeconds() + departX_;
			delta -= positionModeleX_;
			posSelection_.x -= delta;
		}
		else
			animation_ = false;
	}
	
}

optional<ecran_t> Hangar::gestionEvent(const sf::Event& event)
{
	auto retour = Ecran::gestionEvent(event);
	if(retour)
		return retour;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		detruit_ = false;
		return make_optional(PARTIE);
	}
	else if (event.type == sf::Event::MouseButtonPressed && !animation_)
	{
		horloge_.restart();

		departX_ = positionModeleX_;
		destinationX_ = milieuX;

		posSelection_ = { 0, 0 };
		for (auto mod : vaisseau_->getModules())
		{
		    const sf::Vector2i localPosition = sf::Mouse::getPosition(window_);
			mod.checkSelection(window_.mapPixelToCoords(localPosition), posSelection_, positionModeleX_, positionModeleY_);

			if (posSelection_.x != 0 && posSelection_.y != 0)
			{
				titreDescription_.setString(mod.getNom());

				switch (mod.checkPosition(vaisseau_->getModele().getGlobalBounds().width))
				{
					case -1:
						destinationX_ = droiteX;
						break;
					case 1:
						destinationX_ = gaucheX;
						break;
					default:
						destinationX_ = milieuX;
						break;
				}
				break;
			}
		}

		if(departX_ != destinationX_)
			animation_ = true;
	}
	
	return nullopt;
}
