/*********
  Rui Santos
  Complete project details at https://randomnerdtutorials.com  
*********/

#include <WiFi.h>
#include <Adafruit_NeoPixel.h>
#define PIN 2
#define BTN_1 0
#define BTN_2 4
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(10, PIN, NEO_GRB + NEO_KHZ800);
// twelve servo objects can be created on most boards

// GPIO the servo is attached to

// Replace with your network credentials
const char* ssid     = "K-Lab";
const char* password = "allhailklab";

// Set web server port number to 80
WiFiServer server(80);

// Variable to store the HTTP request
String header;

// Decode HTTP GET value
String valueString = String(5);
int pos1 = 0;
int pos2 = 0;

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

void loop(){
  WiFiClient client = server.available();   // Listen for incoming clients

  if (client) {                             // If a new client connects,
    currentTime = millis();
    previousTime = currentTime;
    Serial.println("New Client.");          // print a message out in the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected() && currentTime - previousTime <= timeoutTime) { // loop while the client's connected
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
           client.println("<!DOCTYPE html><html><head>	<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
client.println("<link rel=\"icon\" href=\"data:,\"><style> body { text-align: center;font-family: \"Trebuchet MS\", Arial;margin-left:auto;margin-right:auto;");
client.println(" transition: background 0.5s ease;}.slider{width: 300px;}</style>");
client.println("<script src=\"https://ajax.googleapis.com/ajax/libs/jquery/3.3.1/jquery.min.js\"></script>");
client.println("</head><body><h1>Lamp</h1><p>Position R: <span id=\"RedColor\"></span></p><input type=\"range\" min=\"0\" max=\"255\" class=\"slider\" id=\"RedSlider\" onchange=\"updateColor()\"/>");
client.println("<p>Position G: <span id=\"GreenColor\"></span></p><input type=\"range\" min=\"0\" max=\"255\" class=\"slider\" id=\"GreenSlider\" onchange=\"updateColor()\"/>");
client.println("<p>Position B: <span id=\"BlueColor\"></span></p><input type=\"range\" min=\"0\" max=\"255\" class=\"slider\" id=\"BlueSlider\" onchange=\"updateColor()\"/>");
client.println("<script>var RedSlider = document.getElementById(\"RedSlider\");var RedColor = document.getElementById(\"RedColor\");var GreenSlider = document.getElementById(\"GreenSlider\");");
client.println("var GreenColor = document.getElementById(\"GreenColor\");var BlueSlider = document.getElementById(\"BlueSlider\");		var BlueColor = document.getElementById(\"BlueColor\");");
client.println("function updateColor() {var red = RedSlider.value;var green = GreenSlider.value;var blue = BlueSlider.value;RedColor.innerHTML = red;GreenColor.innerHTML = green;");
client.println("BlueColor.innerHTML = blue;var gradient = \"linear-gradient(to right, rgb(0,0,0), rgb(\" + red + \",\" + green + \",\" + blue + \"), rgb(255,255,255))\";");
client.println("document.body.style.background = gradient;var textColor = getContrastingColor(red, green, blue);document.body.style.color = textColor;");
			// Simulate a GET request to the server (not a real request)
client.println("sendGetRequest(red, green, blue);} function getContrastingColor(red, green, blue) {	var luminance = (red * 299 + green * 587 + blue * 114) / 1000;");
client.println("return (luminance >= 128) ? \"#000000\" : \"#ffffff\"; } function sendGetRequest(red, green, blue) {");
// Simulated server-side handling (not a real server) // Replace this part with a real server-side implementation
client.println("var xhr = new XMLHttpRequest();	var url = \"/example_server_endpoint\"; // Replace with the actual server endpoint");
client.println("var params = \"red=\" + red + \"&green=\" + green + \"&blue=\" + blue; xhr.onreadystatechange = function() {");
client.println("if (xhr.readyState === 4) {		// Optional: Handle the response from the server if needed");
client.println("console.log(xhr.responseText);}}; xhr.open(\"GET\", url + \"?\" + params, true); xhr.send();} // Initialize slider values and colors");
client.println("RedSlider.value = 4; GreenSlider.value = 0; BlueSlider.value = 240; updateColor(); </script> </body> </html>");

            
            //GET /?value=180& HTTP/1.1
            if (header.indexOf("GET /?red=") >= 0 || header.indexOf("&green=") > 0 || header.indexOf("&blue=") > 0) {
  // Extract the values of red, green, and blue from the header
  pos1 = header.indexOf("red=");
  pos2 = header.indexOf("&green=");
  int red = header.substring(pos1 + 4, pos2).toInt();

  pos1 = header.indexOf("&green=");
  pos2 = header.indexOf("&blue=");
  int green = header.substring(pos1 + 7, pos2).toInt();

  pos1 = header.indexOf("&blue=");
  int blue = header.substring(pos1 + 6).toInt();

  // Print the RGB values to the serial monitor
  Serial.print("Red: ");
  Serial.print(red);
  Serial.print(", Green: ");
  Serial.print(green);
  Serial.print(", Blue: ");
  Serial.println(blue);
  pixels.setPixelColor(0, pixels.Color(red,green, blue)); 
  pixels.setPixelColor(1, pixels.Color(red,green, blue)); 
  pixels.setPixelColor(2, pixels.Color(red,green, blue)); 
  pixels.setPixelColor(3, pixels.Color(red,green, blue)); 
  pixels.setPixelColor(4, pixels.Color(red,green, blue)); 
  pixels.setPixelColor(5, pixels.Color(red,green, blue)); 
  pixels.setPixelColor(6, pixels.Color(red,green, blue)); 
  pixels.setPixelColor(7, pixels.Color(red,green, blue)); 
  pixels.setPixelColor(8, pixels.Color(red,green, blue)); 
  pixels.setPixelColor(9, pixels.Color(red,green, blue)); 
  pixels.setPixelColor(10, pixels.Color(red,green, blue));
  pixels.show();
}     
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