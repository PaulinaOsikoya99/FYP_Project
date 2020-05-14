const express = require('express')
const app = express()
const passport = require('passport')
const flash = require('express-flash')
const session = require('express-session')
const bodyParser = require('body-parser');
const bcrypt = require('bcrypt');
const cors = require('cors');
const path = require('path');
const morgan = require('morgan');
const methodOverride = require('method-override')
const fileUpload = require('express-fileupload')

const users = []

app.set('port', 8000);
app.use(fileUpload({
  createParentPath: true
}));
// view engine setup
app.engine('hbs', hbs({extname: 'hbs'}));
app.set('views', path.join(__dirname, 'views'));
app.set('view engine', 'hbs');

app.use(bodyParser.json());
app.use(bodyParser.urlencoded({ extended: false }));
app.use(express.urlencoded({ extended: false }))
app.use(cors());
app.use(flash())
app.use(morgan('dev'));
app.use(session({
  secret: "secret",
  resave: false,
  saveUninitialized: false
}))
const initializePassport = require('./passport-config')
initializePassport(
    passport,
    email => users.find(user => user.email === email),
    id => users.find(user => user.entry === id)
)
app.use(passport.initialize())
app.use(passport.session())
app.use(methodOverride('_method'))

const indexRouter = require('./routes/index')
app.use("/", indexRouter)
app.use("/login", indexRouter)
app.use("/logout", indexRouter)
app.use("/upload", indexRouter)
app.use("/getMessage", indexRouter)
app.use("/getMessage1", indexRouter)
app.use("/getPublished", indexRouter)
app.use("/passport", indexRouter)
app.use("/led/on", indexRouter)
app.use("/led/off", indexRouter)
app.use("/Door/open", indexRouter)
app.use("/Door/closed", indexRouter)
app.use("/window/open", indexRouter)
app.use("/window/closed", indexRouter)


app.use(express.static(path.join(__dirname, 'public')));

var Account = require("./models/account")

app.post('/register', checkNotAuthenticated, async (req, res) => {
  try {
    const hashedPassword = await bcrypt.hash(req.body.password, 10)
    var entry = Date.now().toString();
    await Account.create({
          id: entry,
          name: req.body.name,
          email: req.body.email,
          password: hashedPassword},
        function(err){
          if (err) {
            console.log(err);
            return;
          }
          req.flash('info', 'Successful Registration');
          res.redirect('/login')
        });
    users.push({
      entry: entry,
      name: req.body.name,
      email: req.body.email,
      password: hashedPassword
    })
  } catch {
    req.flash('info', 'Unsuccessful Registration');
    res.redirect('/login')
  }
})

function checkNotAuthenticated(req, res, next) {
  if (req.isAuthenticated()) {
    return res.redirect('/')
  }
  next()
}

app.listen(app.get('port'), function(){
  console.log(("Express server listening on port " + app.get('port')))
});

module.exports = app;
