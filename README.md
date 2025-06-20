🔐 Projet Arduino : Jeu de Devinette pour Ouvrir un Coffre
🧠 Description
Ce projet consiste en un jeu de devinette sur Arduino. L'utilisateur doit deviner un nombre secret entre 0 et 20. S'il devine correctement trois fois, le "coffre" s'ouvre à l'aide de trois servomoteurs. En cas de trois erreurs, le coffre reste fermé. L'interaction se fait à l'aide de boutons, d'un écran LCD RGB, d’un buzzer pour le son et de servomoteurs pour l'action mécanique.

🎮 Fonctionnalités
Deviner un nombre secret avec des boutons UP/DOWN/VALIDATE.

Affichage LCD avec messages dynamiques (scrolling).

Retour sonore en cas de succès ou d’échec.

Ouverture du coffre en 3 étapes (1 servomoteur à chaque bonne réponse).

Fermeture définitive si 3 mauvaises réponses.

Feedback immédiat après chaque tentative.

📦 Matériel Utilisé
1x Arduino Uno (ou compatible)

1x Écran LCD RGB compatible Grove (rgb_lcd)

3x Servomoteurs SG90 (ou similaires)

1x Servomoteur pour fermeture

1x Buzzer

3x Boutons poussoirs

1x Résistance de tirage ou câblage en INPUT_PULLUP

Câblage divers, breadboard

Alimentation USB

📷 Schémas de câblage
Connexions principales (boutons, buzzer, servos, LCD) :

Vue d'ensemble du projet monté :

📌 Assurez-vous que les servomoteurs sont alimentés correctement (évitez d’alimenter plus de 2 servos directement depuis l’Arduino).

⚙️ Configuration des broches
Élément	Broche Arduino
Bouton UP	D5
Bouton DOWN	D6
Bouton VALIDER	D7
Buzzer	D3
Servo 1	D9
Servo 2	D10
Servo 3	D11
Servo de blocage	D12
LCD RGB	I2C (A4/A5)

🚀 Mise en route
Charger le sketch dans votre Arduino via l'IDE Arduino.

Vérifier que tous les périphériques sont bien connectés.

Le jeu démarre automatiquement à l’allumage.

Utiliser les boutons pour ajuster le score proposé.

Valider votre proposition avec le bouton de validation.

Tenter de trouver le bon nombre 3 fois pour gagner !

📝 Notes supplémentaires
Le nombre secret change après chaque tentative.

L’écran affiche des messages animés via scrolling.

Le jeu se termine dès que 3 bonnes ou 3 mauvaises réponses ont été données.

L’alimentation externe est recommandée si plusieurs servos sont utilisés en même temps.

📚 Auteurs & Crédits
Projet développé par:
Lionel
Valentin
Mathéo

Conçu dans un cadre scolaire.
