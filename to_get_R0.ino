
void setup()
{
  pinMode(A3,INPUT);
  Serial.begin(9600);
}

void loop() {
  float sensor1_volt;
  float Rs_CO2;
  float R0;
  float sensorValue;
  sensorValue = (analogRead(A3));
  sensor1_volt = sensorValue * (5.0 / 1023.0);
  Rs_CO2 = ((5.0 * 32850) / sensor1_volt) - 32850;
  R0 = Rs_CO2 / 0.6230805382;
  Serial.print("R0 = ");
  Serial.println(R0);
  delay(1000);
}



