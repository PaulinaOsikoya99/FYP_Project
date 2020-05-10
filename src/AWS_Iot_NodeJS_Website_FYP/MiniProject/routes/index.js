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

//Bind connection to error event (to get notification of connection errors)
db.on('error', console.error.bind(console, 'MongoDB connection error:'));
/* Once the database connection has succeeded, the code in db.once is executed. */
db.once("open", function(callback){
    console.log("Connection to database succeeded.");
});

// var topic = "test/testTopic"; //de
// var pub = "test/testTopic1";
// var host = "a12ez8atbtwwyu-ats.iot.us-east-1.amazonaws.com";
var device1 = awsIot.device;

router.get('/', checkAuthenticated, (req, res) => {
    res.render('index1', {name: req.user.name})
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

router.get('/passport', checkAuthenticated, (req, res) => {
    res.render('passportConfig',{name: req.user.name});
})

router.get('/home', checkAuthenticated, (req, res) => {
    res.render('index1',{name: req.user.name })
})

var device = awsIot.device({
  keyPath: "certs/the_users-private.pem.key",
  certPath: "certs/the_users-certificate.pem.crt",
  caPath: "certs/AmazonRootCA1.pem",
  clientId: "your client id",
  host: "your host endpoint details"
});

device
  .on('connect', function() {
    console.log('connect');

    device.subscribe('humid');
    device.publish('humid', JSON.stringify({ test_data: 1}));
  });

device.publish('humid', JSON.stringify({ test_data: 23}));

device
  .on('message', function(topic, payload) {
    console.log('MQTT topic that arrived: ', topic, payload.toString());
    testTopic = payload.toString();
})



  router.post('/led/on', function(req, res){

          console.log('Written True to pin');
          res.render('index', {title: "Paulina", status: "Led is On"});
          console.log('sent mqtt value from led on');
          device.publish('humid',JSON.stringify({ test_data: 500}));

  });

  router.post('/led/off', function(req, res){

        console.log('Written False to pin');
        res.render('index',{title: "Paulina", status: "Led is Off"});
        console.log('sent mqtt value from led off');
        device.publish('humid', JSON.stringify({ test_data: 409}));
  });


    router.post('/Door/open', function(req, res){

            console.log('Written True to pin');
            res.render('index', {title: "Paulina", status1: "Door is open"});
            console.log('sent mqtt value from door open');
            device.publish('humid',JSON.stringify({ test_data: 540}));

    });

    router.post('/Door/closed', function(req, res){

          console.log('Written False to pin');
          res.render('index',{title: "Paulina", status1: "Door closed"});
          console.log('sent mqtt value from door closed');
          device.publish('humid', JSON.stringify({ test_data: 419}));
    });

    router.post('/window/open', function(req, res){

            console.log('Written True to pin');
            res.render('index', {title: "Paulina", status2: "window is open"});
            console.log('sent mqtt value from window open');
            device.publish('humid',JSON.stringify({ test_data: 540}));

    });

    router.post('/window/closed', function(req, res){

          console.log('Written False to pin');
          res.render('index',{title: "Paulina", status2: "window closed"});
          console.log('sent mqtt value from window closed');
          device.publish('humid', JSON.stringify({ test_data: 419}));
    });

    router.post('/home1', function(req, res){

          console.log('Written False to pin');
          res.render('index');

    });



var testTopic = "";

router.post('/getMessage', (req, res) => {
    console.log("Message:" + testTopic);

        res.send("" + testTopic);
})



router.post('/home', (req, res) => {

    console.log("inside this loop");
    device.publish('humid',  JSON.stringify({ test_data: 12}));
      console.log("inside this loop");

   })


    //databaseTest();
    res.render('index1', {name: req.user.name});
})

router.get('/login', checkNotAuthenticated, (req, res) => {
    res.render('login3')
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

router.post('/logout', (req, res) => {
    req.logOut()
    console.log("post deleted session, logged out")
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

function userUpdate(array, name, email, password, rootCA, privateCert, cert, cb) {
    userDetail = {
        array: array,
        name: name,
        email: email,
        password: password,
        rootCA: rootCA,
        privateCert: privateCert,
        cert: cert
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

function getFilesizeInBytes(filename) {
    var stats = fs.statSync(filename)
    var fileSizeInBytes = stats["size"]
    return fileSizeInBytes
}


module.exports = router;
