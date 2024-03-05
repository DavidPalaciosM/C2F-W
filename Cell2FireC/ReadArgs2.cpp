#include <iostream>
#include <getopt.h>

using namespace std;

void display_help() {
    std::cout << "Usage: ./your_program [options] [arguments]\n"
              << "Options:\n"
              << "  -i, --input-instance-folder          Option 'a'\n"
              << "  -o, --output-folder            Option 'b'\n"
              << "  -w, --weather      Option 'c' with argument\n"
              << "  -f, --FirebreakCells      Option 'd' with argument\n"
              << "  -M, --output-messages      Option 'd' with argument\n"
              << "  -h, --help                Display this help message\n";
}

int parseArgs2(int argc, char* argv[], arguments2* args_ptr){

    bool out_messages = false;
    bool out_fl=false;
	bool out_intensity=false;
	bool out_ros=false;
	bool out_crown_consumption=false;
	bool out_surf_consumption=false;
	bool allow_cros = false;
    bool input_ignitions = false;

    int dnsims = 1;
    int dseed = 123;
    int dnthreads = 1;


    int option;
    int opterr = 1; // Enable printing error messages
    int optopt;     // Variable to store the offending option character

    const char    * short_opt = "i:o:w:f:MFIRCSgcnmwst";

    static struct option long_opt[] = {
    {"input-instance-folder", required_argument,       0, 'i'},
    {"output-folder", required_argument,       0, 'o'},
    {"weather", required_argument, 0, 'w'},
    {"FirebreakCells", required_argument, 0, 'f'},
    {"output-messages", no_argument, 0, 'M'},
    {"out-fl", no_argument, 0, 'F'},
    {"out-intensity", no_argument, 0, 'I'},
    {"out-ros", no_argument, 0, 'R'},
    //{"out-crown", no_argument, 0, 'C'},
    {"out-cfb", no_argument, 0, 'C'},
    {"out-sfb", no_argument, 0, 'S'},
    //{"trajectories", no_argument, 0, 'd'},
    //{"no-output", no_argument, 0, 'd'},
    //{"verbose", no_argument, 0, 'd'},
    {"ignitions", no_argument, 0, 'g'},
    //{"grids", no_argument, 0, 'd'},
    //{"final-grid", no_argument, 0, 'd'},
    //{"PromTuned", no_argument, 0, 'd'},
    //{"statistics", no_argument, 0, 'd'},
    //{"bbo", no_argument, 0, 'd'},
    {"cros", no_argument, 0, 'c'},
    //{"sim-years", no_argument, 0, 'd'},
    {"nsims", no_argument, 0, 'n'},
    {"sim", no_argument, 0, 'm'},
    //{"Weather-Period-Length", no_argument, 0, 'd'},
    //{"nweathers", no_argument, 0, 'W'},
    //{"Fire-Period-Length", no_argument, 0, 'd'},
    //{"IgnitionRad", no_argument, 0, 'd'},
    //{"fmc", no_argument, 0, 'd'},
    //{"scenario", no_argument, 0, 'd'},
    //{"ROS-Threshold", no_argument, 0, 'd'},
    //{"CROS-Threshold", no_argument, 0, 'd'},
    //{"HFI-Threshold", no_argument, 0, 'd'},
    //{"CROSAct-Threshold", no_argument, 0, 'd'},
    //{"HFactor", no_argument, 0, 'd'},
    //{"FFactor", no_argument, 0, 'd'},
    //{"BFactor", no_argument, 0, 'd'},
    //{"EFactor", no_argument, 0, 'd'},
    //{"CBDFactor", no_argument, 0, 'd'},
    //{"CCFFactor", no_argument, 0, 'd'},
    //{"ROS10Factor", no_argument, 0, 'd'},
    //{"ROS-CV", no_argument, 0, 'd'},
    //{"max-fire-periods", no_argument, 0, 'd'},
    {"seed", no_argument, 0, 's'},
    {"nthreads", no_argument, 0, 't'},
    {0, 0, 0, 0} // Terminate the array with all zero values
    };

    // "i:o:w:f:MFIRCSgcnmwst"
     while ((option = getopt_long(argc, argv, short_opt, long_opt, NULL)) != -1) {
        switch (option) {
            case 'i':
                //char* input_folder = optarg;
                args_ptr->InFolder = optarg;
                break;
            case 'o':
                args_ptr->OutFolder = optarg;
                break;
            case 'w':
                args_ptr->WeatherOpt = optarg;
                break;
            case 'f':
                args_ptr->HarvestPlan = optarg;
                break;
            case 'M':
                bool out_messages = true;
                break;
            case 'F':
                bool out_fl = true;
                break;
            case 'I':
                bool out_intensity = true;
                break;
            case 'R':
                bool out_ros=true;
                break;
            case 'C':
                bool out_crown_consumption=true;
                break;
            case 'S':
                bool out_surf_consumption=true;
                break;
            case 'g':
                bool input_ignitions = true;
                break;
            case 'c':
                bool allow_cros = true;
                break;
            case 'n':
                int dnsims = optarg;
                break;
            case 'm':
                args_ptr->Simulator = optarg;
                break;
            case 's':
                int dseed = optarg;
                break;
            case 't':
                int dnthreads = optarg;
                break;
            case 'h':
                display_help();
                return 0; // Exit successfully after displaying help
            case '?':
                // Handle unknown options or missing arguments
                std::cerr << "Unknown option or missing argument\n";
                return 1; // Exit with an error code
            default:
                // Handle other cases
                std::cerr << "Unexpected case\n";
                return 1; // Exit with an error code
        }
    }

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
	args_ptr->Ignitions = input_ignitions;
	args_ptr->OutputGrids = out_grids; 
	args_ptr->FinalGrid = out_finalgrid;
	args_ptr->PromTuned = prom_tuned;
	args_ptr->Stats = out_stats;   
	args_ptr->BBOTuning = bbo_tuning;
	args_ptr->AllowCROS = allow_cros;	

    cout << endl << "it works" << endl;
    return 0;
}