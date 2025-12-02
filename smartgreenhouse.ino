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
  Serial.println("Inisialisasi sistem...\n");

  // Pin modes
  pinMode(LDR_PIN, INPUT);
  pinMode(SOIL_PIN, INPUT);
  pinMode(PIR_PIN, INPUT);
  pinMode(FLAME_PIN, INPUT);
  pinMode(OBJECT_PIN, INPUT);
  // Connect WIFI
  connectWiFi();
  // Setup NTP Time
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  Serial.println("Sinkronisasi waktu dengan NTP...");
  delay(2000);
  // Firebase config
  config.api_key = API_KEY;
  config.database_url = DATABASE_URL;
  auth.user.email = USER_EMAIL;
  auth.user.password = USER_PASSWORD;
  config.token_status_callback = tokenStatusCallback;
  Serial.println("Menghubungkan ke Firebase...");

  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);

  unsigned long fbStart = millis();
  while ((!Firebase.ready()) && (millis() - fbStart < 10000)) {
    Serial.print(".");
    delay(500);
  }

  if (Firebase.ready()) {
    Serial.println("\n\n✓ Firebase terhubung!");
    Serial.println("Sistem siap monitoring!\n");
  } else {
    Serial.println("\n\nX Firebase gagal terhubung, sistem tetap berjalan...\n");
  }
}
void loop() {
    // Cek koneksi WiFi
    if (WiFi.status() != WL_CONNECTED) {
      Serial.println("WiFi terputus! Mencoba reconnect...");
      connectWiFi();
    }
  
    // Update sensor secara berkala
    unsigned long now = millis();
    if (now - lastSensorUpdate > sensorInterval) {
      lastSensorUpdate = now;
      bacaDanKirimData();
    }
  }
  
  // Fungsi koneksi WiFi
  void connectWiFi() {
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    Serial.print("Menghubungkan ke WiFi");
    unsigned long start = millis();
    while (WiFi.status() != WL_CONNECTED) {
      Serial.print(".");
      delay(500);
      if (millis() - start > 20000) {
        Serial.println("\n\nX Gagal terhubung WiFi - restart...");
        ESP.restart();
      }
    }
    Serial.println();
    Serial.println("✓ WiFi Terhubung!");
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());
  }
  void loop() {
    // Cek koneksi WiFi
    if (WiFi.status() != WL_CONNECTED) {
      Serial.println("WiFi terputus! Mencoba reconnect...");
      connectWiFi();
    }
  
    // Update sensor secara berkala
    unsigned long now = millis();
    if (now - lastSensorUpdate > sensorInterval) {
      lastSensorUpdate = now;
      bacaDanKirimData();
    }
  }
  
  // Fungsi koneksi WiFi
  void connectWiFi() {
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    Serial.print("Menghubungkan ke WiFi");
    unsigned long start = millis();
    while (WiFi.status() != WL_CONNECTED) {
      Serial.print(".");
      delay(500);
      if (millis() - start > 20000) {
        Serial.println("\n\nX Gagal terhubung WiFi - restart...");
        ESP.restart();
      }
    }
    Serial.println();
    Serial.println("✓ WiFi Terhubung!");
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());
  }