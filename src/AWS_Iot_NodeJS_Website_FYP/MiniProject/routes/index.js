const express = require("express")
const router = express.Router()
const passport = require('passport')
var mongoose = require('mongoose')
var async = require('async')
var fs = require('fs')
var awsIot = require('aws-iot-device-sdk');
var userModel = require('../models/users')
var Account = require('../models/account');
const dotenv = require('dotenv');
dotenv.config();

var testTopic = "", prevMessage = ""; // mqtt message strings
var published = "", prevPublished = "", publicTopic = "";

var mongDB = process.env.MONGOOSE;
mongoose.connect(mongDB, { useNewUrlParser: true, useUnifiedTopology: true });

//Get the default connection
var db = mongoose.connection;

var device = awsIot.device({
  keyPath: "The users's private.pem.key",
  certPath: "The users'scertificate.pem.crt",
  caPath: "The users's AmazonRootCA1.pem",
  clientId: "your client id ",
  host: "your host entry point"
});


device
  .on('connect', function() {
    console.log('connect');
    console.log('Subscribing to all topics ');
    device.subscribe('humid');
    device.subscribe('door');
    device.subscribe('window');
    device.subscribe('smoke');
    device.subscribe('lights');
    device.subscribe('lights/bedroom');
    device.subscribe('lights/livingroom');
    device.subscribe('motion');
    //testing connection to IOT Core by sending interger values to the Broker
    //before topics publish there topics
    //runs once
      device.publish('humid', JSON.stringify({ test_data: "1 - humid"}));
      device.publish('door', JSON.stringify({ test_data: "2 - door"}));
      device.publish('window', JSON.stringify({ test_data: "3 - window"}));
      device.publish('smoke', JSON.stringify({ test_data: "4 -  smoke"}));
      device.publish('lights', JSON.stringify({ test_data: "5 - lights"}));
      device.publish('lights/bedroom', JSON.stringify({ test_data: "6 - lights\bedroom"}));
      device.publish('lights/livingroom', JSON.stringify({ test_data: "7 - lights\livingroom"}));
      device.publish('motion', JSON.stringify({ test_data: "8 - motion"}));

  });


  device
      .on('message', function(topic, payload) {
          console.log('MQTT message: ', topic, payload.toString());
          testTopic = payload.toString();
      });



//Bind connection to error event (to get notification of connection errors)
db.on('error', console.error.bind(console, 'MongoDB connection error:'));
/* Once the database connection has succeeded, the code in db.once is executed. */
db.once("open", function(callback){
    console.log("Connection to database succeeded.");
});

// var topic = "test/testTopic"; //de
// var pub = "test/testTopic1";
// var host = "a12ez8atbtwwyu-ats.iot.us-east-1.amazonaws.com";



router.get('/', checkAuthenticated, (req, res) => {
    res.render('index1.hbs', {name: req.user.name})
})

router.post('/getMessage', checkAuthenticated, (req, res) => {
    console.log("Message:" + testTopic)
    if (testTopic !== prevMessage && testTopic !== "") {
        prevMessage = testTopic;
        console.log("Sent new message" + testTopic);
        res.send("" + testTopic);
    } else {
        console.log("No new message");
        //res.send("" + message);
    }
})


router.post('/getMessage1', checkAuthenticated, (req, res) => {
    console.log("Message:" + testTopic)
    if (testTopic !== prevMessage && testTopic !== "") {
        prevMessage = testTopic;
        console.log("Sent new message" + testTopic);
        res.send("" + testTopic);
    } else {
        console.log("No new message");
        //res.send("" + message);
    }
})

router.post('/getPublished', checkAuthenticated, (req, res) => {
    console.log("Published:" + published);
    if (published !== prevPublished && published !== "") {
        prevPublished = published;
        console.log("Sent published message" + published);
        res.send("" + "Topic: " + publicTopic + "<br>Message: " + published); // semd the topic and the message
    } else {
        console.log("No new message sent");
    }
})

///////////////////////////////////////////////////////////////////////////////
//
//           ***** ROUTES FOR THE DIFFERENT ELEMENT TO THE HOUSE*********
//
// @param: /led/on - route to publish interger value to led topic  to to turn on led
// @param: /led/off - route to publish interger value to led topic  to to turn off led
// @param: /Door/open - route to publish interger value to door topic   to open door
// @param: /Door/closed - route to publish interger value to door topic   to close door
// @param: /window/open - route to publish interger value to door topic   to open window
// @param: /wndow/closed - route to publish interger value to door topic   to close window
//
//////////////////////////////////////////////////////////////////////////////
//led
router.post('/led/on', (req, res) => {
    console.log("inside led on router post")
    device.publish('lights', JSON.stringify({ test_data:600 }));
      res.render('index1.hbs',{name: req.user.name, status: "LED is on"})
})

router.post('/led/off', (req, res) => {
    console.log("inside led off router post")
    device.publish('lights', JSON.stringify({ test_data:500 }));
      res.render('index1.hbs',{name: req.user.name, status: "LED is off"})
})

//door
router.post('/Door/open', (req, res) => {
    console.log("inside door open router post")
    device.publish('door', JSON.stringify({ test_data:400 }));
      res.render('index1.hbs',{name: req.user.name, status: "Door is open"})
})

router.post('/Door/closed', (req, res) => {
    console.log("inside door closed router post")
    device.publish('door', JSON.stringify({ test_data:300 }));
    res.render('index1.hbs',{name: req.user.name, status: "Door is closed"})
})

//window
router.post('/window/open', (req, res) => {
    console.log("inside window open router post")
    device.publish('window', JSON.stringify({ test_data:200 }));
      res.render('index1.hbs',{name: req.user.name, status: "Window is open"})
})

router.post('/window/closed', (req, res) => {
    console.log("inside window closed router post")
    device.publish('window', JSON.stringify({ test_data:100}));
        res.render('index1.hbs',{name: req.user.name, status: "Window is closed"})
})


router.get('/home', checkAuthenticated, (req, res) => {
    res.render('index1.hbs',{name: req.user.name})
})

router.get('/login', checkNotAuthenticated, (req, res) => {
    res.render('login3.hbs')
})

router.post('/login', checkNotAuthenticated, passport.authenticate('local', {
    successRedirect: '/home',
    failureRedirect: '/login',
    failureFlash: true
}))

router.delete('/logout', (req, res) => {
    req.logOut()
    console.log("deleted session, logged out")
    res.redirect('/login')
})


function checkAuthenticated(req, res, next) {
    if (req.isAuthenticated()) {
        return next()
    }
    res.redirect('/login')
}

function checkNotAuthenticated(req, res, next) {
    if (req.isAuthenticated()) {
        return res.redirect('/')
    }
    next()
}

function userUpdate(array, name, email, password) {
    userDetail = {
        array: array,
        name: name,
        email: email,
        password: password,

    }
    var user = new userModel(userDetail);
    user.save(function (err) {
        if (err) {
            cb(err, null)
            return
        }
        console.log('New user: ' + user);
        users.push(user)
        cb(null, user)
    }  );
}

function createUser(cb) {
    async.parallel([
        function(callback) {
            userUpdate(["null", "null"], "Test Name 1", "test@test.ie", "password",
                "root", "myFormObject.key", "myFormObject.cert", callback)
        },
        function(callback) {
            userUpdate(["null2", "null2"], "Test Name 2", "test2@test.ie", "password2",
                "root2", "myFormObject.key2", "myFormObject.cert2", callback)
        }
    ])
}

function databaseTest(){
        async.series([
            createUser
        ],
// Optional callback
        function(err, results) {
            if (err) {
                console.log('FINAL ERR: '+err);
            }
            else {
                console.log('users: ' + users);
            }
            // All done, disconnect from database
            mongoose.connection.close();
        });
}


module.exports = router;
