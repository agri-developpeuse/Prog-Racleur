# Prog-Racleur
Programmateur pour un racleur de bâtiment agricole

## Détails
Voici un projet que j'ai créé chez un ancien patron pour automatiser un vieux racleur qui n'avait pas de programmateur

## Materiel
- Une grande boite de dérivation pour mettre tout le système dans un environnement étanche (pour ma part je l'ai monté dans la laiterie donc environnement humide)
- un Arduino nano
- 1 relais 5VDC
- Un écran OLED 0.96" I2C
- Un peu de cable électrique (2G 2.5mm²)
- Des cables dupont
- 4 boutons 

## Librairies arduino
à installer avant de compiler le code dans Arduino IDE
https://github.com/adafruit/Adafruit-GFX-Library
https://github.com/adafruit/Adafruit_SSD1306

## Montage 
Pour ma part, j'ai fait le choix de découper une ouverture de la taille de l'écran dans la boite de dérivation afin qu'il soit visible sans avoir besoin de tout ouvrir à chaque fois, et de percer 4 trous Ø13 pour y inserer les boutons avant soudure des fils et branchement a l'arduino.

J'ai fixé l'arduino et le relais au fond de la boite de dérivation avec un pistolet à colle chaude (c'est pas la meilleure des solutions mais au moins ça tient).


On connecte maintenant l'ensemble à l'arduino

### Relais
DC+ sur un pin 5V
DC- sur un pin GND
IN sur le pin D2

### Boutons 
Tous les boutons sont reliés sur une broche 3v3 d'un côté
L'autre côté est relié de la façon suivante :
- OK sur D6
- Annuler sur D5
- Haut sur D3
- Bas sur D4

### Ecran
Le + de l'écran doit être relié suivant votre modèle soit sur un pin 5V soit sur un pin 3.3V
le - ou GND sur un pin GND
SDA sur D18
SCL sur D19

### La commande du racleur 
ATTENTION ! Penser à couper l'alimentation électrique du racleur pendant l'intervention pour éviter des blessures voire la mort !!!

Il ne reste plus qu'a brancher le relais sur la commande du racleur : 
COM d'un côté du bouton de la commande de marche avant
NC de l'autre côté 

On peut maintenant remettre le courant

## Mise en service du système
Brancher l'arduino à l'ordinateur et téléverser le code dessus. Une fois que l'arduino redémarre, si tout à fonctionné, on voit l'écran s'allumer, le racleur doit partir et le temps restant avant le prochain départ doit s'afficher sur l'écran.

On peut maintenant débrancher l'arduino de l'ordinateur et le rebrancher sur une prise standard.

## Parametrage
La dernière étape est de parametrer le système selon vos besoins : 
- Premièrement, chronometrer le temps qu'il faut au racleur pour faire un cycle aller-retour
- Ensuite, en utilisant les boutons haut et bas, trouver le menu "CYCLE" puis y entrer avec le bouton OK
- Changer la valeur présente par le temps chronometré (en minutes) puis valider en appuyant sur OK
- Ensuite aller dans le menu Délai. Le temps affiché dans ce menu correspond au temps entre 2 passages du racleur. Le changer selon vos besoins puis valider avec OK.

Si vous avez besoin d'arrêter le racleur (changement de chaine, paillage, etc...), aller dans le menu Pause puis appuyer sur OK. L'inscription "PAUSE" se met a clignoter sur l'écran, ce qui signifie que le racleur ne partira pas sans intervention de l'utilisateur. Pour sortir du mode pause, appuyer sur OK, l'ecran affiche alors le temps restant avant le prochain départ, le racleur se lancera automatiquement à la fin de ce délai.

J'espère que ce projet vous aidera, de mon côté j'essayerai de détailler un peu plus la démarche, et d'ajouter des photos et des schémas pour que le montage soit plus facile à comprendre et à réaliser.
