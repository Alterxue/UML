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
using namespace std;
#include <iostream>
#include <string>


//------------------------------------------------------ Include personnel
#include "AirCleaner.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
bool AirCleaner::isActive(const DateTime date) const
{
    return workingPeriod.contains(date);
}

Provider* AirCleaner::getProvider() const
{
    return provider;
} //----- Fin de getProviderID

string AirCleaner::getAirCleanerID() const
{
    return cleanerID;
}

double AirCleaner::getLattitude() const
{
    return lattitude;
}

double AirCleaner::getLongitude() const
{
    return longitude;
}

TimeRange AirCleaner::getWorkingPeriod() const
{
    return workingPeriod;
}

//------------------------------------------------- Surcharge d'opérateurs
AirCleaner & AirCleaner::operator = (const AirCleaner & unAirCleaner)
// Algorithme :
//
{
} //----- Fin de operator =


//-------------------------------------------- Constructeurs - destructeur
AirCleaner::AirCleaner(string a_cleanerID, Provider* a_provider, double a_lattitude, double a_longitude, DateTime a_startTime, DateTime a_stopTime)
: cleanerID(a_cleanerID), provider(a_provider), lattitude(a_lattitude), longitude(a_longitude), workingPeriod(TimeRange(a_startTime, a_stopTime))
{
    #ifdef MAP
        cout << "Appel au constructeur de <AirCleaner>" << endl;
    #endif
} //----- Fin de AirCleaner

AirCleaner::~AirCleaner ()
{
    #ifdef MAP
        cout << "Appel au destructeur de <AirCleaner>" << endl;
    #endif
} //----- Fin de ~AirCleaner


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées