int MQ135 = A0;

void setup()
{
  Serial.begin(9600);
  pinMode(MQ135, INPUT);
  pinMode(2, INPUT);
}

void loop()
{
  float MQ135_volt;
  float RS_CO2;
  float R0;
  float Slope;
  float Y_intercept;
  float MQ135Value = (analogRead(MQ135));
  float Y_Value;
  MQ135_volt = MQ135Value * (5.0 / 1023.0);
  RS_CO2 = ((5.0 * 32850) / MQ135_volt) - 32850;
  R0 = 149250;
  Slope = -0.370955166;
  Y_intercept = 0.7597917824;
  Y_Value = RS_CO2 / R0;

  double ppm = pow(10, (log10(Y_Value) - Y_intercept) / Slope);
  Serial.print(ppm);
  Serial.println(" ppm");
  delay(1000);
}
