/*===============================================================
// Nom du fichier : MobilexV1.c
// Auteures : AKBAL Lyna & MAVOUNGOU Emmanuel
// Date de cr�ation : 17/03/2022
// Version : V1
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Description :
// C�est un syst�me mobile roulant (compos� principalement d�une brique LEGO, de 3
// capteurs de contact et d�un capteur ultrason ) qui autorise deux modes de fonctionnement : le
// mode � parking manuel � et le mode � parking automatique � qui peuvent �tre choisis par
// d�faut.
// D�une part, ce syst�me peut circuler sur un circuit � obstacle en direction d�un mur en �tant
// pilot� par un op�rateur via une s�rie de combinaisons d�appui sur 3 capteurs de contact.
// D�autre part, il peut se garer dans une zone de parking (parall�lement au mur) selon ses deux
// modes:
// - manuellement, l�op�rateur le gare en faisant la combinaison associ�e avec les capteurs de
// contact ;
// - automatiquement, il se gare seul gr�ce au capteur ultrason qui d�tecte au pr�alable le mur au
// bout d�une certaine distance limite.
// De plus, lors de ses d�placements sur le circuit, il �mettra :
// - un �do � en avan�ant ;
// - un � r� � en reculant ;
// - un � mi � en tournant � gauche ;
// - un � fa � en tournant � droite ;
// - un � sol � en se garant .
// �-------------------------------------------------------------
//MANUEL D�UTILISATION VERSION 1 :
//D�marrage :
// -On allume la brique Lego
// -On lance le programme (On compile)
// -On acc�de au mode manuel en appuyant simultan�ment
// sur les boutons gauche et droit de la brique.
// -Pour changer vers le mode Automatique, il faut appuyer sur le bouton du milieu (bouton d�entrer)
//Fonctionnement :
//MODE MANUEL :
// -On appuie sur les boutons droit et gauche pour mettre le mode manuel
// -Pour avancer : Appuyer sur le Capteur de contact S2
// -Pour reculer(marche arri�re) :  Appuyer sur le Capteur de contact S3
// -Pour aller � droite : Appuyer simultan�ment sur les capteurs de contact S2 et S3
// -Pour aller � gauche : Appuyer simultan�ment sur les capteurs de contact S1 et S2
// -Pour le parking Manuel : Appuyer simultan�ment sur les capteurs de contact S1 S2 et S3
//MODE AUTOMATIQUE :
// -Ici on utilisera un capteur ultrason S4 qui sera brancher dans l�entr�e 4
// -On appuie sur le bouton du milieu(Bouton entrer) pour passer du mode manuel au mode automatique
// -Pour avancer : Appuyer sur le Capteur S2
// -Pour reculer(marche arri�re) :  Appuyer sur le Capteur S3
// -Pour aller � droite : Appuyer simultan�ment sur les capteurs de contact S2 et S3
// -Pour aller a gauche : Appuyer simultan�ment sur les capteurs de contact S1 et S2
// -Pour le parking Automatique : il s'enclenchera naturellement d�s que le capteur d�tectera un obstacle (ici le mur) � moins de 20cm
// ( distance initialis�e dans le code pour enclencher le parking automatique).
// -------------------------------------------------------------
// A noter :
// - le capteur de contact S1 est sur l'entr�e 1
// - le capteur de contact S2 est sur l'entr�e 2
// - le capteur de contact S3 est sur l'entr�e 3
// - le capteur ultrason S4 est sur l'entr�e 4
// - le moteur A est sur la sortie A
// - le moteur C est sur la sortie C
//===============================================================*/

task main()
{

  SensorType[S1] = sensorEV3_Touch;//capteur de contact branch� sur l'entr�e 1
  SensorType[S2] = sensorEV3_Touch;//capteur de contact branch� sur l'entr�e 2
  SensorType[S3] = sensorEV3_Touch;//capteur de contact branch� sur l'entr�e 3
  SensorType[S4] = sensorEV3_Ultrasonic;//capteur ultrason branch� sur l'entr�e 4
  float fDistance =0;
  int mode=0;
  //setSoundVolume(int nVolume);//FONCTION qui r�gle le volume de la brique entre 0 et 100%
  //playTone(int frequency, int durationIn10MsecTicks);//FONCTION qui joue une note (dont la fr�quence en Hz est pass�e en param�tre) pendant la dur�e donn�e en ms


  // BOUCLE DE BASE (DEMARRAGE) SYSTEME
  while(getButtonPress(buttonLeft)==false || getButtonPress(buttonRight)==false){//tant que l'un des boutons de gauvhe et de droie de la brique LEGO ne sera pas appuy�, le boucle de d�marrage sera enclench�e
  	   displayCenteredTextLine(4,"Bienvenue Mobilex !!"); // affichage � la ligne 4 du message de d�marrage "Bienvebue Mobilex"
  }
  // BOUCLE DE FONCTIONNEMENT DU SYSTEME
  while(getButtonPress(buttonUp)==false || getButtonPress(buttonDown)==false){// tant que l'un des boutons du haut ou du bas de la brique LEGO ne sera pas appuy�, la boucle de fonctionnement sera enclench�e
		   displayCenteredTextLine(4,"Fonctionnement"); //affichage � la ligne 4 du message de d�but de fonctionnement du programme "Fonctionnement"

// PREMIER MODE DE FONCTIONNEMENT PAR DEFAUT
       while(mode==0){// mode manuel
		   	     displayCenteredTextLine(5,"Manuel");//affichage � la ligne 5 du message du lancement du mode manuel "Manuel"

	           while (SensorValue[S1]==0 && SensorValue[S2]==1 && SensorValue[S3]==0){//avancer
                            //playTone(261, 1000);// la brique LEGO joue un "do" durant 1s
						//	setSoundVolume(50);// R�gle le volume � 50%
	        		              setMotorSpeed(motorC,50);// le moteur C tourne � 50% de sa puissance maximale dans un premier sens
	        		              setMotorSpeed(motorA,50);//le moteur A tourne � 50% de sa puissance maximale
	           }
	       	   while (SensorValue[S1]==0 && SensorValue[S2]==0 && SensorValue[S3]==1){//reculer
                         //   playTone(293, 1000);l//la brique LEGO joue un "R�" durant 1s
						//	setSoundVolume(50);//R�gle le volume � 50%
	        	              	setMotorSpeed(motorC,-50);// le moteur C tourne � 50% de sa puissance maximale mais dans le sens contraire au premier
	        		              setMotorSpeed(motorA,-50);// le moteur A tourne � 50% de sa puissance maximale mais dans le sens contraire au premier
	           }
	        	 while (SensorValue[S1]==0 && SensorValue[S2]==1 && SensorValue[S3]==1){//droite
               //             playTone(329, 1000);// la brique LEGO joue un "Mi" durant 1s
						//	setSoundVolume(50);//R�gle le volume � 50%
	            	            setMotorSpeed(motorC,20);// le moteur C tourne � 20% de sa puissance maximale dans un premier sens
	        	                setMotorSpeed(motorA,50);// le moteur A tourne � 50% de sa puissance maximale dans un premier sens
	           }
	           while (SensorValue[S1]==1 && SensorValue[S2]==1 && SensorValue[S3]==0) {//gauche
                          //  playTone( 348, 1000);// la brique LEGO joue un "Fa" durant 1s
							//setSoundVolume(50);//R�gle le volume � 50%
	        	                setMotorSpeed(motorA,20);// le moteur A tourne � 20% de sa puisssance maximale dans un premier sens
	        	                setMotorSpeed(motorC,50);// le moteur C tourne � 50% de sa puissance maximale dans un premier sens
             }
			 // parking manuel
			       if(SensorValue[S3]==1 && SensorValue[S2]==1 && SensorValue[S1]==1){

			          //      playTone(392, 1000);// la brique LEGO joue un "Sol" pendant 1s
						//	setSoundVolume(50);//R�gle le volume � 50%
							              setMotorSpeed(motorA,0);// le moteur A est arr�t�
							              setMotorSpeed(motorC,-50);//le moteur C tourne � 50% de sa puisssance maximale dans le sens contraire au premier
							              sleep(850);// le moteur C doit tourner pendant 850ms
			       }

             if( getButtonPress(buttonEnter)==true){// appui sur le bouton central de la brique LEGO pour quitter le mode manuel et lancer le mode automatique
				  	                mode=1;
				     }
				     if(getButtonPress(buttonUp)==true && getButtonPress(buttonDown)==true){// appui simultan� des boutons du haut et du bas de la brique LEGO pour quitter la boucle de fonctionnement
	                          mode=3;
	           }

	           stopMotor(motorA); //arret du moteur A
	           stopMotor(motorC);// arret du moteur C
      }
	 // SECOND MODE DE FONCTIONNEMENT PAR DEFAUT
	    while(mode==1){//mode automatique
	          displayCenteredTextLine(5,"Automatique");//affichage � la ligne 5 du message du passage au mode automatoque "Automatique"
            fDistance = getUSDistance (S4);// FONCTION qui renvoie la valeur de la distance mesur�e par le capteur ultrason
	          displayCenteredBigTextLine (8,"dist:%.1f cm", fDistance);// affichage au centre de la ligne 8 de la distance en cm mesur�e par le capteur ultrason afin de reconnaitre la distance limite puis lancer le mode parking automatique

	          while (SensorValue[S1]==0 && SensorValue[S2]==1 && SensorValue[S3]==0){//avancer
               //                playTone(261, 1000// la brique LEGO joue un "do" durant 1s
							//   setSoundVolume(50);// R�gle le volume � 50%
	        	                 	 setMotorSpeed(motorC,50);// le moteur C tourne � 50% de sa puissance maximale dans un premier
	        	                 	 setMotorSpeed(motorA,50);// le moteur A tourne � 50% de sa puissance maximale dans un premier
	          }
	         	while (SensorValue[S1]==0 && SensorValue[S2]==0 && SensorValue[S3]==1){//reculer
                 //              playTone(293, 1000);//la brique LEGO joue un "R�" durant 1s
							 //  setSoundVolume(50);// R�gle le volume � 50%
	        		                 setMotorSpeed(motorC,-50);// le moteur C tourne � 50% de sa puissance maximale mais dans le sens contraire au premier
	        		                 setMotorSpeed(motorA,-50);// le moteur A tourne � 50% de sa puissance maximale mais dans le sens contraire au premier
	          }
	          while (SensorValue[S1]==0 && SensorValue[S2]==1 && SensorValue[S3]==1){//droite
                  //             playTone(329, 1000); //la brique LEGO joue un "Mi" durant 1s
							//   setSoundVolume(50);// R�gle le volume � 50%
	                           	 setMotorSpeed(motorC,20);// le moteur C tourne � 20% de sa puissance maximale dans un premier sens
	        	                   setMotorSpeed(motorA,50);// le moteur A tourne � 20% de sa puissance maximale dans un premier sens
	          }
	          while (SensorValue[S1]==1 && SensorValue[S2]==1 && SensorValue[S3]==0) {//gauche
                 //              playTone(348, 1000);// la brique LEGO joue un "Fa" durant 1s
							  // setSoundVolume(50);// R�gle le volume � 50%
	        	                   setMotorSpeed(motorA,20);// le moteur A tourne � 20% de sa puissance maximale dans un premier sens
	        	                   setMotorSpeed(motorC,50);// le moteur C tourne � 50% de sa puissance maximale dans un premier sens
            }
			// parking auto
	          if (getUSDistance(S4)<20){ // encodage de la distance limite "20cm" entre le mur et le syst�me pour lancer le parking automatique
                   //           playTone(392, 1000);// la brique LEGO joue un "Sol" pendant 1s
							//  setSoundVolume(50);// R�gle le volume � 50%
	        	                  setMotorSpeed(motorA,0);// le moteur A est arr�t�
		                          setMotorSpeed(motorC,-50);//le moteur C tourne � 50% de sa puisssance maximale dans le sens contraire au premier
	                          	sleep(850);// le moteur C doit tourner pendant 850ms
			     }
           if(getButtonPress(buttonEnter)==true){// appui sur le bouton central de la brique LEGO pour quitter le mode automatique et relancer le mode manuel
			   		                  mode=0;
			     }
	         if(getButtonPress(buttonUp)==true && getButtonPress(buttonDown)==true){// appui simultan� des boutons du haut et du bas de la brique LEGO pour quitter la boucle de fonctionnement
	                           mode=3;
	         }
           stopMotor(motorA);// arret du moteur A
	         stopMotor(motorC);// arret du moteur C
	   }
  }
}
