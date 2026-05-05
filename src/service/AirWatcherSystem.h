#ifndef AIRWATCHERSYSTEM_H
    #define AIRWATCHERSYSTEM_H

    #include <string>

    #include "DataService.h"
    #include "StatisticsService.h"
    #include "SecurityService.h"
    #include "../model/User.h"

    class AirWatcher 
    {
        public:
            //----------------------------------------------------- Méthodes publiques
            AirWatcher getInstance();
            bool login(std::string userID, std::string password);
            void logout();

            //-------------------------------------------- Constructeurs - destructeur
            AirWatcher();
            ~AirWatcher(); 

        protected:
            User currentUser;
            StatisticsService statsService;
            SecurityService securityService;
            DataServcie dataService;
    };
#endif