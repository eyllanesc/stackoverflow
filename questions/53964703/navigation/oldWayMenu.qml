/*function requestToTextFile (file_name, line) {
    var request = new XMLHttpRequest()
    request.open('GET', file_name)
    request.onreadystatechange = function(event) {
        if (request.readyState == XMLHttpRequest.DONE) {
            line = request.responseText.split('\n')
        }
    }
    request.send()
}

function obroka_danych (x, y, line) {
    for (var i = 0; i < line.length; i ++) {
        if (line[i] == ";") {
            var n = i;

            for (var k = 0; k < n; k ++) {
                x += line [k];
            } //for
        }// if

        if (line[i] == "\n") {
            var m = i;

            for (var l = m; l !=  "\n"; l ++) {
                y += line[l]
            } // for
        } // if
    }
    return [x, y];
}

function process(callback) {
    if (typeof callback !== 'function') {
             callback = false;
        }

        if (callback) {
             callback();
        }
}

obrobki danych wysylam i linie, ktora dostalem i parametry do rozbicia
