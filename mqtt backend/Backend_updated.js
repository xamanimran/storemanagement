// Generate a new random MQTT client id on each page load
var MQTT_CLIENT_ID = "rfid_"+Math.floor((1 + Math.random()) * 0x10000000000).toString(16);

// Create a MQTT client instance
var MQTT_CLIENT = new Paho.MQTT.Client("192.168.10.23", Number("9001"), "/ws", MQTT_CLIENT_ID);



// client instance conneting to the MQTT broker
MQTT_CLIENT.connect(
{ 
	onSuccess: ClientConnected
}
	);





//------------------------------------TagNumber-----------------------
//Subscribing the topic
function ClientConnected() {
	console.log("onConnect");
  MQTT_CLIENT.subscribe("TagNumber");
  
}

//  received messages
function MessageArrived(message) {
  // Get the payload
  var messageBody = message.payloadString;

  // HTML element wrapping the message payload
  var messageHTML = $("<p>"+messageBody+"</p>");

  // Insert inside the div id=temp 
  $("#RFID").prepend(messageHTML);
};
// confirm that msg arrived
MQTT_CLIENT.onMessageArrived = MessageArrived;

//----------------------------------------------------------------------------
