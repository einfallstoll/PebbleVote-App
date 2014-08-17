var ajax = require('ajax');
var Settings = require('settings');
var UI = require('ui');

if (!Settings.data('UUID')) {
    var uuid = UUID();
    Settings.data('UUID', uuid);
    
    console.log('New User with UUID:', uuid);
}

console.log('Settings URL:', 'http://einfallstoll.github.io/PebbleVote-App/index.html#' + encodeURIComponent(Settings.option('question') || ''));

Settings.config({
    url: 'http://einfallstoll.github.io/PebbleVote-App/index.html#' + encodeURIComponent(Settings.option('question') || '')
}, function() {
    console.log('Settings are being saved.');
});

var mainMenu = new UI.Menu({
    sections: [{
        items: [{
            title: "Vote"
        }, {
            title: "My Questions"
        }, {
            title: "My Votes"
        }]
    }]
});

var uploadQuestion = new UI.Card({
    title: 'New Question',
    body: 'Your question is being uploaded...'
});

var question = Settings.option('question');
if (question) {
    console.log('New Question:', question);
    uploadQuestion(question);
} else {
    mainMenu.show();
}

function UUID() {
    return 'xxxxxxxx-xxxx-4xxx-yxxx-xxxxxxxxxxxx'.replace(/[xy]/g, function(c) {
        var r = Math.random()*16|0, v = c == 'x' ? r : (r&0x3|0x8);
        return v.toString(16);
    });
}

function uploadQuestion(question) {
    uploadQuestion.show();
    ajax({
        url: 'http://pebblevote.jit.su/question',
        method: 'post',
        type: 'json',
        data: {
            user: Settings.data('UUID'),
            language: Settings.option('language') || 'en',
            question: question
        }
    }, function() {
        ShowSuccess('Question added', 'Your question was successfully added!', mainMenu);
    }, function() {
        ShowError(uploadQuestion);
    });
}

function ShowSuccess(title, body, next) {
    var successCard = new UI.Card({
        title: title,
        body: body
    });
    
    setTimeout(function() {
        next.show();
        successCard.hide();
    }, 1000);
}

function ShowError(retry) {
    var errorCard = new UI.Card({
        title: 'Error',
        body: 'An error occured. Press any button to try again.'
    });
    
    var retryHandler = function() {
        retry();
        errorCard.hide();
    };
    
    errorCard.on('click', 'up', retryHandler);
    errorCard.on('click', 'select', retryHandler);
    errorCard.on('click', 'down', retryHandler);
}
