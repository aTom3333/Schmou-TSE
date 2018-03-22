#ifndef SCHMOUTSE_DEF_TYPE_H
#define SCHMOUTSE_DEF_TYPE_H

#include <memory>
#include <vector>

/**
 * @brief Regroupement d'alias de type
 * 
 * On définit ici des alias de types qui seront utilisés dans les autres fichiers
 * Comme ça si un jour on veut modifier le type exact pour un certain rôle, c'est aussi
 * simple que de modifier le type auquel l'alias refère
 */

class Vaisseau; // Déclaration pour éviter d'avoir à inclure un header
using vaisseau_ptr = std::shared_ptr<Vaisseau>;
using vaisseau_container = std::vector<vaisseau_ptr>;

class Projectile;
using proj_ptr = std::shared_ptr<Projectile>;
using proj_container = std::vector<proj_ptr>;

class Entite;
using entite_ptr = std::shared_ptr<Entite>;

#endif //SCHMOUTSE_DEF_TYPE_H
