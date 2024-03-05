#! /bin/bash
tmpvar=""
for i in "${args[@]}"; do
  # echo "arg idx $i: ${args[$i]}"
  if [[ "${args[$i]}" == "--output-folder" ]]; then
    tmpvar="${args[++i]}"
    if [[ ! "${tmpvar}" =~ /$ ]]; then
      tmpvar+="/"
    fi
    echo "Logging path: $tmpvar"
    break
  fi
done

ext=`python3 -c "import platform;print(f'.{platform.system()}.{platform.machine()}')"`
./Cell2Fire$ext "${args[@]}" 2>&1 | tee "${tmpvar}log.txt"
