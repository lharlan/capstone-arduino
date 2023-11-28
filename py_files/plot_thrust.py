import matplotlib.pyplot as plt
from datetime import datetime
import numpy as np

def showPLT(time, thrust, rThrust, currTime):

    plt.plot(time, thrust, label = 'Thrust')
    plt.plot(time, rThrust, label= 'Reverse Thrust')
    plt.xlabel('Time')
    plt.ylabel('Thrust (lbs)')
    plt.legend()
    plt.title('Thrust and Reverse Thrust over Time')
    plt.savefig(f'{currTime}_thrustplot.png')

    print(f"Image generated as {currTime}_thrustplot.png\n")

def convertFloat(strList):
    floatList = [eval(i) for i in strList]
    return(floatList)

def stripComma(lst):
    return(lst[:-1])

def trimList(thrust, rThrust, time):
    thrustLen = len(thrust)
    rThrustLen = len(rThrust)
    timeLen = len(time)

    # Put lens into list and find smallest value
    listLen = []
    listLen.append(thrustLen)
    listLen.append(rThrustLen)
    listLen.append(timeLen)
    listMin = min(listLen)

    thrustLen = thrustLen - listMin
    rThrustLen = rThrustLen - listMin
    timeLen = timeLen - listMin

    if thrustLen != 0:
        thrust = thrust[:-thrustLen]
    
    if rThrustLen != 0:
        rThrust = rThrust[:-rThrustLen]
    
    if timeLen != 0:
        time = time[:-timeLen]

    return(thrust, rThrust, time)


with open('thrust.txt', 'r') as thrustRead:
    thrustVal = thrustRead.read().rstrip()

with open('rthrust.txt', 'r') as rThrustRead:
    rThrustVal = rThrustRead.read().rstrip()

with open('time.txt', 'r') as timeRead:
    timeVal = timeRead.read().rstrip()

thrust = thrustVal.split(',')
rThrust = rThrustVal.split(',')
time = timeVal.split(',')

# Remove comma added by arduino code
thrust = stripComma(thrust)
rThrust = stripComma(rThrust)
time = stripComma(time)

# convert to float for graphing
thrust = convertFloat(thrust)
rThrust = convertFloat(rThrust)
time = convertFloat(time)

if len(thrust) == len(rThrust) == len(time):
    pass
else:
    thrust, rThrust, time = trimList(thrust, rThrust, time)

# graph and send time for filename
now = datetime.now()
current_time = now.strftime("%H_%M_%S")

showPLT(time, thrust, rThrust, current_time)