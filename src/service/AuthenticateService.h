/*************************************************************************
                           AuthenticateService -  description
                             -------------------
    début                : 19/05/2026
    copyright            : (C) 2026 par tautret
    e-mail               : tom.autret@insa-lyon.fr
*************************************************************************/

//---------- Interface de la classe <AuthenticateService> (fichier AuthenticateService.h) ----------------
#if ! defined ( AUTHENTICATESERVICE_H )
#define AUTHENTICATESERVICE_H 

//--------------------------------------------------- Interfaces utilisées
#include "../model/User.h"
#include "../model/Role.h"
#include "../model/GovernmentAgency.h"
#include "DataService.h"

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <AuthenticateService>
// Responsable de fournir une instance de `User` (ou d'une classe dérivée)
// correspondant à un id et à un Role donnés. Si pas d'id reconnu renvoie
// un pointeur null 
//------------------------------------------------------------------------

class AuthenticateService
{
//----------------------------------------------------------------- PUBLIC
public:
//----------------------------------------------------- Méthodes publiques
    PrivateUser* loginPrivate(DataContainer& dc, std::string& id);
    // Mode d'emploi :
    // Renvoie le PrivateUser correspondant à l'id si il existe et nullptr
    // sinon 

    Provider* loginProvider(DataContainer& dc, std::string& id);
    // Mode d'emploi :
    // Renvoie le Provider correspondant à l'id si il existe et nullptr
    // sinon 

    GovernmentAgency* loginGovernmentAgency(std::string& id);
    // Mode d'emploi :
    // Renvoie l'objet ' correspondant à l'id si il existe et nullptr
    // sinon 

//------------------------------------------------- Surcharge d'opérateurs

//-------------------------------------------- Constructeurs - destructeur
    AuthenticateService();

    ~AuthenticateService();
    
//------------------------------------------------------------------ PRIVE
protected:
//----------------------------------------------------- Méthodes protégées

//----------------------------------------------------- Attributs protégés
};

#endif // AUTHENTICATESERVICE_H