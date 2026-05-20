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

void DataContainer::addMeasurement(Measurement* ptr_measurement)
{
    if (ptr_measurement == nullptr) {
        return;
    }
    Sensor* sensor = ptr_measurement->getSensor();
    if (sensor == nullptr) {
        return;
    }
    measurementsBySensor[sensor->getSensorID()].push_back(ptr_measurement);
} //----- Fin de addMeasurement

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

Sensor * DataContainer::getSensorByID(const std::string& sensorID)
{
    for (const map<std::string, Sensor*>::value_type& pair : allSensors) {
        if (pair.first == sensorID) {
            return pair.second;
        }
    }
    return nullptr; // Retourne nullptr si le capteur n'est pas trouvé
}

AirCleaner * DataContainer::getAirCleanerByID(const std::string& airCleanerID)
{
    for (const map<std::string, AirCleaner*>::value_type& pair : allAirCleaners) {
        if (pair.first == airCleanerID) {
            return pair.second;
        }
    }
    return nullptr; // Retourne nullptr si l'air cleaner n'est pas trouvé
}

Attribute * DataContainer::getAttributeByID(const std::string& attributeID)
{
    for (const auto& pair : this->allAttributes) {
        if (pair.first == attributeID) {
            return pair.second;
        }
    }
    return nullptr; // Retourne nullptr si l'attribut n'est pas trouvé
}

const std::map<std::string, Attribute*>& DataContainer::getAllAttributes() const
{
    return allAttributes;
} //----- Fin de getAllAttributes

const std::map<std::string, Sensor*>& DataContainer::getAllSensors() const
{
    return allSensors;
} //----- Fin de getAllSensors

const std::map<std::string, PrivateUser*>& DataContainer::getAllUsers() const
{
    return allUsers;
} //----- Fin de getAllUsers

const std::map<string, AirCleaner*>& DataContainer::getAllAirCleaners() const
{
    return allAirCleaners;
} //----- Fin de getAllAirCleaners

const std::map<std::string, Provider*>& DataContainer::getAllProviders() const
{
    return allProviders;
} //----- Fin de getAllProviders

//-------------------------------------------- Constructeurs - destructeur
DataContainer::DataContainer()
{
    #ifdef MAP
        cout <<"Appel au constructeur de <DataContainer>"<< endl;
    #endif
} //----- Fin de DataContainer

DataContainer::~DataContainer()
{
   #ifdef MAP
        cout <<"Appel au destructeur de <DataContainer>"<< endl;
    #endif 
   for (std::map<std::string, AirCleaner*>::value_type& pair : allAirCleaners) {
       delete pair.second;
       pair.second = nullptr;
   }

   for (std::map<std::string, Sensor*>::value_type& pair : allSensors) {
       delete pair.second;
       pair.second = nullptr;
   }

   for (std::map<std::string, Provider*>::value_type& pair : allProviders) {
       delete pair.second;
       pair.second = nullptr;
   }

   for (std::map<std::string, PrivateUser*>::value_type& pair : allUsers) {
       delete pair.second;
       pair.second = nullptr;
   }

   for (std::map<std::string, Attribute*>::value_type& pair : allAttributes) {
       delete pair.second;
       pair.second = nullptr;
   }

   allAirCleaners.clear();
   allSensors.clear();
   allProviders.clear();
   allUsers.clear();
   allAttributes.clear();
} //----- Fin de ~DataContainer
