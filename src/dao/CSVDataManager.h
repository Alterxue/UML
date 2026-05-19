/*************************************************************************
                           CSVDataManager  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
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

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <CSVDataManager>
//
//
//------------------------------------------------------------------------

class CSVDataManager
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques
  void loadSensors(CSVDataContainer & container)const;
    // Mode d'emploi :Renvoie une liste de Sensor à l'appelant
    //
    // Contrat :
    //
  //std::list<Sensor> loadSensorsByUser(PrivateUser user)const;
    // Mode d'emploi :Renvoie la liste des Sensor appartenant a l'user en paramètre à l'appelant
    //
    // Contrat :
    //
  Sensor loadSensorById(std::string sensorID);
  
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
  void loadUsers(CSVDataContainer & container)const;
    // Mode d'emploi :Renvoie une liste de Sensor à l'appelant
    //
    // Contrat :
    //
  void loadAttributes(CSVDataContainer & container)const;
    // Mode d'emploi :Renvoie une liste de Sensor à l'appelant
    //
    // Contrat :
    //
  void loadProviders(CSVDataContainer & container)const;
    // Mode d'emploi :Renvoie une liste de Sensor à l'appelant
    //
    // Contrat :
    //
  void loadCleaners(CSVDataContainer & container)const;
    // Mode d'emploi :Renvoie une liste de Sensor à l'appelant
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
  void updateSensorStatus()
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

