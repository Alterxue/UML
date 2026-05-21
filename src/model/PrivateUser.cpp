/*************************************************************************
                           User  -  description
                             -------------------
    début                : 05/05/2026
    copyright            : (C) 2026 par aeliasmene
    e-mail               : alex.eliasmenet@gmail.com
*************************************************************************/

//---------- Réalisation de la classe <PrivateUser> (fichier PrivateUser.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
#include <iostream>
#include <string>
using namespace std;

//------------------------------------------------------ Include personnel
#include "PrivateUser.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques

void PrivateUser::incrementPoints(int pointsToAdd)
{
    points += pointsToAdd;
}

void PrivateUser::addSensor(Sensor* sensor)
{
    mySensors.push_back(sensor);
}

int PrivateUser::getPoints() const
{
    return points;
}

const std::vector<Sensor*>& PrivateUser::getSensorsList() const
{
    return mySensors;
}

//------------------------------------------------- Surcharge d'opérateurs



//-------------------------------------------- Constructeurs - destructeur
PrivateUser::PrivateUser (string userID, Role role) : User(userID, role), points(0){}

PrivateUser::~PrivateUser ()
{
#ifdef MAP
    cout << "Appel au destructeur de <PrivateUser>" << endl;
#endif
} //----- Fin de ~PrivateUser


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées