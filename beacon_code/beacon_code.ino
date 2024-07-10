#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <DHT.h>

const char* ssid = "IoT_CyberSecurity";
const char* password = "10072024";

const char* serverIP = "192.168.250.98";
const int serverPort = 8000;

#define DHTPIN 14
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

const int mq6Pin = A0;

const int yellowLEDPin = 5;
const int greenLEDPin = 4;

void setup() {
  Serial.begin(115200);
  pinMode(yellowLEDPin, OUTPUT);
  pinMode(greenLEDPin, OUTPUT);
  digitalWrite(greenLEDPin, LOW);
  dht.begin();

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    digitalWrite(yellowLEDPin, HIGH);
    delay(500);
    digitalWrite(yellowLEDPin, LOW);
    delay(500);
    Serial.println("Connecting to WiFi...");
  }
  digitalWrite(yellowLEDPin, LOW);
  digitalWrite(greenLEDPin, HIGH);
  Serial.println("Connected to WiFi");
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    float h = dht.readHumidity();
    float t = dht.readTemperature();
    int gas = analogRead(mq6Pin);

    if (isnan(h) || isnan(t)) {
      Serial.println("Failed to read from DHT sensor!");
      return;
    }

    WiFiClient client;
    String url = "http://" + String(serverIP) + ":" + String(serverPort) + "/data";
    HTTPClient http;
    http.begin(client, url);
    http.addHeader("Content-Type", "application/json");

    String jsonData = "{\"temperature\":" + String(t) + ", \"humidity\":" + String(h) + ", \"gas\":" + String(gas) + "}";
    int httpResponseCode = http.POST(jsonData);
    if (httpResponseCode > 0) {
      String response = http.getString();
      Serial.print(httpResponseCode);
      Serial.println(": " + response);
    } else {
      Serial.print(httpResponseCode);
      Serial.println(": Error on sending POST");
    }
    http.end();
  } else {
    Serial.println("WiFi not connected");
  }
  delay(3000);
}
