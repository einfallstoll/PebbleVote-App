Pebble.addEventListener("ready", function(e) {
    console.log("JavaScript app ready and running!");
    
    if (!localStorage.uuid) {
        localStorage.uuid = generateUUID();
        console.log("Generated UUID:", localStorage.uuid);
    } else {
        console.log("Existing UUID:", localStorage.uuid);
    }
});

var events = {
    either: function(data) {
        console.log("Get random questions");
        
        var req = new XMLHttpRequest(); 
        req.open("POST", "http://pebblevote.jit.su/either");
        req.setRequestHeader("Content-Type", "application/json; charset=utf-8");
        req.onreadystatechange = function() {
            if (req.readyState != 4) return;
            console.log("Status:", req.status);
            console.log("Response:", req.responseText);
            if (req.status >= 200 && req.status < 400) {
                Pebble.sendAppMessage({
                    status: "success",
                    type: "answered"
                }, function() {
                    console.log("Data transmitted");
                }, function(e) {
                    sendError(JSON.stringify(e));
                });
            } else {
                sendError("HTTP Status: " + req.status);
            }
        };
        req.send(JSON.stringify({
            user: localStorage.uuid,
            question: data.data
        }));
    },
    or: function(data) {
        console.log("Get random questions");
        
        var req = new XMLHttpRequest(); 
        req.open("POST", "http://pebblevote.jit.su/or");
        req.setRequestHeader("Content-Type", "application/json; charset=utf-8");
        req.onreadystatechange = function() {
            if (req.readyState != 4) return;
            console.log("Status:", req.status);
            console.log("Response:", req.responseText);
            if (req.status >= 200 && req.status < 400) {
                Pebble.sendAppMessage({
                    status: "success",
                    type: "answered"
                }, function() {
                    console.log("Data transmitted");
                }, function(e) {
                    sendError(JSON.stringify(e));
                });
            } else {
                sendError("HTTP Status: " + req.status);
            }
        };
        req.send(JSON.stringify({
            user: localStorage.uuid,
            question: data.data
        }));
    },
    skip: function(data) {
        console.log("Get random questions");
        
        var req = new XMLHttpRequest(); 
        req.open("POST", "http://pebblevote.jit.su/skip");
        req.setRequestHeader("Content-Type", "application/json; charset=utf-8");
        req.onreadystatechange = function() {
            if (req.readyState != 4) return;
            console.log("Status:", req.status);
            console.log("Response:", req.responseText);
            if (req.status >= 200 && req.status < 400) {
                Pebble.sendAppMessage({
                    status: "success",
                    type: "answered"
                }, function() {
                    console.log("Data transmitted");
                }, function(e) {
                    sendError(JSON.stringify(e));
                });
            } else {
                sendError("HTTP Status: " + req.status);
            }
        };
        req.send(JSON.stringify({
            user: localStorage.uuid,
            question: data.data
        }));
    },
    report: function(data) {
        console.log("Get random questions");
        
        var req = new XMLHttpRequest(); 
        req.open("POST", "http://pebblevote.jit.su/report");
        req.setRequestHeader("Content-Type", "application/json; charset=utf-8");
        req.onreadystatechange = function() {
            if (req.readyState != 4) return;
            console.log("Status:", req.status);
            console.log("Response:", req.responseText);
            if (req.status >= 200 && req.status < 400) {
                Pebble.sendAppMessage({
                    status: "success",
                    type: "answered"
                }, function() {
                    console.log("Data transmitted");
                }, function(e) {
                    sendError(JSON.stringify(e));
                });
            } else {
                sendError("HTTP Status: " + req.status);
            }
        };
        req.send(JSON.stringify({
            user: localStorage.uuid,
            question: data.data
        }));
    },
    random: function(data) {
        console.log("Get random questions");
        
        var req = new XMLHttpRequest(); 
        req.open("POST", "http://pebblevote.jit.su/random");
        req.setRequestHeader("Content-Type", "application/json; charset=utf-8");
        req.onreadystatechange = function() {
            if (req.readyState != 4) return;
            console.log("Status:", req.status);
            console.log("Response:", req.responseText);
            if (req.status >= 200 && req.status < 400) {
                try {
                    var data = JSON.parse(req.responseText);
                    var message = {
                        status: "success",
                        type: "random",
                        count: 0
                    };
                    var lastMessage = {};
                    var i = 0;
                    do {
                        lastMessage = message;
                        
                        if (data.length === 0) break;
                        
                        message.count = i + 1;
                        var index = 10 + i * 10;
                        message[++index] = data[i]._id;
                        message[++index] = data[i].either;
                        message[++index] = data[i].or;
                    } while(i < data.length && JSON.stringify(message).length < data.inbox);
                    
                    console.log(JSON.stringify(lastMessage));
                    
                    if (data.length > 0 && lastMessage.count === 0) {
                        sendError("Low memory");
                    } else {
                        Pebble.sendAppMessage(lastMessage, function() {
                            console.log("Data transmitted");
                        }, function(e) {
                            sendError(JSON.stringify(e));
                        });
                    }
                }
                catch(e) {
                    sendError(e.message);
                }
            } else {
                sendError("HTTP Status: " + req.status);
            }
        };
        req.send(JSON.stringify({
            user: localStorage.uuid,
            language: localStorage.language || 'en'
        }));
    }
};

Pebble.addEventListener("appmessage", function(e) {
    if (!e.payload.type) {
        sendError("Type is not defined!");
    } else if (!events[e.payload.type]) {
        sendError("Event does not exist:", e.payload.type);
    } else {
        console.log("Message for type:", e.payload.type);
        events[e.payload.type](e.payload);
    }
});

function generateUUID() {
    return 'xxxxxxxx-xxxx-4xxx-yxxx-xxxxxxxxxxxx'.replace(/[xy]/g, function(c) {
        var r = Math.random() * 16 | 0, v = c == 'x' ? r : (r&0x3 | 0x8);
        return v.toString(16);
    });
}

function sendError(message) {
    console.log("Send Error:", message);
    Pebble.sendAppMessage({
        status: "error",
        message: message
    }, function() {
        console.log("Error transmitted");
    }, function(e) {
        console.log("Error while transmitting error. ERRORCEPTION!");
    });
}
