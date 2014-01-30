document.ontouchmove = function(event){
    event.preventDefault();
}

$(document).ready(function () {
	var socket = io.connect('http://192.168.1.103:8080');
	
	socket.on('ami-message', function (data) {
  		$('#log').prepend(data.message+"<br>");  
	});
	
	socket.on('ami-bpm', function (data) {
			$('#beat_rate').html(Math.floor(60/(data.message/30))+" bpm");  
	});

  	$('#status').on("click", function () {
     	socket.emit('ami-webclient-order', { message: 'status' });
  	});
  	
});