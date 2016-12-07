# SerialTrackball

Arduino project for reading data from a serial trackball mouse.

In this implementation, the serial data is also converted into a mouse data packet for transmitting to a [**Adafruit Bluefruit EZ-Key**](https://www.adafruit.com/products/1535), but this is not necessarily the only application (one other application I can think of is using a serial mouse/trackball on an Arduino-powered robot for dead-reckoning/positioning).

This code has primarily been implemented for a Microsoft Ballpoint Serial Trackball, which uses a semi-standard version of the Microsoft Serial Mouse protocol (except it has an extra byte). The code was also tested on a Logitech Trackman trackball and found to be working on that too. 

Working example of this can be seen in my RetroBox arcade stick [here](https://www.youtube.com/watch?v=q-1sBoGaoQ0).

For the EZ-Key application, two serial ports are required - one for reading from the serial mouse, and another for talking to the EZ-Key. To achieve this, the [**AltSoftSerial library**](https://www.pjrc.com/teensy/td_libs_AltSoftSerial.html) is required.



## Circuit Diagram

![EZ-Key circuit diagram](https://raw.githubusercontent.com/UltraMegaPhil/SerialTrackball/master/images/trackball-bluefruit-circuit.png)
