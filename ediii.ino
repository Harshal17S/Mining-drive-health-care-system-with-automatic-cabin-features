#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "MAX30100_PulseOximeter.h"

#define REPORTING_PERIOD_PULSE_OXIMETER 1000
#define REPORTING_PERIOD_MQ5 5000  // Report MQ-5 data every 5 seconds

PulseOximeter pox;
uint32_t lastReportTimePulseOximeter = 0;

const int mq5Pin = A0;  // Analog pin for MQ-5 sensor

LiquidCrystal_I2C lcd(0x27, 20, 4); // I2C address 0x27, 20 columns, 4 rows

void onBeatDetected()
{
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Heartbeat detected!");
}

void setup()
{
    Serial.begin(9600);

    lcd.begin(20, 4);
    lcd.backlight();  // Turn on the backlight
    lcd.print("Initializing...");

    Serial.println("Initializing pulse oximeter...");

    if (!pox.begin())
    {
        lcd.clear();
        lcd.print("MAX30100 error!");
        Serial.println("Could not find a valid MAX30100 sensor, check wiring!");
        while (1)
            ;
    }

    pox.setOnBeatDetectedCallback(onBeatDetected);

    delay(1000);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("System initialized");
}

void loop()
{
    // Pulse Oximeter
    pox.update();

    if ((millis() - lastReportTimePulseOximeter) > REPORTING_PERIOD_PULSE_OXIMETER)
    {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Heart rate: ");
        lcd.print(pox.getHeartRate());
        lcd.print(" bpm");

        lcd.setCursor(0, 1);
        lcd.print("SpO2: ");
        lcd.print(pox.getSpO2());
        lcd.print("%");

        lastReportTimePulseOximeter = millis();
    }

    // MQ-5 Gas Sensor
    
    if ((millis() % REPORTING_PERIOD_MQ5) == 0)
    {



        // Add logic to interpret MQ-5 data based on your specific requirements
    }
}