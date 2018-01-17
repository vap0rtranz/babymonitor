/*
MIT License

Copyright (c) [year] [fullname]

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.
*/

// You can costumize the PINs
#define fistLed LED_BUILTIN
#define piezoSpeakerPin 8
#define soundSensorPin 5
        
        
namespace monitoringSystem 
{
    class babyMonitor {
      protected:
        
        //the volume to detect if the baby is crying or no
        int isCrying; 
        //  Sometimes the baby start mumbling or playing, specially at the age when he starts learning how to speak 
        int isMumbling; 
        //This is to configure the baby 
        boolean makeSeveralCalls;
        

        
       public: 
        
         void setVoice(int voiceLevel, boolean isC)
          // set voice level, isC =True to set the voice level of "isCrying" else to set the voice level of isMumbeling
         {
           if (isC){
             isCrying= voiceLevel;
           }
           else{
             isMumbling= voiceLevel;
           
           }
            
         }
         
         void configureSystem(boolean severalCalls)
         // This is optional for users who wants to get several calls, or just one
         {
           
           makeSeveralCalls= severalCalls; 
         
         }
      
            
         void initialize()
         // initialize the system 
         {
            pinMode(soundSensorPin, INPUT);
            pinMode(fistLed, OUTPUT);
            
            Serial.begin(9600);
             
            // Beginning the band manager restarts the modem
            Serial.println("Starting the service");
            
          } 
          
          
        void sendSMS(){
          
            String phoneNumber= "+000000";
            char txtMsg[200]= "Yo! The baby is crying. ";
            char charbuffer[20];
          
            Serial.print("Message to mobile number: ");
            Serial.println(phoneNumber);
          
            // sms text
            Serial.println("SENDING");
            Serial.println();
            Serial.println("Message:");
            Serial.println(txtMsg);
          
            Serial.println("\nCOMPLETE!\n");  
          }
          
          void makeVoiceCall(){
                  String phoneNumber= "+000000";
                  char charbuffer[20];
                   Serial.println("The baby is crying! Trying to call mom");
          }
          
           void playTwinkleTwinkleLittleStar(){
              tone(piezoSpeakerPin,131,10000);
              delay(1000);
              //redundant
              //noTone(piezoSpeakerPin);
           }

            void monitor() {
               
                boolean hasCalledMom= false;
                int noise;
                  
                delay(1000); 
                noise = analogRead(soundSensorPin);
                Serial.println(noise);
                
                if (noise < isMumbling) {
                digitalWrite(fistLed, LOW);
                }
                if (noise > isMumbling && noise < isCrying ) {
                digitalWrite(fistLed, HIGH);
                }
              
                if (noise > isCrying) {
                digitalWrite(fistLed, HIGH);
              
                
                 if (!hasCalledMom ) { 
                   makeVoiceCall();
                   
                    playTwinkleTwinkleLittleStar();
                   
                   if(!makeSeveralCalls) {
                       hasCalledMom= false;
                   }
                  }
                }
                
            }

          };  

};


monitoringSystem::babyMonitor _babyMonitor;

void setup()
{   

    _babyMonitor.initialize() ;
    
    // set isCrying at 600
    _babyMonitor.setVoice(300,false);
    
    // set isMumbeling at 300
    _babyMonitor.setVoice(600,true);
    
    // personalize configuration 
    _babyMonitor.configureSystem(true);
    
    
    // delay 1 minute to prepare the setup, to not infuluence the sound detector
    // delay(60000);
}

void loop()
{
     //start monitoring 
    _babyMonitor.monitor();
}





 

