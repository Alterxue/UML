/*************************************************************************
                           Attribute  -  description
                             -------------------
    début                : 08/05/2026
    copyright            : (C) 2026 par tautret
    e-mail               : tom.autret@insa-lyon.fr
*************************************************************************/

//---------- Interface de la classe <Attribute> (fichier Attribute.h) ----------------
#if ! defined ( TIMERANGE_H )
#define TIMERANGE_H

//--------------------------------------------------- Interfaces utilisées
#include <chrono>

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <TimeRange> : 
// Encaptulation de la logique métier de manipulation des durées
// et du temps
//------------------------------------------------------------------------

class TimeRange
{
//----------------------------------------------------------------- PUBLIC
public:
//----------------------------------------------------- Méthodes publiques
    bool contains(const std::chrono::system_clock::time_point date);
    // Mode d'emploi : 
    // Indique si la date rentrée se trouve entre le début et la fin

    std::chrono::seconds getDuration();
    // Mode d'emploi :
    // Retourne la durée (en s) entre le début et la fin précis à la seconde


//------------------------------------------------- Surcharge d'opérateurs

//-------------------------------------------- Constructeurs - destructeur
    TimeRange(const std::chrono::system_clock::time_point a_start, const std::chrono::system_clock::time_point a_end);
    // Mode d'emploi :
    // Constructeur du TimeRange avec une date de début et de fin

    ~TimeRange();
    // Mode d'emploi :
    // Destructeur du TimeRange

//------------------------------------------------------------------ PRIVE
protected:
//----------------------------------------------------- Attributs protégés
    std::chrono::system_clock::time_point start;
    std::chrono::system_clock::time_point end;
};

#endif // TIMERANGE_H