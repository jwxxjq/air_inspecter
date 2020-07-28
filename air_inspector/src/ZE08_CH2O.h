#pragma once
#include <Arduino.h>
#include <SoftwareSerial.h>

#define ZE08_CH2O_SW_UART_RATE 9600
#define ZE08_CH2O_SW_UART_default_TX_pin 7 //5
#define ZE08_CH2O_SW_UART_default_RX_pin 8 //6
#define ZE08_CH2O_init_time_mills 180000 //180s

//#define ZE08_CH2O_SW_UART_DEBUG
/* Setup debug printing macros. */
#define ZE08_CH2O_SW_UART_DEBUG_PRINTER Serial
#ifdef ZE08_CH2O_SW_UART_DEBUG
  #define ZE08_CH2O_SW_UART_DEBUG_PRINT(...) { ZE08_CH2O_SW_UART_DEBUG_PRINTER.print(__VA_ARGS__); }
  #define ZE08_CH2O_SW_UART_DEBUG_PRINTLN(...) { ZE08_CH2O_SW_UART_DEBUG_PRINTER.println(__VA_ARGS__); }
#else
  #define ZE08_CH2O_SW_UART_DEBUG_PRINT(...) {} /**< Debug Print Placeholder if Debug is disabled */
  #define ZE08_CH2O_SW_UART_DEBUG_PRINTLN(...) {} /**< Debug Print Line Placeholder if Debug is disabled */
#endif

#define ZE08_CH2O_SERIAL_TIMEOUT 500

enum ZE08_CH2O_RESULT {
	ZE08_CH2O_RESULT_OK,
  ZE08_CH2O_RESULT_ERR_FB,
	ZE08_CH2O_RESULT_ERR_CRC,
	ZE08_CH2O_RESULT_ERR_TIMEOUT
};

class ZE08_CH2O
{
public:
  ZE08_CH2O();
  ZE08_CH2O(int8_t RX_pin_in, int8_t TX_pin_in);
  void init();
  uint32_t read_CH2O_value();

private:
  int8_t RX_pin;
  int8_t TX_pin;
  bool heating;
  unsigned long lastInitTimestamp;
  void uart_write(Stream* _serial, byte data[], byte len);
  byte calcCRC(byte *data);
  bool is_heating();
};

