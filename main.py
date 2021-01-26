from pyprnt import prnt
import wmi
import serial
import time

print('serial ' + serial.__version__)

PORT = 'COM4'
BaudRate = 9600

ARD = serial.Serial(PORT, BaudRate)
w = wmi.WMI(namespace="root\OpenHardwareMonitor")
while(True):
    sensor_infos = w.Sensor()
    hardware_infos = w.Hardware()
    hw_info = {}
    for hw in hardware_infos:
        if hw.HardwareType==u'CPU':
            hw_info['CPU'] = hw.Name
        if hw.HardwareType==u'Mainboard':
            hw_info['MB'] = hw.Name
    for sensor in sensor_infos:
        if sensor.Name==u'CPU Core #1':
            if sensor.SensorType==u'Clock':
                hw_info['Clock'] = round(sensor.Value)
        if sensor.Name==u'CPU Package':
            if sensor.SensorType==u'Temperature':
                hw_info['Temp'] = round(sensor.Value)
        if sensor.Name==u'CPU Total':
            if sensor.SensorType==u'Load':
                hw_info['Load'] = round(sensor.Value, 2)
        if sensor.Name==u'Fan #1':
            if sensor.SensorType==u'Fan':
                hw_info['Fan1'] = round(sensor.Value)
        if sensor.Name==u'Fan #2':
            if sensor.SensorType==u'Fan':
                hw_info['DDC_Pump'] = round(sensor.Value)
    #print("CPU : ",hw_info['CPU'], hw_info['Clock'], "Mhz ", hw_info['Load'], "% ", hw_info['Temp'], "'C")
    #print("MB : ", hw_info['MB'])
    #print("Fan : ", hw_info['Fan1'], "RPM")
    #print("Pump : ",hw_info['DDC_Pump'], "RPM")
    ARD.write(str.encode(hw_info['CPU']+"\n"+str(hw_info['Clock'])+"Mhz "+str(hw_info['Load'])+"% "+str(hw_info['Temp'])+"'C\n"+hw_info['MB'][9:]+"\nFan:"+str(hw_info['Fan1'])+"  Pump:"+str(hw_info['DDC_Pump'])))
    #ARD.write("Q".encode('utf-8'))
    #ARD.write(str.encode(hw_info['CPU']))
    #ARD.write(str.encode("\n"+str(hw_info['Clock'])+"Mhz "+str(hw_info['Load'])+"% "+str(hw_info['Temp'])+"'C"))
    #ARD.write(str.encode("\n"+hw_info['MB'][9:]))
    #ARD.write(str.encode("\nFan:"+str(hw_info['Fan1'])+"  Pump:"+str(hw_info['DDC_Pump'])))
    time.sleep(1)
