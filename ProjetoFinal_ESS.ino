#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <Servo.h>

Servo myservo;

int pos = 0;//variable for the position of servo

// Replace these with your WiFi network settings
const char* ssid = "DESKTOP-MJCUSK7 3500"; //replace this with your WiFi network name
const char* password = "qwerty12345678"; //replace this with your WiFi network password
const char* host = "192.168.137.1";
const char* url = "/api.php/";

#define echoPin 4 // attach pin D2 Arduino to pin Echo of HC-SR04
#define trigPin 2 //attach pin D3 Arduino to pin Trig of HC-SR04

// defines variables
long duration; // variable for the duration of sound wave travel
int distance; // variable for the distance measurement

void setup()
{
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin, INPUT); // Sets the echoPin as an INPUT

  delay(1000);
  Serial.begin(115200);

  WiFi.begin(ssid, password);

  Serial.println();
  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

  Serial.println("success!");
  Serial.print("IP Address is: ");
  Serial.println(WiFi.localIP());

  myservo.attach(13);//attach pin 2 GPIO to pin data of esp8266

}

void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
  // Displays the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");



  Serial.print("connecting to ");
  Serial.println(host); // Use WiFiClient class to create TCP connections
  WiFiClient client;
  const int httpPort = 8081;
  if (!client.connect(host, httpPort))
  {
    Serial.println("connection failed");
    return;
  }
  Serial.print("Requesting URL: ");
  Serial.println(url); //Post Data

  String postData;
  if (distance < 15) {
    postData = "filename=lugares&valor=1";
  } else {
    postData = "filename=lugares&valor=0";
  }
  HTTPClient http;
  http.begin("http://192.168.137.1:8081/api.php");
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");
  auto httpCode = http.POST(postData);
  delay (1000);
  Serial.println(httpCode); //Print HTTP return code
  String payload = http.getString();
  Serial.println(payload); //Print request response payload
  http.end(); //Close connection Serial.println();
  Serial.println("closing connection");


  HTTPClient httpPortao;
  httpPortao.begin("http://192.168.137.1:8081/files/lugares/portao.txt");
  //httpPortao.addHeader("Content-Type", "application/x-www-form-urlencoded");
  auto httpCodePor = httpPortao.GET();
  delay (1000);
  Serial.println(httpCodePor); //Print HTTP return code
  String payloadPort = httpPortao.getString();
  Serial.println(payloadPort); //Print request response payload
  httpPortao.end(); //Close connection Serial.println();
  Serial.println("closing connection");

  if (payloadPort == "1") {
    for (pos = 0; pos <= 180; pos += 1) // change here in the place 0 and 180 , into any two degrees you wish the servo to sweep.
    {

      myservo.write(pos);
      delay(15);
    }

    for (pos = 180; pos >= 0; pos -= 1)  // change here also  in the place 0 and 180 , into any two degrees you wish the servo to sweep.
    {
      myservo.write(pos);
      delay(15);
    }
    payloadPort = "0";
    HTTPClient http1;
    http1.begin("http://192.168.137.1:8081/api.php");
    http1.addHeader("Content-Type", "application/x-www-form-urlencoded");
    auto httpCode1 = http1.POST("filename=portao&valor=0");
    delay (1000);
    Serial.println(httpCode1); //Print HTTP return code
    String payload1 = http1.getString();
    Serial.println(payload1); //Print request response payload
    http1.end(); //Close connection Serial.println();
    Serial.println("closing connection");
  }



}
