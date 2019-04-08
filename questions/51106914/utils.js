window.onload = function() {
  new QWebChannel(
      qt.webChannelTransport,
      function(channel) { window.mainwindow = channel.objects.mainwindow; });

  var m = {};

  start_(L, 'L');
  start_(WE, 'WE');

  function start_(API, suffix) {
    var mapDiv = 'map' + suffix;
    var map = API.map(mapDiv, {
      center : [ 51.505, -0.09 ],
      zoom : 4,
      dragging : true,
      scrollWheelZoom : true,
      proxyHost : 'http://srtm.webglearth.com/cgi-bin/corsproxy.fcgi?url='
    });
    m[suffix] = map;

    // Add baselayer
    API.tileLayer('http://{s}.tile.openstreetmap.org/{z}/{x}/{y}.png',
                  {attribution : '© OpenStreetMap contributors'})
        .addTo(map);

    // Add TileJSON overlay
    var json = {
      "profile" : "mercator",
      "name" : "Grand Canyon USGS",
      "format" : "png",
      "bounds" : [ 15.976953506469728, 45.813157465613884 ],
      "minzoom" : 10,
      "version" : "1.0.0",
      "maxzoom" : 16,
      "center" : [ 15.976953506469728, 45.813157465613884, 16 ],
      "type" : "overlay",
      "description" : "",
      "basename" : "grandcanyon",
      "tilejson" : "2.0.0",
      "sheme" : "xyz",
      "tiles" : [ "http://tileserver.maptiler.com/grandcanyon/{z}/{x}/{y}.png" ]
    };
    if (API.tileLayerJSON) {
      var overlay2 = API.tileLayerJSON(json, map);
    } else {
      // If not able to display the overlay, at least move to the same location
      map.setView([ json.center[1], json.center[0] ], json.center[2]);
    }

    // Print coordinates of the mouse
    map.on('click', function(e) {
      document.getElementById('coords').innerHTML =
          e.latlng.lat + ', ' + e.latlng.lng;
      mainwindow.pointClicked(e.latlng.lat, e.latlng.lng);
    });
  }

  // Synchronize view
  m['L'].on('click', function(e) {
    var center = m['L'].getCenter();
    var zoom = m['L'].getZoom();
    m['WE'].setView([ center['lat'], center['lng'] ], zoom);
  });
}