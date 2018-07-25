

#include <WiFi.h>
#include <WiFiUdp.h>

const char* ssid     = "modlab1";
const char* password = "ESAP2017";

WiFiUDP UDPTestServer;
unsigned int UDPPort = 2808;
IPAddress myIPaddress(192, 168, 1, 60);

const int packetSize = 10;

byte packetBuffer[packetSize];

void setup()  {
  pinMode(18, OUTPUT);
  pinMode(19, OUTPUT);
  pinMode(17, OUTPUT);
  pinMode(16, OUTPUT);
  pinMode(2,OUTPUT);
  Serial.begin(115200);
  Serial.println();
  Serial.print("Connecting to ");   Serial.println(ssid);

  WiFi.begin(ssid, password);
  WiFi.config(myIPaddress, IPAddress(192, 168, 1, 1),
              IPAddress(255, 255, 255, 0));

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("WiFi connected");
  Serial.println("WiFi connected");

  UDPTestServer.begin(UDPPort);
}
void loop() {
  handleUDPServer();
  delay(1);
}

void handleUDPServer() {
  int cb = UDPTestServer.parsePacket();
  if (cb) {
    UDPTestServer.read(packetBuffer, packetSize);
    String myData = "";
    for (int i = 0; i < packetSize; i++) {
      myData += (char)packetBuffer[i];
    }
    Serial.print(millis()); Serial.print(", ");
    Serial.println (myData);
    if (myData == "hF") {
      digitalWrite(2, HIGH);
      digitalWrite(hF,HIGH);
      delay(strikeconstant);
      digitalWrite(2, LOW);
      digitalWrite(hF,LOW);
    }
    else if (myData == "hC") {
      digitalWrite(hC,HIGH);
      digitalWrite(2,HIGH);
      delay(strikeconstant);
      digitalWrite(2, LOW);
      digitalWrite(hC,LOW);
    }
  else   if (myData == "Bb") {
    digitalWrite(Bb,HIGH);
    digitalWrite(2, HIGH);
    delay(strikeconstant);
    digitalWrite(Bb,LOW);
    digitalWrite(2,LOW); 
  }
 else  if (myData == "nF"){
    digitalWrite(nF,HIGH);
    digitalWrite(2,HIGH);
    delay(strikeconstant);
    digitalWrite(nF,LOW);
    digitalWrite(2,LOW);
  }
}
}
