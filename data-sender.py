import serial
import json
import urllib2

s = None
def setup():
        print('Start setup')
        global s
        s = serial.Serial('/dev/ttyS0', 57600)
def loop():
        print('looping')
        data = json.loads(s.readline())
        print(data)
        url = ('https://api.thingspeak.com/update?api_key=CQS552MLOQ7ZM0Q5&field1='
        + str(data['volt1']) +'&field2=' + str(data['temp']) +'&field3=10')
        print(urllib2.urlopen(url).read())
if __name__ == '__main__':
        print('Staring program')
        setup()
        while True:
                loop()
