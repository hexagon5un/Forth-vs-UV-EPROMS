import serial
import os
filename = "rm1x_pattern_eeprom"

s=serial.Serial("/dev/ttyUSB0", baudrate=115200, timeout=1)
outfile = open(filename + ".txt", "w") 

def read_until_ok(s):
    """Dual-purpose: waits until ok. is returned, keeps the string"""
    output = ""
    while not "ok.\n" in output:
        output = output + s.read()
    output = output.strip()
    return output

## Double-sure chip is ready
s.write("eprom-init\n")
print (read_until_ok(s))

## Start dump
s.write("dump-all\n")
a = s.readline() # skip command line itself
while not a == '':
    a = s.readline()
    if not "ok." in a: # skip last line
        outfile.write(a)
outfile.close() 

os.system("xxd -r -p " + filename + ".txt > " + filename + ".bin")

