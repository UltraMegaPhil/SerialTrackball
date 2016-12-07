# SerialTrackball

Arduino project for reading data from a serial trackball mouse.

In this implementation, the serial data is also converted into a mouse data packet for transmitting to a [**Adafruit Bluefruit EZ-Key**](https://www.adafruit.com/products/1535), but this is not necessarily the only application (one other application I can think of is using a serial mouse/trackball on an Arduino-powered robot for dead-reckoning/positioning).

For the EZ-Key application, two serial ports are required - one for reading from the serial mouse, and another for talking to the EZ-Key. To achieve this, the [AltSoftSerial library](https://www.pjrc.com/teensy/td_libs_AltSoftSerial.html) is required.


