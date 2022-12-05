/*
  Titre      : DEMO SENSOR DFR0026 - MKR 1000 - Thingsboard
  Auteur     : KOUBELAN RICHARD AKPAGNI
  Date       : 05/12/2022
  Description: lecture du capteur de lumière DFR0026 et envoie de cette valeur a une fréquences spécifique 
               sur la plateforme IDO Thingsbaord
  Version    : 0.0.1
*/

#include <Arduino.h>
#include "WIFIConnector_MKR1000.h"
#include "MQTTConnector.h"



void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600); // Activation du port série pour affichage dans le moniteur série

  wifiConnect(); // Branchement au réseau WIFI
  MQTTConnect(); // Branchement au broker MQTT

  pinMode(A1, INPUT); // Déclaration de la broche A1 en entrée
}

void loop() {
  // put your main code here, to run repeatedly:
      int data; // déclaration de la variable en entier qui va enregistrer la valeur signal lue 
      double valueLux;

      data=analogRead(A1);   //Lire la valeur du signal du capteur  sur le branche analogique A1 et enregistre cette valeur dans la variable 
      
      /*
      Par défaut, sur le Arduino MKR1000, la lecture d'une broche analogue donneras une valeur de 0 a 1023.
      Nous pouvons alors utilisé la règle de 3 pour obtenir la tension lu par la broche analogue
      c'est-à-dire, sachant qu'une lecture de 1023 est égale a 5V, par regle de 3,
      la tension sera donnè par Tension = (lecture *5)/1023
  */
      valueLux =(data*5)/1023;
      
      Serial.println(valueLux);//Affiche la valeur du signal lue au moniteur Serial et retourne à la ligne

       appendPayload("Valeur d'illumination en Lux", valueLux); // Ajout de la donnée température au message MQTT
       sendPayload();                                  // Envoie du message via le protocole MQTT
      delay(1000); //attendre un delais de 1s
}
