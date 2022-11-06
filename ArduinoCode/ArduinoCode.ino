#include "MyDuckClass.h"
//#include "Arduino.h”
#include <WiFi.h>
MyDuckClass roboDuck(27,14,25,26);

// Replace with your network credentials
const char* ssid = "Pixel_9170";
const char* password = "HelloWorld123";

// Set web server port number to 80
WiFiServer server(80);

// Variable to store the HTTP request
String header;

// Current time
unsigned long currentTime = millis();
// Previous time
unsigned long previousTime = 0; 
// Define timeout time in milliseconds (example: 2000ms = 2s)
const long timeoutTime = 2000;

void setup() {
    Serial.begin(115200);
    // Connect to Wi-Fi network with SSID and password
    Serial.print("Connecting to ");
    Serial.println(ssid);
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
    }
    // Print local IP address and start web server
    Serial.println("");
    Serial.println("WiFi connected.");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
    server.begin();
 
}

void loop() {
  //roboDuck.movePropHeading(45);
  //roboDuck.movePropHeading(275);
    WiFiClient client = server.available();   // Listen for incoming clients

  if (client) {                             // If a new client connects,
    currentTime = millis();
    previousTime = currentTime;
    Serial.println("New Client.");          // print a message out in the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected() && currentTime - previousTime <= timeoutTime) {  // loop while the client's connected
      currentTime = millis();
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        header += c;
        if (c == '\n') {                    // if the byte is a newline character
          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();
            
            // Display the HTML web page
            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<link rel=\"icon\" href=\"data:,\">");
            // CSS to style the on/off buttons 
            // Feel free to change the background-color and font-size attributes to fit your preferences
            client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
            client.println(".button { background-color: #4CAF50; border: none; color: white; padding: 16px 40px;");
            client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
            client.println(".button2 {background-color: #555555;}</style></head>");
            
            // Web Page Heading
            client.println("<body><h1>Robo Duck</h1>");
            client.println("<center><div id='grid' style='width:80%; border:5px solid black;'><canvas id='canvas' style='height:100%; width:100%; background-color:white;' /></div></center>");
            client.println("<div style='display:grid; grid-template-rows: 2fr 2fr; grid-template-columns: 2fr 2fr;'><button class='button'>Calibrate</button><button class='button'>Waypoints</button><button class='button'>Spot Lock</button><button class='button'>Return Home</button></div>"); 

            client.println("</body></html>");
            client.println("<div style='width:240px; height:320px;'> \ 
                            <center>ARDUINO</center> \
                             \
                            </div>");
            client.println("<script type='text/javascript'> \ 
                const gridInit = document.getElementById('grid');\
                const height = gridInit.clientHeight;\
                const width = gridInit.clientWidth;\
                function hello(){ \
                  console.log('Hello');\
                }\
                function printMousePos(event) {\
                  var absX = event.clientX;\
                  var absY = event.clientY;\
                  console.log('clientX: ' + event.clientX + '- clientY: ' + event.clientY);\
                  var y = Math.round(document.getElementById('grid').getBoundingClientRect().top);\
                  var x = Math.round(document.getElementById('grid').getBoundingClientRect().left);\
                  console.log(x + 'hello' + y);\
                  var trueX = absX - x;\
                  var trueY = absY - y;\
                  console.log('trueX: ' + trueX + ' trueY: ' + trueY);\
                  console.log('percentX: ' + (trueX / width) + ' percentY: ' + (trueY / height));\ 
                  drawWaypoint(trueX, trueY);\      
                }\
                function drawWaypoint(x, y){\
                  var canvas = document.getElementById('canvas');\
                  var ctx = canvas.getContext('2d');\
                  ctx.beginPath();\
                  ctx.arc(x, y, 10, 0, 2 * Math.PI);\
                  ctx.stroke(); \
                }\
                var grid = document.getElementById('grid');\
                grid.addEventListener('click', printMousePos);\
                hello(); \
                </script> \
                ");
            // The HTTP response ends with another blank line
            client.println();
            // Break out of the while loop
            break;
          } else { // if you got a newline, then clear currentLine
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }
      }
    }
    // Clear the header variable
    header = "";
    // Close the connection
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
  }
}
