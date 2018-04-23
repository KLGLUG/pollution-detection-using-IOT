#include <SoftwareSerial.h>
int MQ135 = A2;
SoftwareSerial mySerial(9, 10);

void setup()
{
  mySerial.begin(9600);   // Setting the baud rate of GSM Module  
  Serial.begin(9600);    // Setting the baud rate of Serial Monitor (Arduino)
  pinMode(MQ135, INPUT);
  delay(100);
}


void loop()
{
  if (Serial.available()>0)
   switch(Serial.read())
  {
    case 's':
      SendMessage();
      break;
    case 'r':
      RecieveMessage();
      break;
  }

 if (mySerial.available()>0)
   Serial.write(mySerial.read());
 if (mySerial.available()>0)
   SendMessage();
}


 void SendMessage()
{
  float MQ135_volt;
  float RS_CO2;
  float R0;
  float Slope;
  float Y_intercept;
  float Y_Value;
  float MQ135Value = (analogRead(MQ135));
  MQ135_volt = MQ135Value * (5.0 / 1023.0);
  RS_CO2 = ((5.0 * 32850) / MQ135_volt) - 32850;
  R0 = 149250;
  Slope = -0.370955166;
  Y_intercept = 0.7597917824;
  Y_Value = RS_CO2 / R0;

  double ppm = pow(10, (log10(Y_Value) - Y_intercept) / Slope);
  Serial.print(ppm);
  Serial.println("ppm");
  //double ppm=400;
  mySerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);  // Delay of 1000 milli seconds or 1 second
  mySerial.println("AT+CMGS=\"+918919353267\"\r"); // Replace x with mobile number
  delay(1000);
  if(ppm<1000)
  {
    mySerial.println("Fresh air. Feel free to breath");
  }
  else if(ppm>1000&&ppm<2000)
  {
    mySerial.println("Some what dangerous!!! try to move away");
  }
  else if(ppm>2000)
  {
    mySerial.println("Dangerous air. Don't breath even if you die");
  }
  delay(100);
  mySerial.println((char)26);// ASCII code of CTRL+Z
  delay(1000);
}


 void RecieveMessage()
{
  mySerial.println("AT+CNMI=2,2,0,0,0"); // AT Command to receive a live SMS
  delay(1000);
 }
