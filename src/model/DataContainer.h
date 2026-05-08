// Contientra les données
// Lui qui fait la construction et la destruction de tout les objets de données

// Colections
// Attribute : map<string, Attribute*> (seulement 4 instances, string : attributeID)
// Sensors   : map<string, Sensor*> (string : sensorID)
// Users     : map<string, User*> (string : userID)
// AirCleaner: vector<AirCleaner*> (accès par parcours)
// Provider  : map<string, Provider*> (string : providerID)

// PipeLine de chragement des données
// 1) attributes.csv  : pour les attributs qui dépendent de personne
// 2) sensors.csv     : création des censors, pas encore de mesures ni de proprio
// 3) user.csv        : On créé les privateUser, on cherche le ou les sensors qu'il possède puis user->addSensor(s), s->setOwner(user)
// 4) provider.csv    : On créé les provider
// 5) cleaner.csv     : On crée les aircleaners et on ajoute au provider correspondant
// 7) measurement.csv : pour chaque mesure on récupère le pointeur de l'attribut et du capteur, on crée le mesurement et on l'ajoute au sensore qui va bien

// Pipeline de destruction
// 1) User + Provider
// 2) AirCleaner
// 3) Sensors, les measurement seront détruits avec
// 4) Attribute