/*
AGRI-DEVELOPPEUSE - Prog-Racleur V1.0
https://github.com/agri-developpeuse/Prog-Racleur
*/


//Librairies pour l'ecran
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <EEPROM.h>

// Définition des paramètres de l'écran
#define SCREEN_WIDTH 128 // Largeur de l'écran en pixels
#define SCREEN_HEIGHT 64 // Hauteur de l'écran en pixels
#define OLED_RESET     -1 // Reset pin (-1 car inexistant)
#define SCREEN_ADDRESS 0x3C //adresse I2C
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Définition des pins d'I/O
const int okPin = 6; //bouton OK sur le pin 6
const int cancelPin = 5; //bouton cancel sur le pin 5
const int downPin = 4; //bouton down sur le pin 4
const int upPin = 3; //bouton up sur le pin 3
const int relayPin = 2; //commande du relais sur le pin 2

// Variables
int eepromDelay = 101; //variable de définition de la case de l'EEPROM qui stocke le délai entre deux départs en minutes
int eepromCycle = 102; //variable de définition de la case de l'EEPROM qui stocke le temps d'un cycle du racleur
int okState = 0; //variable pour le bouton OK
int cancelState = 0; //variable pour le bouton annuler
int downState = 0; //variable pour le bouton bas
int upState = 0; //variable pour le bouton haut
int pause = 0; //EEPROM.read(eepromPause); //variable qui sert a déterminer si le racleur est mis en pause
int cycle = EEPROM.read(eepromCycle); //variable pour la durée d'un cycle
unsigned long cyclems = cycle * 60000;
int startDelay = EEPROM.read(eepromDelay); //valeur entre deux départs en minutes stockée dans l'EEPROM (utilisé pour le paramètrage)
unsigned long startDelayms = startDelay * 6000;//Valeur stockée dans l'EEPROM en minutes * 60000ms (1 min) = délai en ms utilisé par le programme
unsigned long lastStart = 0; //mémorisation du timestamp du dernier départ
unsigned long nextStartTime = lastStart + startDelay; //calcul du timestamp du prochain départ.
unsigned long nextStart = nextStartTime - millis();
int menu = 0; //Variable pour définir quel menu est affiché à l'ecran
int principalvar = 1; //
int aff = 0; //
int menudelaivar = 0; //
int menucyclevar = 0; //
// Variables de temps
unsigned long secondes = 0;
unsigned long minutes = 0;
unsigned long heures = 0;
unsigned long millisecondes = 0;

String tempsrestant = ""; //variable pour stocker le temps restant


void setup() {
  //relai = sortie
  pinMode(relayPin, OUTPUT); 
  // boutons = entrée
  pinMode(okPin, INPUT_PULLUP);
  pinMode(cancelPin, INPUT_PULLUP);
  pinMode(upPin, INPUT_PULLUP);
  pinMode(downPin, INPUT_PULLUP);

   Serial.begin(115200); //lance la connexion port série

  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  delay(2000);
  //réinitialisation de l'écran
  display.clearDisplay();
  display.display();
  display.setTextColor(WHITE);
  
}

void checkButtons() //recherche de l'appui sur un bouton
{
  // read the state of the pushbutton value:
  okState = digitalRead(okPin);
  upState = digitalRead(upPin);
  downState = digitalRead(downPin);
  cancelState = digitalRead(cancelPin);
}

void pause1()
{
  
  display.clearDisplay();
  display.setTextSize(3);
  display.setCursor(20, 25);
  display.println("PAUSE");
  display.display();
  delay(500);
  display.clearDisplay();
  display.display();
  delay(500);
  checkButtons();
  if (okState == LOW) {pause = 0; principalvar = 1;}
}

void menu1() //affichage du menu
{
  while (menu == 1){
    while (aff == 0){
  display.clearDisplay();
  display.setTextSize(2);
  display.setCursor(40,0);
  display.println("MENU");
  display.setCursor(20, 30);
  display.println("Pause");
  display.display();
  aff = 1;
  delay (300);}
  checkButtons();
  if (okState == LOW) {pause = 1; menu = 0; aff = 0;}
  else {if (cancelState == LOW) {menu = 0; principalvar = 1; aff = 0;}
  else {if (downState == LOW){menu = 2; aff = 0;}}}}
  
  while (menu == 2) {
    while (aff == 0) {
    display.clearDisplay();
    display.setTextSize(2);
    display.setCursor(40,0);
    display.println("MENU");
    display.setCursor(20,30);
    display.println("Delai");
    display.display();
    aff = 1;
    delay(300);}
    checkButtons();
    if (okState == LOW) {menu = 0; menudelaivar = 1; aff = 0;}
    else {if (cancelState == LOW) {menu = 0; aff = 0; principalvar = 1;}
    else {if (downState == LOW) {menu = 3; aff = 0;}
    else {if (upState == LOW) {menu = 1; aff = 0;}}}}


  }
  while (menu == 3) {
    while (aff == 0) {
    display.clearDisplay();
    display.setTextSize(2);
    display.setCursor(40,0);
    display.println("MENU");
    display.setCursor(20,30);
    display.println("Cycle");
    display.display();
    aff = 1;
    delay(300);}
    checkButtons();
    if (okState == LOW) {menu = 0; menucyclevar = 1; aff = 0;}
    else {if (cancelState == LOW) {menu = 0; aff = 0; principalvar = 1;}
    else {if (upState == LOW) {menu = 2; aff = 0;}}}


  }
}

void menuDelai() //affichage du menu délai
{
display.clearDisplay();
display.setTextSize(2);
display.setCursor(20,0);
display.println("Delai");
display.setTextSize(3);
display.setCursor(20,30);
display.println(startDelay);
display.display();
delay(200);
checkButtons();
if (upState == LOW) {startDelay = startDelay + 1;}
if (downState == LOW) {startDelay = startDelay - 1;}
if (cancelState == LOW) {startDelay = EEPROM.read(eepromDelay);menu = 2; menudelaivar = 0;}
if (okState == LOW) {EEPROM.write(eepromDelay, startDelay); menudelaivar = 0; menu = 2; nextStartSchedule();}
}


void menuCycle() //affichage du paramétrage de la durée d'un cycle
{
display.clearDisplay();
display.setTextSize(2);
display.setCursor(20,0);
display.println("Cycle");
display.setTextSize(3);
display.setCursor(20,30);
display.println(cycle);
display.display();
delay(200);
checkButtons();
if (upState == LOW) {cycle = cycle + 1;}
if (downState == LOW) {cycle = cycle - 1;}
if (cancelState == LOW) {cycle = EEPROM.read(eepromCycle);menu = 3; menudelaivar = 0;}
if (okState == LOW) {EEPROM.write(eepromCycle, cycle); menucyclevar = 0; menu = 3; cyclems = cycle * 60000; nextStartSchedule();}
}

void nextStartSchedule()
{
  startDelayms = startDelay * 60000;
  lastStart = millis();
  nextStartTime = millis() + startDelayms + cyclems;
}

void start()
{
  digitalWrite(relayPin, HIGH);
  nextStartSchedule();
  delay (1250);
  digitalWrite(relayPin, LOW);
}

void remainingTime() 
{
  tempsrestant = "";
  nextStart = nextStartTime - millis();
  millisecondes = nextStart;
  secondes = nextStart / 1000;
  minutes = secondes / 60;
  heures = minutes / 60;
  millisecondes %= 1000;
  secondes %= 60;
  minutes %= 60;
  heures %= 24;
  if (heures > 0) {
    tempsrestant = String(heures) + ":";
  } else {tempsrestant = "00:";}

  if (minutes < 10) {
    tempsrestant += "0";
  }
  tempsrestant += String(minutes);
}

void principal() //affichage du temps avant prochain pasage
{
  remainingTime() ;
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(10,0);
  display.println("Prochain depart :");
  display.setTextSize(3);
  display.setCursor(20,30);
  display.println(tempsrestant);
  display.display();
  if (millis() >= nextStartTime) {start();}
  delay(300); // a remplacer par millis()
  
  checkButtons();
  if (okState == LOW) {menu = 1; principalvar = 0;}

}


void loop() {
while (pause == 1) {pause1();}
while (principalvar == 1) {principal();}
while (menu != 0) {menu1();}
while (menudelaivar == 1) {menuDelai();}
while (menucyclevar == 1) {menuCycle();}
}
