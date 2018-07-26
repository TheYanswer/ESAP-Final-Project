
#define hF 19
#define hC  18
#define Bb 17
#define F 16
#define dampener 5
#define strikeconstant   30  //in ms

#include <WiFi.h>
#include <WiFiUdp.h>

bool looper = false;

const char* ssid     = "modlab1";
const char* password = "ESAP2017";

WiFiUDP UDPTestServer;
unsigned int UDPPort = 2808;
IPAddress myIPaddress(192, 168, 1, 60);

const int packetSize = 10;

byte packetBuffer[packetSize];

int counter = 1;

float playmoment[] = {0,12.467568, 15.58446, 18.701352,  21.818244,  24.935136,  26.8831935, 28.052028,  31.16892, 33.1169775, 34.285812,  37.402704,  39.3507615, 40.519596,  43.636488,  45.5845455, 46.75338, 49.870272,  51.8183295, 52.987164,  56.104056,  58.0521135, 59.220948,  62.33784, 64.2858975, 65.454732,  68.571624,  70.5196815, 71.688516,  74.805408,  76.7534655, 77.9223,  81.039192,  82.9872495, 84.156084,  87.272976,  89.2210335, 90.389868,  93.50676, 95.4548175,    96.623652, 99.740544,  101.6886015,  102.857436, 105.974328, 107.9223855,  109.09122,  112.208112, 114.1561695,  115.325004, 118.441896, 120.3899535,  121.558788, 124.67568,  126.6237375,  127.792572, 130.909464, 132.8575215,  134.026356, 137.143248, 139.0913055,  140.26014,  143.377032, 145.3250895,  146.493924, 162.078384, 163.63683,  165.195276, 168.312168, 169.870614, 174.545952, 174.545952, 176.4940095,  177.662844, 180.779736, 182.7277935,  183.896628, 187.01352,  188.9615775,  190.130412, 193.247304, 195.1953615,  196.364196, 199.481088, 201.4291455,  202.59798,  205.714872, 207.6629295,  208.831764, 211.948656, 213.8967135,  215.065548, 218.18244,  220.1304975,  221.299332};
float note[] = {0, 87.30705786,116.541,87.30705786,116.541,174.614,130.813,116.5409404,174.6141157,130.8127827,116.5409404,174.6141157,130.8127827,116.5409404,174.6141157,130.8127827,116.5409404,174.6141157,130.8127827,116.5409404,174.6141157,130.8127827,116.5409404,174.6141157,130.8127827,116.5409404,174.6141157,130.8127827,116.5409404,174.6141157,130.8127827,116.5409404,174.6141157,130.8127827,116.5409404,174.6141157,130.8127827,116.5409404,174.6141157,130.8127827,116.5409404,174.6141157,130.8127827,116.5409404,174.6141157,130.8127827,116.5409404,174.6141157,130.8127827,116.5409404,174.6141157,130.8127827,116.5409404,174.6141157,130.8127827,116.5409404,174.6141157,130.8127827,116.5409404,174.6141157,130.8127827,116.5409404,174.6141157,130.8127827,116.5409404,87.30705786,65.40639133,73.41619198,58.27047019,87.30705786,349.2282314,174.6141157,130.8127827,116.5409404,174.6141157,130.8127827,116.5409404,174.6141157,130.8127827,116.5409404,174.6141157,130.8127827,116.5409404,174.6141157,130.8127827,116.5409404,174.6141157,130.8127827,116.5409404,174.6141157,130.8127827,116.5409404,174.6141157,130.8127827,116.5409404};

void setup()  {
  pinMode(2,OUTPUT);
  pinMode(18, OUTPUT);
  pinMode(19, OUTPUT);
  pinMode(17, OUTPUT);
  pinMode(5 , OUTPUT);
  pinMode(16, OUTPUT);
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
  digitalWrite(2,HIGH);
  UDPTestServer.begin(UDPPort);
}
void playnote()
{
  if (counter < 500)
  {
    int waittime = (playmoment[counter] * 1000) - (playmoment[counter - 1] * 1000);
    Serial.println(float(note[counter]));
    Serial.print("waiting ");
    Serial.println(waittime - strikeconstant);
    delay(waittime - strikeconstant);
    if ((note[counter] > 174 && note[counter] < 175) || (note[counter] > 348 && note[counter] < 350)) { //playing high f
      Serial.println("High F");
      digitalWrite( hF, HIGH);
      delay(strikeconstant);
      digitalWrite( hF, LOW);
    }
    else if (note[counter] > 116 && note[counter] < 117  || (note[counter] > 58 && note[counter] < 59)  || (note[counter] > 232 && note[counter] < 233)) { //playing Bb
      Serial.println("Bb");
      digitalWrite( Bb, HIGH);
      delay(strikeconstant);
      digitalWrite( Bb, LOW);
    }
    else if (note[counter] > 130 && note[counter] < 131  || (note[counter] > 65 && note[counter] < 67) || (note[counter] > 260 && note[counter] < 262)) { //playing high C
      Serial.println("High C");
      digitalWrite( hC, HIGH);
      delay(strikeconstant);
      digitalWrite( hC, LOW);
    }
    else if (note[counter] > 87 && note[counter] < 88 ) { //playing F
      Serial.println("F");
      digitalWrite( F, HIGH);
      delay(strikeconstant);
      digitalWrite( F, LOW);
    }
    else {
    }
    //    delay((hold[counter]*1000)-dampenerconstant);
    //    dampen();
    counter ++;
    Serial.println(counter);
  }
}
void loop() {
  handleUDPServer();
  delay(1);
}

void handleUDPServer() {
  if (looper == true) {
    playnote();
  }
  int cb = UDPTestServer.parsePacket();
  if (cb) {
    UDPTestServer.read(packetBuffer, packetSize);
    String myData = "";
    for (int i = 0; i < packetSize; i++) {
      myData += (char)packetBuffer[i];
    }
    Serial.print(millis()); Serial.print(", ");
    Serial.println (myData);
    if (myData == "A") {
      looper = true;
      Serial.println();

    }
  }
}
