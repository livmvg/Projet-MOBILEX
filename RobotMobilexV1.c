/*===============================================================
// Nom du fichier : MobilexV1.c
// Auteures : AKBAL Lyna & MAVOUNGOU Emmanuel
// Date de création : 17/03/2022
// Version : V1
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Description :
// C’est un système mobile roulant (composé principalement d’une brique LEGO, de 3
// capteurs de contact et d’un capteur ultrason ) qui autorise deux modes de fonctionnement : le
// mode « parking manuel » et le mode « parking automatique » qui peuvent être choisis par
// défaut.
// D’une part, ce système peut circuler sur un circuit à obstacle en direction d’un mur en étant
// piloté par un opérateur via une série de combinaisons d’appui sur 3 capteurs de contact.
// D’autre part, il peut se garer dans une zone de parking (parallèlement au mur) selon ses deux
// modes:
// - manuellement, l’opérateur le gare en faisant la combinaison associée avec les capteurs de
// contact ;
// - automatiquement, il se gare seul grâce au capteur ultrason qui détecte au préalable le mur au
// bout d’une certaine distance limite.
// De plus, lors de ses déplacements sur le circuit, il émettra :
// - un «do » en avançant ;
// - un « ré » en reculant ;
// - un « mi » en tournant à gauche ;
// - un « fa » en tournant à droite ;
// - un « sol » en se garant .
// –-------------------------------------------------------------
//MANUEL D’UTILISATION VERSION 1 :
//Démarrage :
// -On allume la brique Lego
// -On lance le programme (On compile)
// -On accède au mode manuel en appuyant simultanément
// sur les boutons gauche et droit de la brique.
// -Pour changer vers le mode Automatique, il faut appuyer sur le bouton du milieu (bouton d’entrer)
//Fonctionnement :
//MODE MANUEL :
// -On appuie sur les boutons droit et gauche pour mettre le mode manuel
// -Pour avancer : Appuyer sur le Capteur de contact S2
// -Pour reculer(marche arrière) :  Appuyer sur le Capteur de contact S3
// -Pour aller à droite : Appuyer simultanément sur les capteurs de contact S2 et S3
// -Pour aller à gauche : Appuyer simultanément sur les capteurs de contact S1 et S2
// -Pour le parking Manuel : Appuyer simultanément sur les capteurs de contact S1 S2 et S3
//MODE AUTOMATIQUE :
// -Ici on utilisera un capteur ultrason S4 qui sera brancher dans l’entrée 4
// -On appuie sur le bouton du milieu(Bouton entrer) pour passer du mode manuel au mode automatique
// -Pour avancer : Appuyer sur le Capteur S2
// -Pour reculer(marche arrière) :  Appuyer sur le Capteur S3
// -Pour aller à droite : Appuyer simultanément sur les capteurs de contact S2 et S3
// -Pour aller a gauche : Appuyer simultanément sur les capteurs de contact S1 et S2
// -Pour le parking Automatique : il s'enclenchera naturellement dès que le capteur détectera un obstacle (ici le mur) à moins de 20cm
// ( distance initialisée dans le code pour enclencher le parking automatique).
// -------------------------------------------------------------
// A noter :
// - le capteur de contact S1 est sur l'entrée 1
// - le capteur de contact S2 est sur l'entrée 2
// - le capteur de contact S3 est sur l'entrée 3
// - le capteur ultrason S4 est sur l'entrée 4
// - le moteur A est sur la sortie A
// - le moteur C est sur la sortie C
//===============================================================*/

task main()
{

  SensorType[S1] = sensorEV3_Touch;//capteur de contact branché sur l'entrée 1
  SensorType[S2] = sensorEV3_Touch;//capteur de contact branché sur l'entrée 2
  SensorType[S3] = sensorEV3_Touch;//capteur de contact branché sur l'entrée 3
  SensorType[S4] = sensorEV3_Ultrasonic;//capteur ultrason branché sur l'entrée 4
  float fDistance =0;
  int mode=0;
  //setSoundVolume(int nVolume);//FONCTION qui règle le volume de la brique entre 0 et 100%
  //playTone(int frequency, int durationIn10MsecTicks);//FONCTION qui joue une note (dont la fréquence en Hz est passée en paramètre) pendant la durée donnée en ms


  // BOUCLE DE BASE (DEMARRAGE) SYSTEME
  while(getButtonPress(buttonLeft)==false || getButtonPress(buttonRight)==false){//tant que l'un des boutons de gauvhe et de droie de la brique LEGO ne sera pas appuyé, le boucle de démarrage sera enclenchée
  	   displayCenteredTextLine(4,"Bienvenue Mobilex !!"); // affichage à la ligne 4 du message de démarrage "Bienvebue Mobilex"
  }
  // BOUCLE DE FONCTIONNEMENT DU SYSTEME
  while(getButtonPress(buttonUp)==false || getButtonPress(buttonDown)==false){// tant que l'un des boutons du haut ou du bas de la brique LEGO ne sera pas appuyé, la boucle de fonctionnement sera enclenchée
		   displayCenteredTextLine(4,"Fonctionnement"); //affichage à la ligne 4 du message de début de fonctionnement du programme "Fonctionnement"

// PREMIER MODE DE FONCTIONNEMENT PAR DEFAUT
       while(mode==0){// mode manuel
		   	     displayCenteredTextLine(5,"Manuel");//affichage à la ligne 5 du message du lancement du mode manuel "Manuel"

	           while (SensorValue[S1]==0 && SensorValue[S2]==1 && SensorValue[S3]==0){//avancer
                            //playTone(261, 1000);// la brique LEGO joue un "do" durant 1s
						//	setSoundVolume(50);// Règle le volume à 50%
	        		              setMotorSpeed(motorC,50);// le moteur C tourne à 50% de sa puissance maximale dans un premier sens
	        		              setMotorSpeed(motorA,50);//le moteur A tourne à 50% de sa puissance maximale
	           }
	       	   while (SensorValue[S1]==0 && SensorValue[S2]==0 && SensorValue[S3]==1){//reculer
                         //   playTone(293, 1000);l//la brique LEGO joue un "Ré" durant 1s
						//	setSoundVolume(50);//Règle le volume à 50%
	        	              	setMotorSpeed(motorC,-50);// le moteur C tourne à 50% de sa puissance maximale mais dans le sens contraire au premier
	        		              setMotorSpeed(motorA,-50);// le moteur A tourne à 50% de sa puissance maximale mais dans le sens contraire au premier
	           }
	        	 while (SensorValue[S1]==0 && SensorValue[S2]==1 && SensorValue[S3]==1){//droite
               //             playTone(329, 1000);// la brique LEGO joue un "Mi" durant 1s
						//	setSoundVolume(50);//Règle le volume à 50%
	            	            setMotorSpeed(motorC,20);// le moteur C tourne à 20% de sa puissance maximale dans un premier sens
	        	                setMotorSpeed(motorA,50);// le moteur A tourne à 50% de sa puissance maximale dans un premier sens
	           }
	           while (SensorValue[S1]==1 && SensorValue[S2]==1 && SensorValue[S3]==0) {//gauche
                          //  playTone( 348, 1000);// la brique LEGO joue un "Fa" durant 1s
							//setSoundVolume(50);//Règle le volume à 50%
	        	                setMotorSpeed(motorA,20);// le moteur A tourne à 20% de sa puisssance maximale dans un premier sens
	        	                setMotorSpeed(motorC,50);// le moteur C tourne à 50% de sa puissance maximale dans un premier sens
             }
			 // parking manuel
			       if(SensorValue[S3]==1 && SensorValue[S2]==1 && SensorValue[S1]==1){

			          //      playTone(392, 1000);// la brique LEGO joue un "Sol" pendant 1s
						//	setSoundVolume(50);//Règle le volume à 50%
							              setMotorSpeed(motorA,0);// le moteur A est arrété
							              setMotorSpeed(motorC,-50);//le moteur C tourne à 50% de sa puisssance maximale dans le sens contraire au premier
							              sleep(850);// le moteur C doit tourner pendant 850ms
			       }

             if( getButtonPress(buttonEnter)==true){// appui sur le bouton central de la brique LEGO pour quitter le mode manuel et lancer le mode automatique
				  	                mode=1;
				     }
				     if(getButtonPress(buttonUp)==true && getButtonPress(buttonDown)==true){// appui simultané des boutons du haut et du bas de la brique LEGO pour quitter la boucle de fonctionnement
	                          mode=3;
	           }

	           stopMotor(motorA); //arret du moteur A
	           stopMotor(motorC);// arret du moteur C
      }
	 // SECOND MODE DE FONCTIONNEMENT PAR DEFAUT
	    while(mode==1){//mode automatique
	          displayCenteredTextLine(5,"Automatique");//affichage à la ligne 5 du message du passage au mode automatoque "Automatique"
            fDistance = getUSDistance (S4);// FONCTION qui renvoie la valeur de la distance mesurée par le capteur ultrason
	          displayCenteredBigTextLine (8,"dist:%.1f cm", fDistance);// affichage au centre de la ligne 8 de la distance en cm mesurée par le capteur ultrason afin de reconnaitre la distance limite puis lancer le mode parking automatique

	          while (SensorValue[S1]==0 && SensorValue[S2]==1 && SensorValue[S3]==0){//avancer
               //                playTone(261, 1000// la brique LEGO joue un "do" durant 1s
							//   setSoundVolume(50);// Règle le volume à 50%
	        	                 	 setMotorSpeed(motorC,50);// le moteur C tourne à 50% de sa puissance maximale dans un premier
	        	                 	 setMotorSpeed(motorA,50);// le moteur A tourne à 50% de sa puissance maximale dans un premier
	          }
	         	while (SensorValue[S1]==0 && SensorValue[S2]==0 && SensorValue[S3]==1){//reculer
                 //              playTone(293, 1000);//la brique LEGO joue un "Ré" durant 1s
							 //  setSoundVolume(50);// Règle le volume à 50%
	        		                 setMotorSpeed(motorC,-50);// le moteur C tourne à 50% de sa puissance maximale mais dans le sens contraire au premier
	        		                 setMotorSpeed(motorA,-50);// le moteur A tourne à 50% de sa puissance maximale mais dans le sens contraire au premier
	          }
	          while (SensorValue[S1]==0 && SensorValue[S2]==1 && SensorValue[S3]==1){//droite
                  //             playTone(329, 1000); //la brique LEGO joue un "Mi" durant 1s
							//   setSoundVolume(50);// Règle le volume à 50%
	                           	 setMotorSpeed(motorC,20);// le moteur C tourne à 20% de sa puissance maximale dans un premier sens
	        	                   setMotorSpeed(motorA,50);// le moteur A tourne à 20% de sa puissance maximale dans un premier sens
	          }
	          while (SensorValue[S1]==1 && SensorValue[S2]==1 && SensorValue[S3]==0) {//gauche
                 //              playTone(348, 1000);// la brique LEGO joue un "Fa" durant 1s
							  // setSoundVolume(50);// Règle le volume à 50%
	        	                   setMotorSpeed(motorA,20);// le moteur A tourne à 20% de sa puissance maximale dans un premier sens
	        	                   setMotorSpeed(motorC,50);// le moteur C tourne à 50% de sa puissance maximale dans un premier sens
            }
			// parking auto
	          if (getUSDistance(S4)<20){ // encodage de la distance limite "20cm" entre le mur et le système pour lancer le parking automatique
                   //           playTone(392, 1000);// la brique LEGO joue un "Sol" pendant 1s
							//  setSoundVolume(50);// Règle le volume à 50%
	        	                  setMotorSpeed(motorA,0);// le moteur A est arrété
		                          setMotorSpeed(motorC,-50);//le moteur C tourne à 50% de sa puisssance maximale dans le sens contraire au premier
	                          	sleep(850);// le moteur C doit tourner pendant 850ms
			     }
           if(getButtonPress(buttonEnter)==true){// appui sur le bouton central de la brique LEGO pour quitter le mode automatique et relancer le mode manuel
			   		                  mode=0;
			     }
	         if(getButtonPress(buttonUp)==true && getButtonPress(buttonDown)==true){// appui simultané des boutons du haut et du bas de la brique LEGO pour quitter la boucle de fonctionnement
	                           mode=3;
	         }
           stopMotor(motorA);// arret du moteur A
	         stopMotor(motorC);// arret du moteur C
	   }
  }
}
