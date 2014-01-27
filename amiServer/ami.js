//Required libraries
var osc = require('./lib/osc.js'),
  util = require('util'),
  events = require('events'),
  connect = require('connect'),
  io = require('socket.io');

var eventEmitter = new events.EventEmitter();

//OSC Server
var client = new osc.Client('127.0.0.1', 9999);
var oscServer = new osc.Server(8080, '0.0.0.0');

client.send('/nodejsStarted', 2000);

var app = connect()
    .use(connect.static('html'))
    .use(function (req,res) {
      res.end("Error!! AMI is not alive!!");
    })
    .listen(8080);
var appIOsocket = io.listen(app);

appIOsocket.on('connection', function (socket) {
  appIOsocket.sockets.emit('ami-message', {message: 'connection established with node http server'});

  client.send('/nodejs', 'nodeConnected');

  socket.on('ami-webclient-order', function(data){
    client.send('/ami/webClient/order', data.message);
  });

  eventEmitter.on('oscEvent', function (msg) {
    if (msg[2][0] == "AMI/master/broadcast/status") {
      socket.emit("ami-message", {message: "status: "+msg[2][1]});
    } else {
      socket.emit("ami-message", {message: msg[2]});
    }
    
  });

}); 

oscServer.on("message", function (msg, rinfo) {
    eventEmitter.emit('oscEvent', msg);
});