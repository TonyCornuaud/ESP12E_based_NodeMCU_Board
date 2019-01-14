/*
   Copyright (c) 2015, Majenko Technologies
   All rights reserved.

   Redistribution and use in source and binary forms, with or without modification,
   are permitted provided that the following conditions are met:

 * * Redistributions of source code must retain the above copyright notice, this
     list of conditions and the following disclaimer.

 * * Redistributions in binary form must reproduce the above copyright notice, this
     list of conditions and the following disclaimer in the documentation and/or
     other materials provided with the distribution.

 * * Neither the name of Majenko Technologies nor the names of its
     contributors may be used to endorse or promote products derived from
     this software without specific prior written permission.

   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
   ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
   WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
   DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
   ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
   (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
   LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
   ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
   (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
   SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

/* Create a WiFi access point and provide a web server on it. */

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

/* Set these to your desired credentials. */
const char *ssid = "ESPap";
const char *password = "thereisnospoon";

ESP8266WebServer server(80);

/* Just a little test message.  Go to http://192.168.4.1 in a web browser
   connected to this access point to see it.
*/

/* See Hackable Magazine #24 May-June 2018 */
static const char *INDEX_HTML = 
"<!DOCTYPE html>\n"
"<html>\n"
"<head>\n"
"<meta charset=\"UTF-8\">\n"
"<title>ESP8266 WiFi Access Point to control LEDs</title>\n"
"</head>\n"
"<body>\n"
"<h1> Control LED</h1>\n"
"<form action=\"/blue_LED\" method=\"get\" target=\"hiddenFrame\">\n"
"<input value=\"Blue LED\" type=\"submit\" class=\"punch\">\n"
"</form>\n"
"<form action=\"/red_LED\" method=\"get\" target=\"hiddenFrame\">\n"
"<input value=\"Red LED\" type=\"submit\" class=\"punch\">\n"
"</form>\n"
"<iframe name=\"hiddenFrame\" class=\"notif\"></iframe>\n"
"</body>\n"
"</html>\n"
;
uint8_t ESP12_F_GPIO_02_BLUE_LED = D4;
uint8_t NODE_MCU_GPIO_16_RED_LED = D0;

/* See Hackable Magazine #24 May-June 2018 */

void handleRoot() {
  //server.send(200, "text/html", "<h1>You are connected</h1>");
  /* See Hackable Magazine #24 May-June 2018 */
  server.send(200, "text/html", INDEX_HTML);
  /* See Hackable Magazine #24 May-June 2018 */
}

/* See Hackable Magazine #24 May-June 2018 */
void handleBlueLED() {
  server.send(200, "text/html", "Energize Only Blue LED");
  digitalWrite(ESP12_F_GPIO_02_BLUE_LED, LOW);
  digitalWrite(NODE_MCU_GPIO_16_RED_LED, HIGH);
}

void handleRedLED() {
  server.send(200, "text/html", "Energize Only Red LED");
  digitalWrite(ESP12_F_GPIO_02_BLUE_LED, HIGH);
  digitalWrite(NODE_MCU_GPIO_16_RED_LED, LOW);
}
/* See Hackable Magazine #24 May-June 2018 */

void setup() {
  delay(1000);
  Serial.begin(115200);
  Serial.println();
  Serial.print("Configuring access point...");
  /* You can remove the password parameter if you want the AP to be open. */
  WiFi.softAP(ssid, password);

  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
  server.on("/", handleRoot);
  /* See Hackable Magazine #24 May-June 2018 */
  pinMode(ESP12_F_GPIO_02_BLUE_LED, OUTPUT);
  pinMode(NODE_MCU_GPIO_16_RED_LED, OUTPUT);
  server.on("/blue_LED", handleBlueLED);
  server.on("/red_LED", handleRedLED);
  /* See Hackable Magazine #24 May-June 2018 */
  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();
}
