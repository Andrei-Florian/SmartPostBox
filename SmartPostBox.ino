// Universum | Universum Projects > SmartPostBox

// Andrei Florian 23/JUN/2018 - 24/JUN/2018

#include <SigFox.h>
#include <ArduinoLowPower.h>

bool proDebug = 1;
int lightIntensity;
int LEDPin = 13;
int laserPin = 1;
int pos;

void reboot() 
{
  Serial.println("  Restarting Device");
  NVIC_SystemReset();
  while(1);
}

void setup()
{
  pinMode(LEDPin, OUTPUT);
  pinMode(laserPin, OUTPUT);
  digitalWrite(laserPin, HIGH);

  if(proDebug)
  {
    Serial.begin(9600);
    while(!Serial) {};
    delay(1000);
    Serial.println("Universum");
    delay(500);
    Serial.println("  SmartPostBox");
    delay(500);
    Serial.println("    Andrei Florian");
    delay(2000);
    Serial.println("");
    Serial.println("");

    Serial.println("Initialising SigFox Module");
  }
  
  if(!SigFox.begin())
  {
    if(proDebug)
    {
      Serial.println("  Error - SigFox Module Responded with Error");
    }
    reboot();
  }

  if(proDebug)
  {
    Serial.println("  Success - Module Initialised");

    Serial.println("Starting SigFox");
  }

  SigFox.begin();

  if(proDebug)
  {
    Serial.println("  Success - SigFox Module Online");

    Serial.println("Setup Complete");
    Serial.println("  Begining Loop");
    Serial.println("");
  }
  
  digitalWrite(LEDPin, HIGH);
  delay(500);
  digitalWrite(LEDPin, LOW);
}

void loop()
{
  lightIntensity = analogRead(A1);

  if(lightIntensity < 800)
  {
    if(pos == 0)
    {
      pos = 1;

      if(proDebug)
      {
        Serial.println("Letter Detected");
        Serial.println("Initialising Sending Protocol");
        Serial.println("  Pending Package");
      }

      if(proDebug)
      {
        Serial.println("    Success");
        Serial.println("  Starting Parse Procedure");
      }

      SigFox.beginPacket();
      
      if(proDebug)
      {
        Serial.println("  Parsing Packet");
      }

      SigFox.print(" ");
      int ret = SigFox.endPacket(true);
      
      if(proDebug)
      {
        Serial.println("    Success");
  
        Serial.println("Algorithm Compltete");
        Serial.println("  Waiting for Letter removal");
        Serial.println("");
      }
    }
  }
  else
  {
    pos = 0;
  }
}
