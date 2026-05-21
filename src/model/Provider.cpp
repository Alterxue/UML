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
using namespace std;
#include <iostream>
#include <string>
#include <list>


//------------------------------------------------------ Include personnel
#include "Provider.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
void Provider::addAirCleaner(AirCleaner* cleaner) 
{
    this->myCleaners.push_back(cleaner);
} //----- Fin de addAirCleaner

const vector<AirCleaner*>& Provider::getMyCleaners() const 
{
    return this->myCleaners;
} //----- Fin de getMyCleaners

//------------------------------------------------- Surcharge d'opérateurs

//-------------------------------------------- Constructeurs - destructeur
Provider::Provider(string userID, Role role) : User(userID,role)
{
    #ifdef MAP
        cout << "Appel au constructeur de <Provider>" << endl;
    #endif
} //----- Fin de Provider

Provider::~Provider ()
{
    #ifdef MAP
        cout << "Appel au destructeur de <Provider>" << endl;
    #endif
} //----- Fin de ~Provider

//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées