#define CATCH_CONFIG_MAIN 
#include "catch.hpp"
#include "game.hpp"


//game tests


TEST_CASE( "placing game objects and correct bike movement" )
{
   bike testBike(40, 30, 0xFFFF);
   REQUIRE(testBike.GetLocationx() == 40);
   REQUIRE(testBike.GetLocationy() == 30);
   REQUIRE(testBike.GetEndLocationx() == 44);
   REQUIRE(testBike.GetEndLocationy() == 34);

   bool up = true;
   bool down = false;
   bool left = false;
   bool right = false;

   //bike is going south by default, and pressing the up key shouldn't change that
   testBike.ReadAndMove(up, down, left, right);
   REQUIRE(testBike.GetLocationx() == 40);
   REQUIRE(testBike.GetLocationy() == 33);
   REQUIRE(testBike.GetEndLocationx() == 44);
   REQUIRE(testBike.GetEndLocationy() == 37);

   up = false;
   left = true;

   //going another direction than south or north should change the location
   testBike.ReadAndMove(up, down, left, right);
   REQUIRE(testBike.GetLocationx() == 37);
   REQUIRE(testBike.GetLocationy() == 33);
   REQUIRE(testBike.GetEndLocationx() == 41);
   REQUIRE(testBike.GetEndLocationy() == 37);
}

TEST_CASE( "correct color allocation" )
{
   color testColor1(0xFF, 0xFF, 0xFF);
   REQUIRE(testColor1.GetColor() == 0xFFFF);
   REQUIRE(testColor1.GetFirstByte() == 0xFF);
   REQUIRE(testColor1.GetSecondByte() == 0xFF);
   color testColor2(0xFF, 20, 16);
   REQUIRE(testColor2.GetColor() == 0xFA90);
   REQUIRE(testColor2.GetFirstByte() == 0xFA);
   REQUIRE(testColor2.GetSecondByte() == 0x90);
}

TEST_CASE( "collision" )
{
   wall testWall1(20, 30, 40, 55, 0);
   wall testWall2(30, 10, 30, 80, 0);
   wall testWall3(20, 60, 80, 75, 0);

   REQUIRE(Collision(testWall1, testWall2));
   REQUIRE(!Collision(testWall1, testWall3));
   REQUIRE(Collision(testWall3, testWall2));
}

TEST_CASE( "combining trails" )
{
   wall testWall1(20, 10, 20, 60, 0);
   wall testWall2(20, 60, 20, 100, 0);
   wall testWall3(20, 100, 80, 100, 0);

   std::array<wall, 50> testBikeTrail = {{
      wall(0, 0, 0, 0, 0, false),
      wall(0, 0, 0, 0, 0, false),
      wall(0, 0, 0, 0, 0, false),
      wall(0, 0, 0, 0, 0, false),
      wall(0, 0, 0, 0, 0, false),
      wall(0, 0, 0, 0, 0, false),
      wall(0, 0, 0, 0, 0, false),
      wall(0, 0, 0, 0, 0, false),
      wall(0, 0, 0, 0, 0, false),
      wall(0, 0, 0, 0, 0, false),
      wall(0, 0, 0, 0, 0, false),
      wall(0, 0, 0, 0, 0, false),
      wall(0, 0, 0, 0, 0, false),
      wall(0, 0, 0, 0, 0, false),
      wall(0, 0, 0, 0, 0, false),
      wall(0, 0, 0, 0, 0, false),
      wall(0, 0, 0, 0, 0, false),
      wall(0, 0, 0, 0, 0, false),
      wall(0, 0, 0, 0, 0, false),
      wall(0, 0, 0, 0, 0, false),
      wall(0, 0, 0, 0, 0, false),
      wall(0, 0, 0, 0, 0, false),
      wall(0, 0, 0, 0, 0, false),
      wall(0, 0, 0, 0, 0, false),
      wall(0, 0, 0, 0, 0, false),
      wall(0, 0, 0, 0, 0, false),
      wall(0, 0, 0, 0, 0, false),
      wall(0, 0, 0, 0, 0, false),
      wall(0, 0, 0, 0, 0, false),
      wall(0, 0, 0, 0, 0, false),
      wall(0, 0, 0, 0, 0, false),
      wall(0, 0, 0, 0, 0, false),
      wall(0, 0, 0, 0, 0, false),
      wall(0, 0, 0, 0, 0, false),
      wall(0, 0, 0, 0, 0, false),
      wall(0, 0, 0, 0, 0, false),
      wall(0, 0, 0, 0, 0, false),
      wall(0, 0, 0, 0, 0, false),
      wall(0, 0, 0, 0, 0, false),
      wall(0, 0, 0, 0, 0, false),
      wall(0, 0, 0, 0, 0, false),
      wall(0, 0, 0, 0, 0, false),
      wall(0, 0, 0, 0, 0, false),
      wall(0, 0, 0, 0, 0, false),
      wall(0, 0, 0, 0, 0, false),
      wall(0, 0, 0, 0, 0, false),
      wall(0, 0, 0, 0, 0, false),
      wall(0, 0, 0, 0, 0, false),
      wall(0, 0, 0, 0, 0, false),
      wall(0, 0, 0, 0, 0, false)
   }};
   uint8_t iterator = 2;

   testBikeTrail[0] = testWall1;
   testBikeTrail[1] = testWall2;
   testBikeTrail[2] = testWall3;

   REQUIRE(CanCombine(testBikeTrail, iterator));
   iterator++;
   REQUIRE(!CanCombine(testBikeTrail, iterator));
}