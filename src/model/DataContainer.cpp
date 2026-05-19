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
    allAirCleaners.push_back(ptr_aircleaner);
} //----- Fin de addAirCleaner

void DataContainer::addProvider(Provider* ptr_provider)
{
    allProviders[ptr_provider->getUserID()] = ptr_provider;
} //----- Fin de addProvider


