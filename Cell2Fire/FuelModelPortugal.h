#ifndef FUELMODELPORTUGAL
#define FUELMODELPOTUGAL
#include "ReadArgs.h"
#include "Cells.h"
#include <iostream>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <string.h>
#include <unordered_map>
#include <string>
#include <vector>

/*
*  Input, Fire, and output structures
*/

 /*
		Functions
 */
 // Initialize coefficients
 void initialize_coeff(int scenario);
 
 // Calculate flank fire 
float flankfire_ros_p(float ros, float bros, float lb) ;

// Calculate rate of spread
float rate_of_spread_p(inputs *data, fuel_coefs *ptr, main_outs *at) ;

// Length-to-Breadth ratio
float l_to_b(float ws);

// BROS
float backfire_ros_p(main_outs *at, snd_outs *sec) ;

// Flame length [m])
float flame_length(inputs *data, fuel_coefs *ptr);

// Angle of the flame w.r.t. horizontal surface (Putnam's)
float angleFL_p(inputs *data, fuel_coefs *ptr) ;

// Transformation from FL to FH using angle 
float flame_height(inputs *data, fuel_coefs *ptr) ;

//byram intensity
float byram_intensity(inputs* data, fuel_coefs* ptr);

// Type of fire (Crown = 1, SROS = 0)
bool fire_type(inputs *data, fuel_coefs *ptr) ;

// CROS adjustements
float rate_of_spread10(inputs *data,arguments *args) ;

bool checkActive(inputs * data,main_outs* at);
float crownfractionburn(inputs* data, main_outs* at);
float final_rate_of_spread10(inputs *data);
// Back fire with CROS 
float backfire_ros10_p(fire_struc *hptr, snd_outs *sec) ;

// Slope effect
float slope_effect(inputs * data);

// Main function to populate spread outputs based on inputs provided from main class
void calculate_p(inputs *data,  fuel_coefs * ptr,arguments *args, main_outs *at, snd_outs *sec, fire_struc *hptr, fire_struc *fptr,fire_struc *bptr,bool & activeCrown);

void determine_destiny_metrics_p(inputs* data, fuel_coefs* ptr,arguments *args, main_outs* at);


#endif
