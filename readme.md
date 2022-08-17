# Simple IR Receiver/Transmitter Circuit + Code
## Definitive 2022 Guide

## Parts Required

- Arduino Uno (This circuit should work with raspberry pi as well) (1)
- Regular LED (1)
- IR LED (1)
- [IR Reciever Module](https://www.amazon.com/Digital-Receiver-Transmitter-Electronic-Building/dp/B08X2MFS6S/ref=sr_1_7?crid=2NCCFPKIWKCZV&keywords=ir+receiver+module&sprefix=ir+receiver+modul%2Caps%2C114&sr=8-7) (1)
- NPN Transistor (1)
- Resistors 
- breadboards, jumper cables

## Libraries Required
- [IRRemote.h](https://github.com/Arduino-IRremote/Arduino-IRremote)
- [IRLib2](https://github.com/cyborg5/IRLib2)

## The Circuit
![](https://i.imgur.com/twgP4qY.png)

## update 8:16:2022

After some testing, I found a bit of a current leakage. It might be through the data line to the NPN transistor as the remedy for this leakage is just attaching a ground wire to one of the ground pins on the arduino to the collector of of the transistor.

# Components Details

The circuit uses an [IR Reciever Module](https://www.amazon.com/Digital-Receiver-Transmitter-Electronic-Building/dp/B08X2MFS6S/ref=sr_1_7?crid=2NCCFPKIWKCZV&keywords=ir+receiver+module&sprefix=ir+receiver+modul%2Caps%2C114&sr=8-7) found here on amazon. Any similar modules will suffice. It's data line is connected to pin 2 on the arduino, and vcc and ground connected to a 3.3v pin and ground respectively on the Ardiuno. Depending on your sensor, you may only have the ground and data pins, and if that is the case, ommit the VCC wire.
The PWM pins on the Arduino is what we will use to send out the IR signal. Its activation will activate a bigger 'amplifier' circuit for the IR Led. It's possible to power the IR Led alone using power from Pin 3, however, output will be limited to 40 ma and range will be greatly diminished due to the square inverse law. The IR Led circuit is switched on when a positive voltage is applied to the NPN gate. 

## Calculate required Resistance
> Ohms = (Power source voltage - component operating voltage) / (operating current in AMPS.)

It's important to use the right resistors with the components you end up with as you can easily burn out a data pin on the Arduino with an IR Led or end up with a fried IR Led. Yikes, I hope you've got good ventilation if that happens. The peak draw of a typical IR Diode is appx 100ma, but the max current carrying capacity in an Arduino is only 40MA for ALL components. I would use a 20 ohms of resistance if using a 3.3v source and 200ohms if using a 5 volt source.

For example, my IR Led current rating is 120 ma peak at 1.6v. My power source is DC 3.3v. Therefore **ohms = (3.3v - 1.6v) / (120ma/1000 ma/a) =  14.166 ohm**. 
For my circuit, I use 2 10ohms resister in series for a total of 20 ohms.

If the IR Led is connected to the Arduino, I would swap out **120ma** as the operating current for **30ma**. While I was able to get a transmission from as low as 30mah from the 3.3v pins, its not powerful enough to be practical. Use an external power circuit.

## Record IR Signal
IR Signals are recorded to the serial output as an array of unsigned ints 16. These are the raw buffers recorded and is what can be used in the sendRaw method for the IR sender object. 

![](https://i.imgur.com/DQk7lAN.png)
**IR Signal Raw buffs are printed in the Serial Monitor**

    irSender.sendRaw(rawData, sizeof(rawData) / sizeof(rawData[0]), 38);
To send a raw buffer, simply call SendRaw() on your irSender object. The third parameter is the frequency used by your IR remote protocol. NEC is 38khz. It's something you're going to have to google or look into the required libraries provided examples.
