#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>
//här är alla bibliotek du behöver


const char* ssid = "WIFI NAME";
const char* password = "WIFI PASS";
//skriv in dina uppgifter
// arp -a (för att se connectade enheter till wifit)
void setup() {

  Serial.begin(115200);
    //sätter uppladdningshastighet till serial
  Serial.println("Booting");
   //utskrift i terminalen bara
  WiFi.mode(WIFI_STA);
    //sätter wifistate
  
  WiFi.begin(ssid, password);
   //koppla upp wifi
  while (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.println("Connection Failed! Rebooting...");
    delay(5000);
    ESP.restart();
  }

  ArduinoOTA.onStart([]() {
    Serial.println("Start updating ");
  });
//här börjar Over the air-uppladdningen
  ArduinoOTA.setHostname("Popcorn");
  
  ArduinoOTA.onEnd([]() {
    Serial.println("\nEnd");
  });
//här avslutas den, eller ja, vi printar grejer när den avslutas här, vi måste inte

  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
  });
//här är under tiden det laddas upp, också bara en printfunktion, denna och de två funktionerna innan är inte ett måste men schysst utskrift

  ArduinoOTA.onError([](ota_error_t error) {
    Serial.printf("Error[%u]: ", error);
    if (error == OTA_AUTH_ERROR) Serial.println("Auth Failed");
    else if (error == OTA_BEGIN_ERROR) Serial.println("Begin Failed");
    else if (error == OTA_CONNECT_ERROR) Serial.println("Connect Failed");
    else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive Failed");
    else if (error == OTA_END_ERROR) Serial.println("End Failed");
  });
//utskrift för error, funktionen lyssnar på felkoder och skriver ut rätt felmeddelande om det blir fel 

  ArduinoOTA.begin();
  Serial.println("Ready");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  //här startar vi upp ArduinoOTA
}

void loop() {
  ArduinoOTA.handle();
  //här kör vi arduino OTA
}
