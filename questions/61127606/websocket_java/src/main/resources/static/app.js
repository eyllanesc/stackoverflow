var ws;

function connect() {
	ws = new WebSocket('ws://localhost:8080/name');

	ws.onmessage = function(text) {
    var tr = document.createElement("tr");
    var td = document.createElement("td");
    td.innerText = text.data;
    tr.appendChild(td);
    document.querySelector("#greetings").appendChild(tr);
	}

  document.querySelector("#connect").setAttribute("disabled", "disabled");
  document.querySelector("#disconnect").removeAttribute("disabled");
  document.querySelector("#conversation").style.display = 'block';
  document.querySelector("#greetings").innerHTML = "";
}

function disconnect() {
    if (ws != null)
        ws.close();
      
    document.querySelector("#connect").removeAttribute("disabled");
    document.querySelector("#disconnect").setAttribute("disabled", "disabled");
    document.querySelector("#conversation").style.display = 'none';
    document.querySelector("#greetings").innerHTML = "";
}

function send() {
  var name = document.querySelector("#name");
	var data = JSON.stringify({'name': name.value});
  ws.send(data);
}
