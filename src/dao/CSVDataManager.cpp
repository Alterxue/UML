/*************************************************************************
                           CSVDataManager  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Réalisation de la classe <CSVDataManager> (fichier CSVDataManager.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include <iostream>

//------------------------------------------------------ Include personnel
#include "CSVDataManager.h"
#include "../model/Role.h"
#include "../model/CSVDataContainer.h"


//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques

void CSVDataManager::loadSensors(CSVDataContainer container){
  // Algorithme :
  //
  Sensor* sensor; 
  string sensorId;
  double lattitude;
  double longitude;
  bool isReliable=true;
  //list<Measurement> mesures;
  ifstream file("../../data/sensor.csv");
  while(file.good){
    sensorId=getline(file,';');
    lattitude=stod(getline(file,';'));
    longitude=stod(getline(file,';'));
    //mesures=loadMeasurementsBySensorID(sensorID);
    container.(new Sensor(sensorId,lattitude,longitude,isReliable,mesures)));
    getline(file,'\n');
    file.peek();
  }
  return dicSensor;
  
}



void CSVDataManager::loadAttributes(CSVDataContainer & container){
  string attributeId;
  string unit;
  string description;
  ifstream file("../../data/attributes.csv");
  getline(file,'\n');
  while(file.good()){
    attributeId=getline(file,';');
    unit=getline(file,';');
    description=getline(file,';');

    container.addAttribute(new Attribute(attributeId,unit,description));
    
    getline('\n');
    file.peek();
  }  
  
}


void CSVDataManager::loadUsers(CSVDataContainer & container){
  string userId;
  string sensorId;
  PrivateUser* user;
  ifstream file("../../data/users.csv");
  while(file.good()){
    userId=getline(file,';');
    sensorId=getline(file,';');
    user=new PrivateUser(userId,PRIVATE_USER);
    container.getSensor(sensorId)->setUser(user);
    container.addUser(user);
    
    getline('\n');
    file.peek();
  }
  
  
}


void CSVDataManager::loadCleaners(CsvDataContainer & container){
  AirCleaner* cleaner;
  string cleanerId;
  
  double lattitude;
  double longitude;
  DateTime dateD;
  DateTime dateF;
  ifstream file("../../data/cleaners.csv")
  while(file.good()){
    cleanerId=getline(file,';');
    lattitude=stod(getline(file,';'));
    longitude=stod(getline(file,'\n'));
    
    cleaner=new AirCleaner(cleanerId,lattitude,longitude,dateD,dateF);
    container.addCleaner(cleaner);
    getline('\n');
    file.peek();
  }
  
    

    
  
  
  
}

void CSVDataManager::loadProviders(CSVDataContainer & container){
  string providerId;
  string cleanerId;
  Provider* provider;
  AirCleaner* cleaner;
  ifstream file("../../data/providers.csv");
  while(file.good()){
    providerId=getline(file,';');
    cleanerId=getline(file,';');
    provider=new Provider(providerId);
    cleaner=container.getCleaner(cleanerId);
    provider->addCleaner(cleaner);
    cleaner->addProvider(provider);
    container.add(provider);

    getline(file,'\n');
    file.peek();
    
  }
}

void CSVDataManager::loadMeasurements(CSVDataContainer & container){
  Measurement* measurement;
  string sensorId;
  Sensor* sensor;
  string stimestamp;
  
  istringstream stream;
  DateTime <std::chrono::system_clock> time;
  
  string attributeId;
  Attribute* attribute;
  double value;
  istream file("../../data/measurements.csv");
  while(file.good()){
    stream.str(getline(file,';'));
    std::chrono::from_stream (stream, "%Y-%d-%m %H:%M:%S", time);
    sensorId=getline(file,';');
    sensor=container.getSensor(sensorId);
    attributeId=getline(file,';');
    attibute=container.getAttribute(attributeId);
    
    value=stod(getline(file,';'));
    measurement=new Mesurements(timestamp,sensor,attribute,value);
    sensor.addMeasurement(measurement);
    container.addMeasurement(measurement);
    
    
    getline(file,'\n');
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

