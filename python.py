import serial
import time
import sys


port = sys.argv[1]
filename = sys.argv[2]
timestamp = sys.argv[3]

ser = serial.Serial(port, 9600, timeout=int(timestamp)+0.01)
time.sleep(5)

ser.write(bytes(timestamp))
logfile = open(filename, 'a')

while 1:
    line = ser.readline() 
    now = time.strftime("%d/%m/%Y; %H:%M:%S", time.localtime())
    a =  "%s; %s" % (now, line)
    print (a)	
    logfile.write(a)
    logfile.flush()    
logfile.close()
ser.close()