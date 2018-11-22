union FloatingPointIEEE754 {
  struct {
    unsigned int m2: 16;
    unsigned int m1: 16;
  } raw;
  float f;
} ieee754;

int address = 0;

void setup() { 
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  
  Serial.begin(9600);
}

void loop() {

  if( Serial.available() ){
    address = Serial.read();
  }  
  if( address == 4+48 ){
    digitalWrite( 3 , HIGH);
    ieee754.f = map(analogRead(A0), 0., 1023., 0., 5.);
    Serial.println("Decimal");
    Serial.println(ieee754.f,5);
    Serial.println("IEEE 754");
    Serial.println(ieee754.raw.m1,HEX);
    Serial.println(ieee754.raw.m2,HEX);
  }
  address = 0;
  digitalWrite( 3 , LOW);
}

float map(int x, double in_min, double in_max, double out_min, double out_max){
  return (float)(x - in_min) * (out_max - out_min) / (float)(in_max - in_min) + out_min;
}

