var STATUS = "INIT_NOK";
var WEB_SRC = true;

if(WEB_SRC)
{
    initComm();
}

/* Initialize Connections. */
function initComm()
{
    console.log("Device count : " + parseInt(localStorage.getItem('DeviceCount')));
    console.log("Device : " + localStorage.getItem('Device'));
    if(localStorage.getItem('Device'))
    {
        console.log("Found stored network and device. Count : " + localStorage.getItem('DeviceCount') + " ID : " +  localStorage.getItem('Device'));
        if(!SOCK_Connect())
        {
            console.log("No connection! Use reconnecting WebSock to cover.");
            setStatus("CONN_NOK");
            VIEW_denoteCannotEstablishCloudConn();
        }
        else
        {
            console.log("Waiting to establish connection on Cloud.");
            setStatus("CONN_WAITING");
            VIEW_doWaitForCloudConnection();
        }
    }
    else
    {
        localStorage.setItem('DeviceCount', 0);
        console.log("Cannot found a stored device. Going to setup mode ..");
        setStatus("INIT_NOK");
        VIEW_doDeviceNotAccessibleInAPMode();
        POST_PollDeviceOnAPMode();
    }
}

/* WebSocket Operations. */
function basicSwitchReq(_id)
{
    var sendData = {
        type: WS_SWITCH,
        id: _id,
        origin: "userclient",
        deviceId: localStorage.getItem('Device')
    };
    SOCK_Switch(sendData);
}

function resetHomeNetworkReq()
{
    var sendData = {
        type: WS_FACTORY,
        origin: "userclient",
        deviceId: localStorage.getItem('Device')
    };
    SOCK_ResetNetwork(sendData);
    localStorage.clear();
    setStatus("INIT_NOK");
    setTimeout(function () { location.reload(true); }, TOUT_AFTER_RESET);
}

/* HTTP Post Operations. */
function setupHomeNetworkReq()
{
    var sendData = {
        type: HTTP_AP_INFO,
        ssid: $("#stassid").val(),
        pass: $("#stapwd").val(),
        origin: SOURCE_USER
   };
   
   POST_SetupAP(sendData);
}

function searchStationReq()
{
    var sendData = {
        type: HTTP_AP_SEARCH,
        origin: SOURCE_USER
    };

    POST_SearchAP(sendData);
}

function registerUserCredentials()
{
    /* TODO: Fill with user data. */
    var sendData = {
        type: HTTP_USR_REG,
        user: $("#stassid").val(),
        pass: $("#stapwd").val(),
        origin: SOURCE_USER,
    };
   
    POST_RegisterUser(sendData);
}

/* Storage variables. */
function getStatus()
{
    return STATUS;
}

function setStatus(_status)
{
    STATUS = _status;
    localStorage.setItem('status', _status);
}

