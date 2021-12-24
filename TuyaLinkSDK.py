#!/usr/bin/env python
import time
import coloredlogs
from tuyalinksdk.client import TuyaClient
from tuyalinksdk.console_qrcode import qrcode_generate
coloredlogs.install(level='DEBUG')
import sys
import serial
import time
 # Define the serial port and baud rate.
ser = serial.Serial('COM22', 115200)	#ENTER YOUR PORT

client = TuyaClient(productid='j62naag6ueueoxfb',
                    uuid='tuyaf378a02c541ece74',
                    authkey='ohxoG5glRDnaamH2c0P1q2Uq7sUot4sT')
#ENTER YOUR CORRESPONDING DETAILS

def on_connected():
    print('Connected.')

def on_qrcode(url):
    qrcode_generate(url)

def on_reset(data):
    print('Reset:', data)

def on_dps(dps):
    print('DataPoints:', dps)
    if(dps == {'101':True}):
    	print("DVD is on...")
    	time.sleep(0.1)
    	ser.write(b'1')
    	print('ON')
    elif(dps=={'101':False}):
    	print("DVD is off...")
    	time.sleep(0.1)
    	ser.write(b'0')
    	print('OFF')
    elif (dps == {'102': True}):
        time.sleep(0.1)
        ser.write(b'O')
        print('Open')
    elif (dps == {'102': False}):
        time.sleep(0.1)
        ser.write(b'C')
        print('Close')
    elif (dps == {'103': True}):
        time.sleep(0.1)
        ser.write(b'P')
        print('Play')
    elif (dps == {'103': False}):
        time.sleep(0.1)
        ser.write(b'Q')
        print('Pause')
    elif (dps == {'104': True}):
        time.sleep(0.1)
        ser.write(b'f')
    elif (dps == {'104': False}):
        time.sleep(0.1)
        ser.write(b'F')
    elif (dps == {'105': True}):
        time.sleep(0.1)
        ser.write(b'B')
    elif (dps == {'105': False}):
        time.sleep(0.1)
        ser.write(b'B')
    elif (dps == {'106': True}):
        time.sleep(0.1)
        ser.write(b'S')
    client.push_dps(dps)

client.on_connected = on_connected
client.on_qrcode = on_qrcode
client.on_reset = on_reset
client.on_dps = on_dps

client.connect()
client.loop_start()

while True:
    time.sleep(1)
