# IPASS-SSD1351-Tron

How to conduct tests
	
	In the tests directory some tests have been set up.
	To actually test the library/application, just move the main.cpp into a folder that contains the what you want to test.
	Or you can change the #include paths in the test file.
	
	The SSD1351 test should be enough to test the basics of the library.
	It is recommended to test the library with the application as well.
	
	note: the application tests use catch2.hpp to test the assertions.

Tron application

	This project contains a tron application using the SSD1351 library.
	To play, just edit and use the makefile to build and run the application.

SSD1351 driver library

    This library makes interfacing with the SSD1351 a piece of cake.

    This is how you set it up:
    step 1, set up the pins:
    Using hwlib::pin_out you can select any pin on your controller.
    For instance hwlib::pin_out( 1, 12 ) selects pin B-12, and hwlib::pin_out( 0, 10 ) selects pin A-10.
    You should have 4 pins: SCLK, SDA, DC and CS.

    step 2, make electrical connection:
    Connect the corresponding pins to the inputs of your chip.
    there are often synonyms for every pin, very confusing.
    some synonyms for your pins are:
    SDA = SI, DA
    SCLK = Cl, CLK
    CS = SS, OC
    Then connect GND to GND(also called G) and 3.3 or 5 Volts to Vcc(also called +)

    step 3, set up the bus:
    Use hwlib::spi_bus_bit_banged_sclk_mosi_miso to set up your bus.
    Initialize it with your SCLK, SDA and hwlib::pin_in_dummy.

    step 4, set SSD1351 class up:
    Using the pins from the last step your initialization should look like this: SSD1351(spiBus, CS, DC)

    step 5, initialize the chip:
    Use the command init() to initialize the chip.
    ALWAYS do this before doing anything else.


    dependencies
    This is library is dependent on hwlib.
    Edit the makefile to include hwlib.

    hardware
    This library was made and tested on an arduino due. It should work on other devices as well, that is if you have pins available and can use hwlib on that device.