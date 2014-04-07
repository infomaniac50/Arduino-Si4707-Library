#include "Arduino.h"  // Required for byte type

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
byte setWBFrequency(long freq);
void tuneWBFrequency(signed char increment);
unsigned int getWBFrequency();
byte getRSSI();
byte getSNR();
signed char getFreqOffset();
void printSAMEStatus();
void setMuteVolume(boolean mute);
void setVolume(int vol);
