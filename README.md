# boatr-soc
The receiver/sender for Linkit Smart 7688 Duo. Running on node/open-wrt.

- Receives data from the micro controller through the serial port, routes it to thingspeak


## 1. Install
```
npm install
```

## 2.List available serial ports
```
node src/app.js 
```

## 3. Connect to serial port 
```
node src/app.js /dev/cu.usbmodem1411
```
