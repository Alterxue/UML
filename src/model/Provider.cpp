/*************************************************************************
                           Provider  -  description
                             -------------------
    début                : 05/05/2026
    copyright            : (C) 2026 par aeliasmene
    e-mail               : alex.eliasmenet@gmail.com
*************************************************************************/

//---------- Réalisation de la classe <Provider> (fichier Provider.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
#include <iostream>
#include <string>
#include <list>
using namespace std;

//------------------------------------------------------ Include personnel
#include "Provider.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques

void Provider::addCleaners(AirCleaner* cleaner) 
{
    this->myCleaners.push_back(*cleaner);
}

const vector<AirCleaner*>& Provider::getMyCleaners() const 
{
    return this->myCleaners;
}

//------------------------------------------------- Surcharge d'opérateurs
Provider & Provider::operator = (const Provider & unProvider)
{
} //----- Fin de operator =


//-------------------------------------------- Constructeurs - destructeur
Provider::Provider(string userID, Role role) : User(userID,role){}

Provider::~Provider ()
{
#ifdef MAP
    cout << "Appel au destructeur de <Provider>" << endl;
#endif
} //----- Fin de ~Provider


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées