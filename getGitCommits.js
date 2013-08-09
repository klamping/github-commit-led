var https = require('https');
var fs = require('fs');

var SerialPort = require("serialport").SerialPort
var serialPort = new SerialPort("/dev/ttyACM0", {
  baudrate: 9600
});

var options = {
    host: 'github.com',
    path: '/users/klamping/contributions_calendar_data'
}
var request = https.request(options, function (res) {
    var data = '';
    res.on('data', function (chunk) {
        data += chunk;
    });
    res.on('end', function () {
        // convert to array so we modify it
        var history = JSON.parse(data);

        // reverse the array so that most recent commits are first
        history.reverse();

        // get only number of commits per day
        var numCommits = history.map(function (dayInfo) {
          return dayInfo[1];
        })

        // write commit data to file for later consumption
        // fs.writeFile("./commitData", numCommits.join(','), function(err) {
        //     if(err) {
        //         console.log(err);
        //     } else {
        //         console.log("The file was saved!");
        //     }
        // });

        serialPort.on("open", function () {
          console.log('open');
          serialPort.write(numCommits.join(','), function(err, results) {
            console.log('err ' + err);
            console.log('results ' + results);
          });
        });
    });
});
request.on('error', function (e) {
    console.log(e.message);
});
request.end();