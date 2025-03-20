#include <ESP8266WiFi.h>

const char* ssid = "Galaxy A35 5G EA22";
const char* password = "Kiiitooo";
const char* host = "192.168.1.1";  // Replace with your ESP8266's IP address

WiFiClient client;

#define MOTOR_LEFT 5   // Example GPIO pins for motor control
#define MOTOR_RIGHT 4  

void setup() {
    Serial.begin(9600);
    WiFi.begin(ssid, password);
    
    Serial.print("Connecting to WiFi...");
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("\nConnected to WiFi!");

    pinMode(MOTOR_LEFT, OUTPUT);
    pinMode(MOTOR_RIGHT, OUTPUT);
}

void loop() {
    if (client.connect(host, 80)) {
        Serial.println("Connected to server");
        String data = client.readStringUntil('\n');
        Serial.println("Received data: " + data);
        
        float roll, pitch;
        sscanf(data.c_str(), "%f,%f", &roll, &pitch);
        
        if (roll > 20) {
            digitalWrite(MOTOR_LEFT, HIGH);
            digitalWrite(MOTOR_RIGHT, LOW);
            Serial.println("Moving Left");
        } else if (roll < -20) {
            digitalWrite(MOTOR_LEFT, LOW);
            digitalWrite(MOTOR_RIGHT, HIGH);
            Serial.println("Moving Right");
        } else {
            digitalWrite(MOTOR_LEFT, LOW);
            digitalWrite(MOTOR_RIGHT, LOW);
            Serial.println("Stop");
        }
        
        delay(100);
    }
    client.stop();
}
