/*************************************************************************
                           Attribute  -  description
                             -------------------
    début                : 08/05/2026
    copyright            : (C) 2026 par tautret
    e-mail               : tom.autret@insa-lyon.fr
*************************************************************************/

//---------- Réalisation de la classe <TimeRange> (fichier TimeRange.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include <iostream>
#include <string>
#include <chrono>

//------------------------------------------------------ Include personnel
#include "TimeRange.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
// type Xxx::Méthode ( liste des paramètres )
// Algorithme :
//
//{
//} //----- Fin de Méthode

bool TimeRange::contains(const chrono::system_clock::time_point date)
{
    return (start<=date && date<=end);
} //----- Fin de contains

chrono::seconds TimeRange::getDuration()
{
    return chrono::duration_cast<chrono::seconds>(end - start);
} //----- Fin de getDuration

//------------------------------------------------- Surcharge d'opérateurs

//-------------------------------------------- Constructeurs - destructeur
TimeRange::TimeRange(const chrono::system_clock::time_point a_start, const chrono::system_clock::time_point a_end): start(a_start), end(a_end)
{
    #ifdef MAP
        cout << "Appel au constructeur de <Attribute>" << endl;
    #endif
} //----- Fin de TimeRange

TimeRange::~TimeRange()
{
    #ifdef MAP
        cout << "Appel au destructeur de <TimeRange>" << endl;
    #endif
} //----- Fin de ~TimeRange

//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées