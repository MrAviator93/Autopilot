/***********************************************************************
FILE SERIALPORT.H CONTAINS BASIC IMPLEMENTATION OF THE SERIAL PORT CLASS

THE FILE CONTENT HAS BEEN CREATED TO SUPPORT "DEVELOPMENT OF FLIGHT
CONTROL SYSTEM FOR MORPHING ELEVON CONTROL SURFACE", 2019 THESIS.

FILE UTMOST REVIEW DONE ON (03.01.2021) BY ARTUR K.
***********************************************************************/

#ifndef ATL_SERIAL_PORT_HPP
#define ATL_SERIAL_PORT_HPP

typedef unsigned int uint32;
const static int MAX_ARDUINO_WAIT_TIME_MS = 2000;

namespace atl {
//-----------------------------------------------------------------------
// BOUD RATE
//-----------------------------------------------------------------------

enum BoudRate {
  BR_110 = 110,
  BR_300 = 300,
  BR_600 = 600,
  BR_1200 = 1200,
  BR_2400 = 2400,
  BR_4800 = 4800,
  BR_9600 = 9600,
  BR_14400 = 14400,
  BR_19200 = 19200,
  CBR_38400 = 38400,
  CBR_56000 = 56000,
  CBR_57600 = 57600,
  CBR_115200 = 115200,
  CBR_128000 = 128000,
  CBR_256000 = 256000
};

//-----------------------------------------------------------------------
// SERIAL PORT CLASS
//
// Serial port class wrapper, that wraps serial port read complexities.
// This class was made specifically for communication with arduino,
// for different micro controller types it may need some adjustments.
//
// BaudRate must match up the settings of the micro-controller,
// i.e. "Serial.begin(256000);"
// If it does not match, the communication won't be established!
//-----------------------------------------------------------------------

class CSerialPort {
public:
  CSerialPort(const char *pPortName, BoudRate boudRate = BoudRate::BR_9600);
  ~CSerialPort();

  int readSerialPort(void *pBuffer, uint32 bufferSize);
  int readSerialPort(char *pBuffer, uint32 bufferSize);

  template <class T> int readSerialPort(T *pObject);

  bool writeSerialPort(char *pBuffer, uint32 bufferSize);
  bool isConnected();

private:
  bool m_initialized{false};
  void *m_pHandle{nullptr}; // HANDLE
  void *m_pStatus{nullptr}; // COMSTAT
  uint32 m_errors{0};       // DWORD
};

template <class T> inline int CSerialPort::readSerialPort(T *pObject) {
  return this->readSerialPort((void *)pObject, sizeof(T));
}

} // namespace atl
#endif // !ATL_SERIAL_PORT_HPP
