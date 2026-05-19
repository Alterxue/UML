/*************************************************************************
                           AirWatcherSystem  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Réalisation de la classe <AirWatcherSystem> (fichier AirWatcherSystem.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include <iostream>

//------------------------------------------------------ Include personnel
#include "AirWatcherSystem.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
// Nom de la méthode
// Algorithme :
//
// {
// } //----- Fin de getInstance



//------------------------------------------------- Surcharge d'opérateurs

//-------------------------------------------- Constructeurs - destructeur
AirWatcherSystem::AirWatcherSystem ()
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au constructeur <AirWatcherSystem>" << endl;
#endif
} //----- Fin de AirWatcherSystem 


AirWatcherSystem::~AirWatcherSystem ( )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au destructeur de <AirWatcherSystem>" << endl;
#endif
} //----- Fin de ~AirWatcherSystem


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées

