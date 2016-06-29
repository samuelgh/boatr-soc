import serial
import json
import urllib2

s = None
def setup():
	global s
	s = serial.Serial("/dev/ttyS0", 57600)
def loop():
    data = json.loads(s.readline())
    print(data)
    url = 'https://api.thingspeak.com/update?api_key=CQS552MLOQ7ZM0Q5&field1='
    + data['volt1'] +'&field2=' + data['temp'] +'&field3=10'

if __name__ == '__main__':
	setup()
	while True:
		loop()
