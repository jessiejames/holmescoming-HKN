#script listens to serial port and writes contents into a file
##############
## requires pySerial to be installed 

import serial

serial_port = '/dev/cu.usbmodem1411'
baud_rate = 9600; #In arduino, Serial.begin(baud_rate)
write_to_file_path = "output.txt";

ser = serial.Serial(serial_port, baud_rate)
k = 5
while True:   
    newFile = open(write_to_file_path, "a")
    line = ser.readline()
    line = line.decode("utf-8")
    print(line)
    newFile.write(line)
    newFile.close()
    k = k-1
