/*************************************************************************
                           CSVDataManager  -  description
                             -------------------
    début                : 19/05/2026
    copyright            : (C) 2026 par scabias
    e-mail               : simon.cabias@insa-lyon.fr
*************************************************************************/

//---------- Réalisation de la classe <CSVDataManager> (fichier CSVDataManager.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

//------------------------------------------------------ Include personnel
#include "CSVDataManager.h"
#include "../model/Role.h"
#include "../model/DataContainer.h"


//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques

void CSVDataManager::loadSensors(DataContainer & container) const{
  // Algorithme :
  //
  Sensor* sensor; 
  string sensorId;
  double lattitude;
  double longitude;
  ifstream file("../../data/sensor.csv");
  string lattitudeStr;
  string longitudeStr;
  string lineRemainder;
  while(file.good()){
    std::getline(file, sensorId, ';');
    std::getline(file, lattitudeStr, ';');
    std::getline(file, longitudeStr, ';');
    lattitude = std::stod(lattitudeStr);
    longitude = std::stod(longitudeStr);
    container.addSensor(new Sensor(sensorId,lattitude,longitude));
    std::getline(file, lineRemainder);
    file.peek();
  }
}



void CSVDataManager::loadAttributes(DataContainer & container) const{
  string attributeId;
  string unit;
  string description;
  ifstream file("../../data/attributes.csv");
  string lineRemainder;
  std::getline(file, lineRemainder);
  while(file.good()){
    std::getline(file, attributeId, ';');
    std::getline(file, unit, ';');
    std::getline(file, description, ';');

    container.addAttribute(new Attribute(attributeId,unit,description));
    
    std::getline(file, lineRemainder);
    file.peek();
  }  
  
}


void CSVDataManager::loadUsers(DataContainer & container) const{
  string userId;
  string sensorId;
  PrivateUser* user;
  ifstream file("../../data/users.csv");
  string lineRemainder;
  while(file.good()){
    std::getline(file, userId, ';');
    std::getline(file, sensorId, ';');
    user=new PrivateUser(userId,PRIVATE_USER);
    container.getSensorByID(sensorId)->setOwner(user); // Associe le capteur à l'utilisateur
    user->addSensor(*container.getSensorByID(sensorId)); // Associe l'utilisateur au capteur
    container.addUser(user); // Ajoute l'utilisateur au conteneur de données
    
    std::getline(file, lineRemainder);
    file.peek();
  }
  
  
}


void CSVDataManager::loadCleaners(DataContainer & container) const{
  AirCleaner* cleaner;
  string cleanerId;
  
  double lattitude;
  double longitude;
  DateTime dateD;
  DateTime dateF;
  ifstream file("../../data/cleaners.csv");
  string lattitudeStr;
  string longitudeStr;
  string lineRemainder;
  while(file.good()){
    std::getline(file, cleanerId, ';');
    std::getline(file, lattitudeStr, ';');
    std::getline(file, longitudeStr);
    lattitude = std::stod(lattitudeStr);
    longitude = std::stod(longitudeStr);
    
    cleaner=new AirCleaner(cleanerId,lattitude,longitude,dateD,dateF);
    container.addAirCleaner(cleaner);
    std::getline(file, lineRemainder);
    file.peek();
  } 
}

void CSVDataManager::loadProviders(DataContainer & container) const{
  string providerId;
  string cleanerId;
  Provider* provider;
  AirCleaner* cleaner;
  ifstream file("../../data/providers.csv");
  string lineRemainder;
  while(file.good()){
    std::getline(file, providerId, ';');
    std::getline(file, cleanerId, ';');
    provider = new Provider(providerId, PROVIDER);
    cleaner=container.getAirCleanerByID(cleanerId);
    provider->addCleaners(cleaner);
    cleaner->setProvider(provider);
    container.addProvider(provider);

    std::getline(file, lineRemainder);
    file.peek();
    
  }
}

void CSVDataManager::loadMeasurements(DataContainer & container){
  Measurement* measurement;
  string sensorId;
  Sensor* sensor;
  string stimestamp;
  
  istringstream stream;
  using DateTime = std::chrono::system_clock::time_point;
  
  string attributeId;
  Attribute* attribute;
  double value;
  istream file("../../data/measurements.csv");
  string valueStr;
  string lineRemainder;
  while(file.good()){
    std::getline(file, stimestamp, ';');
    stream.clear();
    stream.str(stimestamp);
    std::chrono::from_stream (stream, "%Y-%d-%m %H:%M:%S", time);
    std::getline(file, sensorId, ';');
    sensor=container.getSensor(sensorId);
    std::getline(file, attributeId, ';');
    attibute=container.getAttribute(attributeId);
    
    std::getline(file, valueStr, ';');
    value = std::stod(valueStr);
    measurement=new Mesurements(timestamp,sensor,attribute,value);
    sensor.addMeasurement(measurement);
    container.addMeasurement(measurement);
    
    
    std::getline(file, lineRemainder);
    file.peek();
  }
}



//------------------------------------------------- Surcharge d'opérateurs
CSVDataManager & CSVDataManager::operator = ( const CSVDataManager & unCSVDataManager )
// Algorithme :
//
{
} //----- Fin de operator =


//-------------------------------------------- Constructeurs - destructeur
CSVDataManager::CSVDataManager ( const CSVDataManager & unCSVDataManager )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au constructeur de copie de <CSVDataManager>" << endl;
#endif
} //----- Fin de CSVDataManager (constructeur de copie)


CSVDataManager::CSVDataManager ( )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au constructeur de <CSVDataManager>" << endl;
#endif
} //----- Fin de CSVDataManager


CSVDataManager::~CSVDataManager ( )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au destructeur de <CSVDataManager>" << endl;
#endif
} //----- Fin de ~CSVDataManager


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées

