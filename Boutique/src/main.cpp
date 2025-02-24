#include <Wire.h>
#include <DFRobot_RGBLCD1602.h>

DFRobot_RGBLCD1602 lcd(0x2D, 16, 2);

int ledPin = 6;
int inputPin = 7;
int clientCount = 0;
bool lastButtonState = LOW;
bool ledState = false;

void setup()
{
  Serial.begin(115200);
  lcd.init();
  lcd.print("Clients: ");
  lcd.setCursor(9, 0);
  lcd.print(clientCount);
  lcd.setCursor(0, 1);
  lcd.print("LED: OFF"); // Affiche l'état initial de la LED
  pinMode(ledPin, OUTPUT);
  pinMode(inputPin, INPUT);
}

void loop()
{
  int val = digitalRead(inputPin);

  // Mise à jour du compteur de clients quand le bouton est pressé
  if (val == HIGH && lastButtonState == LOW)
  {
    clientCount++;
    lcd.setCursor(9, 0);
    lcd.print("    ");
    lcd.setCursor(9, 0);
    lcd.print(clientCount);
  }

  lastButtonState = val;

  // Contrôle de l'état de la LED et mise à jour de l'affichage
  if (val == HIGH)
  {
    digitalWrite(ledPin, LOW);
    ledState = false; // La LED est éteinte
  }
  else
  {
    digitalWrite(ledPin, HIGH);
    ledState = true; // La LED est allumée
  }

  // Affiche l'état de la LED
  lcd.setCursor(5, 1);
  if (ledState)
  {
    lcd.print(" OFF ");
  }
  else
  {
    lcd.print("ON  ");
  }
}
