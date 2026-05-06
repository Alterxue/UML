/*************************************************************************
                           AuthenticateService -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Interface de la classe <AuthenticateService> (fichier AuthenticateService.h) ----------------
#if ! defined ( AUTHENTICATESERVICE_H )
#define AUTHENTICATESERVICE_H 

//--------------------------------------------------- Interfaces utilisées
#include "../model/User.h"
#include "../model/Role.h"
#include "DataService.h"

// Forward-declare DataService to avoid heavy coupling here; AuthenticateService
// should call DataService to retrieve raw data from CSVs. The implementation
// will contain TODOs where DataService integration is required.
class DataService;

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <AuthenticateService>
//
// Responsable de fournir une instance de `User` (ou d'une classe dérivée)
// correspondant à un `id` et à un `Role` donnés. Ne doit pas parser les CSV
// directement : déléguer à `DataService`.
//------------------------------------------------------------------------

class AuthenticateService
{
//----------------------------------------------------------------- PUBLIC
public:
    bool login(const std::string& id, Role role, User& outUser);
    // Mode d'emploi :
    //
    // Contrat :
    //
};

#endif