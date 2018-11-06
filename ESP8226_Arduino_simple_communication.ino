//Program for a Serial.println("WIFI Not Connected"); for an Arduino to communicate with
//Make the ESP8266 connect with a wifi network by sendin the following string via serial: "<ssid:::password>"
//After that make a GET request by sending the serial string: "<url>"
//JoukeD 5-10-2018

#include <ESP8266WiFi.h>

#include <ESP8266HTTPClient.h>

long mEVLT = 0;
const byte numChars = 150;
char receivedChars[numChars];
char ssid[75];
char password[75];
boolean newData = false;

void setup() {
  Serial.begin(115200);
}

void loop() {
  readSerial();
  processData();
}

void processData() {
  if (newData) {
    char * pch = strstr(receivedChars, ":::");
    if (pch) {
      strncpy(ssid, receivedChars, (pch - receivedChars));
      strncpy(password, receivedChars + (pch - receivedChars) + 1, strlen(receivedChars) - ((pch - receivedChars) + 1));
      connectWifi();
    } else {
      httpRequest();
    }
    newData = false;
  }
}

void connectWifi() {
  WiFi.begin(ssid, password);
  while ( WiFi.status() != WL_CONNECTED ) {
    yield();
  }
  Serial.print("<connected:::");
  Serial.print(WiFi.localIP());
  Serial.println(">");
}

void readSerial() {
  static boolean recvInProgress = false;
  static byte ndx = 0;
  char startMarker = '<';
  char endMarker = '>';
  char rc;

  while (Serial.available() > 0 && newData == false) {
    rc = Serial.read();

    if (recvInProgress == true) {
      if (rc != endMarker) {
        receivedChars[ndx] = rc;
        ndx++;
        if (ndx >= numChars) {
          ndx = numChars - 1;
        }
      }
      else {
        receivedChars[ndx] = '\0'; // terminate the string
        recvInProgress = false;
        ndx = 0;
        newData = true;
      }
    }

    else if (rc == startMarker) {
      recvInProgress = true;
    }
    yield();
  }
}

void httpRequest() {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin(receivedChars);
    int httpCode = http.GET();
    if (httpCode > 0) {
      String payload = http.getString();
      Serial.print("<");
      Serial.print(payload);
      Serial.println(">");
    } else {
      Serial.print("<");
      Serial.print(httpCode);
      Serial.println(">");
    }
    http.end();
  } else {
    Serial.println("<not_connected>");
  }
}
