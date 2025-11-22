# Security Alarm System with RTOS
An embedded security system implemented with FreeRTOS, featuring intruder detection, password interface, and sound alarm. This project is designed for studying basic RTOS concepts.

## Features
Authentication system with 4-bit password

Intruder detection with HC-SR04 ultrasonic sensor

Sound alarm with buzzer

Real-time architecture with FreeRTOS

Resource management with message queues

## Technologies Used
Platform: Arduino Uno

RTOS: FreeRTOS

Language: C/C++

Sensors: HC-SR04 (ultrasonic), Joystick (password input)

Actuators: Buzzer

## Task Architecture Explanation
Task1: DistanceDetection - "The Guard" (checks when distance becomes less than or equal to 10cm - adds values to queue)

Task2: Buzz - "The Alarm" (reads the queue - if it detects values, it activates the alarm)

Task3: EnterPass - "User Interface" (allows password input, password is stored in another queue)

Task4: CheckPass - "The Verifier" (checks password correctness by reading the queue and comparing results, keeping the alarm armed or disarming it)

## Notes
The password is hardcoded in the program since this system is designed for RTOS experimentation rather than production functionality

To reactivate the alarm after disarming, press the Arduino board reset button

## How does the system look like
![WhatsApp Image 2025-11-22 at 09 52 06](https://github.com/user-attachments/assets/ca36b57b-5bd9-4136-8f2c-925a3ec5c046)
