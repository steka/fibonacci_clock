Pebble.addEventListener('ready', function(e) {
//  console.log('JavaScript app ready and running!');
});

Pebble.addEventListener('showConfiguration', function(e) {
  Pebble.openURL('https://steka.github.io/fibonacci_clock/config.htm');
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
