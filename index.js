const express = require('express')
const PORT = process.env.PORT || 8000
var app = express();
var fire = require('./fire')
var cors = require('cors');
var bodyParser = require('body-parser');

app.use(cors());
app.use(bodyParser.json());
app.use(bodyParser.urlencoded({ extended: false }));


app.get('/', (req, res) => {
  res.send(
    '<h1>API Express & Firebase IOT</h1>')
})


app.get('/ver', (req, res) => {
    const db = fire.firestore();
      db.settings({
        timestampsInSnapshots: true
      });
      var wholeData = []
      db.collection('Colmenas').orderBy('Fecha', 'asc').get()
      .then(snapshot => {
        snapshot.forEach(doc => {
        
          wholeData.push(doc.data())
        });
        console.log(wholeData)
        res.send(wholeData)
      })
      .catch(error => {
        console.log('Error!', error);
    })
  })








app.listen(PORT, () => {
    console.log(`escuchando en puerto ${ PORT }`)
  })