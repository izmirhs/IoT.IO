/* TODO migrate to https://github.com/websockets/ws */
var ws   = require("nodejs-websocket");
var util = require('util');

var wsPort = 7890;
var activeWSDeviceConnHandles = [];
var activeWSUserClientConnHandles = [];
var connectedWSUsers = 0;

console.log("WebServer begins.");

var WSServer = ws.createServer(function (conn) {
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
        if(msgParsed.type == "ws_init")
        {
            if (msgParsed.origin == "device")
            {
                if(activeWSDeviceConnHandles[msgParsed.deviceId] != null)
                {
                    /* TODO close previous unresponsive conn over device. */
                    /* TODO use path variable instead of creating enormous conn handle array. */
                    activeWSDeviceConnHandles[msgParsed.deviceId].close();
                }
                activeWSDeviceConnHandles[msgParsed.deviceId] = conn;
            }
            else if (msgParsed.origin == "userclient")
            {
                if(activeWSUserClientConnHandles[msgParsed.deviceId] != null)
                {
                    activeWSUserClientConnHandles[msgParsed.deviceId].close();
                }
                activeWSUserClientConnHandles[msgParsed.deviceId] = conn;
            }
            msgParsed.succeed = 1;
            conn.sendText(JSON.stringify(msgParsed));
        }
        else
        {
            var connHandle = null;
            /* Cross handles to bridge between device and user client. */
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
            }
        }
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


