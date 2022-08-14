//set up command lines tools: 
//./arduino-cli.exe core install arduino:samd
//./arduino-cli.exe core list

//to compile and upload  ./arduino-cli.exe compile './main/main.ino'  

#include <IRremote.hpp>
#include <IRLibRecvPCI.h>
//create our IRsender object with IRremote.hpp
IRsend irSender;
//IRRec object using IRLibRecvPCI on pin 2. tried using pin 7 as data pin but no beuno
IRrecvPCI irReciever(2); 

//raw buffers
uint16_t pBtnRawBuffer[68]={
    8910, 4578, 482, 1762, 478, 654, 478, 658, 478, 
    650, 482, 654, 478, 654, 482, 654, 478, 654, 478, 
    654, 478, 1762, 478, 1762, 478, 1766, 478, 
    1758, 478, 1786, 458, 1786, 454, 1762, 478, 
    654, 478, 654, 478, 658, 478, 654, 478, 654, 478, 
    654, 478, 658, 478, 654, 478, 1762, 478, 1762, 478, 
    1762, 478, 1762, 478, 1762, 478, 1762, 478, 1762, 
    478, 1762, 478, 1000};

uint16_t m1RawBuffer[68]={
    8914, 4582, 478, 1762, 478, 654, 478, 682, 
    450, 658, 478, 654, 478, 654, 478, 658, 
    474, 662, 474, 654, 478, 1762, 478, 1762, 
    478, 1762, 478, 1762, 478, 1762, 478, 1762, 
    478, 1762, 478, 654, 478, 1762, 478, 1762, 
    478, 1762, 478, 1762, 478, 654, 478, 654, 
    478, 658, 478, 1762, 478, 654, 478, 654, 
    478, 658, 478, 654, 478, 1762, 478, 1762, 
    478, 1762, 478, 1000};

uint16_t m2RawBuffer[68]={
    8934, 4562, 498, 1738, 506, 634, 498, 634, 
    498, 634, 502, 630, 502, 630, 502, 634, 
    502, 630, 502, 634, 498, 1742, 498, 1738, 
    506, 1738, 502, 1734, 506, 1738, 502, 1734, 
    506, 1734, 506, 1738, 502, 1738, 502, 1766, 
    474, 1738, 502, 1742, 498, 630, 506, 630, 
    502, 634, 498, 630, 502, 634, 502, 630, 
    502, 630, 502, 658, 478, 1738, 502, 1734, 
    502, 1738, 502, 1000};

uint16_t m3RawBuffer[68]={
    8930, 4566, 498, 1742, 498, 634, 498, 638, 
    494, 638, 498, 634, 498, 638, 494, 638, 
    498, 634, 498, 662, 470, 1746, 494, 1746, 
    494, 1746, 494, 1746, 494, 1746, 494, 1750, 
    490, 1750, 490, 1750, 490, 642, 494, 1746, 
    494, 1770, 470, 1746, 494, 638, 494, 1746, 
    494, 638, 494, 666, 470, 1746, 494, 638, 
    494, 642, 490, 642, 490, 1774, 470, 638, 
    494, 1746, 494, 1000};

uint16_t m4RawBuffer[68]={
8934, 4566, 498, 1742, 498, 634, 502, 634, 498, 
634, 498, 634, 502, 630, 502, 634, 502, 630, 
502, 634, 498, 1742, 502, 1738, 502, 1742, 498, 
1766, 478, 1738, 502, 1738, 502, 1738, 502, 630, 502, 
634, 502, 1738, 502, 1738, 502, 1738, 502, 
630, 502, 1742, 498, 634, 502, 1742, 498, 1742, 
498, 634, 498, 634, 502, 634, 498, 1742, 498, 
634, 502, 1738, 502, 1000};

void setup() {
  Serial.begin(9600);
  irSender.begin(3);
  irReciever.enableIRIn();
}
void loop() {
  if (irReciever.getResults()) {
    Serial.println("\n\n-------------------------");
    Serial.println("Received IR signal:");

    Serial.print(F("\n#define RAW_DATA_LEN "));
    Serial.println(recvGlobal.recvLength, DEC);

    Serial.print(F("uint16_t rawData[RAW_DATA_LEN]={\n"));
    for (bufIndex_t i = 1; i < recvGlobal.recvLength; i++) {
      Serial.print(recvGlobal.recvBuffer[i], DEC);
      Serial.print(F(", "));
    }
    Serial.println(F("1000};"));
    Serial.println("-------------------------");

    irReciever.enableIRIn();
  }else{
    irSender.sendRaw(m1RawBuffer, sizeof(m1RawBuffer) / sizeof(m1RawBuffer[0]), 38);
  }
   delay(1000);
}
