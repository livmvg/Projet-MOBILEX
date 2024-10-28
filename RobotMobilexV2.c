/*===================================================================
//Nom du Fichier : MobilexV2.c
//Auteur : AKBAL Lyna & MAVOUNGOU Emmanuel
//Date de création : 17 MARS 2022
//Version :  V2
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//Description :  C’est un système mobile roulant (composé principalement d’une brique LEGO,un capteur infrarouge et d'une télécommande),
//le système devra être piloté grâce à une télécommande sans fil qui fonctionne grâce au capteur à infrarouge et il autorise
//deux modes de fonctionnement : le mode «  parking manuel » et le mode « parking automatique » qui peuvent être choisis par défaut.
//D’une part, ce système peut circuler sur un circuit à obstacle en direction d’un mur en étant piloté par un opérateur via une série de combinaisons d’appui sur les boutons de la
//télécommande
//D’autre part, il peut se garer dans une zone de parking (parallèlement au mur) selon ses deux modes:
//- manuellement, l’opérateur le gare en faisant la combinaison associée avec la télécommande.
//- automatiquement, il se gare seul grâce au capteur ultrason qui détecte au préalable le mur au bout d’une certaine distance limite.
//-------------------------------------------------------------------------------------------------------------------
MANUEL D’UTILISATION VERSION 2 :
//Démarrage :
//-On allume la brique Lego
//-On lance le programme (On compile)
//-On accède au mode manuel en appuyant simultanément
//sur les boutons gauche et droit de la brique.
//-Pour changer vers le mode Automatique, il faut appuyer sur le bouton du milieu (bouton d'entrée)
//Fonctionnement : Pour un droitier
//MODE MANUEL :
//-On appuie sur les boutons droit et gauche pour mettre le mode manuel
//-Pour avancer : Appuyer sur le bouton bleu en haut
//-Pour reculer(marche arrière) :  Appuyer sur le bouton bleu en bas
//-Pour aller à droite : Appuyer simultanément sur les boutons bleu en haut et rouge en haut
//-Pour aller à gauche :Appuyer simultanément sur les boutons bleu en bas et rouge en bas
//-Pour le parking Manuel : Appuyer simultanément sur les  boutons bleu en bas et rouge en haut
//MODE AUTOMATIQUE :
//-Ici on utilisera un capteur ultrason
//-On appuie sur les bouton du milieu(Bouton d’entrée) pour passer du mode manuel au mode automatique
//-Pour avancer : Appuyer sur le bouton bleu en haut
//-Pour reculer(marche arrière) :  Appuyer sur le bouton bleu en bas
//-Pour aller à droite : Appuyer simultanément sur les boutons bleu en haut et rouge en haut
//-Pour aller à gauche :Appuyer simultanément sur les boutons bleu en bas et rouge en bas
//-Pour le parking Automatique : Ici on verra l’utilité du capteur ultrason
//-Il s'enclenche naturellement dès que le capteur sens un obstacle (ici le mur) a moins de 20 cm
// -------------------------------------------------------------
// A noter :
// - le capteur à infrarouge S1 est sur l'entrée 1
// - le capteur ultrason S4 est sur l'entrée 4
// - le moteur A est sur la sortie A
// - le moteur C est sur la sortie C
//===============================================================*/


task main()
{

  SensorType[S1] = sensorEV3_IRSensor;//capteur infrarouge
  SensorType[S4] = sensorEV3_Ultrasonic;//capteur ultrason
  float fDistance =0;
  float n1;
  float n2;
  double d1;
  double d2;
  double df;
  int mode=0;

  // BOUCLE DE BASE (DEMARRAGE) SYSTEME
  while(getButtonPress(buttonLeft)==false || getButtonPress(buttonRight)==false){ //tant que l'un des boutons de gauvhe et de droie de la brique LEGO ne sera pas appuyé, le boucle de démarrage sera enclenchée
  	            displayCenteredTextLine(4,"Bienvenue Mobilex !!");// affichage à la ligne 4 du message de démarrage "Bienvebue Mobilex"
  }

// BOUCLE DE FONCTIONNEMENT DU SYSTEME
  while (getButtonPress(buttonUp)==false || getButtonPress(buttonDown)==false){// tant que l'un des boutons du haut ou du bas de la brique LEGO ne sera pas appuyé, la boucle de fonctionnement sera enclenchée
		  displayCenteredTextLine(4,"Fonctionnement"); //affichage à la ligne 4 du message de début de fonctionnement du programme "Fonctionnement"

// PREMIER MODE DE FONCTIONNEMENT PAR DEFAUT
      while(mode==0){// mode manuel

              displayCenteredTextLine(5,"Manuel");//affichage à la ligne 5 du message du lancement du mode manuel "Manuel"
              resetMotorEncoder(motorA);//Réinitialise la valeur de l’encodeur du moteur A sur 0.
               n1 = getMotorEncoder(motorA);//Renvoie le nombre de degrés effectués par le moteur motor A pendant sa rotation
	             d1=(17.78*n1)/360;//valeur de la distance parcourue par le moteur A
	             resetMotorEncoder(motorC);//Réinitialise la valeur de lencodeur du moteur C sur 0.
	             n2 = getMotorEncoder(motorC);//Renvoie le nombre de degrés effectués par le moteur motor C pendant sa rotation
	             d2=(17.78*n2)/360;//valeur de la distance parcourue par le moteur C
	             df=(d1+d2)/2;//valeur moyenne de distance
               displayTextLine(8, "Distance parcourue : %1f cm  ",df);// affichage au centre de la ligne 8 de la distance en cm mesurée par le capteur ultrason afin de reconnaitre la distance limite puis lancer le mode parking automatique

               while (getIRRemoteButtons(S1) == 3){//avancer
	        	                setMotorSpeed(motorC,50);// le moteur C tourne à 50% de sa puissance maximale dans un premier
	                          setMotorSpeed(motorA,50);// le moteur A tourne à 50% de sa puissance maximale dans un premier
	             }
               while (getIRRemoteButtons(S1) == 4){//reculer

	        	                setMotorSpeed(motorC,-50);//le moteur C tourne à 50% de sa puissance maximale mais dans le sens contraire au premier
	                         	setMotorSpeed(motorA,-50);//le moteur A tourne à 50% de sa puissance maximale mais dans le sens contraire au premier
	             }
             	while (getIRRemoteButtons(S1) == 8 ){//droite
	                          setMotorSpeed(motorC,20);// le moteur C tourne à 20% de sa puissance maximale dans un premier sens
	                        	setMotorSpeed(motorA,50);// le moteur A tourne à 50% de sa puissance maximale dans un premier sens
	            }
	            while (getIRRemoteButtons(S1) == 5) {//gauche

	        	                 setMotorSpeed(motorA,20);// le moteur A tourne à 20% de sa puissance maximale dans un premier sens
	        	                 setMotorSpeed(motorC,50);// le moteur C tourne à 50% de sa puissance maximale dans un premier sens
              }
			        if(getIRRemoteButtons(S1) == 6){ // parking manuel .
							               setMotorSpeed(motorA,0);// le moteur A est arrété
							               setMotorSpeed(motorC,-50);//le moteur C tourne à 50% de sa puisssance maximale dans le sens contraire au premier
							               sleep(850);// le moteur C tourne pendant 850ms
			        }
              if(getButtonPress(buttonEnter)==true){// appui sur le bouton central de la brique LEGO pour quitter le mode manuel et lancer le mode automatique
				      	             mode=1;
				      }
				      if(getButtonPress(buttonUp)==true && getButtonPress(buttonDown)==true){// appui simultané des boutons du haut et du bas de la brique LEGO pour quitter la boucle de fonctionnement
	                            mode=3;
	            }
	            stopMotor(motorA);// arret moteur A
	            stopMotor(motorC);//arret moteur C
      }

	  // SECOND MODE DE FONCTIONNEMENT PAR DEFAUT
	    while(mode==1){//mode automatique
	          displayCenteredTextLine(5,"Automatique");//affichage à la ligne 5 du message du passage au mode automatoque "Automatique"
	          resetMotorEncoder(motorA);//Réinitialise la valeur de lencodeur du moteur A sur 0.
            n1 = getMotorEncoder(motorA);//Renvoie le nombre de degrés effectués par le moteur motor A pendant sa rotation
			      d1=(17.78*n1)/360;//valeur de la distance parcourue par le moteur A
			      resetMotorEncoder(motorA);//Réinitialise la valeur de lencodeur du moteur C sur 0.
          	n2 = getMotorEncoder(motorC);//Renvoie le nombre de degrés effectués par le moteur motor C pendant sa rotation
	          d2=(17,85*n2)/360;//valeur de la distance parcourue par le moteur C
	          df=(d1+d2)/2;//valeur moyenne de distance
		        fDistance = getUSDistance (S4);// FONCTION qui renvoie la valeur de la distance mesurée par le capteur ultrason
	          displayCenteredBigTextLine (8,"dist:%.1f cm", fDistance);// affichage au centre de la ligne 8 de la distance en cm mesurée par le capteur ultrason afin de reconnaitre la distance limite puis lancer le mode parking automatique

	         while (getIRRemoteButtons(S1) == 3){//avancer

	        		setMotorSpeed(motorC,50);// le moteur C tourne à 50% de sa puissance maximale dans un premier
	        		setMotorSpeed(motorA,50);// le moteur A tourne à 50% de sa puissance maximale dans un premier
	         }
	      	 while (getIRRemoteButtons(S1) == 4){//reculer

	        		setMotorSpeed(motorC,-50);// le moteur C tourne à 50% de sa puissance maximale mais dans le sens contraire au premier
	        		setMotorSpeed(motorA,-50);// le moteur A tourne à 50% de sa puissance maximale mais dans le sens contraire au premier
	          }

		       while (getIRRemoteButtons(S1) == 8 ){//droite

	            	setMotorSpeed(motorC,20);// le moteur C tourne à 20% de sa puissance maximale dans un premier sens
	        	    setMotorSpeed(motorA,50);// le moteur A tourne à 50% de sa puissance maximale dans un premier sens
	         }
	         while (getIRRemoteButtons(S1) == 5) {//gauche

	        	   setMotorSpeed(motorA,20);// le moteur A tourne à 20% de sa puissance maximale dans un premier sens
	        	   setMotorSpeed(motorC,50);// le moteur C tourne à 50% de sa puissance maximale dans un premier sens
            }


		   // parking auto
			     if(fDistance == getUSDistance(S4)<20){ // encodage de la distance limite "20cm" entre le mur et le système pour lancer le parking automatique
		          	displayCenteredBigTextLine(7, "Dist: %.1f cm", fDistance);// affichage au centre de la ligne 7 de la distance en cm mesurée par le capteur ultrason afin de reconnaitre la distance limite puis lancer le mode parking automatique
							  setMotorSpeed(motorA,0);// le moteur A est arrété
							  setMotorSpeed(motorC,-50);//le moteur C tourne à 50% de sa puisssance maximale dans le sens contraire au premier
							  sleep(850);// le moteur C doit tourner pendant 850ms
			     }
           if(getButtonPress(buttonEnter)==true){// appui sur le bouton central de la brique LEGO pour quitter le mode automatique et relancer le mode manuel
				  	    mode=1;
				   }
				   if(getButtonPress(buttonUp)==true && getButtonPress(buttonDown)==true){// appui simultané des boutons du haut et du bas de la brique LEGO pour quitter la boucle de fonctionnement
	             mode=3;
	         }
           stopMotor(motorA);// arret moteur A
	         stopMotor(motorC);//arret moteur C
	   }
  }
}
