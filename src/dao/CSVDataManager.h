/*************************************************************************
                           CSVDataManager  -  description
                             -------------------
    début                : 19/05/2026
    copyright            : (C) 2026 par scabias
    e-mail               : simon.cabias@insa-lyon.fr
*************************************************************************/

//---------- Interface de la classe <CSVDataManager> (fichier CSVDataManager.h) ----------------
#if ! defined ( CSVDATAMANAGER_H )
#define CSVDATAMANAGER_H

//--------------------------------------------------- Interfaces utilisées
#include <list>
#include <string>
#include <vector>
#include "../model/Sensor.h"
#include "../model/Measurement.h"
#include "../model/User.h"
#include "../model/Attribute.h"
#include "../model/Provider.h"
#include "../model/AirCleaner.h"
#include "../model/PrivateUser.h"
#include "../model/DataContainer.h"

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types
using DateTime = std::chrono::system_clock::time_point;

//------------------------------------------------------------------------
// Rôle de la classe <CSVDataManager>
// Va permettre de lire et parser les CSV avant de stocker les données
// DataContainer
//------------------------------------------------------------------------

class CSVDataManager
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques
    void loadAttributes(DataContainer & container) const;
    // Mode d'emploi :
    // Charge les attributs de mesure et les stock dans DataContainer

    void loadSensors(DataContainer & container) const;
    // Mode d'emploi :
    // Charge tous les sensors des fichiers dans le DataContainer

    void loadUsers(DataContainer & container) const;
    // Mode d'emploi :
    // Charge les PrivateUser, les stocke et leur associe leur capteurs

    void loadCleaners(DataContainer & container) const;
    // Mode d'emploi :
    // Charge les AirCleaners et les stocke

    void loadProviders(DataContainer & container) const;
    // Mode d'emploi :
    // Charge tous les Provider et les stocke dans DataContainer

    void loadMeasurements(DataContainer & container) const;
    // Mode d'emploi : 
    // Charges les mesures et les associe au bon capteur

    void saveSensors(const DataContainer & container) const;
    // Mode d'emploi :
    // Sauvegarde tous les sensors dans le fichier CSV

    void saveUsers(const DataContainer & container) const;
    // Mode d'emploi :
    // Sauvegarde tous les utilisateurs dans le fichier CSV

    void saveCleaners(const DataContainer & container) const;
    // Mode d'emploi :
    // Sauvegarde tous les air cleaners dans le fichier CSV

    void saveProviders(const DataContainer & container) const;
    // Mode d'emploi :
    // Sauvegarde tous les providers dans le fichier CSV

    void saveMeasurements(const DataContainer & container) const;
    // Mode d'emploi :
    // Sauvegarde toutes les mesures dans le fichier CSV
 
//------------------------------------------------- Surcharge d'opérateurs

//-------------------------------------------- Constructeurs - destructeur
    CSVDataManager ( );
    // Mode d'emploi :
    // Constructeur de la classe CSVDataManager

    ~CSVDataManager ( );
    // Mode d'emploi :
    // Destructeur de la classe CSVDataManager

//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Méthodes protégées

//----------------------------------------------------- Attributs protégés

};

//-------------------------------- Autres définitions dépendantes de <CSVDataManager>

#endif // CSVDATAMANAGER_H

