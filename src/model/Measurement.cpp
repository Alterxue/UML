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

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
// type Xxx::Méthode ( liste des paramètres )
// Algorithme :
//
//{
//} //----- Fin de Méthode

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