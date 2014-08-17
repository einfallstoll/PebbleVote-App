var UI = require('ui');

var mainMenu = new UI.Menu({
    sections: [{
        items: [{
            title: "My Questions"
        }, {
            title: "Random Questions"
        }, {
            title: "Voted Questions"
        }]
    }]
});

mainMenu.show();
