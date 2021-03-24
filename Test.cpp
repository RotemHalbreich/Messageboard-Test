#include "doctest.h"
#include "Board.hpp"
#include <iostream>
#include <stdexcept>
#include <string>

using namespace ariel;
using namespace std;


TEST_CASE("Reading from an empty board")
{
    Board b;

    //Horizontal
    CHECK(b.read(0, 0, Direction::Horizontal, 1) == "_");
    CHECK(b.read(11, 22, Direction::Horizontal, 8) == "________");
    CHECK(b.read(111, 222, Direction::Horizontal, 12) == "____________");

    //Vertical
    CHECK(b.read(0, 0, Direction::Vertical, 1) == "_");
    CHECK(b.read(11, 22, Direction::Vertical, 8) == "________");
    CHECK(b.read(111, 222, Direction::Vertical, 12) == "____________");
}

TEST_CASE("Post messages to an empty board")
{
    Board b;
    string msg = "my message";

    //Horizontal
    b.post(0, 0, Direction::Horizontal, msg);
    CHECK(b.read(0, 0, Direction::Horizontal, 10) == msg);

    //Vertical
    b.post(0, 0, Direction::Vertical, msg);
    CHECK(b.read(0, 0, Direction::Vertical, 10) == msg);
}

TEST_CASE("Post out of range")
{
    Board b;

    //Horizontal
    CHECK_NOTHROW(b.post(0, 10, Direction::Horizontal, "  "));
    CHECK_NOTHROW(b.post(0, 100, Direction::Horizontal, "  "));
    CHECK_NOTHROW(b.post(0, 1000, Direction::Horizontal, "  "));
    CHECK_NOTHROW(b.post(0, 10000, Direction::Horizontal, "  "));

    //Vertical
    CHECK_NOTHROW(b.post(10, 10000, Direction::Horizontal, "  "));
    CHECK_NOTHROW(b.post(100, 10000, Direction::Horizontal, "  "));
    CHECK_NOTHROW(b.post(1000, 10000, Direction::Horizontal, "  "));
    CHECK_NOTHROW(b.post(10000, 10000, Direction::Horizontal, "  "));
}

TEST_CASE("Read out of range")
{
    Board b;

    /*
      Reading characters outside the board's range size
      Check if doesn't throw an error message out of range
    */

    //Horizontal
    CHECK_NOTHROW(b.read(0, 10, Direction::Horizontal, 3));
    CHECK_NOTHROW(b.read(0, 100, Direction::Horizontal, 3));
    CHECK_NOTHROW(b.read(0, 1000, Direction::Horizontal, 3));
    CHECK_NOTHROW(b.read(0, 10000, Direction::Horizontal, 3));

    //Vertical
    CHECK_NOTHROW(b.read(10, 0, Direction::Horizontal, 3));
    CHECK_NOTHROW(b.read(100, 0, Direction::Horizontal, 3));
    CHECK_NOTHROW(b.read(1000, 0, Direction::Horizontal, 3));
    CHECK_NOTHROW(b.read(10000, 0, Direction::Horizontal, 3));

    /*
     Post words and then read out of range
    */

    //Horizontal
    b.post(0, 0, Direction::Horizontal, "rotem");
    b.post(2, 8, Direction::Horizontal, "rotem");
    b.post(15, 55, Direction::Horizontal, "rotem");

    CHECK(b.read(0, 0, Direction::Horizontal, 8) == "rotem___");
    CHECK(b.read(2, 6, Direction::Horizontal, 7) == "__rotem");
    CHECK(b.read(15, 53, Direction::Horizontal, 10) == "__rotem___");

    //Vertical
    b.post(7, 0, Direction::Vertical, "rotem");
    b.post(8, 10, Direction::Vertical, "rotem");
    b.post(55, 33, Direction::Vertical, "rotem");

    CHECK(b.read(7, 0, Direction::Vertical, 7) == "rotem__");
    CHECK(b.read(5, 10, Direction::Vertical, 8) == "___rotem");
    CHECK(b.read(52, 33, Direction::Vertical, 12) == "___rotem____");
}

TEST_CASE("Read an empty word")
{
    Board b;

    CHECK(b.read(0, 0, Direction::Horizontal, 0) == "");
    CHECK(b.read(0, 0, Direction::Vertical, 0) == "");
    CHECK(b.read(10, 20, Direction::Horizontal, 0) == "");
    CHECK(b.read(10, 20, Direction::Vertical, 0) == "");

    //Adding a string to check if the word is still empty
    b.post(10, 20, Direction::Horizontal, "rotem");
    b.post(10, 20, Direction::Vertical, "rotem");

    CHECK(b.read(10, 20, Direction::Horizontal, 0) == "");
    CHECK(b.read(10, 20, Direction::Vertical, 0) == "");
}

TEST_CASE("Overriding posted words")
{
    Board b;

    b.post(0, 0, Direction::Horizontal, "totem");
    b.post(0, 0, Direction::Vertical, "halbreich");

    CHECK(b.read(0, 0, Direction::Horizontal, 5) == "rotem");
    CHECK(b.read(0, 0, Direction::Vertical, 9) == "halbreich");

    b.post(4, 0, Direction::Vertical, "reich");
    CHECK(b.read(0, 0, Direction::Vertical, 9) == "halbreich");

    b.post(10, 0, Direction::Horizontal, "my name is rotem");
    CHECK(b.read(10, 0, Direction::Horizontal, 16) == "my name is rotem");

    b.post(10, 11, Direction::Horizontal, "stephan");
    CHECK(b.read(10, 0, Direction::Horizontal, 18) == "my name is stephan");

    b.post(10, 11, Direction::Vertical, "gr");
    CHECK(b.read(10, 11, Direction::Horizontal, 7) == "grephan");
}