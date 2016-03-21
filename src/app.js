var serialport = require('serialport');
var request = require('request');
var SerialPort = serialport.SerialPort;

var serialPorts;
// list serial ports:

if (!process.argv[2]) {
  serialport.list(function (err, ports) {
    serialPorts;
    ports.forEach(function(port) {
      console.log(port.comName);
    });
  });
} else {
  var myPort = new SerialPort(process.argv[2], {
     baudRate: 115200,
     // look for return and newline at the end of each data packet:
     parser: serialport.parsers.readline("\n")
   });
   myPort.on('open', showPortOpen);
   myPort.on('data', sendSerialData);
   myPort.on('close', showPortClose);
   myPort.on('error', showError);

   function showPortOpen() {
     console.log('port open. Data rate: ' + myPort.options.baudRate);
  }

  function sendSerialData(data) {
    console.log("data:" + data);
    var jsonData = JSON.parse(data);
    request('https://api.thingspeak.com/update?api_key=CQS552MLOQ7ZM0Q5&field1=' + data.volt1 +'&field2=' + data.temp ,
      function (error, response, body) {
        if (!error && response.statusCode == 200) {
          console.log('Sent request, got response:' + body) // Show the HTML for the Google homepage.
        }
    });
  }

  function showPortClose() {
     console.log('port closed.');
  }

  function showError(error) {
     console.log('Serial port error: ' + error);
  }
}
