/*
  AnalogReadSerial

  Reads an analog input on pin 0, prints the result to the Serial Monitor.
  Graphical representation is available using Serial Plotter (Tools > Serial Plotter menu).
  Attach the center pin of a potentiometer to pin A0, and the outside pins to +5V and ground.

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/AnalogReadSerial

*/
#include <WiFi.h>

const char* ssid = "Airtel_9034156560";
const char* password = "air37671";

const int led = 5;
const int ir1 = 18; //active low.
const int temp_sensor = 15;

void initWiFi() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi ..");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(1000);
  }
  Serial.println("");
  Serial.println("ESP32 Connected!, Local IP: ");
  Serial.println(WiFi.localIP());
}

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(115200);
//  initWiFi();
//  Serial.print("RRSI: ");
//  Serial.println(WiFi.RSSI());
  pinMode(ir1,INPUT);
  pinMode(led,OUTPUT);
}

// the loop routine runs over and over again forever:
void loop() {
  // read the input on analog pin 0:
  int temp_val = analogRead(temp_sensor);
  Serial.println(temp_val);
  delay(1000);
  int ir1_val = digitalRead(ir1);
  if(ir1_val == 0)
  {
    digitalWrite(led,HIGH);
  }
  else
  {
    digitalWrite(led,LOW);
  }
}
