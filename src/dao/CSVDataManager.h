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
 




  //std::list<Sensor> loadSensorsByUser(PrivateUser user)const;
  // Mode d'emploi :Renvoie la liste des Sensor appartenant a l'user en paramètre à l'appelant
  //
  // Contrat :
  //
  // Sensor loadSensorById(std::string sensorID);

  //std::list<Measurement> loadMeasurements()const;
  // Mode d'emploi :Renvoie une liste de Sensor à l'appelant
  //
  // Contrat :
  //
  std::vector<Measurement> loadMeasurementsBySensorID(std::string sensorID);
  // Mode d'emploi : Renvoie une liste de mesure associé au Sensor dont l'ID est en parametre
  //
  // Contrat :
  // 



  void appendNewSensor(const Sensor& sensor,const PrivateUser& user);
  // Mode d'emploi :
  //
  // Contrat :
  //
  //void appendNewSensor(Sensor sensor);
  // Mode d'emploi :Renvoie une liste de Sensor à l'appelant
  //
  // Contrat :
  //
  //void appendNewSensor(Sensor sensor);
  // Mode d'emploi :Renvoie une liste de Sensor à l'appelant
  //
  // Contrat :
  //
  void updateSensorStatus();
  // Mode d'emploi :Renvoie une liste de Sensor à l'appelant
  //
  // Contrat :
  //
    
  

//------------------------------------------------- Surcharge d'opérateurs
    CSVDataManager & operator = ( const CSVDataManager & unCSVDataManager ); 
    // Mode d'emploi :
    //
    // Contrat :
    //


//-------------------------------------------- Constructeurs - destructeur
    CSVDataManager ( const CSVDataManager & unCSVDataManager );
    // Mode d'emploi (constructeur de copie) :
    //
    // Contrat :
    //

    CSVDataManager ( );
    // Mode d'emploi :
    //
    // Contrat :
    //

    virtual ~CSVDataManager ( );
    // Mode d'emploi :
    //
    // Contrat :
    //

//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Méthodes protégées

//----------------------------------------------------- Attributs protégés

};

//-------------------------------- Autres définitions dépendantes de <CSVDataManager>

#endif // CSVDATAMANAGER_H

