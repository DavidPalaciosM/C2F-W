// Inclusions
#include "ReadArgs.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <string>
#include <algorithm>
#include <dirent.h>



inline char separator()
{
#if defined _WIN32 || defined __CYGWIN__
	return '\\';
#else
	return '/';
#endif
}


char* getCmdOption(char ** begin, char ** end, const std::string & option)
{
    char ** itr = std::find(begin, end, option);
    if (itr != end && ++itr != end)
    {
        return *itr;
    }
    return 0;
}

bool cmdOptionExists(char** begin, char** end, const std::string& option)
{
    return std::find(begin, end, option) != end;
}

void parseArgs(int argc, char* argv[], arguments* args_ptr)
{
	// Help
	if (cmdOptionExists(argv, argv + argc, "-h")) {
		printf("-------------------------------------------\n         Help manual!!! \n-------------------------------------------\n");
	}

	// Empty default
	char empty = '\0';


	// Strings
	//--input-instance-folder
	char* input_folder = getCmdOption(argv, argv + argc, "--input-instance-folder");
	if (input_folder) {
		printf("InFolder: %s \n", input_folder);
	}
	else input_folder = &empty;

	//--output-folder
	char* output_folder = getCmdOption(argv, argv + argc, "--output-folder");
	if (output_folder) {
		printf("OutFolder: %s \n", output_folder);
	}
	else output_folder = &empty;

	//--weather
	char* input_weather = getCmdOption(argv, argv + argc, "--weather");
	if (input_weather) {
		printf("WeatherOpt: %s \n", input_weather);
	}
	else input_weather = &empty;

	//--FirebreakPlan
	char* input_hplan = getCmdOption(argv, argv + argc, "--FirebreakCells");
	if (input_hplan) {
		printf("FirebreakCells: %s \n", input_hplan);
	}
	else input_hplan = &empty;

	// Booleans
	bool out_messages = false;
	bool out_trajectories = false;
	bool no_output = false;
	bool verbose_input = false;
	bool iplog_input = false;
	bool input_ignitions = false;
	bool out_grids = false;
	bool out_fl=false;
	bool out_intensity=false;
	bool out_ros=false;
	bool out_crown = false;
	bool out_crown_consumption=false;
	bool out_surf_consumption=false;
	bool out_finalgrid = false;
	bool prom_tuned = false;
	bool out_stats = false;
	bool bbo_tuning = false;
	bool allow_cros = false;

	//--out-messages
	if (cmdOptionExists(argv, argv + argc, "--output-messages")) {
		out_messages = true;
		printf("OutMessages: %d \n", out_messages);
	}

	//--fire-behavior
	if (cmdOptionExists(argv, argv + argc, "--out-fl")) {
		out_fl = true;
		printf("OutFlameLength: %d \n", out_fl);
	}
		//--fire-behavior
	if (cmdOptionExists(argv, argv + argc, "--out-intensity")) {
		out_intensity = true;
		printf("OutIntensity: %d \n", out_intensity);
	}
		//--fire-behavior
	if (cmdOptionExists(argv, argv + argc, "--out-ros")) {
		out_ros = true;
		printf("OutROS: %d \n", out_ros);
	}
			//--fire-behavior
	if (cmdOptionExists(argv, argv + argc, "--out-crown")) {
		out_crown = true;
		printf("OutCrown: %d \n", out_crown);
	}
	
	if (cmdOptionExists(argv, argv + argc, "--out-cfb")) {
		out_crown_consumption = true;
		printf("OutCrownConsumption: %d \n", out_crown_consumption);
	}

	if (cmdOptionExists(argv, argv + argc, "--out-sfb")) {
		out_surf_consumption = true;
		printf("OutSurfaceConsumption: %d \n", out_surf_consumption);
	}
	

	//--trajectories
	//if (cmdOptionExists(argv, argv + argc, "--trajectories")) {
	//	out_trajectories = true;
	//	printf("Trajectories: %d \n", out_trajectories);
	//}

	//--no-output
	//if (cmdOptionExists(argv, argv + argc, "--no-output")) {
	//	no_output = true;
	//	printf("noOutput: %d \n", no_output);
	//}

	//--verbose
	if (cmdOptionExists(argv, argv + argc, "--verbose")) {
		verbose_input = true;
		printf("verbose: %d \n", verbose_input);
	}

	// --ignitionsLog
	if (cmdOptionExists(argv, argv + argc, "--ignitionsLog")) {
		iplog_input = true;
		printf("Ignition Points Log: %d \n", iplog_input);
	}

	//--ignitions
	if (cmdOptionExists(argv, argv + argc, "--ignitions")) {
		input_ignitions = true;
		printf("Ignitions: %d \n", input_ignitions);
	}

	//--grids
	if (cmdOptionExists(argv, argv + argc, "--grids")) {
		out_grids = true;
		printf("OutputGrids: %d \n", out_grids);
	}

	//--final-grid
	if (cmdOptionExists(argv, argv + argc, "--final-grid")) {
		out_finalgrid = true;
		printf("FinalGrid: %d \n", out_finalgrid);
	}

	//--Prom_tuned
	//if (cmdOptionExists(argv, argv + argc, "--PromTuned")) {
	//	prom_tuned = true;
	//	printf("PromTuned: %d \n", prom_tuned);
	//}

	//--statistics
	//if (cmdOptionExists(argv, argv + argc, "--statistics")) {
	//	out_stats = true;
	//	printf("Statistics: %d \n", out_stats);
	//}

	//--bbo
	if (cmdOptionExists(argv, argv + argc, "--bbo")) {
		bbo_tuning = true;
		printf("BBOTuning: %d \n", out_stats);
	}

	//--cros
	if (cmdOptionExists(argv, argv + argc, "--cros")) {
		allow_cros = true;
		printf("CrownROS: %d \n", allow_cros);
	}


	// Floats and ints
	// defaults
	int dsim_years = 1;
	int dnsims = 1;
	int dweather_period_len = 60;
	int dmax_fire_periods = 1000;
	int dseed = 123;
	int diradius = 0;
	int dnthreads = 1;
	int dfmc=100;
	int dscen=3;
	float dROS_Threshold= 0.1;
	float dHFI_Threshold= 0.1;
	float dCROS_Threshold= 0.5;
	//float dCROSAct_Threshold= 1.0;
	float dROSCV= 0.;
	float dHFactor = 1.0;
	float dFFactor = 1.0;
	float dBFactor = 1.0;
	float dEFactor = 1.0;
	float dCBDFactor = 0.0; //spain
	//float dCBHFactor = 1.0;
	float dCCFFactor = 0.0; //spain
	float dROS10Factor = 3.34; //spain
	float dinput_PeriodLen= 1.;
	
	// aux 
	std::string::size_type sz;

	//--sim-years  (float)
	char * sim_years = getCmdOption(argv, argv + argc, "--sim-years");
    if (sim_years){
        printf("TotalYears: %s \n", sim_years);
		args_ptr->TotalYears = std::stoi (sim_years ,&sz); 
    }
	else args_ptr->TotalYears = dsim_years;
	
	//--nsims
	char * input_nsims = getCmdOption(argv, argv + argc, "--nsims");
    if (input_nsims){
        printf("TotalSims: %s \n", input_nsims);
		args_ptr->TotalSims = std::stoi (input_nsims ,&sz);  
    }
	else args_ptr->TotalSims = dnsims;


		//--nsims
	char * simulator_option = getCmdOption(argv, argv + argc, "--sim");
    if (simulator_option){
		std::string s=simulator_option;
		if (s!="S" && s!="K" && s!="C" && s!="P"){
			printf("%s Simulator Option not recognized or not developed, using S&B as default!!! \n", simulator_option);
			args_ptr->Simulator=simulator_option;
		}
		else{
		printf("Simulator: %s \n", simulator_option);
		args_ptr->Simulator = simulator_option; 
		}
    }
	else {
		printf("No Simulator Option Selected, using S&B as default!!! \n");
		args_ptr->Simulator = "S";}
	
	
	//--Weather-Period-Length
	char * weather_period_len = getCmdOption(argv, argv + argc, "--Weather-Period-Length");
    if (weather_period_len){
        printf("WeatherPeriodLength: %s \n", weather_period_len);
		args_ptr->MinutesPerWP = std::stoi (weather_period_len ,&sz); 
    }
	else args_ptr->MinutesPerWP = dweather_period_len;
	
	//--nweathers
	char * nweathers = getCmdOption(argv, argv + argc, "--nweathers");
    if (nweathers){
		args_ptr->NWeatherFiles = std::stoi (nweathers ,&sz); 
    }
	else{
		//std::cout << "No NWeatherFiles specified " << input_weather << std::endl;
		if (std::string(input_weather) == "random") {
			//std::cout << "Counting" << std::endl;
			std::string input_string = input_folder;
			args_ptr->NWeatherFiles = countWeathers(input_string + "/Weathers");
		}
		else {
			///std::cout << "No NWeatherFiles specified 1 default" << std::endl;
			args_ptr->NWeatherFiles = 1;
		}
	} 
	
	//--Fire-Period-Length
	char * input_PeriodLen = getCmdOption(argv, argv + argc, "--Fire-Period-Length");
    if (input_PeriodLen){
        printf("FirePeriodLength: %s \n", input_PeriodLen);
		if (std::stof (input_PeriodLen ,&sz) <= args_ptr->MinutesPerWP){
			 args_ptr->FirePeriodLen = std::stof (input_PeriodLen ,&sz); 
		}
		else args_ptr->FirePeriodLen =  args_ptr->MinutesPerWP;
    } 
	else args_ptr->FirePeriodLen = dinput_PeriodLen;
	
	//--IgnitionRad
	char * input_igrad = getCmdOption(argv, argv + argc, "--IgnitionRad");
    if (input_igrad){
        printf("IgnitionRadius: %s \n", input_igrad);
		args_ptr->IgnitionRadius = std::stoi (input_igrad ,&sz); 
    } 
	else args_ptr->IgnitionRadius =  diradius;
	

	//--fmc
	char * input_fmc = getCmdOption(argv, argv + argc, "--fmc");
    if (input_fmc){
        printf("fmc: %s \n", input_fmc);
		args_ptr->FMC = std::stoi (input_fmc ,&sz);  
    }
	else args_ptr->FMC = dfmc; 
	
		//--scenario
	char * input_scenario = getCmdOption(argv, argv + argc, "--scenario");
    if (input_scenario){
        printf("scenario: %s \n", input_scenario);
		args_ptr->scenario = std::stoi (input_scenario ,&sz);  
    }
	else args_ptr->scenario = dscen; 
	
	
	//--ROS-Threshold
	char * ROS_Threshold = getCmdOption(argv, argv + argc, "--ROS-Threshold");
    if (ROS_Threshold){
        printf("ROSThreshold: %s \n", ROS_Threshold);
		args_ptr->ROSThreshold = std::stof (ROS_Threshold ,&sz); 
    }
	else args_ptr->ROSThreshold = dROS_Threshold;
	
	//--CROS-Threshold
	char * CROS_Threshold = getCmdOption(argv, argv + argc, "--CROS-Threshold");
    if (CROS_Threshold){
        printf("CROSThreshold: %s \n", CROS_Threshold);
		args_ptr->CROSThreshold = std::stof (CROS_Threshold ,&sz); 
    }
	else args_ptr->CROSThreshold = dCROS_Threshold;
	
	//--HFI-Threshold
	char * HFI_Threshold = getCmdOption(argv, argv + argc, "--HFI-Threshold");
    if (HFI_Threshold){
        printf("HFIThreshold: %s \n", HFI_Threshold);
		args_ptr->HFIThreshold = std::stof (HFI_Threshold ,&sz);
    }
	else args_ptr->HFIThreshold = dHFI_Threshold;
	
	//--CROSAct-Threshold
	char * CROSAct_Threshold = getCmdOption(argv, argv + argc, "--CROSAct-Threshold");
    if (CROSAct_Threshold){
        printf("CROSActThreshold: %s \n", CROSAct_Threshold);
		args_ptr->CROSActThreshold = std::stof (CROSAct_Threshold ,&sz); 
    }
	else args_ptr->CROSThreshold = dCROS_Threshold;
	
	
	//--HFactor
	char * H_Factor = getCmdOption(argv, argv + argc, "--HFactor");
    if (H_Factor){
        printf("HFactor: %s \n", H_Factor);
		args_ptr->HFactor = std::stof (H_Factor ,&sz); 
    }
	else args_ptr->HFactor = dHFactor;
	
	//---FFactor
	char * F_Factor = getCmdOption(argv, argv + argc, "--FFactor");
    if (F_Factor){
        printf("FFactor: %s \n", F_Factor);
		args_ptr->FFactor = std::stof (F_Factor ,&sz); 
    }
	else args_ptr->FFactor = dFFactor;
	
	///--BFactor
	char * B_Factor = getCmdOption(argv, argv + argc, "--BFactor");
    if (B_Factor){
        printf("BFactor: %s \n", B_Factor);
		args_ptr->BFactor = std::stof (B_Factor ,&sz); 
    }
	else args_ptr->BFactor = dBFactor;
	
	///--EFactor
	char * E_Factor = getCmdOption(argv, argv + argc, "--EFactor");
    if (E_Factor){
        printf("EFactor: %s \n", E_Factor);
		args_ptr->EFactor = std::stof (E_Factor ,&sz); 
    }
	else args_ptr->EFactor = dEFactor;
		
	///--CBDFactor
	char * CBD_Factor = getCmdOption(argv, argv + argc, "--CBDFactor");
    if (CBD_Factor){
        printf("CBDFactor: %s \n", CBD_Factor);
		args_ptr->CBDFactor = std::stof (CBD_Factor ,&sz); 
    }
	else args_ptr->CBDFactor = dCBDFactor;
	
	///--CCFFactor
	char * CCF_Factor = getCmdOption(argv, argv + argc, "--CCFFactor");
    if (CCF_Factor){
        printf("CCFFactor: %s \n", CCF_Factor);
		args_ptr->CCFFactor = std::stof (CCF_Factor ,&sz); 
    }
	else args_ptr->CCFFactor = dCCFFactor;
	
	///--ROS10Factor
	char * ROS10_Factor = getCmdOption(argv, argv + argc, "--ROS10Factor");
    if (ROS10_Factor){
        printf("ROS10Factor: %s \n", ROS10_Factor);
		args_ptr->ROS10Factor = std::stof (ROS10_Factor, &sz); 
    }
	else args_ptr->ROS10Factor = dROS10Factor;
	
	//--ROS-CV
	char * ROS_CV = getCmdOption(argv, argv + argc, "--ROS-CV");
    if (ROS_CV){
        printf("ROS-CV: %s \n", ROS_CV);
		args_ptr->ROSCV = std::stof (ROS_CV ,&sz); 
    }
	else args_ptr->ROSCV = dROSCV;
	
	//--max-fire-periods
	char * max_fire_periods = getCmdOption(argv, argv + argc, "--max-fire-periods");
    if (max_fire_periods){
        printf("MaxFirePeriods: %s \n", max_fire_periods);
		args_ptr->MaxFirePeriods = std::stoi (max_fire_periods ,&sz); 
    }
	else args_ptr->MaxFirePeriods = dmax_fire_periods;
	
	//--seed  (int)
	char * seed = getCmdOption(argv, argv + argc, "--seed");
    if (seed){
        printf("seed: %s \n", seed);
		args_ptr->seed = std::stoi (seed ,&sz); 
    }
	else args_ptr->seed = dseed;
	
	//--nthreads  (int)
	char* nthreads = getCmdOption(argv, argv + argc, "--nthreads");
	if (nthreads) {
		printf("nthreads: %s \n", nthreads);
		args_ptr->nthreads = std::stoi(nthreads, &sz);
	}
	else args_ptr->nthreads = dnthreads;

	// Populate structure
	// Strings 
	if (input_folder == &empty){
		args_ptr->InFolder = ""; 
	}
	else args_ptr->InFolder = input_folder; 
	
	if (!args_ptr->InFolder.empty() && *args_ptr->InFolder.rbegin()!= separator()){
		args_ptr->InFolder+=separator();
	}

	

	if (output_folder == &empty && input_folder != &empty){
		args_ptr->OutFolder = args_ptr->InFolder + "simOuts";
	} else if(output_folder == &empty && input_folder == &empty){
		args_ptr->OutFolder = "simOuts";
	} else if(output_folder != &empty && input_folder == &empty){
		args_ptr->OutFolder = output_folder;
	} else if(output_folder != &empty && input_folder != &empty){
		args_ptr->OutFolder = output_folder;
	}

	if (!args_ptr->OutFolder.empty() && *args_ptr->OutFolder.rbegin()!= separator()){
		args_ptr->OutFolder+=separator();
	}
		
	if (input_weather == &empty){
		args_ptr->WeatherOpt = "rows";
	}
	else{
		args_ptr->WeatherOpt = input_weather;
	}
	
	if (input_hplan == &empty){
		args_ptr->HarvestPlan = ""; 
	}
	else args_ptr->HarvestPlan = input_hplan; 

		
	// booleans
	args_ptr->OutMessages = out_messages;
	args_ptr->OutFl = out_fl;
	args_ptr->OutIntensity = out_intensity;
	args_ptr->OutRos = out_ros;
	args_ptr->OutCrown = out_crown;
	args_ptr->OutCrownConsumption = out_crown_consumption;
	args_ptr->OutSurfConsumption = out_surf_consumption;
	args_ptr->Trajectories = out_trajectories; 
	args_ptr->NoOutput = no_output;
	args_ptr->verbose = verbose_input;
	args_ptr->IgnitionsLog = iplog_input; 
	args_ptr->Ignitions = input_ignitions;
	args_ptr->OutputGrids = out_grids; 
	args_ptr->FinalGrid = out_finalgrid;
	args_ptr->PromTuned = prom_tuned;
	args_ptr->Stats = out_stats;   
	args_ptr->BBOTuning = bbo_tuning;
	args_ptr->AllowCROS = allow_cros;

}


void printArgs(arguments args){

	/*
	std::cout << "Simulator: "<<args.Simulator<<std::endl;
	std::cout << "InFolder: " << args.InFolder << std::endl; 
	std::cout << "OutFolder: " << args.OutFolder << std::endl; 
	std::cout << "WeatherOpt: " << args.WeatherOpt << std::endl;
	std::cout << "NWeatherFiles: " << args.NWeatherFiles << std::endl;	
	std::cout << "MinutesPerWP: " << args.MinutesPerWP << std::endl; 
	std::cout << "MaxFirePeriods: " << args.MaxFirePeriods << std::endl; 
	std::cout << "Messages: " << args.OutMessages << std::endl;
	std::cout << "OutFlameLength: " << args.OutFl << std::endl;
	std::cout << "OutIntensity: " << args.OutIntensity << std::endl;
	std::cout << "OutROS: " << args.OutRos << std::endl;
	std::cout << "OutCrown: " << args.OutCrown << std::endl;
	std::cout << "OutCrownConsumption: " << args.OutCrownConsumption << std::endl;
	std::cout << "OutSurfConsumption: " << args.OutSurfConsumption << std::endl;
	std::cout << "HarvestPlan: " << args.HarvestPlan << std::endl; 
	std::cout << "TotalYears: " << args.TotalYears << std::endl; 
	std::cout << "TotalSims: " << args.TotalSims << std::endl; 
	std::cout << "FirePeriodLen: " << args.FirePeriodLen << std::endl; 
	std::cout << "Ignitions: " << args.Ignitions << std::endl; 
	std::cout << "IgnitionRad: " << args.IgnitionRadius << std::endl; 
	std::cout << "OutputGrid: " << args.OutputGrids << std::endl; 
	std::cout << "FinalGrid: " << args.FinalGrid << std::endl; 
	std::cout << "PromTuned: " << args.PromTuned << std::endl; 
	std::cout << "BBOTuning: " << args.BBOTuning << std::endl; 
	std::cout << "Statistics: " << args.Stats << std::endl; 
	std::cout << "noOutput: " << args.NoOutput << std::endl; 
	std::cout << "verbose: " << args.verbose << std::endl; 
	std::cout << "seed: " << args.seed << std::endl; 
	std::cout << "nthreads: " << args.nthreads << std::endl;
	*/

	std::cout << "Simulator: "<<args.Simulator<<std::endl;
	std::cout << "InFolder: " << args.InFolder << std::endl; 
	std::cout << "OutFolder: " << args.OutFolder << std::endl; 
	std::cout << "WeatherOpt: " << args.WeatherOpt << std::endl;
	std::cout << "FirebreakCells: " << args.HarvestPlan << std::endl;
	std::cout << "NWeatherFiles: " << args.NWeatherFiles << std::endl;	
	std::cout << "MinutesPerWP: " << args.MinutesPerWP << std::endl; 
	std::cout << "MaxFirePeriods: " << args.MaxFirePeriods << std::endl; 
	std::cout << "Messages: " << args.OutMessages << std::endl;
	std::cout << "OutFlameLength: " << args.OutFl << std::endl;
	std::cout << "OutIntensity: " << args.OutIntensity << std::endl;
	std::cout << "OutROS: " << args.OutRos << std::endl;
	std::cout << "OutCrown: " << args.OutCrown << std::endl;
	std::cout << "OutCrownConsumption: " << args.OutCrownConsumption << std::endl;
	std::cout << "OutSurfConsumption: " << args.OutSurfConsumption << std::endl;
	 
	std::cout << "TotalYears: " << args.TotalYears << std::endl; 
	std::cout << "TotalSims: " << args.TotalSims << std::endl; 
	std::cout << "FirePeriodLen: " << args.FirePeriodLen << std::endl; 
	std::cout << "Ignitions: " << args.Ignitions << std::endl; 
	std::cout << "IgnitionRad: " << args.IgnitionRadius << std::endl; 
	std::cout << "OutputGrid: " << args.OutputGrids << std::endl; 
	std::cout << "FinalGrid: " << args.FinalGrid << std::endl; 
	std::cout << "PromTuned: " << args.PromTuned << std::endl; 
	std::cout << "BBOTuning: " << args.BBOTuning << std::endl; 
	std::cout << "Statistics: " << args.Stats << std::endl; 
	std::cout << "noOutput: " << args.NoOutput << std::endl; 
	std::cout << "verbose: " << args.verbose << std::endl;
	std::cout << "Ignition Points Log: " << args.IgnitionsLog << std::endl; 
	std::cout << "seed: " << args.seed << std::endl; 
	std::cout << "nthreads: " << args.nthreads << std::endl;

	
	
}

int countWeathers(const std::string directory_path) {
	DIR* dir;
	struct dirent* ent;
	int file_count = 0;

	if ((dir = opendir(directory_path.c_str())) != NULL) {
		while ((ent = readdir(dir)) != NULL) {
			if (ent->d_type == DT_REG) {
				std::string filename = ent->d_name;
				if (filename.substr(0, 7) == "Weather" && filename.substr(filename.size() - 4) == ".csv") {
					file_count++;
				}
			}
		}
		closedir(dir);
	}
	else {
		std::cout << "Could not open directory" << std::endl;
		return -1;
	}

	return file_count;
}
