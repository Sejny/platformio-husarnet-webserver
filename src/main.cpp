#include <stdio.h>
#include <Arduino.h>
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include "husarnet.h"

#define HOSTNAME  "husarnet-esp32"
#define JOIN_CODE " fc94:b01d:1803:8dd8:b293:5c7d:7639:932a/vc9tosbd96EFcy2fpo4orV "
#define WIFI_SSID "NETIO-LAN"
#define WIFI_PASS "AhojLidi19"

AsyncWebServer server(80);

void setup() {
    Serial.begin(115200);

    // Connect to the WiFi network
    WiFi.begin(WIFI_SSID, WIFI_PASS);
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.println("Connecting to WiFi...");
    }

    // Connect and join to the Husarnet network
    HusarnetClient* client = new HusarnetClient();
    client->join(HOSTNAME, JOIN_CODE);

    while (!client->isJoined()) {
        delay(1000);
        Serial.println("Connecting to Husarnet...");
    }

    Serial.println("Connected to Husarnet!");
    Serial.print("Husarnet IP address: ");
    Serial.println(client->getIpAddress().c_str());

    // Configure the HTTP server
    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send(200, "text/plain", "Hello, Husarnet!");
    });
    server.begin();
}
void loop() {
    // Loop function is free to do other tasks as the server and
    // the Husarnet stack is running in the background
    delay(1000);
}
