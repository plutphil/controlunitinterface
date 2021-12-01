#include<Arduino.h>
#include<Wire.h>
uint8_t LED = 13;
uint8_t addr= 1;
bool addressset = false;
void onreceive3(){

Serial.println("hi again");
}
void onreceive2(){
    Serial.println(addr);
    
}
void receiveEvent(int bytes) {
    //digitalWrite(LED,HIGH);
    if(digitalRead(7)==LOW){
        //
        Serial.println(addr);
        Wire.write(0);
        //Serial.print("my addr:");
         
        Wire.onReceive(onreceive2);
    }else{
        addr++;
        Wire.begin(addr); 
        Wire.onReceive(receiveEvent);
       
    }
}

void setup(){
 pinMode (LED, OUTPUT);
 digitalWrite(LED,LOW);
 digitalWrite(LED,HIGH);
 delay(10);
 digitalWrite(LED,LOW);
 pinMode(7,INPUT);
Wire.begin(addr); 
Wire.onReceive(receiveEvent);
Serial.begin(115200);
}
void loop(){

    if(Serial.available()>0){
        
        Wire.begin();
        Wire.beginTransmission(0x7F);
        const char buff[] = {0x02,0x02,0x20+(Serial.read()-'0')};
        Wire.write(buff,3);
        Wire.endTransmission();
        Wire.begin(addr); 
        Wire.onReceive(onreceive3);
    }
}