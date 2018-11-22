//OLD WAY
/* union FloatingPointIEEE754 {
  struct {
    unsigned int m2: 16;
    unsigned int m1: 7;
    unsigned int e: 8;
    unsigned int s: 1;
  } raw;
  float f;
} ieee754;
*/
/*  Serial.println("Decimal");
  Serial.println(ieee754.f);
  Serial.println("IEEE 754");
  Serial.print(ieee754.raw.s);
  Serial.println("   Sinal    1 bit");
  Serial.print(ieee754.raw.e);
  Serial.println(" Expoente 8 bits");
  Serial.print(ieee754.raw.m1);
  Serial.println("  Mantissa 7 bits");
  Serial.print(ieee754.raw.m2);
  Serial.println("   Mantissa 16 bits"); */
//OLD WAY

///////////////////////////STARTS HERE//////////////////////////////////
#include <ModbusRTUSlave.h>

ModbusRTUSlave rtu(1, &Serial);

union FloatingPointIEEE754 {
  struct {
    unsigned int m2: 16;
    unsigned int m1: 16;
  } raw;
  float f;
} ieee754;

//int address = 0;
u8 is_me;

u16 _D[100];
u8 _M[50];

void setup() { 
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  
//  Serial.begin(9600);
  
  rtu.addWordArea(0x7000, _D, 100);
  rtu.addBitArea(0x1000, _M, 50);
  rtu.begin(9600);
}

void loop() {
//USING MODBUS
  rtu.process();  
  is_me = _M[1];
  //In QModMaster, there is a problem with address 1000, so we just use the second position of the byte _M and configure the software to write starting on Adress 1009
  if(is_me == 4){
    digitalWrite( 3 , HIGH);
    ieee754.f = map(analogRead(A0), 0., 1023., 0., 5.);
    _D[1] = ieee754.raw.m1;
    _D[2] = ieee754.raw.m2;
    _M[1] = 0;
  }  
  else
    digitalWrite( 3 , LOW);
  
//USING SERIAL
//  if( Serial.available() ){
//    address = Serial.read();
//  }  
//  if( address == 4+48 ){
//    ieee754.f = map(analogRead(A0), 0., 1023., 0., 5.);
//    Serial.println("Decimal");
//    Serial.println(ieee754.f,5);
//    Serial.println("IEEE 754");
//    Serial.println(ieee754.raw.m1,HEX);
//    Serial.println(ieee754.raw.m2,HEX);
//  }
//  address = 0;  
}

float map(int x, double in_min, double in_max, double out_min, double out_max){
  return (float)(x - in_min) * (out_max - out_min) / (float)(in_max - in_min) + out_min;
}


