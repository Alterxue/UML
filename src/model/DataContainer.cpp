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

void DataContainer::addAttribute(const Attribute* ptr_attribute)
{
    allAttributes[ptr_attribute->getID()] = ptr_attribute;
} //----- Fin de addAttribute

void addSensor(const Sensor* ptr_sensor)
{
    allSensors[ptr_sensor->getSensorID()] = 
}