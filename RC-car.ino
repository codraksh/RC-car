#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

const char* ssid     = "YOUR_WIFI_NAME";      // <--- CHANGE THIS
const char* password = "YOUR_WIFI_PASSWORD";  // <--- CHANGE THIS

ESP8266WebServer server(80);

// Motor Pins (D1, D2, D5, D6)
const int LeftMotorForward  = 5;  // D1
const int LeftMotorBackward = 4;  // D2
const int RightMotorForward = 14; // D5
const int RightMotorBackward = 12; // D6

void setup() {
  Serial.begin(9600);
  
  pinMode(LeftMotorForward, OUTPUT); pinMode(LeftMotorBackward, OUTPUT);
  pinMode(RightMotorForward, OUTPUT); pinMode(RightMotorBackward, OUTPUT);

  stopCar();

  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println("\nWiFi connected!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP()); 

  // --- WEB PAGE (Updated with JavaScript) ---
  server.on("/", []() {
    String html = "<!DOCTYPE html><html><head><meta name='viewport' content='width=device-width, initial-scale=1.0'>";
    html += "<style>";
    html += "body { font-family: sans-serif; text-align: center; background-color: #222; color: white; margin: 0; padding: 20px; }";
    html += "button { border: none; color: white; padding: 20px; text-align: center; text-decoration: none; display: inline-block; font-size: 30px; margin: 4px 2px; cursor: pointer; border-radius: 12px; width: 45%; height: 100px; }";
    html += ".green { background-color: #4CAF50; width: 90%; }"; // Forward/Back are wide
    html += ".red { background-color: #f44336; width: 90%; }";   // Stop is wide
    html += ".blue { background-color: #008CBA; }";              // Left/Right
    html += "</style>";
    
    // The JavaScript magic that stops the page from reloading
    html += "<script>";
    html += "function send(action) { fetch('/' + action); }";
    html += "</script>";
    html += "</head><body>";
    
    html += "<h1>Rakshit's RC Car</h1>";
    
    // Buttons with 'onclick' instead of 'href'
    html += "<button class='green' onclick=\"send('forward')\">&#8593; FORWARD</button><br>";
    html += "<button class='blue' onclick=\"send('left')\">&#8592; LEFT</button>";
    html += "<button class='blue' onclick=\"send('right')\">RIGHT &#8594;</button><br>";
    html += "<button class='green' onclick=\"send('backward')\">&#8595; BACKWARD</button><br><br>";
    html += "<button class='red' onclick=\"send('stop')\">STOP</button>";
    
    html += "</body></html>";
    server.send(200, "text/html", html);
  });

  // --- COMMANDS ---
  server.on("/forward", []() {
    digitalWrite(LeftMotorForward, HIGH); digitalWrite(LeftMotorBackward, LOW);
    digitalWrite(RightMotorForward, HIGH); digitalWrite(RightMotorBackward, LOW);
    server.send(200, "text/plain", "OK");
  });
  server.on("/backward", []() {
    digitalWrite(LeftMotorForward, LOW); digitalWrite(LeftMotorBackward, HIGH);
    digitalWrite(RightMotorForward, LOW); digitalWrite(RightMotorBackward, HIGH);
    server.send(200, "text/plain", "OK");
  });
  server.on("/left", []() {
    digitalWrite(LeftMotorForward, LOW); digitalWrite(LeftMotorBackward, HIGH);
    digitalWrite(RightMotorForward, HIGH); digitalWrite(RightMotorBackward, LOW);
    server.send(200, "text/plain", "OK");
  });
  server.on("/right", []() {
    digitalWrite(LeftMotorForward, HIGH); digitalWrite(LeftMotorBackward, LOW);
    digitalWrite(RightMotorForward, LOW); digitalWrite(RightMotorBackward, HIGH);
    server.send(200, "text/plain", "OK");
  });
  server.on("/stop", []() {
    stopCar();
    server.send(200, "text/plain", "OK");
  });

  server.begin();
}

void loop() {
  server.handleClient();
}

void stopCar() {
  digitalWrite(LeftMotorForward, LOW); digitalWrite(LeftMotorBackward, LOW);
  digitalWrite(RightMotorForward, LOW); digitalWrite(RightMotorBackward, LOW);
}