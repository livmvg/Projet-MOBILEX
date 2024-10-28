
task main()
{

  SensorType[S1] = sensorEV3_Touch;
  SensorType[S2] = sensorEV3_Touch;
  SensorType[S3] = sensorEV3_Touch;
  SensorType[S4] = sensorEV3_Ultrasonic;

	int mode=0;

  while(getButtonPress(buttonLeft)==false || getButtonPress(buttonRight)==false){
  	displayCenteredTextLine(4,"Bienvenue Mobilex !!");
	}
	while(getButtonPress(buttonUp)==false || getButtonPress(buttonDown)==false){
		displayCenteredTextLine(4,"Fonctionnement");

    while(mode==0){
		   	   displayCenteredTextLine(5,"Manuel");
				   if( getButtonPress(buttonEnter)==true){
				  	mode=1;
				   }
				   if(getButtonPress(buttonUp)==true && getButtonPress(buttonDown)==true){
	          mode=3;
	         }
	         while (SensorValue[S1]==1&& SensorValue[S2]==0 && SensorValue[S3]==0){//avancer

	        		setMotorSpeed(motorC,50);
	        		setMotorSpeed(motorA,50);
	         }
	        /*while (SensorValue[S1]==0&& SensorValue[S2]==0 && SensorValue[S3]==0){

	        		stopMotor(motorA);
	        		stopMotor(motorC);
	        }	*/
	         while (SensorValue[S2]==1&& SensorValue[S1]==0 && SensorValue[S3]==0){//reculer

	        		setMotorSpeed(motorC,-50);
	        		setMotorSpeed(motorA,-50);
	         }
	        /*while (SensorValue[S2]==0 && SensorValue[S1]==0 && SensorValue[S3]==0){
	        		stopMotor(motorA);
	        		stopMotor(motorC);
	        }*/
	         while (SensorValue[S1]==0 && SensorValue[S2]==1&& SensorValue[S3]==1 ){//droite

	        	setMotorSpeed(motorC,20);
	        	setMotorSpeed(motorA,50);
	         }
	         while (SensorValue[S1]==1 && SensorValue[S2]==1 && SensorValue[S3]==0 && {//gauche

	        	setMotorSpeed(motorC,50);
	        	setMotorSpeed(motorA,20);

	         }
	         if(SensorValue[S1]==1 && SensorValue[S2]==0 && SensorValue[S3]==1){//parking

	            setMotorSpeed(motorC,50);
	            sleep(4000);
	         }
	         stopMotor(motorA);
	         stopMotor(motorC);
    }

    while(mode==1){
	         displayCenteredTextLine(5,"Automatique");
			     if(getButtonPress(buttonEnter)==true){
			   		mode=0;
			     }
	         if(getButtonPress(buttonUp)==true && getButtonPress(buttonDown)==true){
	          mode=3;
	         }
    }
}
