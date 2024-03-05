#!/usr/bin/bash
tmpvar=""
for arg in "$@"; do
  # echo "arg: $arg"
  if [[ "${arg}" == "--output-folder" ]]; then
    tmpvar="${@:$(($#)):1}"
    if [[ ! "${tmpvar}" =~ /$ ]]; then
      tmpvar+="/"
    fi
    break
  fi
done
echo "logging to ${tmpvar}log.txt"

ext=`python3 -c "import platform;print(f'.{platform.system()}.{platform.machine()}')"`
echo "binary extension $ext"

./Cell2Fire$ext "$@" 2>&1 | tee "${tmpvar}log.txt"
