# Arduino Alarm Clock
As a whole, the code contained within this repository provides an Alarm Clock implementation for an Arduino microcontroller, complete with a user interface that
displays text on a Liquid Crystal Display (LCD) linked to a Joy Stick module. This code has been written with the intention that much of it can be reused for other
Arduino projects; if desired, please refer to the [Implementation Notes](#implementation-notes) and [Disclaimers](#disclaimers) sections of this document before proceeding. 
## Directions
A conventional makefile is not provided, rather a developer can directly pull the contents of this repository then compile and upload it to the microcontroller using the Arduino IDE. There are two external dependencies required which include: (1) Arduino.h and (2) inttypes.h. The Arduino header file is needed to communicate with the pins of the microcontroller as well as clock synchronization. The inttypes header file is part of the C standard library which is needed for the uint8_t data type in files that are not dependent on the underlying microcontroller architecture (e.g., Melodies.h). It is important to note that the uint8_t data type is included in the Arduino header file; therefore, any file that includes Arduino.h does not require inttypes.h.

Instructions to compile and upload this code can be found at [Upload a sketch in Arduino IDE](https://support.arduino.cc/hc/en-us/articles/4733418441116-Upload-a-sketch-in-Arduino-IDE). 
### Hardware Set-up
A schematic diagram is provided within this repository, as a '.bch' file that was constructed with [PCB Creator](https://bayareacircuits.com/pcb-design-layout-software-custom/), which can be used to replicate the circuit for this project. It is important that the pin mappings between the Arduino and each peripheral are set-up as depicted in the schematic. If a user would like to make a change to these mappings, then the AlarmClock.ino file must be updated appropriately. 
### User Interface
The user interface for this project consists of two main components: (1) LCD and (2) Joy Stick module; as well as three auxiliary components: (3) Alarm Button, (4) LCD Switch, and (5) LCD Potentiometer.
A further description of each component is provided below:
1. **LCD** - A 2x16 character display that provides a visual interface for each 'Context' defined (e.g., Clock and Temp/Humidity).
3. **Joy Stick Module** - Allows the user to interact with the LCD as defined by the currently visible 'Context' methods. Please refer to the [Instruction Manual](insert-link-to-wiki) for a detailed description of the user interface.
6. **Alarm Button** - Independent button that is used to stop an alarm sound from playing .
7. **LCD Switch** - Connected to the LCD backlight, allowing the user to switch the display ON/OFF without affecting the microcontrollers operations.
8. **LCD Potentiometer** - Connected to the LCD powersupply, allowing the user to adjust the brightness of the text displayed on the LCD. Please refer to the Troubleshooting section
   of the Instruction Manual for more details.
## Implementation Notes
## Disclaimers
1. **This code is _NOT_ well tested -** a majoriy of testing was performed by simply playing with the user interface.
