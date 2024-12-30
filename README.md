# ADS1119 Arduino Library

[![test](https://github.com/ELOWRO/ADS1119/actions/workflows/main.yml/badge.svg)](https://github.com/ELOWRO/ADS1119/actions/workflows/main.yml)

## Texas Instruments ADS1119

#### 16-bit, 1kSPS, 4-ch general-purpose delta-sigma ADC with I2C interface and external Vref inputs

Read more: [https://www.ti.com/product/ADS1119](https://www.ti.com/product/ADS1119)

Log: [https://downloads.arduino.cc/libraries/logs/github.com/ELOWRO/ADS1119/](https://downloads.arduino.cc/libraries/logs/github.com/ELOWRO/ADS1119/)

# Installation

## CLI

```bash
arduino-cli lib install ADS1119
```

# Usage 

## Basic:

```cpp
#include <ADS1119.h>

ADS1119 ads1 = ADS1119(byte(0B1000001));

struct ADS1119Configuration configuration;

void setup() {
  Serial.begin(9600);

  configuration.mux = ADS1119MuxConfiguration::positiveAIN0negativeAIN1;
  configuration.gain = ADS1119Configuration::Gain::one;
  configuration.dataRate  = ADS1119Configuration::DataRate::sps20;
  configuration.conversionMode = ADS1119Configuration::ConversionMode::continuous;
  configuration.voltageReference = ADS1119Configuration::VoltageReferenceSource::external;
  configuration.externalReferenceVoltage = 5.0;

  Serial.println("begin, reset");

  ads1.begin(&configuration);
  /* Config ADS1119 Amux Input as Single Ended*/
  ads1.configADCSingleEnded();
  /* Select ADS1119 Channel
  Single Ended: 4 CHANNELS => AN0, AN1, AN2, AN3
  Differential: 3 CHANNELS => AN0-AN1, AN2-AN3, AN1-AN2, 
  */
  ads1.selectChannel(0); // select AN0 (single ended input mode)
  ads1.reset();

  Serial.println("setup done");
}

void loop() {
   Serial.println(ads1.readVoltage(), 4);
}
```

## Advanced:

```cpp
#include <ADS1119.h>
#include <avr/wdt.h>

ADS1119 ads1 = ADS1119(byte(0B1000001));

struct ADS1119Configuration configuration;

void setup() {
  Serial.begin(9600);
  
  configuration.mux = ADS1119MuxConfiguration::positiveAIN0negativeAIN1;
  configuration.gain = ADS1119Configuration::Gain::one;
  configuration.dataRate  = ADS1119Configuration::DataRate::sps20;
  configuration.conversionMode = ADS1119Configuration::ConversionMode::continuous;
  configuration.voltageReference = ADS1119Configuration::VoltageReferenceSource::external;
  configuration.externalReferenceVoltage = 5.0;

  Serial.println("begin, reset");

  ads1.begin(&configuration);
  /* Config ADS1119 Amux Input as Single Ended*/
  ads1.configADCSingleEnded();
  /* Select ADS1119 Channel
  Single Ended: 4 CHANNELS => AN0, AN1, AN2, AN3
  Differential: 3 CHANNELS => AN0-AN1, AN2-AN3, AN1-AN2, 
  */
  ads1.selectChannel(0); // select AN0 (single ended input mode)
  ads1.reset();
  // Offset Calibration: VREF connected to AIN2 !!!
  // ads1.performOffsetCalibration(ADS1119MuxConfiguration::positiveAIN2negativeAGND);
  // Offset Calibration: shorting the inputs to AVDD / 2 !!!
  ads1.performOffsetCalibration(ADS1119MuxConfiguration::shortedToHalvedAVDD);
  wdt_enable(WDTO_2S);
  Serial.println("setup done");
}

void loop() {
   wdt_reset();
   Serial.println(ads1.readVoltage(), 4);
   //ads.powerDown();
}
```
