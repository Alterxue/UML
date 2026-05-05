/*************************************************************************
                           AirCleaner  -  description
                             -------------------
    début                : 05/05/2026
    copyright            : (C) 2026 par aeliasmene
    e-mail               : alex.eliasmenet@gmail.com
*************************************************************************/

//---------- Réalisation de la classe <AirCleaner> (fichier AirCleaner.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
#include <iostream>
#include <string>
using namespace std;

//------------------------------------------------------ Include personnel
#include "AirCleaner.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques

string AirCleaner::getProviderID() const
{
    return providerID;
}

//------------------------------------------------- Surcharge d'opérateurs
AirCleaner & AirCleaner::operator = (const AirCleaner & unAirCleaner)
// Algorithme :
//
{
} //----- Fin de operator =


//-------------------------------------------- Constructeurs - destructeur

AirCleaner::AirCleaner(string cleanerID, string providerID, double lattitude, double longitude, DateTime startTime, DateTime stopTime)
    : cleanerID(cleanerID), providerID(providerID), lattitude(lattitude), longitude(longitude), startTime(startTime), stopTime(stopTime)
{
}

AirCleaner::~AirCleaner ()
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au destructeur de <AirCleaner>" << endl;
#endif
} //----- Fin de ~AirCleaner


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées