#include <HisenseHeatpumpIR.h>

IRSender irSender(2); // IR led on ESP8266

HisenseHeatpumpIR *heatpumpIR;                        

void setup()
{
  
  Serial.begin(9600);
  delay(500);
  heatpumpIR = new HisenseHeatpumpIR();
  Serial.println(F("Starting"));
    

  
}

void loop()
{
  int i = 0;
  prog_char* buf;


  // Send the same IR command to all supported heatpumps
  Serial.print(F("Sending IR to "));
    // Print the model
  buf = (prog_char*)heatpumpIR->model();
  // 'model' is a PROGMEM pointer, so need to write a byte at a time
  while (char modelChar = pgm_read_byte(buf++))
  {
    Serial.print(modelChar);
  }
  Serial.print(F(", info: "));
 // Print the info 
  buf = (prog_char*)heatpumpIR->info();
  // 'info' is a PROGMEM pointer, so need to write a byte at a time
  while (char infoChar = pgm_read_byte(buf++))
  {
    Serial.print(infoChar);
  }
  Serial.println();  

 
  heatpumpIR->send(irSender, POWER_ON, MODE_HEAT, FAN_3, 30, VDIR_AUTO, HDIR_AUTO);
  delay(1500);
  heatpumpIR->send(irSender, POWER_ON, MODE_DRY,  FAN_2, 20, VDIR_AUTO, HDIR_AUTO);
  delay(1500);
  heatpumpIR->send(irSender, POWER_ON, MODE_FAN, FAN_AUTO, 18, VDIR_AUTO, HDIR_AUTO);
  delay(1500);
  heatpumpIR->send(irSender, POWER_ON, MODE_COOL, FAN_1, 18, VDIR_AUTO, HDIR_AUTO);
  delay(2500);
  heatpumpIR->send(irSender, POWER_OFF, NULL, NULL, NULL, NULL, NULL);
  delay(1500);
  
}
