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

#include "Attribute.h"

class Sensor;

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types
using DateTime = std::chrono::system_clock::time_point;

//------------------------------------------------------------------------
// Rôle de la classe <Measurement>
// Représente une mesure avec sa date, le capteur qui l'a capté,
// le type de la mesure et sa valeur
//------------------------------------------------------------------------

class Measurement
{
//----------------------------------------------------------------- PUBLIC
public:
//----------------------------------------------------- Méthodes publiques

    DateTime getMeasureDate() const;
    Sensor* getSensor() const;
    Attribute* getAttribute() const;
    double getValue() const;
//------------------------------------------------- Surcharge d'opérateurs

//-------------------------------------------- Constructeurs - destructeur
    Measurement(DateTime a_measureDate, Sensor* a_sensor, Attribute* an_attribute, double a_value);

//------------------------------------------------------------------ PRIVE
protected:
//----------------------------------------------------- Attributs protégés
    DateTime measureDate;
    Sensor* sensor;
    Attribute* attribute;
    double value;
};

#endif