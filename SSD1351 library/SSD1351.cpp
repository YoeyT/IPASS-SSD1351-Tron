#include "SSD1351.hpp"

///@file

SSD1351::SSD1351(hwlib::spi_bus& bus, hwlib::pin_out& CS, hwlib::pin_out& DC, const uint8_t screenHeight, const uint8_t screenWidth) :
    bus(bus),
    CS(CS),
    DC(DC),
    screenHeight(screenHeight),
    screenWidth(screenWidth)
{}



void SSD1351::DoCommand(const uint8_t CMD)
{
    //make DC LOW so the chip knows the next byte is a command
    DC.write(0);

    //start a new transaction on the SPI bus and write the command on it
    bus.transaction(CS).write(CMD);
    DC.write(1);
}

void SSD1351::DoCommand(const uint8_t CMD, const uint8_t arg1)
{
    //make DC LOW so the chip knows the next byte is a command
    DC.write(0);

    //start a new transaction on the SPI bus and write the command on it
    auto transaction = bus.transaction(CS);
    transaction.write(CMD);
    DC.write(1);

    //write argument to SPI bus
    transaction.write(arg1);
}

void SSD1351::DoCommand(const uint8_t CMD, const uint8_t arg1, const uint8_t arg2)
{
    //make DC LOW so the chip knows the next byte is a command
    DC.write(0);

    //start a new transaction on the SPI bus and write the command on it
    auto transaction = bus.transaction(CS);
    transaction.write(CMD);
    DC.write(1);

    //write arguments to SPI bus
    transaction.write(arg1);
    transaction.write(arg2);
}

void SSD1351::DoCommand(const uint8_t CMD, const uint8_t arg1, const uint8_t arg2, const uint8_t arg3)
{
    //make DC LOW so the chip knows the next byte is a command
    DC.write(0);

    //start a new transaction on the SPI bus and write the command on it
    auto transaction = bus.transaction(CS);
    transaction.write(CMD);
    DC.write(1);

    //write arguments to SPI bus
    transaction.write(arg1);
    transaction.write(arg2);
    transaction.write(arg3);
}



void SSD1351::DrawPixel(const uint8_t x, const uint8_t y, const color color)
{
    SetCursorLocation(x, y);
    DoCommand(WRITE_RAM, color.GetFirstByte(), color.GetSecondByte());
}

void SSD1351::DrawFastRectangle(uint8_t x, uint8_t y, uint8_t endx, uint8_t endy, const color color)
{
    //select the area to draw between
    DoCommand(SET_COLUMN_ADDR, x, endx);
    DoCommand(SET_ROW_ADDR, y, endy);
    DoCommand(WRITE_RAM);

    //start a new transaction on the SPI bus
    auto transaction = bus.transaction(CS);

    //write until (dx + 1 * dy + 1) from origin point to cover every pixel in area
    for(uint16_t fill = 0; fill != ((endx - x + 1) * (endy - y + 1)); fill++)
    {
        transaction.write(color.GetFirstByte());
        transaction.write(color.GetSecondByte());
    }
}

void SSD1351::Draw5x5BitMap(const std::array<std::array<color, 5>, 5>& bitMap, uint8_t locationx, uint8_t locationy)
{
    DoCommand(SET_COLUMN_ADDR, locationx, (locationx + bitMap[0].size() - 1));
    DoCommand(SET_ROW_ADDR, locationy, (locationy + bitMap.size() - 1));
    DoCommand(WRITE_RAM);

    auto transaction = bus.transaction(CS);
    for(uint8_t y = 0; y < bitMap.size(); y++)
    {
        for(uint8_t x = 0; x < bitMap[0].size(); x++)
        {
            transaction.write(bitMap[y][x].GetFirstByte());
            transaction.write(bitMap[y][x].GetSecondByte());
        }
    }
}

void SSD1351::Draw128x128BitMap(const std::array<std::array<color, 128>, 128>& bitMap)
{
    //cover the entire screen
    DoCommand(SET_COLUMN_ADDR, 0, 127);
    DoCommand(SET_ROW_ADDR, 0, 127);
    DoCommand(WRITE_RAM);

    auto transaction = bus.transaction(CS);

    //write every color in the bitmap via transaction
    for(uint8_t y = 0; y < bitMap.size(); y++)
    {
        for(uint8_t x = 0; x < bitMap[0].size(); x++)
        {
            transaction.write(bitMap[y][x].GetFirstByte());
            transaction.write(bitMap[y][x].GetSecondByte());
        }
    }
}

void SSD1351::FillScreen(const color color)
{
    DrawFastRectangle(0, 0, screenWidth, screenHeight, color);
}

void SSD1351::SetCursorLocation(const uint8_t x, const uint8_t y)
{
    //TODO: deze functie kan beter
    if(x <= screenWidth && y <= screenHeight && x >= 0 && y >= 0)
    {
        DoCommand(SET_COLUMN_ADDR, x, screenWidth);
        DoCommand(SET_ROW_ADDR, y, screenHeight);
    }
}



void SSD1351::Init()
{
    //unlock commands
    DoCommand(CMD_LOCK, 0x12);
    DoCommand(CMD_LOCK, 0xB1);

    //sleep mode on
    DoCommand(DISPLAY_OFF);

    //oscillator frequentie and front clock divider
    DoCommand(CLK_DIVIDER_OSCILLATOR_FREQ, 0xF1);

    //reset to default settings
    DoCommand(MULTIPLEXER_RATIO, 0x7F);

    //set vertical scroll offset to 0
    DoCommand(DISPLAY_OFFSET, 0x00);

    //disable HiZ pin
    DoCommand(SET_GPIO, 0x00);

    //reset to default settings
    DoCommand(FUNCTION_SELECTION, 0x01);

    //reset to default settings
    DoCommand(PRECHARGE, 0x82);

    //reset to default settings
    DoCommand(COM_VOLTAGE, 0x05);

    //reset to default settings
    DoCommand(DISPLAY_MODE_NORMAL);

    //setting the color contrast
    DoCommand(COLOR_CONTRAST, 0xC8, 0x80, 0xC8);

    //reset to default settings
    DoCommand(MASTER_CONTRAST_CONTROLL, 0x0F);

    //reset to default settings
    DoCommand(SET_VSL, 0xA0, 0xB5, 0x55);

    //reset to default settings
    DoCommand(SECOND_PRECHARGE, 0x08);

    //sleep mode off
    DoCommand(DISPLAY_ON);

    //16 bit color sequence C->B->A (R->G->B)
    //65k color depth, 5 bits RED, 6 bits GREEN and 5 bits BLUE
    //calculation: 2^5 * 2^6 * 2^5 = 65536 colors
    //resets the rest to defaults
    DoCommand(SET_REMAP_COLOR_DEPTH, 0x74);

    //reset to default settings
    DoCommand(RAM_START_LINE, 0x80);
}