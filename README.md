# End-of-study project : model-making railway turntable controlled with RaspberryPi 2 / touchscreen / Qt5

Student       | Client         | Academic tutor
------------- | -------------- | -----------------
Thomas Prioul | Cédric Charles | Patrick Martineau

School : __Polytech' Tours__

This project consists in the design of an embedded system made of a RaspberryPi 2, an LCD touchscreen and an electronic board which will drive a step motor. The goal of this is to control a model-making railway turntable, and to integrate this system in a much bigger model-making system that already exists in Mr Charles's house. This existing system is based on the client-server model and already has server and client programs up and running.

The software embedded in the RaspberryPi will be made using Qt 5 (C++) and Qt Quick Controls 2. 

# Contents of this repo

You will find two Qt c++ projects in this repository:
* TurntableClient
* TurntableService

## TurntableService
TurntableService is the background running program that controls the motor using the RPi's GPIOs. It is built in C++ using Qt, WiringPi and standard C++11. The usage of Qt is mostly limited to the use of an event loop and of hooking up event producers / listeners.
This utility features command line parameters, please visit the wiki to know how to use them.

## TurntableClient
TurntableClient is the GUI program that allows you to connect to the DCC server, to control the railway system and the turntable from the same program. Most of the features are easy to understand and or discover. Visit the wiki for more information on how to use this program.

# Developement and deployment

At this time, deployment isn't packaged into installers. You simply compile and run from Qt Creator.
However Qt is installed on a ready-to-use VM with a working cross-compiling toolchain. So it is easy to develop and deploy to the RPi.
Visit the wiki for manual setup of the host developement machine and of the RPi.

# Video demo
https://youtu.be/3iFZytrDC-M
https://1drv.ms/v/s!Ap4uJ_Cmvx8BiL4NV20U5qiH8EYIEg
