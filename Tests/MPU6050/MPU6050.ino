#include <Wire.h>
const int MPU_addr = 0x68;  // I2C address of the MPU-6050

int16_t accelerometer_x, accelerometer_y, accelerometer_z;
int16_t gyro_x, gyro_y, gyro_z;

void setup() {
  Wire.begin();
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x6B);  // PWR_MGMT_1 register
  Wire.write(0);     // Wake up the MPU-6050
  Wire.endTransmission(true);
  Serial.begin(9600);
}

void loop() {
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x3B);  // starting with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_addr, 14, true);  // request a total of 14 registers

  accelerometer_x = Wire.read() << 8 | Wire.read();
  accelerometer_y = Wire.read() << 8 | Wire.read();
  accelerometer_z = Wire.read() << 8 | Wire.read();
  gyro_x = Wire.read() << 8 | Wire.read();
  gyro_y = Wire.read() << 8 | Wire.read();
  gyro_z = Wire.read() << 8 | Wire.read();

  Serial.print("Accelerometer: ");
  Serial.print("X = "); Serial.print(accelerometer_x);
  Serial.print(" | Y = "); Serial.print(accelerometer_y);
  Serial.print(" | Z = "); Serial.println(accelerometer_z);

  Serial.print("Gyroscope: ");
  Serial.print("X = "); Serial.print(gyro_x);
  Serial.print(" | Y = "); Serial.print(gyro_y);
  Serial.print(" | Z = "); Serial.println(gyro_z);

  delay(1000);
}