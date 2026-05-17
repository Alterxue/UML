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

list<AirCleaner> Provider::getMyCleaners(list<AirCleaner> cleaners) const
{
    list<AirCleaner> myCleaners;
    for (const AirCleaner & cleaner : cleaners)
    {
        if (cleaner.isActive(std::chrono::system_clock::now()) && cleaner.getProviderID() == this)
        {
            myCleaners.push_back(cleaner);
        }
    }
    return myCleaners;
}


//------------------------------------------------- Surcharge d'opérateurs
Provider & Provider::operator = (const Provider & unProvider)
{
} //----- Fin de operator =


//-------------------------------------------- Constructeurs - destructeur
Provider::Provider (string providerID) : providerID(providerID){}

Provider::~Provider ()
{
#ifdef MAP
    cout << "Appel au destructeur de <Provider>" << endl;
#endif
} //----- Fin de ~Provider


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées