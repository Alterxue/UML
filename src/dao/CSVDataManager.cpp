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
void CSVDataManager::loadAttributes(DataContainer & container) const
{
  ifstream file("../../data/attributes.csv");
  string line;
  getline(file, line); // Saute la première ligne de attributes.csv

  while(getline(file, line))
  {
    istringstream iss(line);

    string attributeId;
    string unit;
    string description;

    getline(iss, attributeId, ';');
    getline(iss, unit, ';');
    getline(iss, description, ';');
    container.addAttribute(new Attribute(attributeId, unit, description));
  }
} //----- Fin de loadAttributes

void CSVDataManager::loadSensors(DataContainer & container) const
// Algorithme :
{
  ifstream file("../../data/sensor.csv");
  string line;

  while (getline(file, line)) {
    istringstream iss(line);

    string sensorId;
    string lattitudeStr;
    string longitudeStr;

    getline(iss, sensorId, ';');
    getline(iss, lattitudeStr, ';');
    getline(iss, longitudeStr, ';');

    double lattitude = stod(lattitudeStr);
    double longitude = stod(longitudeStr);

    container.addSensor(new Sensor(sensorId, lattitude, longitude));
  }
} //----- Fin de loadSensors

void CSVDataManager::loadUsers(DataContainer & container) const
// Algorithme :
{
  ifstream file("../../data/users.csv");
  string line;

  while(getline(file, line)) {
    istringstream iss(line);

    string userId;
    string sensorId;

    getline(iss, userId, ';');
    getline(iss, sensorId, ';');

    PrivateUser* user = new PrivateUser(userId, PRIVATE_USER);
    Sensor* sensor = container.getSensorByID(sensorId);
    
    if (sensor != nullptr) {
      sensor->setOwner(user); // Associe le capteur à l'utilisateur
      user->addSensor(sensor); // Associe l'utilisateur au capteur
    }
    
    container.addUser(user); // Ajoute l'utilisateur au conteneur de données
  }
} //----- Fin de loadUsers 


void CSVDataManager::loadCleaners(DataContainer & container) const
// Algorithme :
{
  ifstream file("../../data/cleaners.csv");
  string line;

  while(getline(file, line)) {
    istringstream iss(line);

    string cleanerId;
    string lattitudeStr;
    string longitudeStr;
    string dateDStr;
    string dateFStr;

    getline(iss, cleanerId, ';');
    getline(iss, lattitudeStr, ';');
    getline(iss, longitudeStr, ';');
    getline(iss, dateDStr, ';');
    getline(iss, dateFStr, ';');

    double lattitude = stod(lattitudeStr);
    double longitude = stod(longitudeStr);

    // Faire le parsing des dates de début et de fin pour bien avoir un dateTime
    // A finir



  }

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

void CSVDataManager::loadProviders(DataContainer & container) const
// Algorithme :
{
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

void CSVDataManager::loadMeasurements(DataContainer & container) const
// Algorithme :
{
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

