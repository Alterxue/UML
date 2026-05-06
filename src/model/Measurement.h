/*************************************************************************
                           Measurement  -  description
                             -------------------
    début                : 06/05/2026
    copyright            : (C) 2026 par tautret
    e-mail               : tom.autret@insa-lyon.fr
*************************************************************************/

//---------- Interface de la classe <Measurement> (fichier Measurement.h) ----------------
#if ! defined ( MEASUREMENT_H )
#define MEASUREMENT_H

//--------------------------------------------------- Interfaces utilisées
#include <chrono>

#include "Sensor.h"
#include "Attribute.h"

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <Measurement>
//
//
//------------------------------------------------------------------------

class Measurement
{
//----------------------------------------------------------------- PUBLIC
public:
//----------------------------------------------------- Méthodes publiques

//-------------------------------------------- Constructeurs - destructeur
    Measurement(int annee, int mois, int jour, int heure, int minute, int seconde, Sensor& a_sensor, Attribute& an_attribute, double a_value);

//------------------------------------------------------------------ PRIVE
protected:
//----------------------------------------------------- Attributs protégés
    std::chrono::system_clock::time_point measureDate;
    Sensor& sensor;
    Attribute& attribute;
    double value;
};

#endif