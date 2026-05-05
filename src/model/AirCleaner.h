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
#include "Sensor.h"
#include <string>
#include <chrono>
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types
using DateTime = std::chrono::system_clock::time_point;

//------------------------------------------------------------------------
// Rôle de la classe <AirCleaner>
//
//
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

    bool isActive(DateTime time) const;

    std::string getProviderID() const;
//------------------------------------------------- Surcharge d'opérateurs
    AirCleaner & operator = ( const AirCleaner & unAirCleaner );
    // Mode d'emploi :
    //
    // Contrat :
    //


//-------------------------------------------- Constructeurs - destructeur
    AirCleaner(std::string cleanerID, std::string providerID, double lattitude, double longitude, DateTime startTime, DateTime stopTime);
    // Mode d'emploi :
    //
    // Contrat :
    //

    virtual ~AirCleaner ( );
    // Mode d'emploi :
    //
    // Contrat :
    //

//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Méthodes protégées

//----------------------------------------------------- Attributs protégés
    std::string cleanerID;
    std::string providerID;
    double lattitude;
    double longitude;
    DateTime startTime;
    DateTime stopTime;

};

//-------------------------------- Autres définitions dépendantes de <User>

#endif // AIRCLEANER_H