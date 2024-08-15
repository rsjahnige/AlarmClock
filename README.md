# Arduino Alarm Clock
As a whole, the code contained within this repository provides an Alarm Clock implementation for an Arduino microcontroller, complete with a user interface that
displays text on a Liquid Crystal Display (LCD) linked to a Joy Stick module. This code has been written with the intention that much of it can be reused for other
Arduino projects; if desired, please refer to the [Implementation Notes](#implementation-notes) and [Disclaimers](#disclaimers) sections of this document before proceeding. 
## Directions
A conventional makefile is not provided; rather, a developer can directly pull the contents of this repository, then compile and upload it to the microcontroller using the Arduino IDE. Instructions to compile and upload this code to the microcontroller can be found at [Upload a sketch in Arduino IDE](https://support.arduino.cc/hc/en-us/articles/4733418441116-Upload-a-sketch-in-Arduino-IDE). 
### Hardware Set-up
All hardware used for this project was purchased a part of the UNO R3 Super Starter Kit from [Elegoo](https://us.elegoo.com/collections/arduino-kits). A schematic diagram is provided within the [docs/](docs/) folder of this repository, as a '.bch' file, that was constructed with [PCB Creator](https://bayareacircuits.com/pcb-design-layout-software-custom/), which can be used to replicate the circuit for this project. **It is important that the pin mappings between the Arduino and each peripheral are set-up exactly as depicted in the schematic. If a user would like to make a change to these mappings, then the AlarmClock.ino file must be updated accordingly.** 
### User Interface
The user interface for this project consists of two main components: (1) LCD and (2) Joy Stick module; as well as three auxiliary components: (3) Alarm Button, (4) LCD Switch, and (5) LCD Potentiometer.
A further description of each component is provided below:
1. **LCD** - A 2x16 character display that provides a visual interface for each 'Context' defined (e.g., Clock and Temp/Humidity).
2. **Joy Stick Module** - Allows the user to interact with the LCD as defined by the currently visible 'Context' methods. <!--Please refer to the [Instruction Manual](https://github.com/rsjahnige/AlarmClock/wiki/Instruction-Manual) for a detailed description of the user interface.-->
3. **Alarm Button** - Independent button that is used to stop an alarm sound from playing .
4. **LCD Switch** - Connected to the LCD backlight, allowing the user to switch the display ON/OFF without affecting the Arduino.
5. **LCD Potentiometer** - Connected to the LCD power supply, allowing the user to adjust the brightness of the text displayed on the LCD. <!--Please refer to the Troubleshooting section of the Instruction Manual for more details.-->
## Implementation Notes
The design for this project follows the file hierarchy depicted below:  

Note that each class derived from the Context class defines an independent aspect of the user interface (e.g., TempHumid displays values on the LCD read from the DHT11 sensor). Whereas the **AlarmClock.ino** file defines how the different Contexts and components interact with one another. If one so desires, I think it would be a fun project to define your own User Interface for an Alarm Clock by rewwritting the AlarmClock.ino file, using the resources availible in this repository. 
### Hardware Classes
The hardware clases (e.g., LiquidCrystal.h/cpp, JoyStick.h/cpp, ...) have been written in such a way as to be soley dependent upon the underlying Arduino architecture, and independent of any overlaying functionality provided by the Alarm Clock implementation.
### UserInterface Namespace
The UserInterface namespace contains all classes that are used to link the main components of the user interface (i.e., LCD and Joy Stick module) by defining methods for each Joy Stick action (e.g., left/right/up/down/click). Each class contained within this namespace is a decendent of the Context class which is responsible for printing characters to the LCD as well as defining default methods for Joy Stick actions that will be called if not otherwise overridden. 
### Dependencies
There are two external dependencies required which include: (1) Arduino.h and (2) inttypes.h. The Arduino header file is needed to communicate with the pins of the microcontroller as well as for clock synchronization. The inttypes header file is part of the C standard library which is needed for the (u)int8_t data types in files that are not dependent on the underlying microcontroller architecture (e.g., Melodies.h). It is important to note that the (u)int8_t data types are included in the Arduino header file; therefore, any file that includes Arduino.h does not require inttypes.h.
## Disclaimers
1. **This code is _NOT_ well tested -** a majoriy of testing was performed by simply playing with the user interface
2. **I have _NO_ background in circuit design; use at your own risk**
