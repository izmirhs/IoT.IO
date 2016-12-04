var webSocket = null;
var webSocketInterval = null;

function SOCK_Connect()
{   
    webSocketClearInterval();
    webSocket = new WebSocket(CLOUD_ADDRESS);

    webSocket.onopen = function(evt) {
        console.log("Websock was connected to cloud.");
        setStatus("CONN_OK");
        SOCK_MessageInit();
        VIEW_doWaitForDeviceConnection();
    };
    webSocket.onclose = function(evt) {
        console.log("WS Disconnect!!");
        setStatus("CONN_LOST");
        VIEW_doConnectionLostOperations();
    };
    webSocket.onmessage = function(evt) {
        processCommand(evt.data);
    };
    webSocket.onerror = function(evt) {
        console.log("WS ERROR!! " + evt.data);
        webSocketSetInterval();
    };
    
    return webSocket;
}

function SOCK_MessageInit()
{
    var sendData = {
        type: WS_INIT,
        origin: SOURCE_USER,
        deviceId: localStorage.getItem('Device')
    };

    sockCommand(sendData);
}

function SOCK_Bridge()
{
    var sendData = {
        type: WS_BRIDGE,
        origin: SOURCE_USER,
        deviceId: localStorage.getItem('Device')
    };
    sockCommand(sendData);
}

function SOCK_Status()
{
    var sendData = {
        type: WS_STATUS,
        origin: SOURCE_USER,
        deviceId: localStorage.getItem('Device')
    };
    sockCommand(sendData);
}

function SOCK_Switch(_json_data)
{
    sockCommand(_json_data);
}

function SOCK_ResetNetwork(_json_data)
{
    sockCommand(_json_data);
}

function SOCK_Close()
{
    if (webSocket) 
    {
        webSocket.close();
        webSocket = null;
    }
}

function webSocketClearInterval()
{
    if(webSocketInterval)
    {
        clearInterval(webSocketInterval);
        webSocketInterval = null;
    }   
}

function webSocketSetInterval()
{
    webSocketClearInterval();
    webSocketInterval = setInterval(SOCK_Connect, REFRESH_INTERVAL);
}

function sockCommand(json_to_send)
{
    if(webSocket.readyState == 1)
    {
        webSocket.send(JSON.stringify(json_to_send));
    }
    console.log("Sock state is : " + webSocket.readyState + ". Buffered : " + webSocket.bufferedAmount);
}

function processCommand(received)
{
    var receivedObj = JSON.parse(received);
    if (receivedObj.succeed == SUCCESS)
    {
        dispatchCommand(receivedObj);
    }
    else
    {
        console.log("processResponse is NOT succeeded.");
    }
}

function dispatchCommand(result)
{
    var date = new Date();
    console.log(date.getHours() +":"+ date.getMinutes() + ":" + date.getSeconds() + " > " + JSON.stringify(result));
    if(result.type == WS_INIT)
    {
        SOCK_Bridge();
    }
    else if (result.type == WS_BRIDGE)
    {
        VIEW_doConnectionSuccessOperations();
        if(result.ssid != "" && result.ssid != UNDEFINED)
        {
            console.log("STA has been set. Hide Setup!");
            localStorage.setItem('SSID', result.ssid);
            localStorage.setItem('PASS', result.pass);
            localStorage.setItem('IP', result.ip);
            VIEW_showCurrentConfiguration(result.ssid, result.pass, result.ip);
            SOCK_Status();
        }
        else
        {
            console.log("STA not set yet. Fallback to Setup!");
            VIEW_showSetupConfiguration();
        }
    }
    else if(result.type == WS_STATUS)
    {
        if(result.pins != "" && result.pins != UNDEFINED)
        {
            VIEW_validateAndPerformSwitches(result.pins);
        }
    }
    else if (result.type == WS_SWITCH)
    {
        if(result.data.toString() != "" && result.data != UNDEFINED)
        {
            VIEW_doSwitchPerformed(result.id, result.data.toString());
        }
    }
    else if (result.type == WS_SENSOR)
    {
        if(result.data.toString() != "" && result.data != UNDEFINED)
        {
            console.log("Temp gathered : " + result.data);
            VIEW_doShowSensorData(result.data);
        }
    }
    else if(result.type == WS_PING)
    {
        /* Perform ping/pong to catch disconnection. */
    }
    else
    {
        alert("not able to dispatch the response." + result);
    }
}
