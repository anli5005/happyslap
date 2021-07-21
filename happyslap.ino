#include <Wire.h>
#include <Servo.h>

const int MPU_addr = 0x68;
Servo servo;

void setup() {
    servo.attach(9);
    Wire.begin();
    Wire.beginTransmission(MPU_addr);
    Wire.write(0x6B);
    Wire.write(0);
    Wire.endTransmission(true);
    Serial.begin(9600);

    servo.write(90);
}

void loop() {
    Wire.beginTransmission(MPU_addr);
    Wire.write(0x3B);
    Wire.endTransmission(false);
    Wire.requestFrom(MPU_addr, 14, true);
    int16_t AcX = Wire.read() << 8 | Wire.read();
    int16_t AcY = Wire.read() << 8 | Wire.read();
    int16_t AcZ = Wire.read() << 8 | Wire.read();
    int16_t Tmp = Wire.read() << 8 | Wire.read();
    int16_t GyX = Wire.read() << 8 | Wire.read();
    int16_t GyY = Wire.read() << 8 | Wire.read();
    int16_t GyZ = Wire.read() << 8 | Wire.read();
    
    if (abs(AcY) > 1000) {
        Serial.println("Slapping");
        servo.write(0);
        delay(1000);
    } else {
        servo.write(90);
    }

    delay(50);
}