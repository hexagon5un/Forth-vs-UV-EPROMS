import datetime as d
import serial

s=serial.Serial("/dev/ttyUSB0", baudrate=115200, timeout=0)

def read_until_ok(s):
    """Dual-purpose: waits until ok. is returned, keeps the string"""
    output = ""
    while not "ok.\n" in output:
        output = output + s.read()
    output = output.strip()
    return output

s.write("eprom-init\n")
print (read_until_ok(s))

writeData = True

with open("rm1x113.BIN", "rb") as f:
    address = 0  
    starttime = d.datetime.now()
    while address < 2**20:
       ## Which endianness?
        # data = ord(f.read(1)) + 256 * ord(f.read(1))
        data = 256 * ord(f.read(1)) + ord(f.read(1))
        if writeData:
            s.write("%i %i program\n" % (data, address))
        else:
            s.write("%i read hex.\n" % (address))
        print (read_until_ok(s))
        address = address + 1

    endtime = d.datetime.now()
    elapsed = endtime - starttime
    print "elapsed time: %i.%i seconds" % (elapsed.seconds,
            elapsed.microseconds)



