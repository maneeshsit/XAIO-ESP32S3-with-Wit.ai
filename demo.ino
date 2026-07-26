// Include WitAITTS Library

#include <WitAITTS.h>
#include <ESP32I2SAudio.h>
#include <BackgroundAudio.h>

// Wi-fi and wit.ai credentials
const char* WIFI_SSID = "";
const char* WIFI_PASSWORD = "";
const char* WIT_TOKEN = "";

// Connections to I2S amplifiier
#define CUSTOM_BCLK 7
#define CUSTOM_LRC 8
#define CUSTOM_DIN 9

// Create wit.ai object
  WitAITTS tts(CUSTOM_BCLK, CUSTOM_LRC, CUSTOM_DIN);

// Setup
void setup() {
  
  // Start Serial Monitor
  Serial.begin(115200);
  delay(1000);
  Serial.println("ESP32 with wit.ai demo");

  // Set wit.ai Debug Level
  tts.setDebugLevel(DEBUG_INFO);

  // Connect to Wi-Fi and wit.ai
  if (tts.begin(WIFI_SSID, WIFI_PASSWORD, WIT_TOKEN)) {
    Serial.println("✓ TTS Ready!\n");
    tts.setVoice("wit$Colin");
    tts.setStyle("default");
    tts.setSpeed(100);
    tts.setPitch(100);
    tts.setGain(0.3);
    tts.printConfig();
    Serial.println("Type any text and press Enter to speak:\n");
  } else {
    Serial.println("✗ TTS initialization failed!");
    Serial.println("Check WiFi credentials and Wit.ai token");
  }
}

//Loop
void loop() {
  // Check for data
    tts.loop();

  // Read text from Serial monitor
  if (Serial.available()) {
    String text = Serial.readStringUntil('\n');
    text.trim();
    if (text.length() > 0) {
      Serial.println("Speaking: " + text);
      tts.speak(text);
    }
  }
}
