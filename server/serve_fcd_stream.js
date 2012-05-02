
var http = require('http');

http.createServer(function (req, res) {
  res.writeHead(200, {'Content-Type': 'application/json'});
//  res.writeHead(300, {'Content-Length': '20'});
    res.end('aaa={"x":' + Math.random() +  ',"y":' + Math.random() * 10 + '};');
}).listen(4000, "127.0.0.1");
console.log('Server running at http://127.0.0.1:4000/');