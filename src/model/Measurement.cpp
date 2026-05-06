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
using namespace std::chrono;

#include <chrono>
#include <iostream>

//------------------------------------------------------ Include personnel
#include "Measurement.h"

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
Measurement::Measurement(int annee, int mois, int jour, int heure, int minute, int seconde, Sensor* a_sensor, Attribute* an_attribute, double a_value): sensor(a_sensor), attribute(an_attribute), value(a_value)
// Algorithme :
// On vient créer une date calendrier
// On va la convertir en nombre de jours (sys_days)
// On va ajouter ensuite les heures minutes secondes puis créer le time_point final précis à la seconde
{
    year y = year(annee);
    month m = month(mois);
    day d = day(jour);
    year_month_day calendarDate = y/m/d;

    sys_days sd = sys_days(calendarDate);

    hours h = hours(heure);
    minutes mi = minutes(minute);
    seconds s = seconds(seconde);

    measureDate = sd + h + mi + s; 

    #ifdef MAP
        cout << "Appel au constructeur de <Measurement>" << endl;
    #endif
} //----- Fin de Measurement

//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées