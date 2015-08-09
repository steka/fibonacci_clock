Pebble.addEventListener('ready', function(e) {
//  console.log('JavaScript app ready and running!');
});

Pebble.addEventListener('showConfiguration', function(e) {
  Pebble.openURL('https://www.googledrive.com/host/0By3m2JcE6XQ6TGU2QmVoNUdvYTA');
});

Pebble.addEventListener('webviewclosed', function(e) {
  var config_data = JSON.parse(decodeURIComponent(e.response));
//  console.log('Config window returned: ', JSON.stringify(config_data));

  Pebble.sendAppMessage(config_data, function() {
//    console.log('Sent config data to Pebble');  
  }, function() {
//    console.log('Failed to send config data!');
  });
});
