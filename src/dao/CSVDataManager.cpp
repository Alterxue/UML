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

    if (userId.empty()) {
      continue;
    }

    PrivateUser* user = new PrivateUser(userId, PRIVATE_USER);

    while (getline(iss, sensorId, ';')) {
      if (sensorId.empty()) {
        continue;
      }

      Sensor* sensor = container.getSensorByID(sensorId);

      if (sensor != nullptr) {
        sensor->setOwner(user);
        user->addSensor(sensor);
      }
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

void CSVDataManager::saveSensors(const DataContainer & container) const
{
  ofstream file("data/sensors.csv", ios::trunc);

  if (!file.is_open()) {
    return;
  }

  const map<string, Sensor*>& sensors = container.getAllSensors();
  for (map<string, Sensor*>::const_iterator it = sensors.begin(); it != sensors.end(); ++it) {
    const string& sensorId = it->first;
    const Sensor* sensor = it->second;

    if (sensor == nullptr) {
      continue;
    }

    file << sensorId << ";" << sensor->getLattitude() << ";" << sensor->getLongitude() << ";" << endl;
  }
}

void CSVDataManager::saveUsers(const DataContainer & container) const
{
  ofstream file("data/users.csv", ios::trunc);

  if (!file.is_open()) {
    return;
  }

  const map<string, PrivateUser*>& users = container.getAllUsers();
  for (map<string, PrivateUser*>::const_iterator it = users.begin(); it != users.end(); ++it) {
    const string& userId = it->first;
    const PrivateUser* user = it->second;

    if (user == nullptr) {
      continue;
    }

    const vector<Sensor*>& sensors = user->getSensorsList();

    file << userId << ";";

    for (vector<Sensor*>::const_iterator sensorIt = sensors.begin(); sensorIt != sensors.end(); ++sensorIt) {
      const Sensor* sensor = *sensorIt;

      if (sensor == nullptr) {
        continue;
      }

      file << sensor->getSensorID() << ";";
    }

    file << endl;
  }
}

void CSVDataManager::saveCleaners(const DataContainer & container) const
{
  ofstream file("data/cleaners.csv", ios::trunc);

  if (!file.is_open()) {
    return;
  }

  const map<string, AirCleaner*>& cleaners = container.getAllAirCleaners();
  for (map<string, AirCleaner*>::const_iterator it = cleaners.begin(); it != cleaners.end(); ++it) {
    const string& cleanerId = it->first;
    const AirCleaner* cleaner = it->second;

    if (cleaner == nullptr) {
      continue;
    }

    const TimeRange workingPeriod = cleaner->getWorkingPeriod();
    const time_t startRawTime = chrono::system_clock::to_time_t(workingPeriod.getStart());
    const tm* startLocalTime = std::localtime(&startRawTime);
    ostringstream startStream;
    startStream << put_time(startLocalTime, "%Y-%m-%d %H:%M:%S");

    const time_t endRawTime = chrono::system_clock::to_time_t(workingPeriod.getEnd());
    const tm* endLocalTime = std::localtime(&endRawTime);
    ostringstream endStream;
    endStream << put_time(endLocalTime, "%Y-%m-%d %H:%M:%S");

    file << cleanerId << ";"
         << cleaner->getLattitude() << ";"
         << cleaner->getLongitude() << ";"
         << startStream.str() << ";"
         << endStream.str() << ";" << endl;
  }
}

void CSVDataManager::saveProviders(const DataContainer & container) const
{
  ofstream file("data/providers.csv", ios::trunc);

  if (!file.is_open()) {
    return;
  }

  const map<string, Provider*>& providers = container.getAllProviders();
  for (map<string, Provider*>::const_iterator it = providers.begin(); it != providers.end(); ++it) {
    const string& providerId = it->first;
    const Provider* provider = it->second;

    if (provider == nullptr) {
      continue;
    }

    const vector<AirCleaner*>& cleaners = provider->getMyCleaners();

    if (cleaners.empty()) {
      file << providerId << ";;" << endl;
      continue;
    }

    const AirCleaner* cleaner = cleaners.front();
    if (cleaner == nullptr) {
      file << providerId << ";;" << endl;
      continue;
    }

    file << providerId << ";" << cleaner->getAirCleanerID() << ";" << endl;
  }
}

void CSVDataManager::saveMeasurements(const DataContainer & container) const
{
  ofstream file("data/measurements.csv", ios::trunc);

  if (!file.is_open()) {
    return;
  }

  const map<string, vector<Measurement*>>& measurementsBySensor = container.getAllMeasurementsBySensor();
  for (map<string, vector<Measurement*>>::const_iterator it = measurementsBySensor.begin(); it != measurementsBySensor.end(); ++it) {
    const vector<Measurement*>& measurements = it->second;

    for (vector<Measurement*>::const_iterator measurementIt = measurements.begin(); measurementIt != measurements.end(); ++measurementIt) {
      const Measurement* measurement = *measurementIt;

      if (measurement == nullptr || measurement->getSensor() == nullptr || measurement->getAttribute() == nullptr) {
        continue;
      }

      const time_t rawTime = chrono::system_clock::to_time_t(measurement->getMeasureDate());
      const tm* localTime = std::localtime(&rawTime);
      ostringstream timestampStream;
      timestampStream << put_time(localTime, "%Y-%m-%d %H:%M:%S");

      file << timestampStream.str() << ";"
           << measurement->getSensor()->getSensorID() << ";"
           << measurement->getAttribute()->getAttributeID() << ";"
           << measurement->getValue() << ";" << endl;
    }
  }
}

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

