/* Networking configurations. */
var AP_IP               = "192.168.99.1";
var CLOUD_ADDRESS       = "WEBSOCK_HOST_ADDR:PORT";
/* Timeout and Intervals. */
var TIMER_INTERVAL      = 2500;
var REFRESH_INTERVAL    = 2500;
var TOUT_AFTER_SETUP    = 20000;
var TOUT_AFTER_RESET    = 2500;
var AP_REQ_TOUT         = TIMER_INTERVAL - 500;
var SEARCH_REQ_TOUT     = 8 * AP_REQ_TOUT;
/* Generic Definitions. */
var SUCCESS             = "1";
var UNDEFINED           = "undefined";
/* POST Message Types. */
var HTTP_AP_INFO        = "APInfo";
var HTTP_AP_SEARCH      = "APSearch";
var HTTP_AP_POLL        = "APPoll";
var HTTP_AP_DONE        = "APDone";
var HTTP_USR_REG        = "USERReg";
/* Socket Message Types. */
var WS_INIT             = "ws_init";
var WS_BRIDGE           = "Bridge";
var WS_STATUS           = "Status";
var WS_SWITCH           = "Switch";
var WS_FACTORY          = "Factory";
var WS_PING             = "Ping";
/* Targets and Sources of the requests. */
var SOURCE_USER         = "userclient";
var SOURCE_DEVICE       = "device"
