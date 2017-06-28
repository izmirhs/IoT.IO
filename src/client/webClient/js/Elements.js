function VIEW_doConnectionSuccessOperations()
{
    denoteConnectionSuccess();
    showDevices();
}

function VIEW_doConnectionLostOperations()
{
    denoteConnectionLost();
    hideDevices();
}

function VIEW_validateAndPerformSwitches(_resultData)
{
    if (_resultData.toString() != "" && _resultData.toString() != "undefined")
    {
        _resultData.forEach(function(item, i){
            /* Device IDs are not starting from 0, so increment by 1. */
            VIEW_doSwitchPerformed(i + 1, item);
        });
    }
}

function VIEW_validateAndPerformSensors(_resultData)
{
    if (_resultData.toString() != "" && _resultData.toString() != "undefined")
    {
        _resultData.forEach(function(item, i){
            /* Device IDs are not starting from 0, so increment by 1. */
            VIEW_doShowSensorData(i + 1, item);
        });
    }
}

function VIEW_doSwitchPerformed(_id, _data)
{
    if(_data.toString() == "1")
    {
        VIEW_enableSwitch(_id);
    }
    else if(_data.toString() == "0")
    {
        VIEW_disableSwitch(_id);
    }
    else
    {
        console.log("Incorrect status assignment!");
    }
}

function VIEW_doShowSensorData(_id, _data)
{
    VIEW_doShowTempSensorData(_id, _data);
}

function VIEW_doShowTempSensorData(_id, _data)
{
    $("#TempSensorRow" + _id).removeClass("hidden");
    $("#TempSensorData" + _id).text(_data + " \xB0C");
}

function VIEW_disableSwitch(_id)
{
    $("#basicSwitch" + _id).removeClass("btn-success");
    $("#basicSwitch" + _id).find('span').addClass("glyphicon-off");
    $("#basicSwitch" + _id).addClass("btn-danger");
    $("#basicSwitch" + _id).find('span').removeClass("glyphicon-flash");
}

function VIEW_enableSwitch(_id)
{
    $("#basicSwitch" + _id).removeClass("btn-danger");
    $("#basicSwitch" + _id).find('span').removeClass("glyphicon-off");
    $("#basicSwitch" + _id).addClass("btn-success");
    $("#basicSwitch" + _id).find('span').addClass("glyphicon-flash");
}

function VIEW_fillWIFISTAList(parsedList)
{
    $('#searchStationResultDropDown').find("li").detach();
    var menuItemNo = $('#searchStationResultDropDown').find("li").length;
    for (i = 0; i < parsedList.length; i++)
    {
        if(parsedList[i])
        {
            $('#searchStationResultDropDown').append($("<li onClick='$(\"#stassid\").val($(this).text())';><a href='#'>" + parsedList[i] + "</a></li>"));
        }
    }
}

function VIEW_showCurrentConfiguration(_ssid, _pass, _ip)
{
    $("#currentConfigurationScreenSSIDSpan").html(_ssid);
    $("#currentConfigurationScreenPASSSpan").html(_pass);
    $("#currentConfigurationScreenIPSpan").html(_ip);
    $("#setupConfigurationScreen").addClass("hidden");
    $("#currentConfigurationScreenX").removeClass("hidden");
}

function VIEW_showSetupConfiguration()
{
    $("#setupConfigurationScreen").removeClass("hidden");
    $("#currentConfigurationScreenX").addClass("hidden");
}

function denoteConnectionSuccess(_fromInit)
{
    document.getElementById("connectionStatDiv").innerHTML = " Connected.";
    $('#connectionStatDiv').removeClass("text-danger");
    $('#connectionStatDiv').removeClass("text-warning");
    $('#connectionStatDiv').addClass("text-success");
    $('#connectionStatDiv').removeClass("glyphicon-ban-circle");
    $('#connectionStatDiv').removeClass("glyphicon-signal");
    $('#connectionStatDiv').addClass("glyphicon-flash");
    $("#statDiv").text("Connection established.");
}

function denoteConnectionLost()
{
    $("#statDiv").text("Ensure that your device get connected or perform setup!");
    document.getElementById("connectionStatDiv").innerHTML = " Disconnected!";
    $('#connectionStatDiv').addClass("text-danger");
    $('#connectionStatDiv').removeClass("text-success");
    $('#connectionStatDiv').removeClass("text-warning");
    $('#connectionStatDiv').addClass("glyphicon-ban-circle");
    $('#connectionStatDiv').removeClass("glyphicon-flash");
    $('#connectionStatDiv').removeClass("glyphicon-signal");
}

function VIEW_doDeviceAccessibleInAPMode()
{
    $("#statDiv").text("Ready to set up.");
    document.getElementById("connectionStatDiv").innerHTML = " Ready!";
    $('#connectionStatDiv').addClass("text-warning");
    $('#connectionStatDiv').removeClass("text-danger");
    $('#connectionStatDiv').addClass("glyphicon-signal");
    $('#connectionStatDiv').removeClass("glyphicon-ban-circle");
}

function VIEW_doDeviceNotAccessibleInAPMode()
{
    $("#statDiv").text("Please perform setup operation.");
}

function VIEW_doDeviceIDNotApplicableInAPMode()
{
    $("#statDiv").text("Inappropriate device!");
}

function VIEW_doWaitForCloudConnection()
{
    $("#statDiv").text("Connecting to the cloud. Ensure that you have internet connection!");
}

function VIEW_doWaitForDeviceConnection()
{
    $("#statDiv").text("Connected to cloud. Ensure that your device has plugged!");
}

function VIEW_doWaitAfterSetupRequest()
{
    $("#statDiv").text("Device is configuring, please wait...");
}

function VIEW_denoteCannotEstablishCloudConn()
{
    $("#statDiv").text("Not able to reach to cloud! Check your netwotk.");
    denoteConnectionLost();
}

function showDevices()
{
    $('#DeviceListOfGPIOs').removeClass("hidden");
    $('#DeviceListToBeMonitored').removeClass("hidden");
    $('#DeviceListOfTimers').removeClass("hidden");
}

function hideDevices()
{
    $('#DeviceListOfGPIOs').addClass("hidden");
    $('#DeviceListToBeMonitored').addClass("hidden");
    $('#DeviceListOfTimers').addClass("hidden");
}

function refreshPage()
{
    location.reload(true);
}

