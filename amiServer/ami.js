var osc = require('./lib/osc.js');
var util = require('util');
var events = require('events');
var eventEmitter = new events.EventEmitter();

var client = new osc.Client('127.0.0.1', 9999);
var oscServer = new osc.Server(9998, '0.0.0.0');

client.send('/nodejsStarted', 2000);

var app = require('http').createServer(handler)
  , io = require('socket.io').listen(app)
  , fs = require('fs')

app.listen(8080);

function handler (req, res) {
  fs.readFile(__dirname + '/index.html',
  function (err, data) {
    if (err) {
      res.writeHead(500);
      return res.end('Error loading index.html');
    }

    res.writeHead(200);
    res.end(data);
  });
}

io.sockets.on('connection', function (socket) {
  client.send('/ami/webClient/message', "new Connection");
  socket.emit('ami-message', { message: 'welcome to ami interface' });
  socket.on('ami-webclient-out', function (data) {
    client.send('/ami/webClient/message', data.message);
  });

});

oscServer.on("message", function (msg, rinfo) {
    console.log("Message:");
    console.log(msg);
    eventEmitter.emit('oscEvent');
});