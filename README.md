# SEISMOCARE – Earthquake Stabilized Dialysis System

### Smart India Hackathon 2025 – Team ResQure

## Overview

SEISMOCARE is a prototype earthquake detection and response system designed to enhance the safety of dialysis patients during seismic events. The system uses multiple vibration and motion sensors to detect tremors, distinguish between machine vibrations and actual earthquake activity, and automatically activate safety mechanisms such as blood tube clamping, alarms, and emergency notifications.

The prototype demonstrates how a dialysis machine can be protected from instability while preventing blood loss and ensuring patient safety during earthquakes.

---

## Features

### Real-Time Seismic Detection

* Uses MPU6050 (Accelerometer + Gyroscope) for motion sensing.
* Uses ADXL345 Accelerometer for redundant vibration monitoring.
* Uses vibration sensors and vibration motors to simulate real-world tremors.

### Earthquake Intensity Monitoring

* Displays detected tremor intensity through LEDs.

  * Green → Normal
  * Yellow → Mild Tremor
  * Red → Severe Tremor

### Automated Blood Flow Protection

* SG90 Servo Motor acts as a blood tube clamp.
* Automatically closes tubing when dangerous tremors are detected.

### Emergency Alert System

* Piezo buzzer activates during seismic events.
* Provides audible warning to hospital staff.

### Data Logging & IoT Integration

* ESP32 enables Wi-Fi communication.
* Earthquake data can be transmitted to:

  * Local dashboard
  * Hospital monitoring system
  * Cloud database

### LCD Display Interface

Displays:

* Tremor intensity
* Sensor readings
* System status
* Safety mode activation

---

# Hardware Components

| Component               | Quantity |
| ----------------------- | -------- |
| Arduino UNO             | 1        |
| ESP32 DevKit            | 1        |
| MPU6050                 | 1        |
| ADXL345                 | 1        |
| 16x2 LCD Display (I2C)  | 1        |
| SG90 Servo Motor        | 1        |
| Piezo Buzzer            | 1        |
| Push Button             | 1        |
| Green LED               | 1        |
| Yellow LED              | 1        |
| Red LED                 | 1        |
| 220Ω Resistors          | 3        |
| SW-420 Vibration Sensor | 1        |
| Coin Vibration Motor    | 2        |
| Perf Board              | 1        |
| Jumper Wires            | Multiple |
| 5V Power Supply         | 1        |

---

# Pin Configuration

## MPU6050

| MPU6050 | Arduino |
| ------- | ------- |
| VCC     | 5V      |
| GND     | GND     |
| SDA     | A4      |
| SCL     | A5      |

---

## ADXL345

| ADXL345 | Arduino |
| ------- | ------- |
| VCC     | 3.3V    |
| GND     | GND     |
| SDA     | A4      |
| SCL     | A5      |
| CS      | 3.3V    |
| SDO     | GND     |

---

## LCD Display

| LCD | Arduino |
| --- | ------- |
| VCC | 5V      |
| GND | GND     |
| SDA | A4      |
| SCL | A5      |

Address: **0x27**

---

## Servo Motor

| Servo  | Arduino |
| ------ | ------- |
| Signal | D9      |
| VCC    | 5V      |
| GND    | GND     |

---

## Buzzer

| Buzzer | Arduino |
| ------ | ------- |
| +      | D8      |
| -      | GND     |

---

## Push Button

| Button     | Arduino |
| ---------- | ------- |
| One Side   | D7      |
| Other Side | GND     |

---

## Earthquake Intensity LEDs

| LED    | Arduino Pin |
| ------ | ----------- |
| Green  | D3          |
| Yellow | D4          |
| Red    | D5          |

---

## Vibration Sensor

| Sensor | Arduino |
| ------ | ------- |
| DO     | D2      |
| VCC    | 5V      |
| GND    | GND     |

---

## ESP32 Communication

| ESP32 | Arduino UNO |
| ----- | ----------- |
| TX2   | Arduino RX  |
| RX2   | Arduino TX  |
| GND   | GND         |

---

# System Workflow

### Normal State

1. MPU6050 and ADXL345 continuously monitor movement.
2. LCD displays normal readings.
3. Green LED remains ON.
4. Servo clamp remains open.

---

### Mild Tremor Detected

1. Sensor readings exceed lower threshold.
2. Yellow LED turns ON.
3. LCD displays warning.
4. System continues monitoring.

---

### Moderate Tremor Detected

1. Vibration pattern resembles seismic activity.
2. Buzzer starts beeping.
3. Red LED turns ON.
4. Alert message displayed.

---

### Severe Earthquake Detected

1. Tremor exceeds critical threshold.
2. Servo motor closes blood tube clamp.
3. Buzzer sounds continuously.
4. Emergency mode activated.
5. Event data transmitted through ESP32.

---

# Project Architecture

```text
          MPU6050
             |
             |
          ADXL345
             |
             |
      Vibration Sensor
             |
             |
        Arduino UNO
             |
   ---------------------
   |     |      |      |
 LCD   LEDs  Buzzer Servo
                     |
                Tube Clamp

             |
          ESP32
             |
         Wi-Fi
             |
      Web Dashboard
```

---

# Future Enhancements

* TinyML-based earthquake classification
* Automatic blood return pump control
* SMS and mobile app notifications
* Cloud-based earthquake analytics
* Hospital-wide monitoring dashboard
* Battery backup during power failure
* Multiple dialysis machine integration

---

# Project Objective

The objective of SEISMOCARE is to provide a low-cost retrofit safety solution for dialysis machines that can detect earthquakes in real time, stabilize equipment, protect patients, prevent blood loss, and improve disaster preparedness in healthcare facilities.

**Team:** ResQure
**Project:** SEISMOCARE – Earthquake Stabilized Dialysis System
**SIH Problem Statement ID:** 25084
**Theme:** Disaster Management 
