#include "hwlib.hpp"
#include "SSD1351.hpp"

int main()
{
    //this is all of the basic setup that is needed to control the chip
    hwlib::target::pin_out SCL(1, 13);
    hwlib::target::pin_out SDA(1, 12);
    hwlib::target::pin_out CS(0, 10);
    hwlib::target::pin_out DC(0, 11);

    auto bus =  hwlib::spi_bus_bit_banged_sclk_mosi_miso(SCL, SDA, hwlib::pin_in_dummy);

    SSD1351 OLED_Display(bus, CS, DC);

    OLED_Display.Init();

    //tests

    //test RGB color on every pixel
    OLED_Display.FillScreen(color(0xFF, 0x00, 0x00));
    OLED_Display.FillScreen(color(0x00, 0xFF, 0x00));
    OLED_Display.FillScreen(color(0x00, 0x00, 0xFF));

    //Draw Rows of different colors
    //This pattern should fade from blue to red, with a bit of green in the middle.
    //It should also have a weird pattern of stripes.
    for(uint8_t y = 0; y < 128; y++)
    {
        OLED_Display.DrawFastRectangle(0, y, 127, y, ((0xFFFF / 127) * y));
    }

    hwlib::wait_ms(500);

    //invert colors
    OLED_Display.DoCommand(INVERT_GREY_SCALE);
    hwlib::wait_ms(1000);
    //revert
    OLED_Display.DoCommand(DISPLAY_MODE_NORMAL);


    OLED_Display.FillScreen(0);


    //Draw some pixels
    for(uint8_t xy = 0; xy < 128; xy++)
    {
        OLED_Display.DrawPixel(xy, xy, 0xFFFF);
    }


    return 0;
}