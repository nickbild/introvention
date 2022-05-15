#define __STATIC_FORCEINLINE                   __attribute__((always_inline)) static inline
#define __SSAT(ARG1, ARG2) \
__extension__ \
({                          \
  int32_t __RES, __ARG1 = (ARG1); \
  __ASM volatile ("ssat %0, %1, %2" : "=r" (__RES) :  "I" (ARG2), "r" (__ARG1) : "cc" ); \
  __RES; \
 })
 
#include <stdio.h>
#include <movement_disorder_detection_inferencing.h>
#include "edge-impulse-sdk/classifier/ei_run_classifier.h"
#include "edge-impulse-sdk/porting/ei_classifier_porting.h"
#include "edge-impulse-sdk/dsp/kissfft/kiss_fftr.h"
#include <Arduino_LSM6DS3.h>
#include <WiFiNINA.h>
#include "secrets.h"


// Callback function declaration
static int get_signal_data(size_t offset, size_t length, float *out_ptr);

// Raw features used in inferences.
float features[375] = {};

WiFiClient client;

const char* host = "192.168.1.139";
const char* url = "/anomaly?";

int inference(void) {
    
    signal_t signal;            // Wrapper for raw input buffer
    ei_impulse_result_t result; // Used to store inference output
    EI_IMPULSE_ERROR res;       // Return code from inference

    // Calculate the length of the buffer
    size_t buf_len = sizeof(features) / sizeof(features[0]);

    // Make sure that the length of the buffer matches expected input length
    if (buf_len != EI_CLASSIFIER_DSP_INPUT_FRAME_SIZE) {
        printf("ERROR: The size of the input buffer is not correct.\r\n");
        printf("Expected %d items, but got %d\r\n", 
                EI_CLASSIFIER_DSP_INPUT_FRAME_SIZE, 
                (int)buf_len);
        return 1;
    }

    // Assign callback function to fill buffer used for preprocessing/inference
    signal.total_length = EI_CLASSIFIER_DSP_INPUT_FRAME_SIZE;
    signal.get_data = &get_signal_data;

    // Perform DSP pre-processing and inference
    res = run_classifier(&signal, &result, false);

    // Print return code and how long it took to perform inference
    printf("run_classifier returned: %d\r\n", res);
    printf("Timing: DSP %d ms, inference %d ms, anomaly %d ms\r\n", 
            result.timing.dsp, 
            result.timing.classification, 
            result.timing.anomaly);

    Serial.println(result.anomaly);

    // Report anomalies to web API.
    if (result.anomaly > 1) {
      if (!client.connect(host, 5000)) {
        Serial.println("Connection failed.");
      }
      
      client.print(String("GET ") + url + "count=1 HTTP/1.1\r\n" +
      "Host: " + host + "\r\n" +
      "Connection: close\r\n\r\n");

       while(client.available()) {}
  
       client.stop();
    }

    return 0;
}

// Callback: fill a section of the out_ptr buffer when requested
static int get_signal_data(size_t offset, size_t length, float *out_ptr) {
    for (size_t i = 0; i < length; i++) {
        out_ptr[i] = (features + offset)[i];
    }

    return EIDSP_OK;
}

void setup() {
  Serial.begin(115200);

  if (!IMU.begin()) {
    Serial.println("Failed to initialize IMU!");
    while (1);
  }

   WiFi.begin(SSID, PASSWORD);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

}

void loop() {
  // Collect 2 seconds of accelerometer data.
  getAccelData();
  // Run anomaly detection.
  inference();
}

void getAccelData() {
  float x, y, z;
  int cnt = 0;
  int idx = 0;

  // Get 125 samples (~2 seconds).
  while (true) {
    if (IMU.accelerationAvailable()) {
      IMU.readAcceleration(x, y, z);

      // Store in global array used by inference engine.
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
