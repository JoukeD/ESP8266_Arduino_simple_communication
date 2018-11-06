# ESP8266_Arduino_simple_communication
Simple code to make universal communication between a ESP8266-chip and Arduino easy.

# How to use

ESP8266 should be flashed with latest [NodeMCU firmware](https://github.com/nodemcu/nodemcu-firmware).

After that upload this sketch to the ESP8266 via the Arduino IDE.

Connect an Arduino via serial to the ESP8266.

All the serial commands starting with a "<" and end with a ">" wil be read by the ESP8266, according to the [brainchild of Robin2](https://forum.arduino.cc/index.php?topic=288234.0).

Commands that need multiple value's will have the values split with ":::".

## Commands

Send the following commands via serial to the ESP8266 to perform the specified operations:

### Connect to/Change WIFI network

To connect to a WIFI network send the following command over serial to the ESP8266:

`<ssid:::password>`

Where `ssid` must be the ssid of the wifi network to connect to and `password` the password.

ESP8266 Response:

`<connected:::local-ip-address>`

Where `local-ip-address` will be filled with the local-ip-address obtained by the local DHCP-server.

### GET-request to url:

`<url-with-parameters>`

If the request was succesfull the ESP8266 will send the response:

`<payload>`

Where `payload` will be the contents of the url requested.

If the request was unsuccesfull the ESP8266 will return:

`<httpCode>`

Where `httpCode`will be a Http-code according to the following set of codes:

HTTPC_ERROR_CONNECTION_REFUSED  = -1
HTTPC_ERROR_SEND_HEADER_FAILED  = -2
HTTPC_ERROR_SEND_PAYLOAD_FAILED = -3
HTTPC_ERROR_NOT_CONNECTED       = -4
HTTPC_ERROR_CONNECTION_LOST     = -5
HTTPC_ERROR_NO_STREAM           = -6
HTTPC_ERROR_NO_HTTP_SERVER      = -7
HTTPC_ERROR_TOO_LESS_RAM        = -8
HTTPC_ERROR_ENCODING            = -9
HTTPC_ERROR_STREAM_WRITE        = -10
HTTPC_ERROR_READ_TIMEOUT        = -11
Source [ESP8266HTTPClient.h by Arduino](https://github.com/esp8266/Arduino/blob/master/libraries/ESP8266HTTPClient/src/ESP8266HTTPClient.h)
