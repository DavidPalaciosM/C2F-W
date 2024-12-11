#!/bin/bash
# run simulations from model, put them in test_results, compare to target_results


rm -rf target_results
unzip -q target_results.zip

# recreate targets with tests
# cd test
# rm -rf test_results target_results target_results.zip
# execute the for loop
# mv test_results target_results
# zip -r target_results.zip target_results
# git add target_results.zip
# git commit -m "Update target results"
# git push

# add to path
PATH=../Cell2Fire:$PATH

# run
set -x # enable debug tracing
for format in asc tif; do
    for model in fbp kitral sb; do
        echo running $model-$format
        output_folder=test_results/$model-$format
        mkdir -p $output_folder
        rm -rf $output_folder/*
        if [ "$model" == "fbp" ]; then
            additional_args="--cros"
            sim_code="C"
        elif [ "$model" == "sb" ]; then
            additional_args="--scenario 1"
            sim_code="S"
        elif [ "$model" == "kitral" ]; then
            additional_args=""
            sim_code="K"
        fi
        Cell2Fire$1 --input-instance-folder model/$model-$format --output-folder $output_folder --nsims 113 --output-messages --grids --out-ros --out-intensity --sim ${sim_code} --seed 123 --ignitionsLog $additional_args > test_results/$model-$format/log.txt
        sed -i "1 s/version: .*/version: v0.0.1/" test_results/$model-$format/log.txt
    done
done
set +x # disable debug tracing

# find difference between directories and files

# define the directories to compare
dir1="test_results"
dir2="target_results"

# get the list of files in each directory
dir1_files=$(find "$dir1" -type f | sort)
dir1_num_files=$(ls -1 $dir1_files | wc -l)
# echo $dir1_files $dir1_num_files
dir2_files=$(find "$dir2" -type f | sort)
dir2_num_files=$(ls -1 $dir2_files | wc -l)
# echo $dir2_files $dir2_num_files

# check if the number of files in each directory is equal
if [ $dir1_num_files -ne $dir2_num_files ]; then
    echo "Directories are not equal due to number"
    echo "Directory ${dir1} has ${dir1_num_files} files"
    echo "Directory ${dir2} has ${dir2_num_files} files"
    exit 1
fi

# use diff to compare the files in each directory
diff_output=$(diff -rq "$dir1" "$dir2")
# echo $diff_output

# check if there is any difference
if [ -z "$diff_output" ]; then
    echo "Directories are equal"
else
    echo "Directories are not equal due to differences"
    # compare file by file if fails show the file name
    for file1 in $(find "$dir1" -type f); do
        # find file1 in dir2
        file2=$(echo $file1 | sed "s/${dir1}/${dir2}/")
        # echo "Comparing $file1 and $file2"
        diff_output=$(diff "$file1" "$file2")
        if [ -n "$diff_output" ]; then
            echo "Files are not equal, aborting... $file1"
            echo $diff_output
            exit 1
        fi
    done
    #uncomment exit below to check all differences
    #exit 1
fi

rm -rf target_results
exit 0
