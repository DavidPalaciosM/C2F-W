#!/usr/bin/bash
ext=`python3 -c "import platform;print(f'.{platform.system()}.{platform.machine()}')"`
./Cell2Fire$ext $@ 2>&1 | tee log.txt 

