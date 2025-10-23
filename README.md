Hi! My name is Ben Davis, this is a collection of the work 
I have done.
My projects are separated by the type of board used.


Altera FPGA:

  -Audio I2C: Connected FPGA to speakers via I2C to
  play an mp3 file.

  -FIFO RAM: Read and writable RAM that uses a FIFO
  order.

  -Parking Lot Meter: FSM using RAM and timers to 
  simulate a day of parking lot metrics, displaying 
  the day's data once the day is done.

Tiva C Series:

  -I2C_ArduinoUno: Sending data and controlling the 
  arduino with the Tiva being the master board.
  Arduino controls LEDs wired onto its pins.

  -LCD Display/Touch Screen: Touch screen buttons can
  switch the PLL frequency of the Tiva board. Onboard
  interrupt timers measure the Tiva's internal temperature
  every two seconds via the ADC.

  -UART: Has two different projects. One measures the board's
  internal temperature and sends the data to Putty. Happens
  every two seconds using an interrupt timer. The other receives
  a character typed into the keyboard, and sends the same character
  to be printed on Putty.