quick2link
==========

Experimental code for distributed embedded architectures.

The Arduino code is inspired by and forked from Ward Cunningham's Txtzyme https://github.com/WardCunningham/Txtzyme

We've added code that provides Python and Java DSLs on the Pi or Laptop, and 
generalising the mcirocontroller code to work on Arduino or teensy 2.0/3.0

We've added basic Servo control and will add PWM, LCD and I2C control.

We're also adding location and discovery services.

Set up
------

### Arduino

On Unices, create a soft link (`ln -s`) from the directory where your Arduino environment keeps its sketches to each directory in the arduino-sketches directory:

    cd <your Arduino directory>
    ln -s <quick2link directory>/arduino-sketches/* .
    
(notice the dot at the end of the command, that's the current directory). On Windows you'll probably have to copy them over and find another way of working with version control.

Then do the same for the libraries

    cd <your Arduino directory>/libraries
    ln -s <quick2link directory>/arduino-libraries/* .
    
For the I2C connection, connect SDA to A4, SCL to A5, and Ground to Ground. The lines on our 6-pin headers are:

     ---------------
    | 3v3  SCL  Int |
    | 5v   SDA  Gnd |
     -----     -----
     
     
         
### Python

You need to have your added to your `quick2wire-python-api` directory to your exported `PYTHONPATH` 

