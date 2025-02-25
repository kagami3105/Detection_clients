/*
  Titre      : Projet pour détecter le nombre de clients qui entre dans une boutique
  Auteur     : Boladji ODELOUI
  Date       : 24/02/2025
  Description: Le programme détecte le nombre de clients qui entre dans une boutique
  Version    : 0.0.1
*/

#include <Wire.h>
#include <DFRobot_RGBLCD1602.h>

// Initialisation de l'écran LCD
DFRobot_RGBLCD1602 lcd(0x2D, 16, 2); // Adresse I2C avec 16 colonnes et 2 lignes sur l'écran

// Définition des broches
#define LED_PIN 6   // Broche pour la LED
#define TAPIS_PIN 7 // Broche pour le capteur de pression au sol

// Les variables globales
int counter = 0;        // Le compteur du client
int nbr_total = 0; // Nombre total de clients entré dans la boutique
bool etat_bouton = LOW; // L'état du capteur de pression au sol
bool etat_led = false;  // L'état initial de la LED

void setup()
{
  Serial.begin(9600); // Initialisation de la communication série

  // La configuration de l'écran LCD
  lcd.init();
  lcd.print("Clients: ");
  lcd.setCursor(9, 0);
  lcd.print(counter);
  lcd.setCursor(0, 1);
  lcd.print("Sorties: ");
  lcd.setCursor(9, 1);
  lcd.print(nbr_total);
  lcd.setCursor(11, 1);
  lcd.print("   OFF");

  // Configuration des broches
  pinMode(LED_PIN, OUTPUT);
  pinMode(TAPIS_PIN, INPUT);
}

void loop()
{
  // Condition pour déterminer s'il y a un nouveau client qui est entré
  if (digitalRead(TAPIS_PIN) == HIGH && etat_bouton == LOW)
  {
    counter = counter + 1; // Incrémentation du compteur
    //delay(1000);           // Temps d'attente après l'incrémentation du compteur
    nbr_total = counter / 2;
    // Mise à jour de l'Affichage du compteur sur l'écran LCD
    lcd.setCursor(9, 0);
    lcd.print("   "); // Efface l'ancien nombre pour le compteur
    lcd.setCursor(9, 0);
    lcd.print(counter); // Affiche le compteur

    lcd.setCursor(9, 1);
    lcd.print("   "); // Efface l'ancien nombre pour le compteur
    lcd.setCursor(9, 1);
    lcd.print(nbr_total); 
  }
  // Mise à jour de l'état précédent du capteur de pression au sol
  etat_bouton = digitalRead(TAPIS_PIN);

  // Condition pour la gestion de l'état de la LED

  if (digitalRead(TAPIS_PIN) == HIGH)
  {
    digitalWrite(LED_PIN, LOW); // Eteindre la LED
    etat_led = false;
  }
  else
  {
    digitalWrite(LED_PIN, HIGH); // Allumer la LED
    etat_led = true;
  }

  // Mise à jour de l'affichage de l'État de la LED sur l'écran LCD
  lcd.setCursor(11, 1);
  if (etat_led == false)
  {
    lcd.print("  ON ");
  }
  else
  {
    lcd.print("  OFF");
  }
}
