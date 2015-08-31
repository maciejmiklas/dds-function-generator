# Overview
DDSFunctionGenerator is 100% software based Direct Digital Synthesizer.
The basic idea of such synthesizer is to create a software loop where each iteration will output single point of particular wave. Higher amount of points within single period increases resolution and reduces frequency - due to limited processing power.
There is also a good motivation to optimize the code - each extra operation consumes CPU cycles and decreases maximal output frequency.

<img src="/doc/dev1.jpg" alt="Drawing" width="200px"/>
![Login](/doc/dev2.jpg)
![Login](/doc/dev3.jpg)
![Login](/fritzing/DDS Generator_schem.jpg)

#Generated wave signals
## Sine with 120 probes per period
![sine 5.5 KHz, 120 probes](/doc/wave_sine__120_5.5KHz.jpg)
![sine 10 KHz, 120 probes](/doc/wave_sine__120_10Hz.jpg)

## Sine with 360 probes per period
Max frequency is limited to 1.8Khz where sine with 120 steps reaches 5.58Khz
![sine 1.8 KHz, 360 probes](/doc/wave_sine__360_1.8KHz.jpg)

Signal at 10Hz is smoother when compared to sine with 120 steps.
![sine 10 KHz, 360 probes](/doc/wave_sine__360_10Hz.jpg)
 
## Square
Following duty cycles are available: 10%, 20%, 30%, 50% (on screen-shot below) and 70%
![square ](/doc/wave_square.jpg)
 
## Saw
![square ](/doc/saw.jpg) 

# Wave Generator
 Wave Generator
Arduino does not have Analog to Digital converter - there is only PWM generator, but in order to generate smooth wave we need stable analog voltage. Common pattern to solve this problem is to take a few digital outputs and connect them together trough voltage divider - you can see that on schematics in the right bottom corner. We are using Arduino's digital output D0-D7 because they are all managed by single register (Port D). This means that we can change value of all 8 bits (D0-D7) with single assignment, for example: PODTD = B10000001 would set D0 and D7 to 1. This also means that mapping between byte value and analog output is linear, here are few examples that I've measured using oscilloscope:
| PORTD | Out|
| B00000001 | 22 mV |
| B00000010 | 38 mV |
| B00000100 | 73 mV |
| B00001000 | 140 mV |
| B00010000 | 276 mV |
| B00100000 | 545 mV |
| B01000000 | 1.08 V |
| B10000000 | 2.18 V |

| PORTD | Out |
| B00000001 | 22 mV |
| B00000011 | 56 mV |
| B00000111 | 125 mV |
| B00001111 | 265 mV |
| B00011111 | 543 mV |
| B00111111 | 1.1 V |
| B01111111 | 2.23 V |
| B11111111 | 4.47 V |

Each generated wave consist of few steps - for example sine has 120 (or 360 because there are two versions). Each step is pre-calculated and stored in an array - main loop simply goes over this array and assigns value from it to PORTD.

To smooth out generated signal I've used capacitor 470pF on the output. The op-amp works as a buffer so that resistance of a device connected to the output cannot influence generated wave - capacitor would discharge faster and we would change characteristics of voltage divider.

# Configuration
 Configuration
There are four buttons:
* Frequency Up - increase frequency
* Frequency Down - decrease frequency
* Delay Step - value of the step for frequency change
* Select Wave -  you can choose from from sine 120, sine 360, square and saw

Reaction on buttons is handled by interrupts, so that the main loop can concentrate on generating high frequency wave.

# Frequency adjustment
There is a small catch... single press on Frequency Up does not necessary change the frequency by one hertz, but it changes the amount of wasted CPU cycles per step .... I will try to explain this from the beginning:
as you remember we are generating wave by going over pre-calculated table - each byte in such table will be assigned to PORTD and this happens within a single "step". In order to plot wave we have to go over whole table, once we are done, we have to start from the beginning. In order to change frequency, we have to alter time for each step - this is the only possibility to proportionally scale up he whole wave. The smallest amount of delay in our case is the single CPU operation - it's called NOP and it takes 1327 nano seconds - NOP itself is quicker but I've also considered time required to call a method.
For example single period of sine consist of 120 steps, increasing delay by one, would add one NOP operation to each step, meaning that single period would take additional 120 * 1327ns.
The good news is, that LCD display always displays correct frequency in hertz, only pressing Up and Down buttons changes it by few hertz. The bottom line of LCD display shows period time in nano seconds.

# Code Optimization
My first version has used Arduino API and I was getting about 150Hz for sine with 120 steps - final optimization went up to 5,6KHz. I've used interrupts to handle input from buttons,  direct registry access, removed all unnecessary method calls, reduced size of a variables  - like from 16 to 8bits and finally exchanged floating points with integers.

There is always a tradeoff - code readability had decreased, direct access to  registers is also tricky, because they can be used for different proposals. Arduino API takes care of all those problems, but it need few extra CPU cycles.
