#include <WiFi.h>
int led = 2;

WiFiClient client;
WiFiServer server(80);

void setup() {
  // put your setup code here, to run once:
  pinMode(led,OUTPUT);

  Serial.begin(9600);
  WiFi.begin("Airtel_9034156560", "air37671");
  while(WiFi.status() != WL_CONNECTED)
  {
    Serial.print("..");
    delay(200);
  }
  Serial.println();
  Serial.println("ESP32 is Connected!, IP address:");
  Serial.println(WiFi.localIP());
}

void loop() {
  // put your main code here, to run repeatedly:
//  digitalWrite(led,HIGH);
//  delay(100);
//  digitalWrite(led,LOW);
//  delay(100);
  client = server.available();
  if (client == 1)
  {  
    String request =  client.readStringUntil('\n');
    Serial.println(request);
//    request.trim();
//    if(request == "GET /ledon HTTP/1.1")
//    {
//      digitalWrite(led, HIGH);
//    }
//    if(request == "GET /ledoff HTTP/1.1")
//    {
//      digitalWrite(led, LOW);
//    }
  }





  
}
