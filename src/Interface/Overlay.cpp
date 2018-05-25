#include "Overlay.h"

//TODO PG constantes magiques, lier à un écran pour chargement et window

void Overlay::init(vaisseau_ptr vaisseau)
{
	// Chargement des images
	font_.loadFromFile("../../rc/Font/whitrabt.ttf");
	overlayText_.loadFromFile("../../rc/UI/overlay.png");
	overlay_.setTexture(overlayText_);

	// Initialisation des barre de vie, d'armure et de bouclier
    for(size_t i = 0 ; i < 3 ; i++)
    {
        barre_[i].setSize({OVERLAY_BARRE_L, OVERLAY_BARRE_H});
        barre_[i].setPosition(20, 12 + (OVERLAY_BARRE_H + 4) * i);
        switch(i)
        {
            case 0 :
                {
                    barre_[i].setFillColor({255, 66, 66, 150});
                    break;
                }
            case 1 :
                {
                    barre_[i].setFillColor({244, 244, 66, 150});
                    break;
                }
            case 2 :
                {
                    barre_[i].setFillColor({66, 166, 244, 150});
                    break;
                }
            default :
                throw std::runtime_error("");
        }
    }

	// Compteur qui permet de connaitre le nombre de capacités a afficher
	size_t n = 0, m = 0;

	// Initialisation des icones
	for(size_t i = 0; i < vaisseau->getskills().size(); i++)
	{
		if (vaisseau->getskills()[i] != nullptr)
		{
			if(vaisseau->getskills()[i]->getAffiche())
				vaisseau->getskills()[i]->initIcon(n);

			if (vaisseau->getskills()[i]->getTir())
				vaisseau->getskills()[i]->initIcon(m);

			n += vaisseau->getskills()[i]->getAffiche() ? 1 : 0;
			m += vaisseau->getskills()[i]->getTir() ? 1 : 0;
		}
	}

	// Initialisation du texte affichant les cooldowns
	statuts_ = new sf::Text[n];
	for(size_t i = 0; i < n; i++)
	{
		statuts_[i].setFont(font_);
		statuts_[i].setCharacterSize(20);
		statuts_[i].setFillColor({ 0, 0, 0, 102 });
		statuts_[i].setPosition(935, 185 + 135 * i);
	}
}

Overlay::~Overlay()
{
	delete[] statuts_;
}

void Overlay::draw(sf::RenderWindow & window, vaisseau_ptr vaisseau, bool bDraw) const
{
	// Affichage de l'overlay
	if (bDraw)
	{
		for(size_t i = 0; i < 3; i++) //barres de stats
			window.draw(barre_[i]);

		window.draw(overlay_); //overlay fixe

		size_t n = 0, m = 0;
		for(size_t i = 0; i < vaisseau->getskills().size(); i++)
		{
			if (vaisseau->getskills()[i] != nullptr && vaisseau->getskills()[i]->getAffiche())
			{
				window.draw(vaisseau->getskills()[i]->getIcon());
				window.draw(statuts_[n]);
				n++;
			}

			if (vaisseau->getskills()[i] != nullptr && vaisseau->getskills()[i]->getTir())
			{
				window.draw(vaisseau->getskills()[i]->getIcon());
				vaisseau->getskills()[i]->afficherNom();
				m++;
			}

			if(vaisseau->getskills()[i] != nullptr)
				window.draw(vaisseau->getskills()[i]->getMasque());
		}
			
	}
}

void Overlay::gestion(vaisseau_ptr vaisseau)
{

	// Gestion de barres de vie, d'armure et de bouclier
	barre_[0].setSize({ OVERLAY_BARRE_L*vaisseau->getPv() / vaisseau->getPvMax(), OVERLAY_BARRE_H });
	barre_[1].setSize({ OVERLAY_BARRE_L*vaisseau->getArmure() / vaisseau->getArmureMax(), OVERLAY_BARRE_H });
	barre_[2].setSize({ OVERLAY_BARRE_L*vaisseau->getBouclier() / vaisseau->getBouclierMax(), OVERLAY_BARRE_H });


	size_t n = 0;
	for(size_t i = 0; i < vaisseau->getskills().size(); i++)
	{
		if (vaisseau->getskills()[i] != nullptr)
		{
			vaisseau->getskills()[i]->gestionIcon();

			if (vaisseau->getskills()[i]->getAffiche())
			{
				// TODO TF Vérifier que ça marche avec des sf::Time
				sf::Time cooldown = (vaisseau->getskills()[i]->getCooldown() - vaisseau->getskills()[i]->getTime());
			    const std::wstring str = cooldown.asMilliseconds() <= 0 ? L"Prét" : std::to_wstring(cooldown.asMilliseconds());
				statuts_[n].setString(str);

				statuts_[n].setPosition(1015 - statuts_[n].getLocalBounds().width, statuts_[n].getPosition().y);
				n++;
			}
		}

	}
		
}
