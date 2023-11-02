#pragma once
#include <vector>
#include <tuple>
#include <string>
using std::vector;
using std::tuple;
using std::string;

namespace TD{
    class wave{
        vector<tuple<string, size_t>> waves;

        vector<tuple<std::string, size_t>>::iterator current_wave;

        tuple<std::string, size_t> current_enemy;

        void test(){
            waves.end();
        }

    };
}
