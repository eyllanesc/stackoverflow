var current = undefined;
var port = null;
tryConnectagain();

function tryConnectagain() {
    port = chrome.runtime.connectNative('org.eyllanesc.qt_host');
    port.onMessage.addListener(onReceived);
    port.onDisconnect.addListener(onDisconnect);
}

function onReceived(argument) {
    console.log("response", argument);
}

function onDisconnect() {
    port = null;
    console.log("last error: ", chrome.runtime.lastError.message);
    setTimeout(tryConnectagain, 1000);
}

function sendMessageToNativeApp(message) {
    console.log("send:",message);
    if (port != null) port.postMessage({
        message: message
    });
}

function newUrl(u) {
    if (u != undefined && !u.includes(current) && !u.includes("chrome-extension://") && u.includes('.')) {
        var u = new URL(u);
        var domain = u.hostname.replace("www.", "");
        if (domain != current) {
            current = domain;
            sendMessageToNativeApp(current);
            console.log(current);
        }
    } else if (current != "NotURL") {
        current = "NotURL";
        sendMessageToNativeApp(current);
        console.log(current);
    }
}

// Here I'm trying to intercept all URL change situations

chrome.tabs.onActivated.addListener(function(activeInfo) {
    chrome.tabs.get(activeInfo.tabId, function(tab) {
        if (tab.active && tab.highlighted) newUrl(tab.url);
    });
});