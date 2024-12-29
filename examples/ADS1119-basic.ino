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
