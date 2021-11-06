#include <WiFi.h>

const char* ssid = "Airtel_9034156560";
const char* password = "air37671";

const int led = 5;
const int ir1 = 18; //active low.
const int temp_sensor = 34;

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

void setup() {
  Serial.begin(115200);
  initWiFi();
  Serial.print("RRSI: ");
  Serial.println(WiFi.RSSI());
  pinMode(ir1,INPUT);
  pinMode(led,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  float temp_val = analogRead(temp_sensor);
  float val = temp_val/10;
  Serial.println(val);
  int ir1_val = digitalRead(ir1);
  if(val <= 38)
  {
    digitalWrite(led,HIGH);
  }
  else
  {
    digitalWrite(led,LOW);
  }
//  if(ir1_val == 0)
//  {
//    digitalWrite(led,HIGH);
//  }
//  else
//  {
//    digitalWrite(led,LOW);
//  }
}
