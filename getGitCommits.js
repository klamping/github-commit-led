var https = require('https');
var fs = require('fs');

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
        numCommits = history.map(function (dayInfo) {
          return dayInfo[1];
        })

        numCommits = numCommits.slice(0,56);

        // write commit data to file for later consumption
        fs.writeFile("./commitData", numCommits.join(','), function(err) {
            if(err) {
                console.log(err);
            } else {
                console.log("The file was saved!");
            }
        });
    });
});
request.on('error', function (e) {
    console.log(e.message);
});
request.end();
