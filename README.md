Wi-Fi Controlled RC Car - Mobile Interface

🚗 Description

A wireless, remote-controlled vehicle powered by a NodeMCU and an L298N motor driver for precision movement. This project hosts a lightweight, mobile-accessible web interface directly on the NodeMCU, allowing users to connect via a smartphone and transmit directional commands over a local Wi-Fi network with minimal latency.

✨ Features

Mobile Web Interface: Built-in web server hosting a UI to control the car from any smartphone browser.

Local Wi-Fi Control: Operates independently on a local area network (LAN).

Low Latency: Optimized C/C++ control code to ensure real-time physical responses to user inputs.

Precision Movement: Differential steering utilizing an L298N motor driver.

🛠️ Hardware Requirements

1x NodeMCU (ESP8266)

1x L298N Motor Driver

2x or 4x DC Motors with Wheels

1x Robot Chassis

Battery Pack (e.g., 2x 18650 batteries)

Jumper Wires

🔌 Circuit / Wiring Diagram

(Note: Update these pins based on your exact wiring)

L298N Motor Driver

NodeMCU Pin

IN1 (Right Motor Forward)

D1 (GPIO 5)

IN2 (Right Motor Backward)

D2 (GPIO 4)

IN3 (Left Motor Forward)

D3 (GPIO 0)

IN4 (Left Motor Backward)

D4 (GPIO 2)

12V IN

Battery Positive

GND

Battery GND & NodeMCU GND

📸 [Insert a GIF or short video of the RC car moving while controlled by your phone here]

💻 Software & Libraries

IDE: Arduino IDE

Language: C/C++

Required Libraries:

ESP8266WiFi.h (Built-in)

ESP8266WebServer.h (Built-in)

🚀 How to Run

Clone this repository.

Open the .ino file in Arduino IDE.

Update the ssid and password variables in the code to your local Wi-Fi network (or configure it to act as an Access Point).

Upload to the NodeMCU.

Open the Serial Monitor to find the IP address of the car.

Enter the IP address into your smartphone's web browser to access the control interface.
