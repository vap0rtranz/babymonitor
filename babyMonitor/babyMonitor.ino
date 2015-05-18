
#include <GSM.h>
#include "notes.h"


// You can costumize the PINs
#define fistLed 11
#define secLed 12
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
            GSMPIN PINManager;
            GSMBand band;
            pinMode(soundSensorPin, INPUT);
            pinMode(fistLed, OUTPUT);
            pinMode(secLed, OUTPUT);
            
            Serial.begin(9600);
             
            // Beginning the band manager restarts the modem
            Serial.println("Starting the service");
            
            // This part help when you debug problems with GSM Shield connectivity 
            //int pin_query = PINManager.isPIN();
            //Serial.println(pin_query);
            
            band.begin();
            configureBand();
          } 
          
          
        void sendSMS(){
          
            GSM_SMS sms;
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
          
            // send the message
            phoneNumber.toCharArray(charbuffer, 16);
            sms.beginSMS(charbuffer);
            sms.print(txtMsg);
            sms.endSMS(); 
          
            Serial.println("\nCOMPLETE!\n");  
          }
          
          void makeVoiceCall(){
                  String phoneNumber= "+000000";
                  char charbuffer[20];
                  GSMVoiceCall vcs;
                  // Check if the receiving end has picked up the call
                  phoneNumber.toCharArray(charbuffer, 16);
                   Serial.println("The baby is crying! Trying to call mom");
                  if(vcs.voiceCall(charbuffer))
                  {
                    Serial.println("Call Established. Enter line to end");
                    // Wait for some input from the line
                    while(Serial.read()!='\n' && (vcs.getvoiceCallStatus()==TALKING));          
                    // And hang up
                    vcs.hangCall();
                  }
          }
          
          void configureBand()
          {     
                GSMVoiceCall vcs;
                GSM gsmAccess; 
                GSMBand band;
                // Configuring the GSM band
                // for more information about configuring the band visit: http://arduino.cc/en/Tutorial/GSMToolsBandManagement
                String newBand;
                // This should costumized based on your country, check the above-mentioned link
                newBand== GSM_MODE_EGSM_DCS; 
            
                boolean operationSuccess; 
                operationSuccess = band.setBand(newBand); 
                Serial.println(operationSuccess);
                if(operationSuccess)
                { 
                  Serial.println("Success! GSM has been initialized.");
                  
                } 
                else
                { 
                  Serial.println("Error while changing band");
                 }
          }
          
          void playTwinkleTwinkleLittleStar(){
            int melody[] = {NOTE_B4, NOTE_B4, NOTE_FS5, NOTE_FS5, NOTE_GS5, NOTE_GS5, NOTE_FS5, NOTE_NONE, NOTE_E5, NOTE_E5, NOTE_DS5, NOTE_DS5, NOTE_CS5, NOTE_CS5, NOTE_B4, NOTE_NONE, NOTE_FS5, NOTE_FS5, NOTE_E5, NOTE_E5, NOTE_DS5, NOTE_DS5, NOTE_CS5, NOTE_NONE, NOTE_FS5, NOTE_FS5, NOTE_E5, NOTE_E5, NOTE_DS5, NOTE_DS5, NOTE_DS5, NOTE_DS5, NOTE_CS5, NOTE_NONE, NOTE_B4, NOTE_B4, NOTE_FS5, NOTE_FS5, NOTE_GS5, NOTE_GS5, NOTE_FS5, NOTE_NONE, NOTE_E5, NOTE_E5, NOTE_DS5, NOTE_DS5, NOTE_CS5, NOTE_CS5, NOTE_B4, NOTE_NONE};
            int noteDurations[] = {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,4,4,4,4,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2};
            for (int thisNote = 0; thisNote < sizeof(melody)/sizeof(int); thisNote++) {
              int noteDuration = 1000/noteDurations[thisNote];
              tone(8, melody[thisNote],noteDuration);
          
              delay(noteDuration);
              noTone(8);
            }
          }

 
            void monitor() {
               
                boolean hasCalledMom= false;
                int noise;
                  
                delay(1000); 
                noise = analogRead(soundSensorPin);
                Serial.println(noise);
                
                if (noise < isMumbling) {
                digitalWrite(fistLed, LOW);
                digitalWrite(secLed, LOW);
                }
                if (noise > isMumbling && noise < isCrying ) {
                digitalWrite(fistLed, HIGH);
                digitalWrite(secLed, LOW);
                }
              
                if (noise > isCrying) {
                digitalWrite(fistLed, HIGH);
                digitalWrite(secLed, HIGH);
              
                
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

    _babyMonitor.initialize() ;
    
    // set isCrying at 600
    _babyMonitor.setVoice(300,false);
    
    // set isMumbeling at 300
    _babyMonitor.setVoice(600,true);
    
    // personalize configuration 
    _babyMonitor.configureSystem(true);
    
    
    // delay 1 minute to prepare the setup, to not infuluence the sound detector
     delay(60000);
}

void loop()
{
     //start monitoring 
    _babyMonitor.monitor();
}





 
