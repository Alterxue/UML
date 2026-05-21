/*************************************************************************
                           TimeRange  -  description
                             -------------------
    début                : 08/05/2026
    copyright            : (C) 2026 par tautret
    e-mail               : tom.autret@insa-lyon.fr
*************************************************************************/

//---------- Interface de la classe <TimeRange> (fichier TimeRange.h) ----------------
#if ! defined ( TIMERANGE_H )
#define TIMERANGE_H

//--------------------------------------------------- Interfaces utilisées
#include <chrono>

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types
using DateTime = std::chrono::system_clock::time_point;
using Seconds = std::chrono::seconds;

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
    bool contains(const DateTime date) const;
    // Mode d'emploi : 
    // Indique si la date rentrée se trouve entre le début et la fin

    Seconds getDuration() const;
    // Mode d'emploi :
    // Retourne la durée (en s) entre le début et la fin précis à la seconde

    DateTime getStart() const;
    // Mode d'emploi :
    // Retourne le début du TimeRange

    DateTime getEnd() const;
    // Mode d'emploi :
    // Retourne la fin du TimeRange

//------------------------------------------------- Surcharge d'opérateurs

//-------------------------------------------- Constructeurs - destructeur
    TimeRange(const DateTime a_start, const DateTime a_end);
    // Mode d'emploi :
    // Constructeur du TimeRange avec une date de début et de fin

    ~TimeRange();
    // Mode d'emploi :
    // Destructeur du TimeRange

//------------------------------------------------------------------ PRIVE
protected:
//----------------------------------------------------- Attributs protégés
    DateTime start;
    DateTime end;
};

#endif // TIMERANGE_H