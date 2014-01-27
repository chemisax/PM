document.ontouchmove = function(event){
    event.preventDefault();
}

$(document).ready(function () {
	var socket = io.connect('http://192.168.1.103:8080');
	
	socket.on('ami-message', function (data) {
  		$('#dataout').prepend(data.message+"<br>");  
	});

	$('#play').on("click", function () {
     	socket.emit('ami-webclient-order', { message: 'play' });
  	});
  	$('#stop').on("click", function () {
     	socket.emit('ami-webclient-order', { message: 'stop' });
  	});
  	$('#status').on("click", function () {
     	socket.emit('ami-webclient-order', { message: 'status' });
  	});
  	$('#chbg').on("click", function () {
     	socket.emit('ami-webclient-order', { message: 'chbg' });
  	});
  	$('#chclr').on("click", function () {
     	socket.emit('ami-webclient-order', { message: 'chclr' });
  	});
});