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
#include <chrono>
#include <ctime>
#include <iomanip>

//------------------------------------------------------ Include personnel
#include "CSVDataManager.h"
#include "../model/Role.h"
#include "../model/DataContainer.h"


//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
void CSVDataManager::loadAttributes(DataContainer & container) const
{
  ifstream file("data/attributes.csv");
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
  ifstream file("data/sensors.csv");
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
  ifstream file("data/users.csv");
  string line;

  while (getline(file, line)) {
    istringstream iss(line);

    string userId;
    string sensorId;

    getline(iss, userId, ';');
    getline(iss, sensorId, ';');

    if (userId.empty()) {
      continue;
    }

    PrivateUser* user = new PrivateUser(userId, PRIVATE_USER);
    Sensor* sensor = container.getSensorByID(sensorId);

    if (sensor != nullptr) {
      sensor->setOwner(user);
      user->addSensor(sensor);
    }

    container.addUser(user);
  }
} //----- Fin de loadUsers

void CSVDataManager::loadCleaners(DataContainer & container) const
// Algorithme :
{
  ifstream file("data/cleaners.csv");
  string line;

  while (getline(file, line)) {
    istringstream iss(line);

    string cleanerId;
    string lattitudeStr;
    string longitudeStr;
    string startStr;
    string endStr;

    getline(iss, cleanerId, ';');
    getline(iss, lattitudeStr, ';');
    getline(iss, longitudeStr, ';');
    getline(iss, startStr, ';');
    getline(iss, endStr, ';');

    if (cleanerId.empty() || lattitudeStr.empty() || longitudeStr.empty() || startStr.empty() || endStr.empty()) {
      continue;
    }

    double lattitude = stod(lattitudeStr);
    double longitude = stod(longitudeStr);

    std::tm startTm = {};
    std::tm endTm = {};
    std::istringstream startStream(startStr);
    std::istringstream endStream(endStr);
    startStream >> std::get_time(&startTm, "%Y-%m-%d %H:%M:%S");
    endStream >> std::get_time(&endTm, "%Y-%m-%d %H:%M:%S");
    if (startStream.fail() || endStream.fail()) {
      continue;
    }

    DateTime dateD = std::chrono::system_clock::from_time_t(std::mktime(&startTm));
    DateTime dateF = std::chrono::system_clock::from_time_t(std::mktime(&endTm));

    AirCleaner* cleaner = new AirCleaner(cleanerId, lattitude, longitude, dateD, dateF);
    container.addAirCleaner(cleaner);
  }
} //----- Fin de loadCleaners

void CSVDataManager::loadProviders(DataContainer & container) const
// Algorithme :
{
  ifstream file("data/providers.csv");
  string line;

  while (getline(file, line)) {
    istringstream iss(line);

    string providerId;
    string cleanerId;

    getline(iss, providerId, ';');
    getline(iss, cleanerId, ';');

    if (providerId.empty() || cleanerId.empty()) {
      continue;
    }

    Provider* provider = new Provider(providerId, PROVIDER);
    AirCleaner* cleaner = container.getAirCleanerByID(cleanerId);
    if (cleaner != nullptr) {
      provider->addAirCleaner(cleaner);
      cleaner->setProvider(provider);
    }
    container.addProvider(provider);
  }
} //----- Fin de loadProviders

void CSVDataManager::loadMeasurements(DataContainer & container) const
// Algorithme :
{
  ifstream file("data/measurements.csv");
  string line;

  while (getline(file, line)) {
    istringstream iss(line);

    string stimestamp;
    string sensorId;
    string attributeId;
    string valueStr;

    getline(iss, stimestamp, ';');
    getline(iss, sensorId, ';');
    getline(iss, attributeId, ';');
    getline(iss, valueStr, ';');

    if (stimestamp.empty() || sensorId.empty() || attributeId.empty() || valueStr.empty()) {
      continue;
    }

    std::tm tm = {};
    std::istringstream stream(stimestamp);
    stream >> std::get_time(&tm, "%Y-%m-%d %H:%M:%S");
    if (stream.fail()) {
      continue;
    }

    DateTime measureDate = std::chrono::system_clock::from_time_t(std::mktime(&tm));
    Sensor* sensor = container.getSensorByID(sensorId);
    Attribute* attribute = container.getAttributeByID(attributeId);
    if (sensor == nullptr || attribute == nullptr) {
      continue;
    }

    double value = std::stod(valueStr);
    Measurement* measurement = new Measurement(measureDate, sensor, attribute, value);
    sensor->addMeasurement(measurement);
    container.addMeasurement(measurement);
  }
} //----- Fin de loadMeasurements

//------------------------------------------------- Surcharge d'opérateurs

//-------------------------------------------- Constructeurs - destructeur
CSVDataManager::CSVDataManager ( )
// Algorithme :
{
  #ifdef MAP
      cout << "Appel au constructeur de <CSVDataManager>" << endl;
  #endif
} //----- Fin de CSVDataManager

CSVDataManager::~CSVDataManager ( )
// Algorithme :
{
  #ifdef MAP
      cout << "Appel au destructeur de <CSVDataManager>" << endl;
  #endif
} //----- Fin de ~CSVDataManager

//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées

