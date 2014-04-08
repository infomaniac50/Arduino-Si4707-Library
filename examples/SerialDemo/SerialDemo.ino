/* Si4707 Breakout Example Code - I2C version
  by: Jim Lindblom
      SparkFun Electronics
  date: February 28, 2012

  license: Beerware. Please use, re-use, and modify this code without
  restriction! We hope you find it useful. If you do, feel free to buy us
  a beer when we meet :).

  This example code shows off some of the functionality of the Si4707
  weather band receiver IC. Throw this code on your favorite Arduino
  and connect it like so:

    Si4707 Breakout -------------- Arduino
      3.3V  ----------------------  3.3V
      GND   ----------------------  GND
      SDIO  ----------------------  SDA (A4 on older 'duinos)
      SCLK  ----------------------  SCL (A5 on older 'duinos
      RST   ----------------------   4 (can be any digital pin)

  Any other pins on the Si4707 breakout can be left unconnected.
  The SEN pin is pulled high, which will affect the I2C address.
  The GPO1/2 pins are not used as outputs, and their default
  states set the Si4707 into I2C mode.

  For more information on the Si4707, check out the abundance of
  information provided by Silicon Labs:
  https://www.silabs.com/products/audiovideo/amfmreceivers/Pages/Si4707.aspx
  Specifically, check out the Programming Guide (AN332).

  When you start up the sketch, it will attempt to initialize the
  Si4707 and tune to the frequency defined by the tuneFrequency
  global variable. After tuning a menu will be printed to the
  serial monitor, have fun interacting with the options presented!
*/
#include <Wire.h>
#include <Si4707.h>

// Pin definitions:
// (If desired, these pins can be moved to other digital pins)
// SEN is optional, if not used, make sure SEN_ADDRESS is 1
const int senPin = 5;
const int rstPin = 4;

Si4707 wb(rstPin, senPin);

// Not defined, because they must be connected to A4 and A5,
//  are SDIO and SCLK.

// Put the WB frequency you'd like to tune to here:
// The value should be in kHz, so 162475 equates to 162.475 MHz
// The sketch will attempt to tune to this frequency when it starts.
// Find your frequency here: http://www.nws.noaa.gov/nwr/indexnw.htm
unsigned long tuneFrequency = 162475; // 162.475 MHz

// Initial volume level:
int rxVolume = 63;  // Maximum loudness (should be between 0 and 63)

// The setup function initializes Serial, the Si4707, and tunes the Si4707
//  to the WB station defined at the top of this sketch (tuneFrequency).
//  To finish, it prints out the interaction menu over serial.
void setup()
{
  // Serial is used to interact with the menu, and to print debug info
  Serial.begin(9600);

  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }

  if (!wb.begin())
    while(1);

  // After initializing, we can tune to a WB frequency. Use the
  //  setWBFrequency() function to tune to a frequency. The frequency
  //  parameter given to the function should be your chosen frequency in
  //  kHz. So to tune to 162.55 MHz, send 162550. The tuneFrequency
  //  variable is defined globablly near the top of this sketch.
  if (wb.setWBFrequency(tuneFrequency))
  {
    Serial.println(F("Tune Success!"));
  }
  else
    Serial.println(F("Tune unsuccessful"));

  // After tuning, check out the serial monitor to interact with the menu.
  printMenu();
}

void loop()
{
  // Wait for a serial byte to be received:
  while( !Serial.available() )
    ;
  char c = Serial.read();
  // Once received, act on the serial input:
  switch (c)
  {
  case 'u':
    wb.tuneWBFrequency(1);  // Tune up 1 increment (2.5kHz)
    break;
  case 'd':
    wb.tuneWBFrequency(-1);  // Tune down 1 increment (2.5kHz)
    break;
  case 'U':
    wb.tuneWBFrequency(10);  // Tune up 10 increments (25kHz)
    break;
  case 'D':
    wb.tuneWBFrequency(-10);  // Tune down 10 increments (25kHz)
    break;
  case 's':
    wb.printSAMEStatus();
    break;
  case 'r':
    Serial.print("RSSI = ");
    Serial.println(wb.getRSSI());
    break;
  case 'S':
    Serial.print("SNR = ");
    Serial.println(wb.getSNR());
    break;
  case 'o':
    Serial.print("Frequency offset = ");
    Serial.println(wb.getFreqOffset());
    break;
  case 'f':
    Serial.print("Frequency = ");
    // getWBFrequency() returns the 2-byte frequency code sent
    // to the Si4707. To get a real-looking freq, multiply by .0025
    Serial.print((float) wb.getWBFrequency() * 0.0025, 4);
    Serial.println(" MHz");
    break;
  case 'm':
    wb.setMuteVolume(1);  // Turn mute on
    break;
  case 'M':
    wb.setMuteVolume(0);  // Turn mute off
    break;
  case '+':
    wb.setVolume(++rxVolume); // increment volume
    break;
  case '-':
    wb.setVolume(--rxVolume); // decrement volume
    break;
  case 'h':
    printMenu(); // print the help menu
  }
}

void printMenu()
{
  Serial.println();
  Serial.println(F("Si4707 Weather Band Example Code Menu"));
  Serial.println(F("====================================="));
  Serial.println(F("\t u) Fine tune up (+2.5kHz)"));
  Serial.println(F("\t d) Fine tune down (-2.5kHz)"));
  Serial.println(F("\t U) Coarse tune up (+25kHz)"));
  Serial.println(F("\t D) Coarse tune down (-25kHz)"));
  Serial.println(F("\t s) Get SAME status"));
  Serial.println(F("\t r) Get RSSI"));
  Serial.println(F("\t S) Get SNR"));
  Serial.println(F("\t o) Get Frequency offset"));
  Serial.println(F("\t f) Get Tune Frequency"));
  Serial.println(F("\t m) Mute audio output"));
  Serial.println(F("\t M) Un-mute audio output"));
  Serial.println(F("\t +) Increase volume"));
  Serial.println(F("\t -) Decrease volume"));
  Serial.println(F("\t h) Re-print this menu"));
  Serial.println();
}


