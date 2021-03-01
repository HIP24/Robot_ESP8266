#include <ESP8266WiFi.h>

// Enter your wifi network name and Wifi Password
const char* ssid = "PamukAilesi2.4GHz";
const char* password = "3BuR3paahjfb";

// Set web server port number to 80
WiFiServer server(80);

// Variable to store the HTTP request
String header;

// These variables store current output state of motor pins
String speedArmsState = "off";
String armsTogetherState = "off";
String armsApartrState = "off";

String speedWheelLeftState = "off";
String forwardsLeftState = "off";
String backwardsLeftState = "off";

String speedWheelRightState = "off";
String forwardsRightState = "off";
String backwardsRightState = "off";


// Assign output variables to GPIO pins
const int speedArms = 16;
const int armsTogether = 5;
const int armsApart = 4;

const int speedWheelLeft = 14;
const int forwardsLeft = 12;
const int backwardsLeft = 13;

const int speedWheelRight = 15;
const int forwardsRight = 3;
const int backwardsRight = 1;

// Current time
unsigned long currentTime = millis();
// Previous time
unsigned long previousTime = 0; 
// Define timeout time in milliseconds (example: 2000ms = 2s)
const long timeoutTime = 2000;

void setup() {
Serial.begin(9600);

//-----------------------------------------------------------------

// Initialize the output variables as outputs
//Arms
pinMode(speedArms, OUTPUT);
pinMode(armsApart, OUTPUT);
pinMode(armsTogether, OUTPUT);

//Left Wheeel
pinMode(speedWheelLeft, OUTPUT);
pinMode(forwardsLeft, OUTPUT);
pinMode(backwardsLeft, OUTPUT);

//Right Wheeel
pinMode(speedWheelRight, OUTPUT);
pinMode(forwardsRight, OUTPUT);
pinMode(backwardsRight, OUTPUT);

//-----------------------------------------------------------------

// Set outputs to LOW
digitalWrite(speedArms, LOW);
digitalWrite(armsApart, LOW);
digitalWrite(armsTogether, LOW);

digitalWrite(speedWheelLeft, LOW);
digitalWrite(forwardsLeft, LOW);
digitalWrite(backwardsLeft, LOW);

digitalWrite(speedWheelRight, LOW);
digitalWrite(forwardsRight, LOW);
digitalWrite(backwardsRight, LOW);

//-----------------------------------------------------------------

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




void loop(){
WiFiClient client = server.available(); // Listen for incoming clients

if (client) { // If a new client connects,
Serial.println("New Client."); // print a message out in the serial port
String currentLine = ""; // make a String to hold incoming data from the client
currentTime = millis();
previousTime = currentTime;
while (client.connected() && currentTime - previousTime <= timeoutTime) { // loop while the client's connected
currentTime = millis(); 
if (client.available()) { // if there's bytes to read from the client,
char c = client.read(); // read a byte, then
Serial.write(c); // print it out the serial monitor
header += c;
if (c == '\n') { // if the byte is a newline character
// if the current line is blank, you got two newline characters in a row.
// that's the end of the client HTTP request, so send a response:
if (currentLine.length() == 0) {
// HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
// and a content-type so the client knows what's coming, then a blank line:
client.println("HTTP/1.1 200 OK");
client.println("Content-type:text/html");
client.println("Connection: close");
client.println();

// turns the GPIOs on and off ofd arms
if (header.indexOf("GET /16/on") >= 0) {
Serial.println("Arms are on");
speedArmsState = "on";
digitalWrite(speedArms, HIGH);
} else if (header.indexOf("GET /16/off") >= 0) {
Serial.println("Arms are off");
speedArmsState = "off";
digitalWrite(speedArms, LOW   );
} else if (header.indexOf("GET /5/on") >= 0) {
Serial.println("Arms forward");
armsTogetherState = "on";
digitalWrite(armsTogether, HIGH);
} else if (header.indexOf("GET /5/off") >= 0) {
Serial.println("Arms forward off");
armsTogetherState = "off";
digitalWrite(armsTogether, LOW);
} else if (header.indexOf("GET /4/on") >= 0) {
Serial.println("Arms backwards on");
armsApartrState = "on";
digitalWrite(armsApart, HIGH);
} else if (header.indexOf("GET /4/off") >= 0) {
Serial.println("Arms backwards off");
armsApartrState = "off";
digitalWrite(armsApart, LOW);
}



// turns the GPIOs on and off of left wheel
else if (header.indexOf("GET /14/on") >= 0) {
Serial.println("speedWheelLeft  is on");
speedWheelLeftState  = "on";
digitalWrite(speedWheelLeft , HIGH);
} else if (header.indexOf("GET /14/off") >= 0) {
Serial.println("speedWheelLeft  is off");
speedWheelLeftState  = "off";
digitalWrite(speedWheelLeft , LOW   );
} else if (header.indexOf("GET /12/on") >= 0) {
Serial.println("forwardsLeft  is on");
forwardsLeftState  = "on";
digitalWrite(forwardsLeft , HIGH);
} else if (header.indexOf("GET /12/off") >= 0) {
Serial.println("forwardsLeft  is off");
forwardsLeftState  = "off";
digitalWrite(forwardsLeft , LOW);
} else if (header.indexOf("GET /13/on") >= 0) {
Serial.println("backwardsLeft  is on");
backwardsLeftState  = "on";
digitalWrite(backwardsLeft , HIGH);
} else if (header.indexOf("GET /13/off") >= 0) {
Serial.println("backwardsLeft  is off");
backwardsLeftState  = "off";
digitalWrite(backwardsLeft , LOW);
}



// turns the GPIOs on and off of right wheel
else if (header.indexOf("GET /15/on") >= 0) {
Serial.println("speedWheelRight   is on");
speedWheelRightState   = "on";
digitalWrite(speedWheelRight , HIGH);
} else if (header.indexOf("GET /15/off") >= 0) {
Serial.println("speedWheelRight   is off");
speedWheelRightState   = "off";
digitalWrite(speedWheelRight , LOW   );
} else if (header.indexOf("GET /3/on") >= 0) {
Serial.println("forwardsLeft  is on");
forwardsRightState   = "on";
digitalWrite(forwardsRight  , HIGH);
} else if (header.indexOf("GET /3/off") >= 0) {
Serial.println("forwardsLeft  is off");
forwardsRightState   = "off";
digitalWrite(forwardsRight  , LOW);
} else if (header.indexOf("GET /1/on") >= 0) {
Serial.println("backwardsLeft  is on");
backwardsRightState   = "on";
digitalWrite(backwardsRight  , HIGH);
} else if (header.indexOf("GET /1/off") >= 0) {
Serial.println("backwardsLeft  is off");
backwardsRightState   = "off";
digitalWrite(backwardsRight  , LOW);
}



// Display the HTML web page
client.println("<!DOCTYPE html><html>");
client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
client.println("<link rel=\"icon\" href=\"data:,\">");
// CSS to style the on/off buttons 
client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");

client.println(".column { float: left;  width: 33.33%;  padding: 10px;  height: 300px; }");
client.println(".row:after {  content: "";  display: table;  clear: both;}");
client.println("* { box-sizing: border-box;}");

//client.println(".buttonRed { background-color: #ff0000; border: none; color: white; padding: 16px 40px; border-radius: 60%;");
//client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
client.println(".buttonGreen { background-color: #00ff00; border: none; color: white; padding: 16px 40px; border-radius: 60%;");
client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
//client.println(".buttonYellow { background-color: #feeb36; border: none; color: white; padding: 16px 40px; border-radius: 60%;");
//client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
client.println(".buttonOff { background-color: #77878A; border: none; color: white; padding: 16px 40px; border-radius: 70%;");
client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}</style></head>");

// Web Page Heading
client.println("<body><h1>My LED Control Server</h1>");


client.println("<div class='row'>");

    client.println("<div class='column'>");
                  //------------------------------------------------------------------------------------------------------------------------------------------------------1
                  // Display current state, and ON/OFF buttons for GPIO 4 
                  client.println("<p>Arms are " + speedArmsState + "</p>");
                  // If the speedArmsState is off, it displays the OFF button 
                  if (speedArmsState=="off") {
                  client.println("<p><a href=\"/16/on\"><button class=\"button buttonOff\">OFF</button></a></p>");
                  } else {
                  client.println("<p><a href=\"/16/off\"><button class=\"button buttonGreen\">ON</button></a></p>");
                  } 
                  
                  // Display current state, and ON/OFF buttons for GPIO 16 
                  client.println("<p>Arms together " + armsTogetherState + "</p>");
                  // If the armsTogetherState is off, it displays the OFF button 
                  if (armsTogetherState =="off") {
                  client.println("<p><a href=\"/5/on\"><button class=\"button buttonOff\">OFF</button></a></p>");
                  } else {
                  client.println("<p><a href=\"/5/off\"><button class=\"button buttonGreen\">ON</button></a></p>");
                  }
                  client.println("</body></html>");
                  
                  // Display current state, and ON/OFF buttons for GPIO 5 
                  client.println("<p>Arms apart " + armsApartrState + "</p>");
                  // If the armsApartrState is off, it displays the OFF button 
                  if (armsApartrState =="off") {
                  client.println("<p><a href=\"/4/on\"><button class=\"button buttonOff\">OFF</button></a></p>");
                  } else {
                  client.println("<p><a href=\"/4/off\"><button class=\"button buttonGreen\">ON</button></a></p>");
                  }
    client.println("</div>");


//------------------------------------------------------------------------------------------------------------------------------------------------------2

    client.println("<div class='column'>");
                  // Display current state, and ON/OFF buttons for GPIO 14 
                  client.println("<p>Left Wheel is " + speedWheelLeftState  + "</p>");
                  // If the speedArmsState is off, it displays the OFF button 
                  if (speedWheelLeftState =="off") {
                  client.println("<p><a href=\"/14/on\"><button class=\"button buttonOff\">OFF</button></a></p>");
                  } else {
                  client.println("<p><a href=\"/14/off\"><button class=\"button buttonGreen\">ON</button></a></p>");
                  } 
                  
                  // Display current state, and ON/OFF buttons for GPIO 12
                  client.println("<p>Left Forwards is " + forwardsLeftState  + "</p>");
                  // If the armsTogetherState is off, it displays the OFF button 
                  if (forwardsLeftState  =="off") {
                  client.println("<p><a href=\"/12/on\"><button class=\"button buttonOff\">OFF</button></a></p>");
                  } else {
                  client.println("<p><a href=\"/12/off\"><button class=\"button buttonGreen\">ON</button></a></p>");
                  }
                  client.println("</body></html>");
                  
                  // Display current state, and ON/OFF buttons for GPIO 13
                  client.println("<p>Left Backwards is " + backwardsLeftState  + "</p>");
                  // If the armsApartrState is off, it displays the OFF button 
                  if (backwardsLeftState  =="off") {
                  client.println("<p><a href=\"/13/on\"><button class=\"button buttonOff\">OFF</button></a></p>");
                  } else {
                  client.println("<p><a href=\"/13/off\"><button class=\"button buttonGreen\">ON</button></a></p>");
                  }
    client.println("</div>");

 
 //------------------------------------------------------------------------------------------------------------------------------------------------------3
 
    client.println("<div class='column'>");
                 
                  // Display current state, and ON/OFF buttons for GPIO 15
                  client.println("<p>Right Wheel is " + speedWheelRightState   + "</p>");
                  // If the speedArmsState is off, it displays the OFF button 
                  if (speedWheelRightState  =="off") {
                  client.println("<p><a href=\"/15/on\"><button class=\"button buttonOff\">OFF</button></a></p>");
                  } else {
                  client.println("<p><a href=\"/15/off\"><button class=\"button buttonGreen\">ON</button></a></p>");
                  } 
                  
                  // Display current state, and ON/OFF buttons for GPIO 10
                  client.println("<p>Right Forwards is " + forwardsRightState   + "</p>");
                  // If the armsTogetherState is off, it displays the OFF button 
                  if (forwardsRightState   =="off") {
                  client.println("<p><a href=\"/3/on\"><button class=\"button buttonOff\">OFF</button></a></p>");
                  } else {
                  client.println("<p><a href=\"/3/off\"><button class=\"button buttonGreen\">ON</button></a></p>");
                  }
                  client.println("</body></html>");
                  
                  // Display current state, and ON/OFF buttons for GPIO 13
                  client.println("<p>Right Backwards is " + backwardsRightState   + "</p>");
                  // If the armsApartrState is off, it displays the OFF button 
                  if (backwardsRightState   =="off") {
                  client.println("<p><a href=\"/1/on\"><button class=\"button buttonOff\">OFF</button></a></p>");
                  } else {
                  client.println("<p><a href=\"/1/off\"><button class=\"button buttonGreen\">ON</button></a></p>");
                  }
                  client.println("</div>");


    client.println("</div>");


client.println("</body></html>");

// The HTTP response ends with another blank line
client.println();
// Break out of the while loop
break;
} else { // if you got a newline, then clear currentLine
currentLine = "";
}
} else if (c != '\r') { // if you got anything else but a carriage return character,
currentLine += c; // add it to the end of the currentLine
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
