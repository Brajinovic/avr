Three Wire SPI
==============

Basic info
----------

The ATTiny does not have the necessary hardware to support SPI but it does have a USI (Universal Serial Interface). With this chip you are able to simulate SPI and I2C Communicatoin protocols. 

ATTiny - SPI master

.. list-table:: Connections
    :widths: 25 25 50


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