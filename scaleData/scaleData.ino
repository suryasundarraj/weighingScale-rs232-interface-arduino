#include <SoftwareSerial.h>

SoftwareSerial scale(10, 11); // RX, TX

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  scale.begin(9600);
}
String data = "0.00";
String prevData = "0.00";
int weightDataReceived = 0;
int count = 0;
void loop() {
  // put your main code here, to run repeatedly:
  if(scale.available()){
    data = scale.readStringUntil('\r');
    data[5] = '\0';
    delay(50);
    if(prevData == data){
      count++;
      if(count > 2){
        count = 0;
        weightDataReceived = 1;
      }
    }
    else{
      weightDataReceived = 0;
      prevData = data;
    }
  }
  if(weightDataReceived == 1){
    Serial.print("Weighing Scale Reading : ");
    Serial.println(data);
    weightDataReceived = 0;
  }
}
