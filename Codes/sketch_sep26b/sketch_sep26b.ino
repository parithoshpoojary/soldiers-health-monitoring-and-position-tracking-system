int val;
int tempPin = A0;

void setup()
{
  Serial.begin(9600);
}
void loop()
{
  val = analogRead(tempPin);
  float temp = ((val/1024.0)*5000);
  float cel = (temp/10) - 200;
  float farh = (cel*9)/5 + 32;
  Serial.print("TEMPRATURE = ");
  Serial.print(cel);
  Serial.print("C   ");
  Serial.print(farh);
  Serial.print("F");
  Serial.println();
  delay(1000);
}
