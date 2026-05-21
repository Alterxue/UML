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
#include <chrono>

//------------------------------------------------------ Include personnel
#include "TimeRange.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
bool TimeRange::contains(const DateTime date) const
{
    return (start<=date && date<=end);
} //----- Fin de contains

Seconds TimeRange::getDuration() const
{
    return chrono::duration_cast<Seconds>(end - start);
} //----- Fin de getDuration

DateTime TimeRange::getStart()
{
    return start;
} //----- Fin de getStart

DateTime TimeRange::getEnd()
{
    return end;
} //----- Fin de getEnd

//------------------------------------------------- Surcharge d'opérateurs

//-------------------------------------------- Constructeurs - destructeur
TimeRange::TimeRange(const DateTime a_start, const DateTime a_end): start(a_start), end(a_end)
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