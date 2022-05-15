#include <Arduino_LSM6DS3.h>

float features[375] = {};

void setup() {
  Serial.begin(115200);

  if (!IMU.begin()) {
    Serial.println("Failed to initialize IMU!");
    while (1);
  }
}

void loop() {
  // Collect 2 seconds of accelerometer data.
  getAccelData();

  for (int i=0; i<375; i=i+3) {
    Serial.print(features[i]);
    Serial.print("\t");
    Serial.print(features[i+1]);
    Serial.print("\t");
    Serial.println(features[i+2]);
  }
  Serial.println("********");
}

void getAccelData() {
  float x, y, z;
  int cnt = 0;
  int idx = 0;

  // Get 125 samples (~2 seconds).
  while (true) {
    if (IMU.accelerationAvailable()) {
      IMU.readAcceleration(x, y, z);

      // Store in global array.
      features[idx] = x;
      idx++;
      features[idx] = y;
      idx++;
      features[idx] = z;
      idx++;

      cnt += 1;
      if (cnt >=125) {
        break;  
      }
    }
  }
}
