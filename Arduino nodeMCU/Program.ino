#include <ESP8266WiFi.h>

#define LED D2

const char* ssid = "FansElectronics";               // Nama WIFI kamu
const char* password = "BIGboss#";                  // Password Wifi
const char* host = "192.168.1.5";                 // Link website / Ip Server

bool Parsing = false;
String dataPHP, data[8];
void setup()
{
  Serial.begin(115200);
  Serial.println();

  Serial.printf("Connecting to %s ", ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println(" connected");

  pinMode(LED, OUTPUT);
  digitalWrite(LED, HIGH);
}


void loop()
{
  WiFiClient client;

  Serial.printf("\n[Connecting to %s ... ", host);
  if (client.connect(host, 80)) {
    Serial.println("connected]");
    Serial.println("[Sending a request]");

    String url = "tutorial-iot/baca-data.php?id=1"; // Lokasi File Baca Data
    client.print(String("GET /") + url + " HTTP/1.1\r\n" +
                 "Host: " + host + "\r\n" +
                 "Connection: close\r\n" +
                 "\r\n"
                );

    Serial.println("[Response:]");
    while (client.connected())
    {
      if (client.available())
      {
        dataPHP = client.readStringUntil('\n');
        int q = 0;
        Serial.print("Data Masuk : ");
        Serial.print(dataPHP);
        Serial.println();

        data[q] = "";
        for (int i = 0; i < dataPHP.length(); i++) {
          if (dataPHP[i] == '#') {
            q++;
            data[q] = "";
          }
          else {
            data[q] = data[q] + dataPHP[i];
          }
        }
        Serial.println(data[1].toInt());
        digitalWrite(LED, data[1].toInt());
        Parsing = false;
        dataPHP = "";
      }
    }
    client.stop();
    Serial.println("\n[Disconnected]");
  }
  else
  {
    Serial.println("connection failed!]");
    client.stop();
  }
  delay(1000);
}
