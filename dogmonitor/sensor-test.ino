/******************************************************************************
 * sound_detector_demo.ino
 * Sound detector sample sketch
 * Byron Jacquot @ SparkFun Electronics
 * February 19, 2014
 * https://github.com/sparkfun/Sound_Detector
 * 
 * This sketch demonstrates the use of the Sparkfun Sound Detector board.
 *
 * The Sound Detector is a small board that combines a microphone and some 
 * processing circuitry.  It provides not only an audio output, but also a 
 * binary indication of the presence of sound and an analog representation 
 * of it's amplitude.  
 *
 * This sketch demonstrates two different modes of usage for the Sound
 * Detector.  The gate output (a binary indication that is high when sound
 * is present, and low when conditions are quiet) is used to fire a pin-change 
 * ISR, which lights an LED when the sound is present.  The envelope output 
 * (an analog voltage to rises to indicate the amplitude of the sound) is 
 * sampled in the loop(), and it prints an indication of the level to the 
 * serial terminal. 
 *
 * For more details about the Sound Detector, please check the hookup guide.
 *
 * Connections:
 * The Sound Detector is connected to the Adrduino as follows:
 * (Sound Detector -> Arduino pin)
 * GND → GND
 * VCC → 5V
 * Gate → Pin 2
 * Envelope → A0
 * 
 * Resources:
 * Additional library requirements: none
 * 
 * Development environment specifics:
 * Using Arduino IDe 1.0.5
 * Tested on Redboard, 3.3v/8MHz and 5v/16MHz ProMini hardware.
 * 
 * This code is beerware; if you see me (or any other SparkFun employee) at the
 * local, and you've found our code helpful, please buy us a round!
 * 
 * Distributed as-is; no warranty is given.
 ******************************************************************************/

 // Define hardware connections
#define PIN_GATE_IN 2
#define IRQ_GATE_IN  0
#define PIN_LED_OUT 13
#define PIN_SOUND_IN A0
#define PIN_TEMP_IN A1

// reference voltage
float referenceVoltage = 5.0; //Set to 5, 3.3, 2.56 or 1.1 depending on analogReference Setting

// soundISR()
// This function is installed as an interrupt service routine for the pin
// change interrupt.  When digital input 2 changes state, this routine
// is called.
// It queries the state of that pin, and sets the onboard LED to reflect that 
// pin's state.
void soundISR()
{
  int pin_val;

  pin_val = digitalRead(PIN_GATE_IN);
  digitalWrite(PIN_LED_OUT, pin_val);   
}

void setup()
{
  Serial.begin(9600);

  //  Configure LED pin as output
  pinMode(PIN_LED_OUT, OUTPUT);

  // configure input to interrupt
  pinMode(PIN_GATE_IN, INPUT);
  attachInterrupt(IRQ_GATE_IN, soundISR, CHANGE);

  // Display status
  Serial.println("Initialized");
  
  
}

void loop()
{
  int sound;
  int rawTemp;
  float tempC;

  // Check the envelope input
  sound = analogRead(PIN_SOUND_IN);

  // Convert envelope sound into a message
  Serial.print("Sound: ");
  Serial.print(sound);
  if(sound > 200)
  {
    Serial.println(" Quiet.");
  }
  else if( (sound > 99) && ( sound < 201) )
  {
    Serial.println(" Moderate.");
  }
  else if(sound < 100)
  {
    Serial.println(" Loud.");
  }
  
  // capture temperature
  Serial.print("Temp: ");
  rawTemp = analogRead(PIN_TEMP_IN);
  Serial.println(rawTemp);

  // Convert envelope sound into a message
  // A lot of examples divide the sensor reading by 1024. This is incorrect and should be 1023. There are 1024 values including 0 so this should be 1023.
  //Your Atmega is powered by 5V, and the datasheet of the Atmega states that its ADC has a definition of 1024 values (i.e. 10bits). 
  // So in your formula, 5/1024 is representing each voltage step represented by a bit:
  //If you read the application notes in the LM35 datasheet, you'll find the following formula:
  //Vout=10mV/°C
  //if you're binding the LM35 with a 200ohms resistor. So if you use the rule of three, you'll get:

  tempC = (referenceVoltage * rawTemp * 100) / 1023;
  Serial.print("TempC 100: ");
  Serial.println(tempC);
  tempC = (tempC * 9/5) + 32; 
  Serial.print("TempF: ");
  Serial.println(tempC);

  // pause for 1 second
  delay(1000);
}

