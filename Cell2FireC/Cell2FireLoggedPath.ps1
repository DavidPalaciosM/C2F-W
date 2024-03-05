$tmpvar = ""
for ($i=0; $i -lt $args.Length; $i++) {
    # Write-Output ('arg idx ' + $i + ': ' + $args[$i])
    if ($args[$i] -eq "--output-folder") {
        $tmpvar = $args[$i+1]
        if ($tmpvar -notmatch '\\$') {
            $tmpvar += '\'
        }
        Write-Output ('Logging path: ' + $tmpvar)
        break
    }
}
.\Cell2Fire.exe $args 2>&1 | Tee-Object -FilePath ($tmpvar + 'log.txt')

