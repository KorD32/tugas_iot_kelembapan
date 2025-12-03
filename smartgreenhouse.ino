#include <WiFi.h>
#include <firebase_esp_auth.h>
#include <addons/TokenHelper.h>
#include <addons/RTDBHelper.h>
#include <time.h>

const char* ssid = "Mafia lantai 3";
const char* password = "d0tkerasj4l4";

#define API_KEY "AIzaSyBgwBQ1UQLMVHaUmCVElxVawQwxmdcXy00"
#define DATABASE_URL "https://kelembapan-503da-default-rtdb.asia-southeast1.firebasedatabase.app"
#define USER_EMAIL "apalah@gmail.com"
#define USER_PASSWORD "123456"

#define dht 23
#define ldr 19
#define soil 18

void setup() {
  Serial.begin(115200);
  delay(100);
  Serial.println("\n=== SMART PLANT GREENHOUSE ===");

  pinMode(LDR_PIN, INPUT);
  pinMode(SOIL_PIN, INPUT);
  pinMode(PIR_PIN, INPUT);
  pinMode(FLAME_PIN, INPUT);
  pinMode(OBJECT_PIN, INPUT);
  connectWiFi();
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  delay(2000);
  config.api_key = API_KEY;
  config.database_url = DATABASE_URL;
  auth.user.email = USER_EMAIL;
  auth.user.password = USER_PASSWORD;
  config.token_status_callback = tokenStatusCallback;
  Serial.println("firebase connecting");

  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);

  unsigned long fbStart = millis();
  while ((!Firebase.ready()) && (millis() - fbStart < 10000)) {
    Serial.print(".");
    delay(500);
  }

  if (Firebase.ready()) {
    Serial.println("\n\n firebase terhubung");
    Serial.println("sistem siap\n");
  } else {
    Serial.println("\n\n gagal\n");
  }
}
void loop() {
    if (WiFi.status() != WL_CONNECTED) {
      Serial.println("reconnect wifi");
      connectWiFi();
    }
  
    unsigned long now = millis();
    if (now - lastSensorUpdate > sensorInterval) {
      lastSensorUpdate = now;
      bacaDanKirimData();
    }
  }
  
  void connectWiFi() {
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    Serial.print("connecting wifi");
    unsigned long start = millis();
    while (WiFi.status() != WL_CONNECTED) {
      Serial.print(".");
      delay(500);
      if (millis() - start > 20000) {
        Serial.println("\n\n gagal terhubung");
        ESP.restart();
      }
    }
    Serial.println();
    Serial.println("terhubung");
    Serial.print("IP ");
    Serial.println(WiFi.localIP());
  }
  void loop() {
    if (WiFi.status() != WL_CONNECTED) {
      Serial.println("wifi reconnect");
      connectWiFi();
    }
  
    unsigned long now = millis();
    if (now - lastSensorUpdate > sensorInterval) {
      lastSensorUpdate = now;
      bacaDanKirimData();
    }
  }
  
  void connectWiFi() {
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    Serial.print("Mconnecting wifi");
    unsigned long start = millis();
    while (WiFi.status() != WL_CONNECTED) {
      Serial.print(".");
      delay(500);
      if (millis() - start > 20000) {
        Serial.println("\n\n gagal connect");
        ESP.restart();
      }
    }
    Serial.println();
    Serial.println("berhasil terhubung");
    Serial.print("IP:");
    Serial.println(WiFi.localIP());
  }