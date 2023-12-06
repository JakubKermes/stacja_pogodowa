

#include <WiFiEsp.h>

char ssid[] = "PLAY Internet 4G";    
char pass[] = "";    
char ssid1[] = "OPPO A91";
char pass1[] = "";

char server[] = "192.168.1.117";
char server1[] = "192.168.1.100";

String postData;
int status = WL_IDLE_STATUS;
WiFiEspClient client;

//---------------------

 #include <SFE_BMP180.h>
 #include <Wire.h>
 #include "DHT.h"
 #include <i2c.h>
 #include <i2c_BMP280.h>
 #include <i2c_Sensor.h>

 #define dht11 7 // humidity and temp
 #define LS A0 // light sensor
 // pins 6,5,4   5v power
 DHT dht;
 SFE_BMP180 pressure;
 
 double pressureval,tempval;
 int temp,ls,lst,humidity;
 

void setup()
{
  // initialize serial for debugging
  Serial.begin(115200);
  // initialize serial for ESP module
  Serial1.begin(9600);
  // initialize ESP module
  WiFi.init(&Serial1);

  // check for the presence of the shield
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi shield not present");
    // don't continue
    while (true);
  }

  // attempt to connect to WiFi network
  while ( status != WL_CONNECTED) {
    Serial.print("Attempting to connect to WPA SSID: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network
    status = WiFi.begin(ssid, pass);
    break;
    Serial.begin(ssid1,pass1);
  }

  // you're connected now, so print out the data
  Serial.println("You're connected to the network");

  printWifiStatus();
  client.setTimeout(12000);

  //----------------------------------

   Serial.println("SETUP?");
  pinMode(dht11, INPUT);
     Serial.println("1?");

  pinMode(LS, INPUT);
     Serial.println("2?");

  pressure.begin();

     Serial.println("3?");

  dht.setup(dht11);
  
  //power 5v
  pinMode(6, OUTPUT);
  digitalWrite(6, HIGH);
 pinMode(5, OUTPUT);
  digitalWrite(5, HIGH);  
  pinMode(4, OUTPUT);
  digitalWrite(4, HIGH);


}


void loop() {
  Serial.println("LOOP");
  HumiditySensor();
LightSensor();
Bmp180();
tempval -=80;
pressureval -= 200;
Serial.print(tempval);
Serial.println("*C");
Serial.print(ls);
Serial.println("% nasłonecznienia");
Serial.print(humidity);
Serial.println("% wilgotnosci powietrza");
Serial.print(pressureval);
Serial.println(" hpa");
Serial.println("_____________________________");

 // -------------------------------------

 
 
    postData = "temperature=" + (String)(int)tempval + "&pressure=" + (String)(int)pressureval + "&humidity=" + (String)humidity + "&lightlevel=" + (String)ls;
    //  postData = "temperature=" + (String)"12" + "&pressure=" + (String)"12" + "&humidity=" + (String)"12" + "&lightlevel=" + (String)"12";
    //post.php?temperature=0.00&pressure=0.00&humidity=20&lightlevel=78

  Serial.println(postData);
  client.connect(server,80);
  delay(1000);
  Serial.println(client.connected());
  if(client.connected()){
    client.setTimeout(1200);
    Serial.println("get");
    client.print("GET /post.php?");
    client.println(postData);
    delay(100);
    }else{
      Serial.println("Second try");
      client.connect(server1, 80);
      Serial.println(client.connected());
        Serial.println(client.connected());
    Serial.println("get");
    client.print("GET /post.php?");
    client.println(postData);
    }
  if(client.connected()){
   // Serial.println(postData);
    client.stop();
  }
  delay(600000);

}

void printWifiStatus()
{
  // print the SSID of the network you're attached to
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength
  long rssi = WiFi.RSSI();
  Serial.print("Signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}

//---------------------------------

int HumiditySensor()
{
  delay(dht.getMinimumSamplingPeriod());
  humidity=dht.getHumidity();
  temp=dht.getTemperature();
}

int LightSensor()
{
  lst=analogRead(LS);
  ls = map(lst,0,1024,0,100);
}

int Bmp180()
{ 
  delay(pressure.getTemperature(tempval));
  
  delay(pressure.startPressure(0));
  pressure.getPressure(pressureval, tempval);
}
