function sendCommand(command,x,y) {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
  if (xhttp.readyState === 4)  { 
	document.getElementById('cmd_status').innerHTML = xhttp.responseText;
  }
};
  if(typeof x == "undefined" || typeof y == "undefined"){
	document.getElementById('cmd_status').innerHTML = 'Sending command to cobot';
	xhttp.open("GET", "command?command="+command, true);
  }else{
	if(isNaN(parseInt(x)) || isNaN(parseInt(y))){
		document.getElementById('cmd_status').innerHTML = 'X/Y position have to be a number';
	}else{
		document.getElementById('cmd_status').innerHTML = 'Sending command to cobot';
		xhttp.open("GET", "command?"+"x_pos="+x+"&y_pos="+y, true);
	}
  }
  xhttp.send();
}

function updateStatus(cobot){
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
	if (xhttp.readyState === 4)  { 
		document.getElementById('stats_master').innerHTML = xhttp.responseText;
	}
  };
  xhttp.open("GET", "status?"+"cobot="+cobot, true);
  xhttp.send();
}

window.onload = function(){
	setInterval(updateStatus('master'),100);
	setInterval(updateStatus('slave'),100);
}