#include <Wire.h>

#define HMC5883L_ADDR 0x1E  // I2C address of the HMC5883L sensor

void setup() {
  Wire.begin(); // Initialize the I2C communication
  Serial.begin(9600); // Initialize serial communication
  delay(100);

  // Initialize the HMC5883L
  Wire.beginTransmission(HMC5883L_ADDR);
  Wire.write(0x00); // Configuration Register A
  Wire.write(0x70); // Set the data output rate (75 Hz) and measurement mode (Normal)
  Wire.endTransmission();

  Wire.beginTransmission(HMC5883L_ADDR);
  Wire.write(0x01); // Configuration Register B
  Wire.write(0xA0); // Set the sensor gain (±1.3 Gauss)
  Wire.endTransmission();

  Wire.beginTransmission(HMC5883L_ADDR);
  Wire.write(0x02); // Mode Register
  Wire.write(0x00); // Continuous-measurement mode
  Wire.endTransmission();
}

void loop() {
  int x, y, z; // Variables to store magnetic field data

  // Request data
  Wire.beginTransmission(HMC5883L_ADDR);
  Wire.write(0x03); // Select register 3 - X MSB register
  Wire.endTransmission();

  // Read data
  Wire.requestFrom(HMC5883L_ADDR, 6);
  if (Wire.available() >= 6) {
    x = Wire.read() << 8 | Wire.read();
    z = Wire.read() << 8 | Wire.read();
    y = Wire.read() << 8 | Wire.read();
  }

  // Print the calibrated magnetic field data in microteslas
  Serial.print("X (uT): ");
  Serial.print(x);
  Serial.print("   Y (uT): ");
  Serial.print(y);
  Serial.print("   Z (uT): ");
  Serial.println(z);

  delay(500); // Delay for readability
}
