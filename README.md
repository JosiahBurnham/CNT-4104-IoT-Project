# CNT-4104-IoT-Project
IoT project for Computer Networks (4104)

This project is an IoT Plant Watering System that utilizes a entirely serverless backend to make choices on watering based collectd sensor data, and local data.

The sensors are connected to the arduino.
The pump, and API calls are handled by an ESP 8266.
Communication between arduino and ESP are handled via serial connection.

## circuit diagram
![image](https://user-images.githubusercontent.com/62119663/201561058-4b6ac088-5577-4c00-a2a0-68c0264e078d.png)

## General Setup

1) Wire up all the sensor and pump like it shows in the diagram above
2) Flash the arduino with the IoT_Watering.Ino file
3) Change the Definitions to the WiFi, and API to your own
4) Flash that changed code to your ESP
5) Have a health plant, you don't have to remember about!
