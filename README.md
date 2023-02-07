# Overview
DDSFunctionGenerator is a 100% software-based Direct Digital Synthesizer.
The basic idea of such a synthesizer is to create a software loop where each iteration will output a single point of a particular wave. A higher amount of points within a single period increases resolution and reduces frequency - due to limited processing power.
There is also a good motivation to optimize the code - each extra operation consumes CPU cycles and decreases maximal output frequency.

<img src="/doc/dev1.jpg" width="300px"/>
<img src="/doc/dev2.jpg" width="300px"/>
<img src="/doc/dev3.jpg" width="300px"/>
<img src="/fritzing/DDS Generator_schem.jpg" width="600px"/>

#Generated wave signals
## Sine with 120 probes per period
<img src="/doc/wave_sine__120_5.5KHz.jpg" alt="sine 5.5 KHz, 120 probes" width="600px"/>
<img src="/doc/wave_sine__120_10Hz.jpg" alt="sine 10 KHz, 120 probes" width="600px"/>

## Sine with 360 probes per period
Max frequency is limited to 1.8Khz where sine with 120 steps reaches 5.58Khz
<img src="/doc/wave_sine__360_1.8KHz.jpg" alt="sine 1.8 KHz, 360 probes" width="600px"/>

The signal at 10Hz is smoother when compared to sine with 120 steps.
<img src="/doc/wave_sine__360_10Hz.jpg" alt="sine 10 KHz, 360 probes" width="600px"/>

## Square
The following duty cycles are available: 10%, 20%, 30%, 50% (on the screenshot below), and 70%
<img src="/doc/wave_square.jpg" width="600px"/>

## Saw
<img src="/doc/wave_saw.jpg" width="600px"/>


# Wave Generator
Arduino does not have an Analog to Digital converter - there is only a PWM generator, but to generate a smooth wave, we need stable analog voltage. A typical pattern to solve this problem is to take a few digital outputs and connect them through a voltage divider - you can see that on schematics in the bottom right corner. We are using Arduino's digital output D0-D7 because they are all managed by a single register (Port D). It means we can change the value of all 8 bits (D0-D7) with a single assignment. For example: PODTD = B10000001 would set D0 and D7 to 1. It also means that mapping between byte value and analog output is linear. Here are a few examples that I've measured using an oscilloscope:

PORTD | Out |  | PORTD | Out |
-----|-----|---|-----|-----
B00000001 | 22 mV| |B00000001 | 22 mV
B00000010 | 38 mV| |B00000011 | 56 mV
B00000100 | 73 mV| |B00000111 | 125 mV
B00001000 | 140 mV| |B00001111 | 265 mV
B00010000 | 276 mV| |B00011111 | 543 mV
B00100000 | 545 mV| |B00111111 | 1.1 V
B01000000 | 1.08 V| |B01111111 | 2.23 V
B10000000 | 2.18 V| |B11111111 | 4.47 V

Each generated wave consists of a few steps - for example, the sine has 120 (or 360 because there are two versions). Each step is pre-calculated and stored in an array - the main loop goes over this array and assigns a value from it to PORTD.

To smooth out generated signal, I've used a 470pF capacitor on the output. The op-amp works as a buffer so that the resistance of a device connected to the output cannot influence generated wave - the capacitor would discharge faster, and we would change the characteristics of a voltage divider.

# Configuration
There are four buttons:
* Frequency Up - increase frequency by offset set by Delay Step
* Frequency Down - decrease frequency  by offset set by Delay Step
* Delay Step - the value of the step for frequency change
* Select Wave -  you can choose from sine 120, sine 360, square, and saw

Reaction on buttons is handled by interrupts so that the main loop can concentrate on generating high-frequency waves.

# Frequency adjustment
There is a small catch, a single press on frequency Up does not necessarily change the frequency by one hertz, but it changes the number of wasted CPU cycles per step. I will try to explain this from the beginning:
As you remember, we are generating a wave by going over a pre-calculated table - each byte in such the table will be assigned to PORTD, which happens within a single step. To plot the wave, we have to go over the whole table. Once we are done, we have to start from the beginning. To change frequency, we have to alter the time for each step - this is the only possibility to scale up the whole wave proportionally. The slightest delay in our case is the single CPU operation - it's called NOP and takes 1327 nanoseconds - NOP itself is quicker but I've also considered the time required to call a method.
For example single period of sine consists of 120 steps. Increasing delay by one would add one NOP operation to each step, meaning that a single period would take additional 120 * 1327ns.

The good news is that LCD always displays the correct frequency in hertz. Only pressing the Up and Down buttons change it by a few hertz. The bottom line of the LCD shows the period in nanoseconds.

# Code Optimization
My first version used Arduino API, and I was getting about 150Hz for sine with 120 steps - final optimization went up to 5,6KHz. I've used the interrupts to handle input from buttons,  direct registry access, removed all unnecessary method calls, reduced size of variables  - like from 16 to 8bits, and finally exchanged floating points with integers.
