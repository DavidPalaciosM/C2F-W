//
// Created by mati on 20-02-25.
//
#include "../../Cell2Fire/FuelModelKitral.h"
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_all.hpp>

TEST_CASE(

    "Slope effect works correctly",
    "[slope_effect]"
    )
{
    REQUIRE_THAT(slope_effect(156.75, 170, 100), Catch::Matchers::WithinAbs(1.0124, 0.001));
    REQUIRE_THAT(slope_effect(201.124, 192.543, 100), Catch::Matchers::WithinAbs(0.992, 0.001));
    REQUIRE_THAT(slope_effect(201.124, 201.124, 100), Catch::Matchers::WithinAbs(1, 0.001));
    // REQUIRE_THROWS(slope_effect(156.75, 170, 0));
}