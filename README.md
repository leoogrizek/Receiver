# Remote-Controlled Airplane Receiver

## Description
This repository contains the code and documentation for a remote-controlled airplane receiver built using an Arduino Nano and a NRF24L01 transceiver. The receiver is part of a larger project to create a remote-controlled airplane.

## Table of Contents
- [Building the Airframe](#building-the-airframe)
- [Electronics](#electronics)
- [Installation](#installation)
- [Usage](#usage)

## Building the Airframe
Instructions for building the airframe can be found [here](https://www.rcpano.net/2020/05/19/how-to-make-rc-trainer-airplane-diy-model-airplane-for-beginners/). Follow all the steps except for the part about electronics. For this part, you will need the following tools:

- Utility knife
- Hot glue gun
- Drill
- Coping saw
- Small and large pliers (with wire cutter)
- Large ruler

## Electronics
For information regarding the electronics and other details, refer to the `RC_airplane_english.pdf` file in this repository. For this part, you will need the following tools:

- Soldering station
- Wire cutter
- Wire stripper
- Crimping tool for 2.54mm connectors

## Installation
To get this project up and running, you will need to have Microchip Studio installed on your computer. You can download it from [here](https://www.microchip.com/mplab/microchip-studio). After installing Microchip Studio, clone this repository and add the `Receiver` folder to the project. AVR LIBM is necessary and should be installed within Microchip Studio by default.

## Usage
Build the project using the GNU compiler for AVR (atmega328p) in Microchip Studio and upload the code to your Arduino Nano. Make sure to connect the NRF24L01 transceiver and other components as described in `RC_airplane_english.pdf`. ESC may not start if its connected to the Arduino after it has been powered, in this case temporarily remove the battery.