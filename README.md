# Introvention

Introvention is a wearable device that seeks to diagnose movement disorders earlier than is presently possible by leveraging machine learning.

![](https://raw.githubusercontent.com/nickbild/introvention/main/media/wearing_sm.jpg)

## How It Works

![](https://raw.githubusercontent.com/nickbild/introvention/main/media/introvention_architecture.jpg)

Movement disorders, such as Parkinson’s disease and essential tremor, have presented clinicans with many diagnostic difficulties.  Commonly these types of diseases are not diagnosed until after a patient has started to experience significant symptoms.  It has been recognized in recent years that beginning treatments earlier can lead can lead to better outcomes.  In particular, it has been reported that people with Parkinson’s disease that delay treatment have a worse quality of life than those that are treated early [1].  It makes sense then that we would want to detect such diseases as early as possible, even before symptoms are noticable, to improve long-term outcomes through intervention.

This is the idea behind Introvention, which is a prototype wearable device that uses a low-power microcontroller and machine learning to detect abnormal muscular movements — tremors, twitches, jerks, etc. — at a subclinical level.  Worn around the clock, Introvention looks for unusual movements and reports them to a clinician to give them additional information that may assist them in making an early diagnosis.

An Arduino Nano 33 IoT microcontroller development board, with an onboard accelerometer is placed in a 3D printed case along with a rechargable LiPo battery.  The case is worn on the back of the hand.  Introvention continually samples movement data from the accelerometer and feeds it into a K-means clustering algorithm that has been trained to recognize the patterns of normal muscular movements that occur during typical, daily activities.  When anomalous muscular activity is detected, it is transmitted via WiFi to a [web API](https://github.com/nickbild/introvention/blob/main/api.py) that records it in a database.  A [web dashboard](https://github.com/nickbild/introvention/blob/main/dashboard.py) can present this data to a clinician graphically so that they can observe daily trends related to abnormal muscular movements.  The Arduino sketch is [available here](https://github.com/nickbild/introvention/tree/main/introvention_arduino).  The machine learning pipeline can be [viewed here](https://studio.edgeimpulse.com/public/105457/latest).

## Media

![](https://raw.githubusercontent.com/nickbild/introvention/main/media/components_sm.jpg)

![](https://raw.githubusercontent.com/nickbild/introvention/main/media/open_box_sm.jpg)

![](https://raw.githubusercontent.com/nickbild/introvention/main/media/lid_on_sm.jpg)

## Bill of Materials

- 1 x Arduino Nano 33 IoT
- 1 x 3.7V to 5.0V power boost converter
- 1 x 350 mAh LiPo battery
- 3D printed case ([case](https://github.com/nickbild/introvention/blob/main/media/introvention_case.stl), [lid](https://github.com/nickbild/introvention/blob/main/media/introvention_lid.stl))
- Velcro straps

## Disclaimer

Introvention is a prototype that has not been approved by the FDA or any other regulatory agency.  It is not suitable for diagnosing any medical condition.

## About the Author

[Nick A. Bild, MS](https://nickbild79.firebaseapp.com/#!/)

## References

[1] Rees RN, Acharya AP, Schrag A, Noyce AJ. An early diagnosis is not the same as a timely diagnosis of Parkinson's disease. F1000Res. 2018;7:F1000 Faculty Rev-1106. Published 2018 Jul 18. doi:10.12688/f1000research.14528.1
