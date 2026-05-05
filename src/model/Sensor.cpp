/*************************************************************************
                           Sensor  -  description
                             -------------------
    début                : 05/05/2026
    copyright            : (C) 2026 par aeliasmene
    e-mail               : alex.eliasmenet@gmail.com
*************************************************************************/

//---------- Réalisation de la classe <Sensor> (fichier Sensor.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
#include <iostream>
#include <string>
using namespace std;

//------------------------------------------------------ Include personnel
#include "Sensor.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques

string Sensor::getSensorID() const
{
    return this->sensorID;
}

void Sensor::setReliability(bool reliability)
{
    this->isReliable = reliability;
}

//------------------------------------------------- Surcharge d'opérateurs
Sensor & Sensor::operator = (const Sensor & unSensor)
// Algorithme :
//
{
} //----- Fin de operator =


//-------------------------------------------- Constructeurs - destructeur
Sensor::Sensor (const Sensor & unSensor)
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au constructeur de copie de <Sensor>" << endl;
#endif
} //----- Fin de Sensor (constructeur de copie)



Sensor::Sensor(string sensorID, string lattitude, string longitude, bool isReliable) : sensorID(sensorID), lattitude(stod(lattitude)), longitude(stod(longitude)), isReliable(isReliable){}


Sensor::~Sensor ()
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au destructeur de <Sensor>" << endl;
#endif
} //----- Fin de ~Sensor


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées
