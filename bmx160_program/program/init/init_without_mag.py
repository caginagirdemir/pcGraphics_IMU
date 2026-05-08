import smbus
import time

bus = smbus.SMBus(1)

address = 0x68

bus.write_byte_data(address, 0x7E, 0xB6) #RESET VALUE
time.sleep(0.015)


bus.write_byte_data(address, 0x7E, 0x11) #ACCELERATION SET NORMAL MODE
time.sleep(0.05)
bus.write_byte_data(address, 0x7E, 0x15) #GYROSCOPE SET NORMAL MODE
time.sleep(0.1)
# bus.write_byte_data(address, 0x7E, 0x19) #MAGNOTEMETER SET NORMAL MODE
# time.sleep(0.1)


#ACCELERATION FREQUENCY SETTING
bus.write_byte_data(address, 0x40, 0x2B)
time.sleep(0.1)
rv = bus.read_byte_data(address, 0x40)
rv = rv & 0x0F
if(rv == 0xC): print("Acceleration Frequency: 1600Hz")
elif(rv == 0xB): print("Acceleration Frequency: 800Hz")
elif(rv == 0xA): print("Acceleration Frequency: 400Hz")
elif(rv == 0x8): print("Acceleration Frequency: 200Hz")
else: print("Acceleration Frequency: lower than 200Hz")


#ACCELERATION RANGE SETTING
bus.write_byte_data(address, 0x41, 0x05)
time.sleep(0.1)
rv = bus.read_byte_data(address, 0x41)
rv = rv & 0x0F
if(rv == 0x3): print("Acceleration Range: 2G")
elif(rv == 0x5): print("Acceleration Range: 4G")
elif(rv == 0x8): print("Acceleration Range: 8G")
elif(rv == 0xC): print("Acceleration Range: 16Hz")
else: print("Acceleration Range: 2G (Misused)")


#GYROSCOPE FREQUENCY SETTING
bus.write_byte_data(address, 0x42, 0x2B)
time.sleep(0.1)
rv = bus.read_byte_data(address, 0x42)
rv = rv & 0x0F
if(rv == 0xD): print("Gyroscope Frequency: 3200Hz")
elif(rv == 0xC): print("Gyroscope Frequency: 1600Hz")
elif(rv == 0xB): print("Gyroscope Frequency: 800Hz")
elif(rv == 0xA): print("Gyroscope Frequency: 400Hz")
elif(rv == 0x8): print("Gyroscope Frequency: 200Hz")
else: print("Gyroscope Frequency: lower than 200Hz")


#GYROSCOPE RANGE SETTING
bus.write_byte_data(address, 0x43, 0x03)
time.sleep(0.1)
rv = bus.read_byte_data(address, 0x43)
rv = rv & 0x07
if(rv == 0x0): print("Gyroscope Range: 2000deg/s")
elif(rv == 0x1): print("Gyroscope Range: 1000deg/s")
elif(rv == 0x2): print("Gyroscope Range: 500deg/s")
elif(rv == 0x3): print("Gyroscope Range: 250deg/s")
elif(rv == 0x4): print("Gyroscope Range: 125deg/s")
else: print("Reserved Value (Misused)")


# bus.write_byte_data(address, 0x4C, 0x80) #MAGNETOMETER IF SET SETUP MODE
# time.sleep(0.05)
# #MAGNETOMETER SET SLEEP MODE FOR SETTING (INDIRECT WRITE)
# bus.write_byte_data(address, 0x4F, 0x01) #VALUE 0x80 FOR SOFT RESET
# bus.write_byte_data(address, 0x4E, 0x4B) #REGISTER ADDRESS

#0x01 -> LOW POWER PRESET NORMAL MODE(10Hz) FORCED MODE(>300Hz) RMS Noise x/y/z 1.0/1.0/1.4
#0x04 -> REGULAR PRESET NORMAL MODE(10Hz) FORCED MODE(100Hz) RMS Noise x/y/z 0.6/0.6/0.6
#0x07 -> ENHANCED REGULAR PRESET NORMAL MODE(10Hz) FORCED MODE(60Hz) RMS Noise x/y/z 0.5/0.5/0.5
#0x18 -> HIGH ACCURACY PRESET !!!ATTENTION!!! BOARD NEEDS CARRY AT LEAST 4.9mA CURRENT

# #REPRESENT XY (INDIRECT WRITE)
# bus.write_byte_data(address, 0x4F, 0x04) #VALUE
# bus.write_byte_data(address, 0x4E, 0x51) #REGISTER ADDRESS

# # #REPRESENT Z (INDIRECT WRITE)
# bus.write_byte_data(address, 0x4F, 0x0E) #VALUE
# bus.write_byte_data(address, 0x4E, 0x52) #REGISTER ADDRESS

# #MAGNETOMETER ODR (INDIRECT WRITE)
# bus.write_byte_data(address, 0x4F, 0x02) #VALUE (FORCE MODE) 0x00 FOR NORMAL MODE
# bus.write_byte_data(address, 0x4E, 0x4C) #REGISTER ADDRESS

#MAGNETOMETER IF SET DATA MODE (YOU SHOULD SET THESE VALUES FOR DATA MODE)
# bus.write_byte_data(address, 0x4F, 0x02)
# bus.write_byte_data(address, 0x4E, 0x4C)
# bus.write_byte_data(address, 0x4D, 0x42)

# #MAGNETOMETER ODR (DIRECT WRITE FOR BMX160)
# bus.write_byte_data(address, 0x44, 0x08) #SET 100 HZ
# bus.write_byte_data(address, 0x4C, 0x00) #TRIGGER OFFSET

time.sleep(1)

rv = bus.read_byte_data(address, 0x02)
rv = rv & 0x1F
if(rv == 0):
    print("No IMU Error")
else:
    print("%X" % rv)
