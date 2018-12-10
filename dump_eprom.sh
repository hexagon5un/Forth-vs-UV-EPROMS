filename=dump_`now`.txt
echo Running Folie for setup, no logging
echo "include h" | folie -p /dev/ttyUSB0 
echo Logging to $filename
echo Now set for logging: type dump-all
folie -p /dev/ttyUSB0 -c $filename
head -n -1 $filename | tail -n +2 > foo
mv foo $filename
./changes.sh

