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
    bool isActive(const DateTime date) const;
    // Mode d'emploi :
    // Indique si l'AirCleaner était actif à la date donnée

    Provider * getProvider() const;
    // Mode d'emploi : 
    // Renvoie le Provider de ce Aircleaner

    std::string getAirCleanerID() const;
    // Mode d'emploi :
    // Renvoie l'ID de ce AirCleaner
    
    double getLattitude() const;
    // Mode d'emploi :
    // Renvoie la lattitude du AirCleaner

    double getLongitude() const;
    // Mode d'emploi :
    // Renvoie la longitude du AirCleaner

    TimeRange getWorkingPeriod() const;
    // Mode d'emploi :
    // Renvoie la période de fonctionnement du AirCleaner

    void setProvider(Provider* a_provider);
    // Mode d'emploi :
    // Définit le Provider de ce AirCleaner

//------------------------------------------------- Surcharge d'opérateurs

//-------------------------------------------- Constructeurs - destructeur
    AirCleaner(std::string a_cleanerID, double a_lattitude, double a_longitude, DateTime a_startTime, DateTime a_stopTime);
    // Mode d'emploi :
    // Constructeur du AirCleaner

    ~AirCleaner ( );
    // Mode d'emploi :
    // Destructeur du AirCleaner

//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Méthodes protégées

//----------------------------------------------------- Attributs protégés
    std::string cleanerID;
    // Lien non possédant vers le fournisseur de l'AirCleaner.
    Provider* provider;
    double lattitude;
    double longitude;
    TimeRange workingPeriod;
};

//-------------------------------- Autres définitions dépendantes de <AirCleaner>

#endif // AIRCLEANER_H