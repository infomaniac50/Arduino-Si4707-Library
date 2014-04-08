#include "Arduino.h"  // Required for byte type

// In 2-wire mode, connecting the SEN pin to the Arduino is optional.
//  If it's not connected, make sure SEN_ADDRESS is defined as 1
//  assuming SEN is pulled high as on the breakout board.
#define SEN_ADDRESS 1
// In two-wire mode: if SEN is pulled high
#if SEN_ADDRESS
  #define SI4707_ADDRESS 0b1100011
#else  // Else if SEN is pulled low
  #define SI4707_ADDRESS 0b0010001
#endif


class Si4707 {
private:
  // Pin definitions:
  // (If desired, these pins can be moved to other digital pins)
  // SEN is optional, if not used, make sure SEN_ADDRESS is 1
  int senPin;
  int rstPin;
  // Not defined, because they must be connected to A4 and A5,
  //  are SDIO and SCLK.

  // These arrays will be used by most command functions to construct
  // the command string and receive response bytes.
  byte rsp[15];
  byte cmd[8];

  void powerUp(void);
  byte command_Tune_Freq(unsigned int frequency);
  unsigned int command_Tune_Status(byte intAck, byte returnIndex);
  byte command_Get_Rev(byte returnIndex);
  byte command_SAME_Status(byte returnIndex);
  byte command_RSQ_Status(byte returnIndex);
  byte command_Get_Int_Status(void);
  void waitForCTS(void);
  void writeCommand(byte cmdSize, byte * command, byte replySize, byte * reply);
  unsigned int getProperty(unsigned int property);
  void setProperty(unsigned int propNumber, unsigned int propValue);
  void i2cReadBytes(byte number_bytes, byte * data_in);
  void i2cWriteBytes(uint8_t number_bytes, uint8_t *data_out);
  byte initSi4707();
public:
  Si4707(int _rstPin, int _senPin);
  boolean begin();
  byte setWBFrequency(long freq);
  void tuneWBFrequency(signed char increment);
  unsigned int getWBFrequency();
  byte getRSSI();
  byte getSNR();
  signed char getFreqOffset();
  void printSAMEStatus();
  void setMuteVolume(boolean mute);
  void setVolume(int vol);

};

