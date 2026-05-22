/*************************************************************************
                           DataContainer  -  description
                             -------------------
    début                : 19/05/2026
    copyright            : (C) 2026 par tautret
    e-mail               : tom.autret@insa-lyon.fr
*************************************************************************/

//---------- Réalisation de la classe <DataContainer> (fichier DataContainer.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
#include <iostream>
#include <string>
#include <vector>
#include <map>
using namespace std;

//------------------------------------------------------ Include personnel
#include "DataContainer.h"
#include "Attribute.h"
#include "Sensor.h"
#include "PrivateUser.h"
#include "AirCleaner.h"
#include "Provider.h"
#include "Measurement.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
void DataContainer::addAttribute(Attribute* ptr_attribute)
{
    allAttributes[ptr_attribute->getAttributeID()] = ptr_attribute;
} //----- Fin de addAttribute

void DataContainer::addSensor(Sensor* ptr_sensor)
{
    allSensors[ptr_sensor->getSensorID()] = ptr_sensor;
} //----- Fin de addSensor

void DataContainer::addUser(PrivateUser* ptr_privateuser)
{
    allUsers[ptr_privateuser->getUserID()] = ptr_privateuser;
} //----- Fin de addUser

void DataContainer::addAirCleaner(AirCleaner* ptr_aircleaner)
{
    allAirCleaners[ptr_aircleaner->getAirCleanerID()] = ptr_aircleaner;
} //----- Fin de addAirCleaner

void DataContainer::addProvider(Provider* ptr_provider)
{
    allProviders[ptr_provider->getUserID()] = ptr_provider;
} //----- Fin de addProvider

void DataContainer::addMeasurement(Measurement* ptr_measurement)
{
    Sensor* sensor = ptr_measurement->getSensor();
    measurementsBySensor[sensor->getSensorID()].push_back(ptr_measurement);
} //----- Fin de addMeasurement

const std::map<std::string, Attribute*>& DataContainer::getAllAttributes() const
{
    return allAttributes;
} //----- Fin de getAllAttributes

const std::map<std::string, Sensor*>& DataContainer::getAllSensors() const
{
    return allSensors;
} //----- Fin de getAllSensors

const std::map<string, PrivateUser*>& DataContainer::getAllUsers() const
{
    return allUsers;
} //----- Fin de getAllUsers

const std::map<string, AirCleaner*>& DataContainer::getAllAirCleaners() const
{
    return allAirCleaners;
} //----- Fin de getAllAirCleaners

const std::map<string, Provider*>& DataContainer::getAllProviders() const
{
    return allProviders;
} //----- Fin de getAllProviders

const std::map<string, vector<Measurement*>>& DataContainer::getAllMeasurementsBySensor() const
{
    return measurementsBySensor;
} //----- Fin de getAllMeasurementsBySensor 

Attribute * DataContainer::getAttributeByID(const string& attributeID)
{
    map<string, Attribute*>::const_iterator it = allAttributes.find(attributeID);
    if (it == allAttributes.end() || it->second == nullptr) {
        return nullptr;
    }
    return it->second;
} // ---- Fin de getAttributeByID

Sensor * DataContainer::getSensorByID(const string& sensorID)
{
    map<string, Sensor*>::const_iterator it = allSensors.find(sensorID);
    if (it == allSensors.end() || it->second == nullptr) {
        return nullptr;
    }
    return it->second;
} // ---- Fin de getSensorByID

PrivateUser* DataContainer::getPrivateUserByID(const string& userID)
{
    map<string, PrivateUser*>::const_iterator it = allUsers.find(userID);
    if (it == allUsers.end() || it->second == nullptr) {
        return nullptr;
    }
    return it->second;
} // ---- Fin de getPrivateUserByID

AirCleaner * DataContainer::getAirCleanerByID(const std::string& airCleanerID)
{
    map<string, AirCleaner*>::const_iterator it = allAirCleaners.find(airCleanerID);
    if (it == allAirCleaners.end() || it->second == nullptr) {
        return nullptr;
    }
    return it->second;
} // ---- Fin de getAirCleanerByID

Provider* DataContainer::getProviderByID(const std::string& providerID)
{
    map<string, Provider*>::const_iterator it = allProviders.find(providerID);
    if (it == allProviders.end() || it->second == nullptr) {
        return nullptr;
    }
    return it->second;
} // ---- Fin de getProviderByID

void DataContainer::clear()
{
    for (auto& pair : measurementsBySensor) {
        for (Measurement* measurement : pair.second) {
            delete measurement;
        }
        pair.second.clear();
    }
    measurementsBySensor.clear();

    for (auto& pair : allAirCleaners) {
        delete pair.second;
        pair.second = nullptr;
    }
    allAirCleaners.clear();

    for (auto& pair : allSensors) {
        delete pair.second;
        pair.second = nullptr;
    }
    allSensors.clear();

    for (auto& pair : allProviders) {
        delete pair.second;
        pair.second = nullptr;
    }
    allProviders.clear();

    for (auto& pair : allUsers) {
        delete pair.second;
        pair.second = nullptr;
    }
    allUsers.clear();

    for (auto& pair : allAttributes) {
        delete pair.second;
        pair.second = nullptr;
    }
    allAttributes.clear();
} //---- Fin de clear

void DataContainer::removeSensor(const std::string& sensorID)
{
    map<string, Sensor*>::iterator sensorIt = allSensors.find(sensorID);
    if (sensorIt != allSensors.end()) {
        delete sensorIt->second;
        allSensors.erase(sensorIt);
    }
    
    map<string, vector<Measurement*>>::iterator measurementIt = measurementsBySensor.find(sensorID);
    if (measurementIt != measurementsBySensor.end()) {
        for (Measurement* measurement : measurementIt->second) {
            delete measurement;
        }
        measurementsBySensor.erase(measurementIt);
    }
} //----- Fin de removeSensor

//-------------------------------------------- Constructeurs - destructeur
DataContainer::DataContainer()
{
    #ifdef MAP
        cout << "Appel au constructeur de <DataContainer>" << endl;
    #endif
} //----- Fin de DataContainer

DataContainer::~DataContainer()
{
    #ifdef MAP
        cout << "Appel au destructeur de <DataContainer>" << endl;
    #endif
    this->clear();
} //----- Fin de ~DataContainer

//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées