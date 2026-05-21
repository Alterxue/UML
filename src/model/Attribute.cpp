/*************************************************************************
                           Attribute  -  description
                             -------------------
    début                : 06/05/2026
    copyright            : (C) 2026 par tautret
    e-mail               : tom.autret@insa-lyon.fr
*************************************************************************/

//---------- Réalisation de la classe <Attribute> (fichier Attribute.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include <iostream>
#include <string>

//------------------------------------------------------ Include personnel
#include "Attribute.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
string Attribute::getAttributeID() const
{
    return attributeID;
} //----- Fin de getAttributeID

//------------------------------------------------- Surcharge d'opérateurs

//-------------------------------------------- Constructeurs - destructeur
Attribute::Attribute(const string a_attributeID, const string a_unit, const string a_description): attributeID(a_attributeID), 
unit(a_unit), description(a_description)
{
    #ifdef MAP
        cout << "Appel au constructeur de <Attribute>" << endl;
    #endif
} //----- Fin de Attribute

Attribute::~Attribute()
{
    #ifdef MAP
        cout << "Appel au destructeur de <Attribute>" << endl;
    #endif
} //----- Fin de ~Attribute

//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées