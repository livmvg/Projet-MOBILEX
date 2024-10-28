
task main()
{
 {
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

}











}
