#include "hwlib.hpp"
#include "game.hpp"

int main()
{
    //example setup for game
    hwlib::target::pin_out SCL(1, 13);
    hwlib::target::pin_out SDA(1, 12);
    hwlib::target::pin_out CS(0, 10);
    hwlib::target::pin_out DC(0, 11);

    hwlib::target::pin_in top(2, 24);
    hwlib::target::pin_in down(2, 25);
    hwlib::target::pin_in left(2, 23);
    hwlib::target::pin_in right(2, 28);

    auto bus =  hwlib::spi_bus_bit_banged_sclk_mosi_miso(SCL, SDA, hwlib::pin_in_dummy);

    SSD1351 OLED_Display(bus, CS, DC);

    //run the game forever
    for(;;)
    {
        StartGame(OLED_Display, top, down, left, right);
    }

    return 0;
}