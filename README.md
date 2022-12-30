# Arduino LED exercise

Part of ISDN1011 industrial training

![Demonstration GIF](cover.gif)

## Hardware

Arduino Nano. 

Pin 2 have a button to ground. 

Pin 7, 5, A5, A4, A3, A2, A1 and A0 are the outputs, each connecting to an LED through a resistor

## analogWrite65535test.ino

Fades the D9 pin from 0V to 5V with 0-65535 levels, then back to 0V again. 

There are a total of 65536=2^16 levels, not the default 256=2^8 levels that analogWrite provides. 

The 8-bit nature of the ATmega328P microprocessor is well shown as it cannot easily handle these tasks without additional logic. 

## aw65535_button_meteor

Fades the D9 pin from 0V to 5V or from 5V to 0V with 0-65535 levels on the press of a button. 

Transition can be cancelled mid-way. 

Though not required to occur simultaneously, while doing so, 8 LEDs are also flashed in a meteor-like pattern. 

Note that there are only 6 PWM-capable pins in the Arduino Nano. 

In this exercise, the methods of implementing a software PWM is displayed. 

However, the CPU must be running in a hot loop for this to happen, since the microprocessor cannot multitask. 

The advantages of using interrupts is well shown as it can trigger code whether or not the CPU is busy. 

## Credits

analogWrite16 and setupPWM16 function taken from https://arduino.stackexchange.com/a/12719
