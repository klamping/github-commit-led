var SerialPort = require("serialport").SerialPort
var serialPort = new SerialPort("/dev/ttyACM1", {
  baudrate: 9600
});

        serialPort.open(function () {
          console.log('open');
          
          serialPort.on('data', function(data) {
            console.log('data received: ' + data);
          });
});
