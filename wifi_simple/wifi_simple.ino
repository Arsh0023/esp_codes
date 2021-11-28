#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "";
const char* password = "";

const int led = 5;
const int ir1 = 18; //active low. //will be for the input of the visitor.
const int ir2 = 19; // will be for the outgoing of the visitor.
const int temp_sensor = 34;

float max_temp = 29;
int visitor_in = 0;
int visitor_out = 0;

String host_in = "https://arsh0023.pythonanywhere.com/api/setvisitorin/123/"; //make sure to check the passphrase.
String host_out = "https://arsh0023.pythonanywhere.com/api/setvisitorout/123/";
String temperature_url = "https://arsh0023.pythonanywhere.com/api/settemp/123/";

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
  float temp_val = analogRead(temp_sensor);
  float val = temp_val/10;
  Serial.println(val);
  int ir1_val = digitalRead(ir1);
  int ir2_val = digitalRead(ir2);
  if(val <= max_temp)
  {
    digitalWrite(led,LOW);
  }
  else
  {
    digitalWrite(led,HIGH);
  }

  int flag = 0;
  
  if((WiFi.status() == WL_CONNECTED))
  {
    flag = 1;
  }
  
  HTTPClient http;
  HTTPClient http1;
  HTTPClient t_http;
  
  if(ir1_val == 0 and flag == 1)
  {
    visitor_in++;
    //api call to set the visitor_in.
    String url = host_in+String(visitor_in); //cool way to convert int to string.
//    Serial.println(url);
    http.begin(url);
    int httpCode = http.GET(); 
  }
  
  if(ir2_val == 0)
  {
    if(visitor_in != 0 and flag == 1)
    {
      visitor_out++;
      visitor_in--;
      String url_in = host_in+String(visitor_in);
      String url_out = host_out+String(visitor_out);
      http.begin(url_in);
      int httpCode = http.GET();
//      Serial.println(url_in);
      http1.begin(url_out);
      int httpCode1 = http1.GET();
//      Serial.println(url_out);
    }  
  }
  

  Serial.println("visitor_in");
  Serial.println(visitor_in);
  Serial.println("visitor_out");
  Serial.println(visitor_out);
  http.end();
  http1.end();
  String set_temp = temperature_url+String(val);
  t_http.begin(set_temp);
  int t_code = t_http.GET();
  t_http.end();
  delay(500);
  
//  if(ir1_val == 0) // this means when the value is 0 the person is there.
//  {
//    digitalWrite(led,HIGH);
//  }
//  else
//  {
//    digitalWrite(led,LOW);
//  }
}
