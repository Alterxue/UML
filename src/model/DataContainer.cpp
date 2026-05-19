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

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques

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
