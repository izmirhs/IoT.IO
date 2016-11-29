var setupAPPostHandle = null;
var searchStationPostHandle = null;
var pollDevicePostHandle = null;
var pollDeviceInterval = null;

function POST_CustomRequest(json_to_send, _hostIP)
{
    var timeoutVal = json_to_send.type == HTTP_AP_SEARCH ? SEARCH_REQ_TOUT : AP_REQ_TOUT;
    
    var req = $.ajax({
        type: "POST",
        url: "http://" + _hostIP,
        dataType: "text",
        data: JSON.stringify(json_to_send),
        success: processResponse,
        error:processError,
        timeout: timeoutVal
   });
   
   return req;
}

function POST_SearchAP()
{
    var sendData = {
        type: HTTP_AP_SEARCH
    };
    if(searchStationPostHandle)
    {
        searchStationPostHandle.abort();
    }

    searchStationPostHandle = POST_CustomRequest(sendData, AP_IP);
}

function POST_SetupAP(json_to_send)
{
    if(setupAPPostHandle)
    {
        setupAPPostHandle.abort();
    }

    setupAPPostHandle = POST_CustomRequest(json_to_send, AP_IP);
}

function POST_PollDeviceOnAPMode()
{
    var sendData = {
        type: HTTP_AP_POLL
    };
    
    if(pollDevicePostHandle)
    {
        pollDevicePostHandle.abort();
    }

    pollDevicePostHandle = POST_CustomRequest(sendData, AP_IP);
}

function POST_PollDeviceOnAPModeLoop()
{
    POST_PollDeviceOnAPMode();
    pollDeviceInterval = setInterval(POST_PollDeviceOnAPMode, TIMER_INTERVAL);
}


function POST_APDone()
{
    var sendData = {
        type: HTTP_AP_DONE
    };

    /* No need to handlize due to one shotness and reboot. */
    POST_CustomRequest(sendData, AP_IP);
}

function processError(err)
{
    console.log("processError" + JSON.stringify(err));
}

function processResponse(result)
{
    console.log(result);
    var resultObj = JSON.parse(result);
    if (resultObj.succeed == SUCCESS)
    {
        dispatchResponse(resultObj);
    }
    else
    {
        console.log("processResponse is NOT succeeded.");
    }
}

function dispatchResponse(result)
{
    if (result.type == HTTP_AP_INFO)
    {
        if(result.deviceId != null && result.deviceId != "")
        {
            console.log("Storing device ID ...");
            /* Like to have an array of devices */
            localStorage.setItem('Device', result.deviceId);
            localStorage.setItem('DeviceCount', parseInt(localStorage.getItem('DeviceCount')) + 1);
            /* Succeeded to set AP info to the device. */
            POST_APDone();
            VIEW_doWaitAfterSetupRequest();
            setTimeout(function () { location.reload(true); }, TOUT_AFTER_SETUP);
        }
        else
        {
            console.log("Not a valid device ID!!! Can't communite. Stay in Setup Mode!");
        }
    }
    else if (result.type == HTTP_AP_SEARCH)
    {
        console.log("Listing search results...");
        if(result.data != "" && result.data != "undefined")
        {
            console.log(result.data);
            VIEW_fillWIFISTAList(result.data);
        }
        else
        {
            console.log("No valid data after search.");
        }
    }
    else if (result.type == HTTP_AP_POLL)
    {
        clearInterval(pollDeviceInterval);
        VIEW_doDeviceAccessibleInAPMode();
    }
    else
    {
        alert("not able to dispatch the response." + result);
    }
}
