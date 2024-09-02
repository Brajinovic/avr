Three Wire SPI
==============

Basic info
----------

The ATTiny does not have the necessary hardware to support SPI but it does have a USI (Universal Serial Interface). With this chip you are able to simulate SPI and I2C Communicatoin protocols. 

.. note:: When you look up the pinout from the Digispark ATTiny 85, you will se MISO and MOSI labeling on the ``PB0`` and ``PB1``. These are NOT the labels for the USI as there is no SPI Hardware to be referenced. These pins are for the programming of the ATTiny and should not be referenced when making wiring decisions about the USI. Insted, you should find the ``Digital Input`` and ``Digital Output`` labeling and follow that. In the data sheet from the ATTiny 85 you will se the block diagram of the USI, and the pins referenced there are ``DO`` and ``DI``.

ATTiny - SPI master

.. list-table:: Connections
   :widths: 25 50 25 50
   :header-rows: 1

   * - AtTiny (master) Pin
     - Pin description
     - AtMega 2560 (slave) Pin
     - Pin description
     
   * - PB0
     - Digital Input (DI)
     - 50
     - MOSI (Master Out/Slave In)

   * - PB1
     - Digital Output (DO)
     - 51
     - MISO (Master In/Slave Out)

   * - PB2
     - Clock
     - 52
     - SCK 

   * - PB3
     - SS - Slave Select
     - 53
     - SS