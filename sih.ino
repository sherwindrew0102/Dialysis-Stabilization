#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_ADXL345_U.h>
#include <ESP32Servo.h>

// === Components ===
Adafruit_MPU6050 mpu;
Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified(12345);
LiquidCrystal_I2C lcd(0x27, 16, 2); // adjust I2C address if needed
Servo clampServo;

// === Pin Definitions ===
#define SERVO_PIN 18
#define BUZZER_PIN 20
#define BUTTON_PIN 15

// === Settings ===
float quakeThreshold = 2.5; // g-force threshold
bool quakeDetected = false;

void setup() {
  Serial.begin(115200);
  Wire.begin();

  // LCD
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("SeismoCare Init");

  // MPU6050
  if (!mpu.begin()) {
    lcd.setCursor(0,1);
    lcd.print("MPU6050 FAIL");
    while (1);
  }

  // ADXL345
  if (!accel.begin()) {
    lcd.setCursor(0,1);
    lcd.print("ADXL345 FAIL");
    while (1);
  }

  // Servo
  clampServo.attach(SERVO_PIN);
  clampServo.write(0); // start unclamped

  // Buzzer
  pinMode(BUZZER_PIN, OUTPUT);
  digitalWrite(BUZZER_PIN, LOW);

  // Button
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  delay(1000);
  lcd.clear();
  lcd.print("System Ready");
}

void loop() {
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  sensors_event_t event;
  accel.getEvent(&event);

  // Calculate magnitude from MPU6050
  float mpuMagnitude = sqrt(a.acceleration.x*a.acceleration.x +
                            a.acceleration.y*a.acceleration.y +
                            a.acceleration.z*a.acceleration.z) / 9.81;

  // Calculate magnitude from ADXL345
  float adxlMagnitude = sqrt(event.acceleration.x*event.acceleration.x +
                             event.acceleration.y*event.acceleration.y +
                             event.acceleration.z*event.acceleration.z) / 9.81;

  // Check earthquake condition
  if ((mpuMagnitude > quakeThreshold || adxlMagnitude > quakeThreshold) && !quakeDetected) {
    quakeDetected = true;
    triggerSafety();
  }

  // Reset with button
  if (digitalRead(BUTTON_PIN) == LOW && quakeDetected) {
    resetSystem();
  }

  delay(200);
}

void triggerSafety() {
  lcd.clear();
  lcd.print("EARTHQUAKE!");
  lcd.setCursor(0,1);
  lcd.print("Machine Stopped");

  clampServo.write(90); // close clamp
  digitalWrite(BUZZER_PIN, HIGH); // alarm
  delay(2000);
  digitalWrite(BUZZER_PIN, LOW);
}

void resetSystem() {
  lcd.clear();
  lcd.print("System Reset");
  clampServo.write(0); // unclamp
  digitalWrite(BUZZER_PIN, LOW);
  quakeDetected = false;
  delay(1000);
  lcd.clear();
  lcd.print("Monitoring...");
}
