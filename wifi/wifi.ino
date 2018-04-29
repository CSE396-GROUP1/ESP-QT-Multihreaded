#include <SoftwareSerial.h>
SoftwareSerial WiFiSerial(10, 11); // RX, TX  

//#define net_id "Emre iPhone'u"
//#define net_pw "emrecancelik"

#define net_id "TurkTelekom_T4A6A"
#define net_pw "JY7s22vx"

#define server_ip "192.168.1.111"
#define server_port "8081"

String  msg = "";

void setup() {
  Serial.begin(115200);
  WiFiSerial.begin(115200);

  WiFiSerial.println("AT");     ;
  
  delay(1000);
   
  while(!WiFiSerial.find("OK")){  
    WiFiSerial.println("AT");
    Serial.println("AT");
    delay(1000); 
  }
  
  WiFiSerial.println("AT+CWMODE=3"); 
  delay(500);
  WiFiSerial.println("AT+CIPMUX=0");
  delay(500);

  String cmd = String("AT+CWJAP=\"")+net_id+"\",\""+net_pw+"\"";
  WiFiSerial.println(cmd);      
  Serial.println(cmd);
  delay(3000);

  while(!WiFiSerial.find("OK")){
    WiFiSerial.println(cmd);      
    Serial.println(cmd);
    delay(3000);
  }

  cmd = String("AT+CIPSTART=\"TCP\",\"") + server_ip + "\"," + server_port; 
  WiFiSerial.println(cmd);
  Serial.println(cmd);
  delay(3000);

  while(!WiFiSerial.find("CONNECT") && !WiFiSerial.find("ALREADY")){
    WiFiSerial.println(cmd);
    Serial.println(cmd);
    delay(3000);
  }
  if(WiFiSerial.available()>0)
    Serial.write("Connected!");
  
}
 
void loop()
{
  if (WiFiSerial.available())
    Serial.write(WiFiSerial.read());

  if (Serial.available())
     WiFiSerial.write(Serial.read());
  
}
