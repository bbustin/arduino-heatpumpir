#include <FujitsuHeatpumpIR.h>
#include <PanasonicCKPHeatpumpIR.h>
#include <PanasonicHeatpumpIR.h>
#include <CarrierHeatpumpIR.h>
#include <MideaHeatpumpIR.h>
#include <MitsubishiHeatpumpIR.h>
#include <SamsungHeatpumpIR.h>

IRSender irSender(2); // IR led on ESP8266

// Array with all supported heatpumps
HeatpumpIR *heatpumpIR[] = {new PanasonicCKPHeatpumpIR(), new PanasonicDKEHeatpumpIR(), new PanasonicJKEHeatpumpIR(),
                            new PanasonicNKEHeatpumpIR(), new CarrierHeatpumpIR(), new MideaHeatpumpIR(),
                            new FujitsuHeatpumpIR(), new MitsubishiFDHeatpumpIR(), new MitsubishiFEHeatpumpIR(),
                            new SamsungHeatpumpIR(), NULL};

void setup()
{
  Serial.begin(9600);
  delay(500);

  Serial.println(F("Starting"));
}

void loop()
{
  int i = 0;
  prog_char* buf;

  do {
    // Send the same IR command to all supported heatpumps
    Serial.print(F("Sending IR to "));

    buf = (prog_char*)heatpumpIR[i]->model();
    // 'model' is a PROGMEM pointer, so need to write a byte at a time
    while (char modelChar = pgm_read_byte(buf++))
    {
      Serial.print(modelChar);
    }
    Serial.print(F(", info: "));

    buf = (prog_char*)heatpumpIR[i]->info();
    // 'info' is a PROGMEM pointer, so need to write a byte at a time
    while (char infoChar = pgm_read_byte(buf++))
    {
      Serial.print(infoChar);
    }
    Serial.println();

    // Send the IR command
    heatpumpIR[i]->send(irSender, POWER_ON, MODE_HEAT, FAN_2, 24, VDIR_UP, HDIR_AUTO);
    delay(500);
  }
  while (heatpumpIR[++i] != NULL);

  delay(2000);
}