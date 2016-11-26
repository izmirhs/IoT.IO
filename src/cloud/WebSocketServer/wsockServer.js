/* TODO migrate to https://github.com/websockets/ws */
var ws   = require("nodejs-websocket");
var util = require('util');

var wsPort = 7890;
var activeWSDeviceConnHandles = [];
var activeWSUserClientConnHandles = [];
var connectedWSUsers = 0;

var connectionHandles = [];

console.log("WebServer begins.");

var WSServer = ws.createServer(function (conn) {
	console.log("Connection to path : " + conn.path);
	var handle = {path : conn.path, device : null, userclient : null};
	connectionHandles.push(handle);
    conn.on("text", function (msg) {
        console.log("Received -> "+ msg);
        try 
        {
            var msgParsed = JSON.parse(msg.toString());
        }
        catch (e)
        {
            console.log("Not a JSON!");
            return;
        }
        var msgParsed = JSON.parse(msg.toString());
		var currentHandle = storedHandleItem(conn.path);
		
		if(currentHandle != null)
		{
			if (msgParsed.origin == "device")
		    {
		        
		    }
		    else if (msgParsed.origin == "userclient")
		    {
		        
		    }
		}
		else
		{
			console.log("Handle is null!");
		}
		

        
        /*var connHandle = null;
        if (msgParsed.origin == "device")
        {
            connHandle = activeWSUserClientConnHandles[msgParsed.deviceId];
        }
        else if (msgParsed.origin == "userclient")
        {
            connHandle = activeWSDeviceConnHandles[msgParsed.deviceId];
        }
        
        if(connHandle != null)
        {
            if(connHandle.readyState == conn.OPEN)
            {
                connHandle.sendText(msg);
            }
            else
            {
                console.log("Connection status on " + msgParsed.deviceId + " is : " +  connHandle.readyState);
            }
        }
        else
        {
            console.log("Not a valid WS handle.");
        }*/
    });
    
    conn.on("close", function (code, reason) {
        connectedWSUsers --;
        console.log("Connection closed. Code : " + code + ", reason : " + reason);
    });
    
    conn.on("error", function (err) {
        console.log("Error on connection : " + err);
    });
    
    connectedWSUsers ++;
}).listen(wsPort);

WSServer.on("close", function () {
    console.log("Server was closed and all connections have been killed.");
});

WSServer.on("error", function (errObj) {
    console.log("Error on WebServer!");
});

function storedHandleItem(path)
{
	var itemObj = null;
    connectionHandles.forEach(function (obj) {
        if (obj.path == path)
		{
			itemObj = obj;
		}
    });

	return itemObj;
}


