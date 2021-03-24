#pragma once
#include <string>
#include <map>
#include "Direction.hpp"

using namespace std;

struct blank
{
    char ch = '_';
};

namespace ariel
{
    class Board
    {
    private:
        uint _rows, _cols;
        map<uint, map<uint, blank>> _board;

    public:
        Board(){}

        ~Board() {}

        void post(uint row, uint column, Direction direction, const string &message);
        static std::string read(uint row, uint column, Direction direction, uint length);
        void show();
    };
}