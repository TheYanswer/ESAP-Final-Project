//this UDP code only is for carrying out one and only one function that corresponds to the packet that is received.
//Modified by Luc H, the UDP code for repeating a function when a packet is received is located in the codes for the songs.

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
  Serial.print("Connecting to ");   Serial.println(ssid);                       //Print that connection is in progress

  WiFi.begin(ssid, password);                                                   //Connect to WiFi
  WiFi.config(myIPaddress, IPAddress(192, 168, 1, 1), 
              IPAddress(255, 255, 255, 0));

  while (WiFi.status() != WL_CONNECTED) {                                       //print ........... to show that it is still connecting while WiFi is still not connected
    delay(500);
    Serial.print(".");
  }

  Serial.println("WiFi connected");                                               //print connection successful!
  Serial.println("WiFi connected");
  digitalWrite(2,HIGH);
  UDPTestServer.begin(UDPPort);
}
void loop() {
  handleUDPServer();                                      //carry out "handleUDPServer" function
  delay(1);
}

void handleUDPServer() {                                  //set "handleUDPServer" as function
  int cb = UDPTestServer.parsePacket();
  if (cb) {
    UDPTestServer.read(packetBuffer, packetSize);
    String myData = "";
    for (int i = 0; i < packetSize; i++) {
      myData += (char)packetBuffer[i];           //converts myData to characters
    }
    Serial.print(millis()); Serial.print(", ");
    Serial.println (myData);                      //reads myData
    if (myData == "hF") {                        //if myData in character form is "hF", execute the following function
      digitalWrite(2, HIGH);                    //blink led to show action
      digitalWrite(hF,HIGH);                    //turn on solenoid
      delay(strikeconstant);                    //on time
      digitalWrite(2, LOW);                     //turn off solenoid
      digitalWrite(hF,LOW);                     //turn off led
    }
    else if (myData == "hC") {                  //Pretty much same as above
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
