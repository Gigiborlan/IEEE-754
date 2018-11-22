# IEEE-754 Arduino
This repository contains two ways of transmiting a IEEE-754 float variable.

  - Using Serial
  - Using Modbus library
  
The data is read using analogRead in port A0 and stored in a float.
Then, it is transformed in two variables of 16 bits and transmitted.

To act as the master in the ModBus communication, you can use [QModMaster software](https://sourceforge.net/projects/qmodmaster/) .
