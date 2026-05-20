/*************************************************************************
                           Measurement  -  description
                             -------------------
    début                : 06/05/2026
    copyright            : (C) 2026 par tautret
    e-mail               : tom.autret@insa-lyon.fr
*************************************************************************/

//---------- Réalisation de la classe <Measurement> (fichier Measurement.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;

#include <chrono>
#include <iostream>

//------------------------------------------------------ Include personnel
#include "Measurement.h"
#include "Sensor.h"
using DateTime = std::chrono::system_clock::time_point;
//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
// type Xxx::Méthode ( liste des paramètres )
// Algorithme :
//
//{
//} //----- Fin de Méthode
DateTime Measurement::getMeasureDate() const
{
    return this->measureDate;
} //----- Fin de getMeasureDate

Sensor* Measurement::getSensor() const
{
    return this->sensor;
} //----- Fin de getSensor

Attribute* Measurement::getAttribute() const
{
    return this->attribute;
} //----- Fin de getAttribute

double Measurement::getValue() const
{
    return this->value;
} //----- Fin de getValue

bool Measurement::getIsValid() const
{
    return this->isValid;
} //----- Fin de isvalid

void Measurement::setIsValid(bool valid)
{
    this->isValid = valid;
} //----- Fin de setIsValid
//------------------------------------------------- Surcharge d'opérateurs

//-------------------------------------------- Constructeurs - destructeur
Measurement::Measurement(DateTime a_mesureDate, Sensor* a_sensor, Attribute* an_attribute, double a_value): measureDate(a_mesureDate) ,sensor(a_sensor), attribute(an_attribute), value(a_value)
// Algorithme
{
    #ifdef MAP
        cout << "Appel au constructeur de <Measurement>" << endl;
    #endif
    isValid = true;
} //----- Fin de Measurement

//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées