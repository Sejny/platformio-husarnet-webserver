/* Blink Example
   This example code is in the Public Domain (or CC0 licensed, at your option.)
   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/

#include <stdio.h>
#include <Arduino.h>
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include "husarnet.h"
#include <driver/gpio.h>

#define HOSTNAME  "husarnet-esp32"
#define JOIN_CODE "XXXXXXXXXXXXXX"
#define WIFI_SSID "wifi_ssid"
#define WIFI_PASS "wifi_pass"

AsyncWebServer server(80);

void setup() {
    Serial.begin(115200);
    pinMode(LED_BUILTIN, OUTPUT);

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
    digitalWrite(LED_BUILTIN, HIGH);
    delay(1000);
    digitalWrite(LED_BUILTIN, HIGH);
    delay(1000);
}
