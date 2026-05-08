/*************************************************************************
                           AirCleaner  -  description
                             -------------------
    début                : 05/05/2026
    copyright            : (C) 2026 par aeliasmene
    e-mail               : alex.eliasmenet@gmail.com
*************************************************************************/

//---------- Interface de la classe <AirCleaner> (fichier AirCleaner.h) ----------------
#if ! defined ( AIRCLEANER_H )
#define AIRCLEANER_H

//--------------------------------------------------- Interfaces utilisées
#include <string>
#include <chrono>

#include "Sensor.h"
#include "TimeRange.h"
#include "Provider.h"
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types
using DateTime = std::chrono::system_clock::time_point;

//------------------------------------------------------------------------
// Rôle de la classe <AirCleaner>
// Représente un AirCleaner avec son ID, son fournisseur, sa position
// et sa durée de fonctionnement
//------------------------------------------------------------------------

class AirCleaner
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques
    // type Méthode ( liste des paramètres );
    // Mode d'emploi :
    //
    // Contrat :
    //

    bool isActive(DateTime date) const;
    // Mode d'emploi :
    // Indique si l'AirCleaner était actif à la date donnée

    Provider* getProviderID() const;
    // Mode d'emploi : 
    // Renvoie le Provider de ce Aircleaner
    
//------------------------------------------------- Surcharge d'opérateurs
    AirCleaner & operator = ( const AirCleaner & unAirCleaner );
    // Mode d'emploi :
    //
    // Contrat :
    //

//-------------------------------------------- Constructeurs - destructeur
    AirCleaner(std::string a_cleanerID, Provider* a_provider, double a_lattitude, double a_longitude, DateTime a_startTime, DateTime a_stopTime);
    // Mode d'emploi :
    // Constructeur du AirCleaner à partir des paramètres

    ~AirCleaner ( );
    // Mode d'emploi :
    // Destructeur du AirCleaner

//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Méthodes protégées

//----------------------------------------------------- Attributs protégés
    std::string cleanerID;
    Provider* provider;
    double lattitude;
    double longitude;
    TimeRange workingPeriod;
};

//-------------------------------- Autres définitions dépendantes de <User>

#endif // AIRCLEANER_H