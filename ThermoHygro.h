#ifndef DHT11_H
#define DHT11_H

#include <Arduino.h>

namespace DHT11 
{
  class ThermoHygro;     // Forward declaration so RealNum and ThermoHygro can be friends

  /*!!! 'result' string is NOT NULL terminated !!!*/
  // Converts 'num' to character string equivalent; Writes a maximum of 'size' 
  // characters to the input array 'result' and returns the number of characters 
  // written. Intended for internal use of RealNum but could be useful in isolation 
  uint8_t itos(int8_t num, uint8_t size, char *result);

  class RealNum 
  {
  public:
    RealNum(int8_t integer=0, uint8_t decimal=0);

    int8_t getInteger(void) const { return _integer; }
    uint8_t getDecimal(void) const { return _decimal; }

    bool operator ==(const RealNum& right);  
    bool operator !=(const RealNum& right);

    /* 
      !!! 'result' string is not NULL terminated !!!
        >> See comment in TempHumid.cpp file for printData()
    */
    // Function will write a maximum of 'size' characters to the input array 
    // 'result' and return the number of characters written; 'size' >= 8 recommended
    uint8_t toString(uint8_t size, char *result) const;

    friend class ThermoHygro;    // Allows ThermoHygro to set private member variables

  private:
    int8_t _integer;
    uint8_t _decimal;
  };

  class ThermoHygro
  {
  public:
    // Data sheet recommends a 5-second delay between read operations
    ThermoHygro(uint8_t dataPin, unsigned long timeDelay=5000);

    void setDataPin(uint8_t dataPin) { _data_pin = dataPin; }
    uint8_t getDataPin(void) const { return _data_pin; }

    void setTimeDelay(unsigned long timeDelay) { _time_delay = timeDelay; }
    unsigned long getTimeDelay() const { return _time_delay; }
  
    const RealNum getTemperature();
    const RealNum getHumidity();

  protected:
    void readData(void);

  private:
    uint8_t _data_pin; 
    unsigned long _time_delay, _timer;        // Delay (in milliseconds) of subsequent read operations - non-blocking

    RealNum _temp, _humid;
  };
};



#endif
