# coding: utf-8
__version__ = "2.0"
__author__ = "Cristobal Pais"
__authors__ = ["Cristobal Pais", "David Palacios", "Fernando Badilla"]

import os
import subprocess
import sys
from argparse import ArgumentParser
from pathlib import Path
from platform import machine as platform_machine
from platform import system as platform_system

# from fire2a.managedata import GenDataFile
import DataGeneratorC as DataGenerator


def parser():
    parser = ArgumentParser()
    # Folders
    parser.add_argument(
        "--input-instance-folder",
        help="The path to the folder contains all the files for the simulation",
        dest="InFolder",
        type=str,
        default=None,
    )
    parser.add_argument(
        "--output-folder",
        help="The path to the folder for simulation output files",
        dest="OutFolder",
        type=str,
        default=None,
    )
    # Integers
    parser.add_argument(
        "--sim-years",
        help="Number of years per simulation (default 1)",
        dest="sim_years",
        type=int,
        default=1,
    )
    parser.add_argument("--nsims", help="Total number of simulations (replications)", dest="nsims", type=int, default=1)
    parser.add_argument("--seed", help="Seed for random numbers (default is 123)", dest="seed", type=int, default=123)
    parser.add_argument(
        "--nweathers",
        help="Max index of weather files to sample for the random version (inside the Weathers Folder)",
        dest="nweathers",
        type=int,
        nargs="?",
    )
    parser.add_argument(
        "--nthreads", help="Number of threads to run the simulation", dest="nthreads", type=int, default=1
    )
    parser.add_argument(
        "--max-fire-periods",
        help="Maximum fire periods per year (default 1000)",
        dest="max_fire_periods",
        type=int,
        default=1000,
    )
    parser.add_argument("--fmc", help="foliar moisture content for every fuel)", dest="fmc", type=int, default=100)
    parser.add_argument("--scenario", help="surface moisture content scenario)", dest="scenario", type=int, default=3)
    parser.add_argument(
        "--IgnitionRad",
        help="Adjacents degree for defining an ignition area (around ignition point)",
        dest="IgRadius",
        type=int,
        default=0,
    )
    parser.add_argument(
        "--gridsStep", help="Grids are generated every n time steps", dest="gridsStep", type=int, default=60
    )
    parser.add_argument(
        "--gridsFreq", help="Grids are generated every n episodes/sims", dest="gridsFreq", type=int, default=-1
    )
    # Heuristic
    parser.add_argument(
        "--heuristic",
        help="Heuristic version to run (-1 default no heuristic, 0 all)",
        dest="heuristic",
        type=int,
        default=-1,
    )
    parser.add_argument(
        "--MessagesPath",
        help="Path with the .txt messages generated for simulators",
        dest="messages_path",
        type=str,
        default=None,
    )
    parser.add_argument(
        "--GASelection",
        help="Use the genetic algorithm instead of greedy selection when calling the heuristic",
        dest="GASelection",
        default=False,
        action="store_true",
    )
    parser.add_argument(
        "--FirebreakCells",
        help="File with initial firebreak cells (csv with year, number of cells: e.g 1,1,2,3,4,10)",
        dest="HCells",
        type=str,
        default=None,
    )
    parser.add_argument(
        "--msgheur", help="Path to messages needed for Heuristics", dest="msgHeur", type=str, default=""
    )
    parser.add_argument("--applyPlan", help="Path to Heuristic/Harvesting plan", dest="planPath", type=str, default="")
    parser.add_argument(
        "--DFraction", help="Demand fraction w.r.t. total forest available", dest="TFraction", type=float, default=1.0
    )
    parser.add_argument(
        "--GPTree",
        help="Use the Global Propagation tree for calculating the VaR and performing the heuristic plan",
        dest="GPTree",
        default=False,
        action="store_true",
    )
    parser.add_argument(
        "--customValue", help="Path to Heuristic/Harvesting custom value file", dest="valueFile", type=str, default=None
    )
    parser.add_argument(
        "--noEvaluation",
        help="Generate the treatment plans without evaluating them",
        dest="noEvaluation",
        default=False,
        action="store_true",
    )
    # Genetic params
    parser.add_argument(
        "--ngen", help="Number of generations for genetic algorithm", dest="ngen", type=int, default=500
    )
    parser.add_argument("--npop", help="Population for genetic algorithm", dest="npop", type=int, default=100)
    parser.add_argument("--tsize", help="Tournament size", dest="tSize", type=int, default=3)
    parser.add_argument("--cxpb", help="Crossover prob.", dest="cxpb", type=float, default=0.8)
    parser.add_argument("--mutpb", help="Mutation prob.", dest="mutpb", type=float, default=0.2)
    parser.add_argument("--indpb", help="Individual prob.", dest="indpb", type=float, default=0.5)
    # Booleans
    parser.add_argument(
        "--weather",
        help="The 'type' of weather: constant, distribution, random, rows (default rows)",
        dest="WeatherOpt",
        type=str,
        default="rows",
    )
    parser.add_argument(
        "--sim",
        help="Simulator version: currently S (Scott & Burgan), K (Kitral) and C (Canada)",
        dest="Simulator",
        type=str,
        default="S",
    )
    parser.add_argument(
        "--spreadPlots", help="Generate spread plots", dest="spreadPlots", default=False, action="store_true"
    )
    parser.add_argument(
        "--final-grid", help="GGenerate final grid", dest="finalGrid", default=False, action="store_true"
    )
    parser.add_argument(
        "--verbose", help="Output all the simulation log", dest="verbose", default=False, action="store_true"
    )
    parser.add_argument(
        "--ignitions",
        help="Activates the predefined ignition points when using the folder execution",
        dest="ignitions",
        default=False,
        action="store_true",
    )
    parser.add_argument("--grids", help="Generate grids", dest="grids", default=False, action="store_true")
    parser.add_argument(
        "--simPlots", help="generate simulation/replication plots", dest="plots", default=False, action="store_true"
    )
    parser.add_argument(
        "--allPlots",
        help="generate spread and simulation/replication plots",
        dest="allPlots",
        default=False,
        action="store_true",
    )
    parser.add_argument(
        "--combine",
        help="Combine fire evolution diagrams with the forest background",
        dest="combine",
        default=False,
        action="store_true",
    )
    parser.add_argument(
        "--no-output", help="Activates no-output mode ", dest="no_output", default=False, action="store_true"
    )
    parser.add_argument(
        "--gen-data",
        help="Generates the Data.csv file before the simulation",
        dest="input_gendata",
        default=False,
        action="store_true",
    )
    parser.add_argument(
        "--output-messages",
        help="Generates a file with messages per cell, hit period, and hit ROS",
        dest="OutMessages",
        default=False,
        action="store_true",
    )
    parser.add_argument(
        "--out-fl", help="Generates ASCII files with Flame Length", dest="OutFl", default=False, action="store_true"
    )
    parser.add_argument(
        "--out-intensity",
        help="Generates ASCII files with Byram Intensity",
        dest="OutIntensity",
        default=False,
        action="store_true",
    )
    parser.add_argument(
        "--out-ros", help="Generates ASCII files with hit ROS", dest="OutRos", default=False, action="store_true"
    )
    parser.add_argument(
        "--out-crown",
        help="Generates ASCII files with Boolean for Crown Fire",
        dest="OutCrown",
        default=False,
        action="store_true",
    )
    parser.add_argument(
        "--out-cfb",
        help="Generates ASCII files with Crown Fire Fuel Consumption",
        dest="OutCrownConsumption",
        default=False,
        action="store_true",
    )
    parser.add_argument(
        "--out-sfb",
        help="Generates ASCII files with Surface Fire Fuel Consumption (only canadian fire behavior)",
        dest="OutSurfConsumption",
        default=False,
        action="store_true",
    )
    parser.add_argument(
        "--Prometheus-tuned",
        help="Activates the predefined tuning parameters based on Prometheus",
        dest="PromTuning",
        default=False,
        action="store_true",
    )
    parser.add_argument(
        "--trajectories",
        help="Save fire trajectories FI and FS for MSS",
        dest="input_trajectories",
        default=False,
        action="store_true",
    )
    parser.add_argument(
        "--stats", help="Output statistics from the simulations", dest="stats", default=False, action="store_true"
    )
    parser.add_argument(
        "--geotiffs",
        help="Generate .tif files for georeferencing inputs and outputs",
        dest="Geotiffs",
        default=False,
        action="store_true",
    )
    parser.add_argument(
        "--correctedStats",
        help="Normalize the number of grids outputs for hourly stats",
        dest="tCorrected",
        default=False,
        action="store_true",
    )
    parser.add_argument(
        "--onlyProcessing",
        help="Read a previous simulation OutFolder and process it (Cell2Fire simulation is not called)",
        dest="onlyProcessing",
        default=False,
        action="store_true",
    )
    parser.add_argument(
        "--bbo", help="Use factors in BBOFuels.csv file", dest="BBO", default=False, action="store_true"
    )
    parser.add_argument("--cros", help="Allow Crown Fire", dest="cros", default=False, action="store_true")
    parser.add_argument(
        "--fdemand", help="Finer demand/treatment fraction", dest="fdemand", default=False, action="store_true"
    )
    parser.add_argument(
        "--pdfOutputs", help="Generate pdf versions of all plots", dest="pdfOutputs", default=False, action="store_true"
    )
    # Floats
    parser.add_argument(
        "--Fire-Period-Length",
        help="Fire Period length in minutes (needed for ROS computations). Default 1.0",
        dest="input_PeriodLen",
        type=float,
        default=1.0,
    )
    parser.add_argument(
        "--Weather-Period-Length",
        help="Weather Period length in minutes (needed weather update). Default 60",
        dest="weather_period_len",
        type=float,
        default=60,
    )
    parser.add_argument(
        "--ROS-Threshold",
        help="A fire will not start or continue to burn in a cell if the head ros\
                             is not above this value (m/min) default 0.1.",
        dest="ROS_Threshold",
        type=float,
        default=0.1,
    )
    parser.add_argument(
        "--HFI-Threshold",
        help="A fire will not start or continue to burn in a cell if the HFI is \
                              not above this value (Kw/m) default is 10.",
        dest="HFI_Threshold",
        type=float,
        default=0.1,
    )
    parser.add_argument(
        "--ROS-CV",
        help="Coefficient of Variation for normal random ROS (e.g. 0.13), \
                              but default is 0 (deteriministic)",
        dest="ROS_CV",
        type=float,
        default=0.0,
    )
    parser.add_argument("--HFactor", help="Adjustement factor: HROS", dest="HFactor", type=float, default=1.0)
    parser.add_argument("--FFactor", help="Adjustement factor: FROS", dest="FFactor", type=float, default=1.0)
    parser.add_argument("--BFactor", help="Adjustement factor: BROS", dest="BFactor", type=float, default=1.0)
    parser.add_argument("--EFactor", help="Adjustement ellipse factor", dest="EFactor", type=float, default=1.0)
    parser.add_argument(
        "--BurningLen",
        help="Burning length period (periods a cell is burning)",
        dest="BurningLen",
        type=float,
        default=-1.0,
    )
    parser.add_argument("--ROS10Factor", help="FM10 Crown Fire factor", dest="ROS10Factor", type=float, default=3.34)
    parser.add_argument("--CCFFactor", help="CCF Crown Fire factor", dest="CCFFactor", type=float, default=0.0)
    parser.add_argument("--CBDFactor", help="CBD Crown Fire factor", dest="CBDFactor", type=float, default=0.0)
    return parser


def generateDataC(args):
    dataName = os.path.join(args.InFolder, "Data.csv")
    if os.path.isfile(dataName) is False:
        print("Generating Data.csv File...", flush=True)
        # GenDataFile(args.InFolder, args.Simulator)
        DataGenerator.GenDataFile(args.InFolder, args.Simulator)


def get_ext() -> str:
    """Get the extension for the executable file based on the platform system and machine"""
    ext = ""
    if platform_system() == "Windows":
        ext = ".exe"
    else:
        ext = f".{platform_system()}.{platform_machine()}"

    if ext not in [".exe", ".Linux.x86_64", ".Darwin.arm64", ".Darwin.x86_64"]:
        print(f"Untested platform:", ext, file=sys.stderr)
    if ext == ".Darwin.arm64":
        print(f"Build not automated, may be using old binary: {ext}", ext, file=sys.stderr)

    return ext


def run(args):
    # Parse args for calling C++ via subprocess

    execArray = [
        str(Path("Cell2Fire" + get_ext()).absolute()),
        "--input-instance-folder",
        args.InFolder,
        "--output-folder",
        args.OutFolder if (args.OutFolder is not None) else "",
        "--ignitions" if (args.ignitions) else "",
        "--sim",
        args.Simulator,
        "--sim-years",
        str(args.sim_years),
        "--nsims",
        str(args.nsims),
        "--nthreads",
        str(args.nthreads),
        "--grids" if (args.grids) else "",
        "--final-grid" if (args.finalGrid) else "",
        "--Fire-Period-Length",
        str(args.input_PeriodLen),
        "--output-messages" if (args.OutMessages) else "",
        "--out-fl" if (args.OutFl) else "",
        "--out-intensity" if (args.OutIntensity) else "",
        "--out-ros" if (args.OutRos) else "",
        "--out-crown" if (args.OutCrown) else "",
        "--out-cfb" if (args.OutCrownConsumption) else "",
        "--out-sfb" if (args.OutSurfConsumption) else "",
        "--weather",
        args.WeatherOpt,
        "--nweathers" if args.nweathers is not None else "",
        str(args.nweathers) if args.nweathers is not None else "",
        "--ROS-CV",
        str(args.ROS_CV),
        "--IgnitionRad",
        str(args.IgRadius),
        "--seed",
        str(int(args.seed)),
        "--ROS-Threshold",
        str(args.ROS_Threshold),
        "--HFI-Threshold",
        str(args.HFI_Threshold),
        "--bbo" if (args.BBO) else "",
        "--FirebreakCells",
        args.HCells if (args.HCells is not None) else "",
        "--cros" if (args.cros) else "",
        "--ROS10Factor",
        str(args.ROS10Factor),
        "--CCFFactor",
        str(args.CCFFactor),
        "--CBDFactor",
        str(args.CBDFactor),
        "--HFactor",
        str(args.HFactor),
        "--FFactor",
        str(args.FFactor),
        "--BFactor",
        str(args.BFactor),
        "--EFactor",
        str(args.EFactor),
    ]
    print("C2Fcmd:", " ".join(execArray))

    # Output log
    if args.OutFolder is not None:
        if os.path.isdir(args.OutFolder) is False:
            os.makedirs(args.OutFolder)
        LogName = os.path.join(args.OutFolder, "LogFile.txt")
    else:
        LogName = os.path.join(args.InFolder, "LogFile.txt")

    # Perform the call
    # TODO :
    #   - doesn't differentiate between stoud & err
    #   - doesn't return 1 or 0 on fail success
    # enhance with queues https://stackoverflow.com/questions/2804543/read-subprocess-stdout-line-by-line
    print("Calling Cell2Fire simulator...", flush=True)

    with open(LogName, "w") as output:
        proc = subprocess.Popen(execArray, stdout=subprocess.PIPE, stderr=subprocess.STDOUT, universal_newlines=True)

        while True:
            line = proc.stdout.readline()
            if not line and proc.poll() is not None:
                break

            print(line, end="")  # , flush=False (default) fixes line by line jamming
            output.write(line)
            output.flush()

        proc.wait()

    # with open(LogName, "w") as output:
    #     proc = subprocess.Popen(execArray, stdout=output)
    #     proc.communicate()
    # proc.wait()

    # Perform the call
    # print("Calling Cell2Fire simulator...", flush=True)
    # with open(LogName, "w") as output:
    #     completed_process = subprocess.run(execArray, stdout=output)

    # if completed_process.returncode != 0:
    #     print("Cell2Fire simulator failed.", completed_process.stderr, flush=True)
    #     sys.exit(1)

    print("Cell2Fire simulator finished.", flush=True)


def main(argv=None):
    if argv is None:
        argv = sys.argv[1:]
    # Parse inputs (args)
    args = parser().parse_args(argv)
    # print("args:", args)

    # Check if we need to generate DataC.csv
    # Now it is generated on DataGenerator.cpp
    #generateDataC(args)

    # C++ init and run
    run(args)


if __name__ == "__main__":
    sys.exit(main())
