/*************************************************************************
                           Attribute  -  description
                             -------------------
    début                : 06/05/2026
    copyright            : (C) 2026 par tautret
    e-mail               : tom.autret@insa-lyon.fr
*************************************************************************/

//---------- Interface de la classe <Attribute> (fichier Attribute.h) ----------------
#if ! defined ( ATTRIBUTE_H )
#define ATTRIBUTE_H

//--------------------------------------------------- Interfaces utilisées
#include <string>

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <Attribute> : 
// Représenter le type d'une mesure avec son code, son unité,
// et sa description
//------------------------------------------------------------------------

class Attribute
{
//----------------------------------------------------------------- PUBLIC
public:
//----------------------------------------------------- Méthodes publiques

//------------------------------------------------- Surcharge d'opérateurs

//-------------------------------------------- Constructeurs - destructeur
    Attribute(const std::string a_attributeID, const std::string a_unit, const std::string a_description);

//------------------------------------------------------------------ PRIVE
protected:
//----------------------------------------------------- Attributs protégés
    std::string attributeID;
    std::string unit;
    std::string description;
};

#endif // ATTRIBUTE_H