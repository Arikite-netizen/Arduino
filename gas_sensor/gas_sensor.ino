#include <LiquidCrystal.h>
#include <MQ135.h>
#include <Adafruit_Sensor.h>
#include <forcedClimate.h>  // include adafruit library for BME280 sensor
#include <Wire.h>

#define PIN_MQ135 A0  // define the analog pin for the gas sensor mq135
MQ135 mq135_sensor(PIN_MQ135);

#define PIN_BME_SDA A5                    // define the analog pin for BME sensor
#define PIN_BME_SCL A4
ForcedClimate climateSensor = ForcedClimate();


#define SEALEVELPRESSURE_HPA (1013.25) // sea pressure defined

int sensorValue;
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup()
{  lcd.begin(16, 2);
   Serial.begin(9600);                            // sets the serial port to 9600

   climateSensor.begin();
}

void loop()
{ 
  float ppm = mq135_sensor.getPPM();    // get ppm value for mq135
  
  sensorValue = analogRead(0);       // read analog input pin 0 of mq135 sensor
  Serial.print("AirQua=");
  Serial.print(sensorValue, DEC);               // prints the value read
  
  Serial.print("PPM=");
  Serial.print(ppm);               // prints the value read
  lcd.setCursor(0,0);

  Serial.print("Temperature: ");                      //analog readings from BME280 in forcedclimate sensor
  Serial.print(climateSensor.getTemperatureCelcius());
  Serial.print(", Humidity: ");
  Serial.print(climateSensor.getRelativeHumidity());
  Serial.print(" and Pressure: ");
  Serial.print(climateSensor.getPressure());
  Serial.println();
  
  lcd.print("MQ135: ");
  lcd.print("ArQ=");
  lcd.print(sensorValue,DEC);
  lcd.print(" ");
  lcd.print("PPM= ");
  lcd.print(ppm);

   for (int positionCounter = 0; positionCounter < 16; positionCounter++)
   {
    // scroll one position Right:
    lcd.scrollDisplayRight();
    // wait a bit:
    delay(1000);
   }
// wait 1000ms for next reading
// lets start another sensor BME 280

  lcd.setCursor(0, 0);
  lcd.print("Temperature: ");
  lcd.print(climateSensor.getTemperatureCelcius());
  lcd.write(1);
  lcd.print("C");
 
  lcd.setCursor(0, 1);
  lcd.print("Humidity: ");
  lcd.print(climateSensor.getRelativeHumidity());
  lcd.print("%");
 
  lcd.setCursor(0, 2);
  lcd.print("Pressure: ");
  lcd.print(climateSensor.getPressure());
  lcd.print("hPa");

  delay(1000); 
  lcd.clear(); 
}
