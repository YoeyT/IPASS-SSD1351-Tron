#pragma once
#include "hwlib.hpp"
#include "color.hpp"
#include <array>

///@file

/*!   
    \mainpage SSD1351 driver library

    \section info
    This library makes interfacing with the SSD1351 a piece of cake.

    This is how you set it up:

    step 1, set up the pins:\n
    Using hwlib::pin_out you can select any pin on your controller.
    For instance hwlib::pin_out( 1, 12 ) selects pin B-12, and hwlib::pin_out( 0, 10 ) selects pin A-10.
    You should have 4 pins: SCLK, SDA, DC and CS.

    step 2, make electrical connection:\n
    Connect the corresponding pins to the inputs of your chip.
    there are often synonyms for every pin, very confusing.
    some synonyms for your pins are:\n
    SDA = SI, DA\n
    SCLK = Cl, CLK\n
    CS = SS, OC\n
    Then connect GND to GND(also called G) and 3.3 or 5 Volts to Vcc(also called +)

    step 3, set up the bus:\n
    Use hwlib::spi_bus_bit_banged_sclk_mosi_miso to set up your bus.
    Initialize it with your SCLK, SDA and hwlib::pin_in_dummy.

    step 4, set SSD1351 class up:\n
    Using the pins from the last step your initialization should look like this: SSD1351(spiBus, CS, DC)

    step 5, initialize the chip:\n
    Use the command init() to initialize the chip.
    ALWAYS do this before doing anything else.


    \section dependencies
    This is library is dependent on hwlib.
    Edit the makefile to include hwlib.

    \section hardware
    This library was made and tested on an arduino due. It should work on other devices as well, that is if you have pins available and can use hwlib on that device.
*/

//SSD1351 commands
//see datasheet pages 32-37 
#define SET_COLUMN_ADDR 0x15
#define SET_ROW_ADDR 0x75
#define WRITE_RAM 0x5C

#define CMD_LOCK 0xFD
#define DISPLAY_ON 0xAF
#define DISPLAY_OFF 0xAE
#define CLK_DIVIDER_OSCILLATOR_FREQ 0xB3
#define MULTIPLEXER_RATIO 0xCA
#define DISPLAY_OFFSET 0xA2
#define SET_GPIO 0xB5
#define FUNCTION_SELECTION 0xAB
#define PRECHARGE 0xB1
#define COM_VOLTAGE 0xBE
#define DISPLAY_MODE_NORMAL 0xA6
#define COLOR_CONTRAST 0xC1
#define MASTER_CONTRAST_CONTROLL 0xC7
#define SET_VSL 0xB4
#define SECOND_PRECHARGE 0xB6
#define SET_REMAP_COLOR_DEPTH 0xA0
#define RAM_START_LINE 0xA1
#define SET_GREY_SCALE 0xB8
#define INVERT_GREY_SCALE 0xA7
#define ALL_PIXELS_OFF 0xA4
#define ALL_PIXELS_ON 0xA5

#define HORIZONTAL_SCROLL 0x96
#define START_SCROLL 0x9E
#define STOP_SCROLL 0x9F

///\brief
///SSD1351 driver class
///\details
///This class is responsible for driving the chip using 4-pin SPI.
///The SPI-bus and pins are provided by hwlib, this is it's only dependency.
///You can use this class to do any command on the SSD1351.
class SSD1351
{
private:
    ///\brief
    ///the SPI-bus
    ///\details
    ///The SPI-bus is provided by hwlib.
    ///It contains the SCLK, MOSI and MISO pins.
    ///You don't need a MISO pin, so initialize the bus with hwlib::pin_in_dummy for MISO.
    hwlib::spi_bus& bus;

    ///\brief
    ///chip select and data/command pins
    hwlib::pin_out& CS;
    hwlib::pin_out& DC;

    ///\brief
    ///screen dimensions
    uint8_t screenHeight;
    uint8_t screenWidth;

public:
    ///\brief
    ///constructor
    ///\details
    ///You must provide an hwlib::spi_bus and hwlib::pin_out for CS and DC.
    ///The screen dimensions can differ from product to product, but most screens are 128x128 pixels. So counting from 0, screen height and width should be 127.
    SSD1351(hwlib::spi_bus& bus, hwlib::pin_out& CS, hwlib::pin_out& DC, const uint8_t screenHeight = 127, const uint8_t screenWidth = 127);


    ///\brief
    ///command functions
    ///\details
    ///These functions will do any command for you.
    ///There are four of them so you can call this function with up to 3 extra arguments.
    ///Confront the SSD1351 datasheet pages 32 - 37 to understand the commands you're using.
    void DoCommand(const uint8_t CMD);

    ///\brief
    ///alternative DoCommand function with 1 argument
    void DoCommand(const uint8_t CMD, const uint8_t arg1);

    ///\brief
    ///alternative DoCommand function with 2 arguments
    void DoCommand(const uint8_t CMD, const uint8_t arg1, const uint8_t arg2);

    ///\brief
    ///alternative DoCommand function with 3 arguments
    void DoCommand(const uint8_t CMD, const uint8_t arg1, const uint8_t arg2, const uint8_t arg3);


    ///\brief
    ///initialize SSD1351
    ///\details
    ///This functions will do a lot of commands that need to be done before using the chip.
    ///Most of the settings are reset to default, bus some are set a certain way.
    ///If you're going to use the chip then this should ALWAYS be the first function you call.
    ///A lot of the settings can be tinkered with afterwards, but always be carefull when changing settings.
    ///Confront the SSD1351 datasheet pages 32 - 37 to understand the commands you're using.
    void Init();

    ///\brief
    ///Draws a pixel on the screen
    ///\details
    ///Draws a pixels of a certain color on (x, y).
    void DrawPixel(const uint8_t x, const uint8_t y, const color color);

    ///\brief
    ///Draws a rectangle
    ///\details
    ///The way this functions draws a rectangle is way faster than doing it with individual pixels.
    ///So always use this function to create a rectangle of one color.
    ///Takes in the coordinates of the starting point, the end point and a color.
    ///the starting point locations should always be lower or the same as the end locations.
    void DrawFastRectangle(uint8_t x, uint8_t y, uint8_t endx, uint8_t endy, const color color);

    ///\brief
    ///Draw 5x5 pixels bitmap
    ///\details
    ///This function draws a small bitmap.
    ///Bitmaps are fast to draw complexer images with.
    ///A bitmap of this size is best used to draw characters with for instance.
    void Draw5x5BitMap(const std::array<std::array<color, 5>, 5>& bitMap, uint8_t locationx, uint8_t locationy);

    ///\brief
    ///Draw a bitmap on the entire screen
    ///\details
    ///This function draws a big bitmap.
    ///Bitmaps are fast to draw complexer images with.
    ///A bitmap of this size is best used to draw big complex images with.
    void Draw128x128BitMap(const std::array<std::array<color, 128>, 128>& bitMap);

    ///\brief
    ///fills the entire screen with one color
    ///\details
    ///This functions just draws a fast rectangle on the entire screen of a certain color.
    void FillScreen(const color color);

    ///\brief
    ///sets the cursor to (x, y)
    ///\details
    ///This funtion sets the cursor to location (x, y).
    ///The end location of the cursor is always the end of the screen.
    void SetCursorLocation(const uint8_t x, const uint8_t y);
};