var jshelper;

new QWebChannel(qt.webChannelTransport, function (channel) {
    jshelper = channel.objects.jshelper;
});


function geocodePosition(pos) {
    geocoder.geocode({
        latLng: pos
    }, function (responses) {
        if (responses && responses.length > 0) {
            updateMarkerAddress(responses[0].formatted_address);
        } else {
            updateMarkerAddress('Cannot determine address at this location.');
        }
    });
}


function updateMarkerStatus(str) {
    document.getElementById('markerStatus').innerHTML = str;
}

function updateMarkerPosition(latLng) {
    document.getElementById('info').innerHTML = [
        latLng.lat(),
        latLng.lng()
    ].join(', ');
}


function updateMarkerAddress(str) {
    document.getElementById('address').innerHTML = str;
}


var geocoder = new google.maps.Geocoder();
var map;


var goldStar = {
    path: 'M 125,5 155,90 245,90 175,145 200,230 125,180 50,230 75,145 5,90 95,90 z',
    fillColor: 'yellow',
    fillOpacity: 0.8,
    scale: 0.1,
    strokeColor: 'gold',
    strokeWeight: 1
};


function addMarker(lat, lon, city, url) {
    var newmarker = new google.maps.Marker({
        position: new google.maps.LatLng(lat, lon),
        icon: goldStar,
        map: map,
        title: city
    });
    newmarker['infowindow'] = new google.maps.InfoWindow({
        content: url
    });
    google.maps.event.addListener(newmarker, 'click', function () {
        this['infowindow'].open(map, this);
    });
}


function initialize() {
    var latLng = new google.maps.LatLng(40.767367, -111.848007);
    // create as a global variable
    map = new google.maps.Map(document.getElementById('mapCanvas'), {
        zoom: 11,
        center: latLng,
        mapTypeId: google.maps.MapTypeId.ROADMAP
    });
    var marker = new google.maps.Marker({
        position: latLng,
        title: 'Point A',
        map: map,
        draggable: true
    });

    // Update current position info.
    updateMarkerPosition(latLng);
    geocodePosition(latLng);

    // Add dragging event listeners.
    google.maps.event.addListener(marker, 'dragstart', function () {
        updateMarkerAddress('Dragging...');
    });

    google.maps.event.addListener(marker, 'drag', function () {
        updateMarkerStatus('Dragging...');
        updateMarkerPosition(marker.getPosition());
        jshelper.markerMoved(marker.position.lat(), marker.position.lng());
    });

    google.maps.event.addListener(marker, 'dragend', function () {
        updateMarkerStatus('Drag ended');
        geocodePosition(marker.getPosition());
    });

//  return latLng
}


// Onload handler to fire off the app.
google.maps.event.addDomListener(window, 'load', initialize);




