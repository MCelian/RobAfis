# Robafis

Ce projet contient le firmware pour un robot basé sur la carte **MegaPi de MakeBlock**, développé en utilisant l'écosystème **PlatformIO** sur **VS Code**.

L'architecture est centrée autour d'une classe `Robot` qui agit comme un contrôleur principal, gérant des sous-systèmes comme le `Chassis` et le `Bras`. Cette approche favorise une meilleure organisation du code, une maintenance simplifiée et résout les problèmes courants de "multiple definition" avec les bibliothèques Arduino.

---

## 🏛️ Architecture Logicielle

Le projet est structuré en plusieurs classes pour séparer les responsabilités :

*   **`Robot`** : La classe principale qui orchestre l'ensemble du robot. C'est la seule classe qui interagit directement avec les moteurs via la bibliothèque `MeMegaPi.h`. Elle expose des méthodes de haut niveau comme `avancer()` ou `leverBras()`.
*   **`Chassis`** : Une classe qui représente la base mobile du robot. Elle ne contient pas de logique de contrôle moteur directe mais stocke les pointeurs vers les moteurs correspondants.
*   **`Bras`** : Similaire au `Chassis`, cette classe représente le bras motorisé du robot.

Cette conception, où `Robot.cpp` est le seul fichier à inclure `MeMegaPi.h`, est cruciale pour éviter les erreurs de "linker" (éditeur de liens) dues à des définitions multiples de variables globales présentes dans certaines bibliothèques Arduino.

---

## 🚀 Utilisation

Le fichier `main.cpp` devient très simple. Il suffit de créer une instance de la classe `Robot` et d'appeler ses méthodes pour contrôler le robot :

```cpp
Robot robot;

void loop() {
  robot.avancer();
  delay(1000);
  robot.leverBras();
  delay(1000);
  robot.arreterAvancement();
  robot.arreterBras();
}
```

## 💻 1. Prérequis et Configuration

Pour développer et téléverser le code, vous avez besoin de l'environnement de développement suivant :

### 1.1. 💾 VS Code et Extension PlatformIO

1.  **Installer Visual Studio Code (VS Code)** : Téléchargez et installez VS Code si ce n'est pas déjà fait.
2.  **Installer l'Extension PlatformIO** : Ouvrez VS Code, allez dans l'onglet Extensions (ou appuyez sur `Ctrl+Shift+X`) et recherchez **`PlatformIO IDE`**. Installez cette extension. Elle est essentielle pour compiler, gérer les librairies et téléverser le code sur la MegaPi.
    

### 1.2. 🛠️ Dépendances de Librairies

Les librairies externes sont récupérées depuis le **Registre de PlatformIO** : **https://registry.platformio.org/**

Le projet utilise les dépendances de librairies suivantes, qui sont gérées automatiquement par PlatformIO via le fichier `platformio.ini` :

* **MakeBlock** : Contient les classes spécifiques à la MegaPi, comme `MeMegaPiDCMotor` et `MeMegaPi.h`.

Assurez-vous que la section `lib_deps` dans `platformio.ini` est correctement configurée :

```ini
[env:megaatmega2560]
...
lib_deps =
    makeblock-official/MakeBlockDrive@^3.27
     ; Librairie officielle de MakeBlock