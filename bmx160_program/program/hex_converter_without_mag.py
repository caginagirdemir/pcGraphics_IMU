import math
import time
from datetime import datetime

print("Enter source file name:")
filename_source=input()

print("Enter file name:")
filename=input()



#scale factor header olacak
#not dusulecek kayit sirasi olarak zaman, acc, gyro, rhall, mag


def get_time(buffer):

    sensor_t = float(0)

    if(buffer[0] &1  != 0):
        sensor_t += 0.039
    if(buffer[0] &2 != 0):
        sensor_t += 0.078
    if(buffer[0] &4 != 0):
        sensor_t += 0.156
    if(buffer[0] &8 != 0):
        sensor_t += 0.3125
    if(buffer[0] &16 != 0):
        sensor_t += 0.625
    if(buffer[0] &32 != 0):
        sensor_t += 1.25
    if(buffer[0] &64 != 0):
        sensor_t += 2.5
    if(buffer[0] &128 != 0):
        sensor_t += 5

    if (buffer[1] &1 != 0):
        sensor_t += 10
    if (buffer[1] &2 != 0):
        sensor_t += 20
    if (buffer[1] &4 != 0):
        sensor_t += 40
    if (buffer[1] &8 != 0):
        sensor_t += 80
    if (buffer[1] &16 != 0):
        sensor_t += 160
    if (buffer[1] &32 != 0):
        sensor_t += 320
    if (buffer[1] &64 != 0):
        sensor_t += 640
    if (buffer[1] &128 != 0):
        sensor_t += 1280

    if (buffer[2] &1 != 0):
        sensor_t += 2560
    if (buffer[2] &2 != 0):
        sensor_t += 5120
    if (buffer[2] &4 != 0):
        sensor_t += 10240
    if (buffer[2] &8 != 0):
        sensor_t += 20480
    if (buffer[2] &16 != 0):
        sensor_t += 40960
    if (buffer[2] &32 != 0):
        sensor_t += 8192128
    if (buffer[2] &64 != 0):
        sensor_t += 163840
    if (buffer[2] &128 != 0):
        sensor_t += 327680
    return(sensor_t)

f_2 = open(filename_source,"r")
f_3 = open(filename+ '.txt',"w")

sensor_time = []
sensor_data= []
lines=f_2.readlines()
i=1
divided = lines[0].split(',')


if  (divided[0] == "03"):
    scalefactor_A = float(16384)
elif(divided[0] == "05"):
    scalefactor_A = float(8192)
else:
    exit("Accelerometer Range Value Mistaken or Out of Range")


if  (divided[1].rstrip() == "04"):
    scalefactor_G = float(262.4)
elif(divided[1].rstrip() == "03"):
    scalefactor_G = float(131.2)
elif(divided[1].rstrip() == "02"):
    scalefactor_G = float(65.6)
else:
    exit("Gyroscope Range Value Mistaken or Out of Range")

 

for line in lines[1:]:   
    divided= line.split(',')
    sensor_time.append(int(divided[2], 16))
    sensor_time.append(int(divided[1], 16))
    sensor_time.append(int(divided[0], 16))

    lbyte = int(divided[14], 16)
    hbyte = int(divided[13], 16)
    hbyte = hbyte - 256 if hbyte > 127 else hbyte
    val = ((hbyte << 8) + lbyte)
    gx = ("%.2f" % float(int(val) / scalefactor_G))

    lbyte = int(divided[12], 16)
    hbyte = int(divided[11], 16)
    hbyte = hbyte - 256 if hbyte > 127 else hbyte
    val = ((hbyte << 8) + lbyte)
    gy = ("%.2f" % float(int(val) / scalefactor_G))

    lbyte = int(divided[10], 16)
    hbyte = int(divided[9], 16)
    hbyte = hbyte - 256 if hbyte > 127 else hbyte
    val = ((hbyte << 8) + lbyte)
    gz = ("%.2f" % float(int(val) / scalefactor_G))



    lbyte = int(divided[4], 16)
    hbyte = int(divided[3], 16)
    hbyte = hbyte - 256 if hbyte > 127 else hbyte
    val = ((hbyte << 8) + lbyte)
    az = ("%.2f" % float(int(val)  / scalefactor_A))

    lbyte = int(divided[6], 16)
    hbyte = int(divided[5], 16)
    hbyte = hbyte - 256 if hbyte > 127 else hbyte
    val = ((hbyte << 8) + lbyte)
    ay = ("%.2f" % float(int(val)  / scalefactor_A))

    lbyte = int(divided[8], 16)
    hbyte = int(divided[7], 16)
    hbyte = hbyte - 256 if hbyte > 127 else hbyte
    val = ((hbyte << 8) + lbyte)
    ax = ("%.2f" % float(int(val)  / scalefactor_A))

    time_val = "%.3f" %  get_time(sensor_time)
    sensor_time.clear()
    f_3.write(time_val+","+ax+","+ay+","+az+","+gx+","+gy+","+gz+"\n")
    i+=1
    if(i == len(lines)-1):
        f_2.close()
        break
f_3.close()

sensor_time.clear()
f_3 = open(filename+ '.txt',"r")
lines=f_3.readlines()
i = 0
for line in lines:   
    divided= lines[i].split(',')
    sensor_time.append(float(divided[0]))
    
    i=i+1
f_3.close()
j = 0
# leak_flag = False
# sensor_diff = []
for i in sensor_time[1:]:
    print("%.5f" % (i - sensor_time[j]))
    # sensor_diff.append(i - sensor_time[j])
    # if((i - sensor_time[j]) < 2):
    #     print("OVER SAMPLING BETWEEN %d and %d Samples" % (j,(j+1)))
    #     leak_flag = True
    # elif((i - sensor_time[j]) > 4):
    #     print("LEAK BETWEEN %d and %d Samples" % (j,(j+1)))
    #     leak_flag = True
    j+=1
#print(sum(sensor_diff) / len(sensor_diff))
# sensor_diff.clear()
# if(not leak_flag):
#     print("LEAK CHECK OK!")

time_elapsed = (sensor_time[(len(sensor_time)-1)] - sensor_time[0])
sample = len(sensor_time)
print("Time Elapsed : %.5f ms" % time_elapsed)
print("Sample : %i" % sample)
print("Calculated Freqeuncy :  %d Hz" % (int(sample) / float(time_elapsed/1000)))
