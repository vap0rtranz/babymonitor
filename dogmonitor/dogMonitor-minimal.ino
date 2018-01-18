/* MIT License

Copyright (c) 2018 Justin R. Pittman

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.
*/

/********** debug Scaffolding as Variadic macro called "DEBUG" ************/
#define DEBUG   //If you comment this line, the DPRINT & DPRINTLN lines are defined as blank.
#ifdef DEBUG    //Macros are usually in all capital letters.
  #define DPRINT(...)    Serial.print(__VA_ARGS__)     //DPRINT is a macro, debug print
  #define DPRINTLN(...)  Serial.println(__VA_ARGS__)   //DPRINTLN is a macro, debug print with new line
#else
  #define DPRINT(...)    //now defines a blank line
  #define DPRINTLN(...)  //now defines a blank line
#endif

// Setup some constants, for the Arduino board pins, etc.
const byte fistLed = LED_BUILTIN;
const byte piezoSpeakerPin = 8;
const byte soundSensorPin = 19; //AO5
const int samplePeriod = 1000; //1sec samples
const int sampleBuffer = 3; 

// the analog pins are, respectively: temperature, light, moisture
// piezoSpeakerPin = 8; soundSensorPin = 5; temperaturePin = 2;
const byte pin[] = {8, 19, 2};
int sensor[3];
        
namespace monitoringSystem 
{
    class babyMonitor {
      protected:
        
        //the volume to detect if the baby is crying or no
        int isBarking; 
        //  Sometimes the baby start mumbling or playing, specially at the age when he starts learning how to speak 
        int isNapping; 
        //This is to configure the baby 
        boolean makeSeveralCalls;
        
       public: 
        
         void setVoice(int voiceLevel, boolean isC)
          // set voice level, isC =True to set the voice level of "isCrying" else to set the voice level of isMumbeling
         {
           if (isC){
             isBarking= voiceLevel;
           }
           else{
             isNapping= voiceLevel;
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
            DPRINTLN("Starting the service");
          } 
          
        void sendSMS(){
          
            String phoneNumber= "+000000";
            char txtMsg[200]= "Yo! The baby is crying. ";
            char charbuffer[20];
          
            DPRINTLN("Message to mobile number: ");
            DPRINTLN(phoneNumber);
          
            // sms text
            DPRINTLN("SENDING");
            DPRINTLN();
            DPRINTLN("Message:");
            DPRINTLN(txtMsg);
            DPRINTLN("\nCOMPLETE!\n");  
          }
          
          void makeVoiceCall(){
                  String phoneNumber= "+000000";
                  char charbuffer[20];
                  DPRINTLN("The baby is crying! Trying to call mom");
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
                
                //take the analog sensor readings
                // # of samples to take
                for (int i = 0; i < sampleBuffer; i++) {
                     // run through sensors in sequence
                     for (int j = 0; j < 3; j++) {
                         sensor[j] = sensor[j] + analogRead(pin[j]);
                      }
                  }
                // smooth out raw sensor readings by simple average of samples
                for (int j = 0; j < 3; j++) {
                      sensor[j] = sensor[j] / sampleBuffer;
                 }

                // record sensor readings
                
                 for (int j = 0; j < 3; j++) {
                    DPRINT(sensor[j]);
                    DPRINT(",");
                 }
                 
                noise = sensor[0];

                if (noise < isNapping) {
                digitalWrite(fistLed, LOW);
                }
              
                if (noise > isBarking) {
                digitalWrite(fistLed, HIGH);
                
                 if (!hasCalledMom ) { 
                   makeVoiceCall();
                   
                    playTwinkleTwinkleLittleStar();
                    delay(1000);
                   
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
  // macro setup for debugging
  pinMode(LED_BUILTIN,OUTPUT); // a bit paranoid redundant 
  while (!Serial){
    // if L13 blink light lit, then waiting for serial
    digitalWrite(LED_BUILTIN, HIGH); 
  }
  DPRINTLN("You're connected Arduino console");
  
    _babyMonitor.initialize() ;
    
    // set isNapping at 500
    _babyMonitor.setVoice(500,false);
    
    // set isBarking at 700
    _babyMonitor.setVoice(700,true);
    
    // personalize configuration 
    _babyMonitor.configureSystem(true);
    
    
    // delay 1 minute to prepare the setup, to not infuluence the sound detector
    // delay(60000);
}

void loop()
{
     //start monitoring 
    _babyMonitor.monitor();
    
    delay(samplePeriod); // loop after sampling delay 
}





 

