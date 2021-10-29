
#define BLYNK_PRINT Serial
#include <SPI.h>
#include <DHT.h>
#include <SimpleTimer.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>


char auth[] = "B_ilzoH-EVk1u8B3UoJxOMDmtZWg1sYx";
char ssid[] = "siritrae_2.4G";
char pass[] = "Vasayos0036";
BlynkTimer timer;
#define DHTPIN  D8
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
WidgetLED led1(V7);
WidgetLED led2(V8);
WidgetLED led3(V9);
WidgetLCD lcd(V2);

BLYNK_WRITE(V1)
{
  if( param.asInt() ==1)
  {
    Blynk.virtualWrite(V1, 1);
    digitalWrite(5, HIGH);
    digitalWrite(4, HIGH);
    digitalWrite(0, HIGH);
    digitalWrite(2, HIGH);
  }
}

void sendSensor()
{
  float h = dht.readHumidity();
  float t = dht.readTemperature(); // or dht.readTemperature(true) for Fahrenheit

  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  Blynk.virtualWrite(V5, h);
  Blynk.virtualWrite(V6, t);
}

void setup()
{
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
  dht.begin();
  pinMode (13, INPUT); // ขา INPUT ของโมดูล
  pinMode (5,OUTPUT);
  pinMode (4,OUTPUT);
  pinMode (0,OUTPUT);
  pinMode (2,OUTPUT);
  timer.setInterval(1000L, sendSensor);
}

void loop()
{
  Blynk.run();
  timer.run();
  
  float t = dht.readTemperature(); // ดึงค่าอุณหภูมิ

  if (t >24)
    digitalWrite(0, HIGH);
//    led1.on();
  else if (t >18)
    digitalWrite(0, LOW);
//    led1.off();
  if (t >28)
    digitalWrite(4, HIGH);
//    led2.on();
  else if (t >24)
    digitalWrite(4, LOW);
//    led2.off();
  if (t <=28)
    digitalWrite(5, HIGH);
//    led3.on();
  else if (t >28)
    digitalWrite(5, LOW);
//    led3.off();
    lcd.print(0, 0, "PM =");
    lcd.print(0, 1, "8 microgram/m^3");
}
