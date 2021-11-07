#include <WiFi.h>

const char* ssid = "Airtel_9034156560";
const char* password = "air37671";

const int led = 5;
const int ir1 = 18; //active low. //will be for the input of the visitor.
const int ir2 = 19; // will be for the outgoing of the visitor.
const int temp_sensor = 34;

int visitor_in = 0;
int visitor_out = 0;

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
  int ir2_val = digitalRead(ir2);
  if(val <= 20)
  {
    digitalWrite(led,LOW);
  }
  else
  {
    digitalWrite(led,HIGH);
  }

  if(ir1_val == 0)
  {
    visitor_in++;
    //api call to set the visitor_in.
  }
  
  if(ir2_val == 0)
  {
    if(visitor_in != 0)
    {
      visitor_out++;
      visitor_in--;
    }  
    //api call to set both.
  }

//  Serial.println("visitor_in");
//  Serial.println(visitor_in);
//  Serial.println("visitor_out");
//  Serial.println(visitor_out);
  delay(1000);
  
//  if(ir1_val == 0) // this means when the value is 0 the person is there.
//  {
//    digitalWrite(led,HIGH);
//  }
//  else
//  {
//    digitalWrite(led,LOW);
//  }
}
