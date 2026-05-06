# AirWatcher - Application de Surveillance de la Qualité de l'Air

## Vue d'ensemble
Application de gestion et d'analyse des données de qualité de l'air collectées par des capteurs répartis sur un territoire. Cette application traite les données stockées en fichiers CSV et fournit des services statistiques et d'authentification.

---

## Architecture du projet

L'application est organisée en trois couches principales :

- **Model** : Classes représentant les entités métier
- **DAO (Data Access Object)** : Classes responsables de la gestion des données (chargement CSV, etc.)
- **Service** : Classes fournissant les fonctionnalités métier (statistiques, authentification, etc.)

---

## 📦 COUCHE MODEL - Classes métier

### `Attribute` - Description d'un type de mesure

**Rôle** : Représente un type de mesure d'air (O3, NO2, PM10, CO, etc.) avec ses propriétés.

#### Attributs protégés :
- `std::string attributeID` : Identifiant unique du type de mesure (ex: "O3", "NO2")
- `std::string unit` : Unité de mesure (ex: "μg/m³", "mg/m³")
- `std::string description` : Description textuelle (ex: "concentration d'ozone")

#### Méthodes publiques :
- `Attribute(const std::string a_attributeID, const std::string a_unit, const std::string a_description)`
  - Constructeur : initialise un nouvel attribut avec son ID, son unité et sa description
  - Paramètres : ID de l'attribut, unité de mesure, description
  - Utilisé lors du chargement des données depuis `attributes.csv`

---

### `Measurement` - Enregistrement d'une mesure

**Rôle** : Représente une mesure unique d'un capteur à une date/heure précise pour un type d'attribut donné.

#### Attributs protégés :
- `std::chrono::system_clock::time_point measureDate` : Timestamp précis de la mesure (année, mois, jour, heure, minute, seconde)
- `Sensor* sensor` : Pointeur brut vers le capteur ayant effectué la mesure
- `Attribute* attribute` : Pointeur brut vers le type d'attribut mesuré (ex: O3)
- `double value` : Valeur numérique de la mesure

#### Méthodes publiques :
- `Measurement(int annee, int mois, int jour, int heure, int minute, int seconde, Sensor* a_sensor, Attribute* an_attribute, double a_value)`
  - Constructeur : crée une mesure avec date/heure décomposées et pointers vers Sensor et Attribute
  - La date/heure sont converties en `system_clock::time_point` pour manipulation précise
  - Les pointers passés doivent pointer vers des objets valides pendant toute la durée de vie de la Measurement
  - Paramètres : composants de date (année, mois, jour, heure, minute, seconde), pointeur Sensor, pointeur Attribute, valeur

#### Notes d'implémentation :
- Utilise des **pointeurs bruts** plutôt que des références ou `shared_ptr` car :
  - Les Sensor et Attribute ont une durée de vie supérieure (chargés une fois au démarrage)
  - Plus léger en terme de performance
  - Pas de gestion complexe de propriété

---

### `Sensor` - Capteur de mesure (à implémenter)

**Rôle** : Représente un capteur physique installé sur le territoire, identifié par ses coordonnées géographiques.

#### Attributs protégés (à définir) :
- `std::string sensorID` : Identifiant unique du capteur
- `double latitude` : Latitude de localisation du capteur
- `double longitude` : Longitude de localisation du capteur
- `bool reliability` : État de fiabilité du capteur
- `std::vector<Measurement> measurements` : Mesures collectées par ce capteur

#### Méthodes publiques :
- `Sensor()` : Constructeur (à implémenter)
- `std::string getSensorID() const` : Retourne l'ID du capteur
- `void setReliability(bool reliability)` : Modifie l'état de fiabilité du capteur
- `int calculateDistance(double userLatitude, double userLongitude) const` : Calcule la distance entre le capteur et l'utilisateur

---

### `TimeRange` - Plage horaire (à implémenter)

**Rôle** : Représente une plage de temps (intervalle start - end) pour les analyses temporelles.

#### Attributs protégés (à définir) :
- (À définir selon les besoins)

---

### `User` - Utilisateur (classe parent à implémenter)

**Rôle** : Classe de base abstraite représentant un utilisateur du système.

#### Attributs protégés (à définir) :
- `std::string userID` : Identifiant unique de l'utilisateur
- `Role role` : Rôle de l'utilisateur (PRIVATE_USER, PROVIDER, GOVERNMENT_AGENCY)

#### Méthodes publiques :
- `User()` : Constructeur (à implémenter)
- `User(const User& unUser)` : Constructeur de copie
- `std::string getUserID() const` : Retourne l'ID utilisateur
- `User& operator=(const User& unUser)` : Opérateur d'affectation

---

### `PrivateUser` - Utilisateur privé (hérité de User à implémenter)

**Rôle** : Représente un citoyen qui consulte les données de qualité de l'air et gère des capteurs personnels.

#### Attributs protégés (à définir) :
- `int points` : Points de contribution/gamification du citoyen
- `std::list<Sensor> mySensors` : Liste des capteurs personnels de l'utilisateur

#### Méthodes publiques :
- `PrivateUser()` : Constructeur (à implémenter)
- `PrivateUser(const PrivateUser& unPrivateUser)` : Constructeur de copie
- `int getPoints() const` : Retourne le nombre de points
- `void incrementPoints(int pointsToAdd)` : Ajoute des points
- `void addSensor(const Sensor& sensor)` : Ajoute un capteur personnel
- `PrivateUser& operator=(const PrivateUser& unPrivateUser)` : Opérateur d'affectation

---

### `GovernmentAgency` - Agence gouvernementale (hérité de User à implémenter)

**Rôle** : Représente l'agence gouvernementale responsable de la surveillance et de la gestion du système.

#### Attributs protégés (à définir) :
- (Hérités de User)

#### Méthodes publiques :
- `GovernmentAgency()` : Constructeur (à implémenter)
- `GovernmentAgency(const GovernmentAgency& unGovernmentAgency)` : Constructeur de copie
- `void manageSystem()` : Gère les fonctionnalités principales du système
- `void flagSensors(Sensor& sensor)` : Signale un capteur comme défaillant ou peu fiable
- `GovernmentAgency& operator=(const GovernmentAgency& unGovernmentAgency)` : Opérateur d'affectation

---

### `Provider` - Fournisseur (à implémenter)

**Rôle** : Représente une entreprise ou organisation qui opère des purificateurs d'air (AirCleaner).

#### Attributs protégés (à définir) :
- `std::string providerID` : Identifiant unique du fournisseur
- `std::list<AirCleaner> myCleaners` : Liste des purificateurs gérés par ce fournisseur

#### Méthodes publiques :
- `Provider(std::string providerID)` : Constructeur avec ID du fournisseur
- `Provider(const Provider& unProvider)` : Constructeur de copie
- `std::list<AirCleaner> getMyCleaners(std::list<AirCleaner> cleaners) const` : Récupère les purificateurs gérés par ce provider
- `Provider& operator=(const Provider& unProvider)` : Opérateur d'affectation

---

### `AirCleaner` - Purificateur d'air (à implémenter)

**Rôle** : Représente un dispositif de purification d'air opéré par un fournisseur à une localisation spécifique.

#### Attributs protégés (à définir) :
- `std::string airCleanerID` : Identifiant unique du purificateur
- `std::string providerID` : ID du fournisseur propriétaire
- `double latitude` : Latitude de localisation
- `double longitude` : Longitude de localisation
- `DateTime startTime` : Date/heure d'activation
- `DateTime endTime` : Date/heure de désactivation (optionnel)
- `bool isOperational` : État opérationnel

#### Méthodes publiques :
- `AirCleaner()` : Constructeur (à implémenter)
- `AirCleaner(const AirCleaner& unAirCleaner)` : Constructeur de copie
- `bool isActive(DateTime time) const` : Vérifie si le purificateur est actif à un moment donné
- `std::string getProviderID() const` : Retourne l'ID du fournisseur
- `AirCleaner& operator=(const AirCleaner& unAirCleaner)` : Opérateur d'affectation

---

### `Role` - Énumération des rôles

**Rôle** : Énumération définissant les différents rôles d'utilisateur dans le système.

#### Valeurs :
- `PRIVATE_USER` : Citoyen consulant les données et gérant des capteurs personnels
- `PROVIDER` : Entreprise opérant des purificateurs d'air
- `GOVERNMENT_AGENCY` : Agence gouvernementale gérant le système

---

## 🗄️ COUCHE DAO - Accès aux données

### `CSVDataManager` (à implémenter)
Responsable du chargement et de la gestion des données CSV :
- Charge les fichiers : `attributes.csv`, `sensors.csv`, `measurements.csv`
- Stocke les `Attribute` dans un `std::map<std::string, Attribute>`
- Fournit des accesseurs pour récupérer les entités par ID

---

## ⚙️ COUCHE SERVICE - Logique métier

### `AuthenticateService` (à implémenter)
Service d'authentification des utilisateurs

### `SecurityService` (à implémenter)
Service de gestion des droits d'accès

### `DataService` (à implémenter)
Service de gestion des données

### `StatisticsService` (à implémenter)
Service de calcul de statistiques sur les mesures

### `AirWatcherSystem` (à implémenter)
Orchestrateur principal du système
