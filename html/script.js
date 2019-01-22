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

function updateStatus(cobot) {
	var xhttp = new XMLHttpRequest();
	if( cobot === "master"){
		xhttp.onreadystatechange = function() {
			if (xhttp.readyState === 4)  { 
				var xml = xhttp.responseXML;
				document.getElementById('stats_master').innerHTML=xml.getElementsByTagName("STATUS")[0].childNodes[0].nodeValue;
				document.getElementById('x_pos_master').innerHTML=xml.getElementsByTagName("X_POS")[0].childNodes[0].nodeValue;
				document.getElementById('y_pos_master').innerHTML=xml.getElementsByTagName("Y_POS")[0].childNodes[0].nodeValue;
			}
		};
	}else{
		xhttp.onreadystatechange = function() {
			if (xhttp.readyState === 4)  { 
				var xml = xhttp.responseXML;
				document.getElementById('stats_slave').innerHTML=xml.getElementsByTagName("STATUS")[0].childNodes[0].nodeValue;
				document.getElementById('x_pos_slave').innerHTML=xml.getElementsByTagName("X_POS")[0].childNodes[0].nodeValue;
				document.getElementById('y_pos_slave').innerHTML=xml.getElementsByTagName("Y_POS")[0].childNodes[0].nodeValue;
			}
		}
	}
	xhttp.open("GET", "status?"+"cobot="+cobot, true);
	xhttp.send();
}

window.onload = function() {
	setInterval(function(){updateStatus('master')},100);
	setInterval(function(){updateStatus('slave')},100);
};