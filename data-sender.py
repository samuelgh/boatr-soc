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
        url = ('https://data.sparkfun.com/input/LQ9yDE9Ym0FAbYYGLYLV?private_key=A1qY6eqX92Sg8zzlvzv2&temp='
        + str(data['volt1']) +'&volt=' + str(data['temp']))
        print(urllib2.urlopen(url).read())
if __name__ == '__main__':
        print('Staring program')
        setup()
        while True:
                loop()
