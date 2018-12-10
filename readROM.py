import serial
import time

s=serial.Serial("/dev/ttyUSB0", baudrate=115200, timeout=0)

def read_until_ok(s):
    """Dual-purpose: waits until ok. is returned, keeps the string"""
    output = ""
    while not "ok.\n" in output:
        output = output + s.read()
    output = output.strip()
    return output

print ("You should have run folie and included h already: folie -p /dev/ttyUSB0")

ts = int(time.mktime(time.localtime()))
outfile = open("dump_%d.txt")
## this is fucked.  easier to script in bash


# with open("rm1x113.BIN", "rb") as f:
#     address = 0  
#     starttime = d.datetime.now()
#     while address < 2**20:
#        ## Which endianness? The other one, naturally
#         ## data = ord(f.read(1)) + 256 * ord(f.read(1))
#         ## data = 256 * ord(f.read(1)) + ord(f.read(1))
#         if writeData:
#             s.write("%i %i program\n" % (data, address))
#         else:
#             s.write("%i read hex.\n" % (address))
#         print (read_until_ok(s))
#         address = address + 1

#     endtime = d.datetime.now()
#     elapsed = endtime - starttime
#     print "elapsed time: %i.%i seconds" % (elapsed.seconds,
#             elapsed.microseconds)



