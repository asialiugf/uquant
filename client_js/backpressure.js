/* NOTE: ws as client cannot even remotely stress uWebSockets.js,
 * however we don't care for ultra correctness here as
 * Socket.IO is so pointlessly slow anyways, we simply do not care */
const WebSocket = require('ws');

/* By default we use 10% active traders, 90% passive watchers */
const numClients = 1250;
const tradersFraction = 0.1;

/* 125 * 4 = 500, even though 4 instances cannot stress the server fully */
console.log("RUN 4 INSTANCES OF THIS CLIENT");

let shares = [
	'NFLX',
	'TSLA',
	'AMZN',
	'GOOG',
	'NVDA'
];

function establishConnections(remainingClients) {

	if (!remainingClients) {
		return;
	}

	/* Current value of our share */
	let value;

	let socket = new WebSocket('ws://124.221.96.31:8300');
	socket.onopen = () => {
		/* Randomly select one share this client will be interested in */
		let shareOfInterest = shares[parseInt(Math.random() * shares.length)];

		/* Subscribe to the share we are interested in */
		socket.send(JSON.stringify({action: 'sub', share: shareOfInterest}));

		/* Is this client going to be an active trader, or a passive watcher? */
		if (remainingClients <= numClients * tradersFraction) {
			/* If so, then buy and sell shares every 1ms, driving change in the stock market */
			setInterval(() => {
				/* For simplicity we just randomly buy/sell */
				if (Math.random() < 0.5) {
					socket.send(JSON.stringify({action: 'buy', share: shareOfInterest}));
				} else {
					socket.send(JSON.stringify({action: 'sell', share: shareOfInterest}));
				}
			}, 1);
		}

		/* establishConnections(remainingClients - 1); */
	};

	socket.onmessage = (e) => {
              //  console.log(String(e.data));
		//  let json = JSON.parse(e.data);
            
	};

	/*
	socket.onerror = (e) => {
		console.log("Error occurred: " + e);
	};

	socket.ping = () => {
		socket.send(JSON.stringify({action: 'ping'}));
	};

	*/
	socket.pong = (e) => {
		socket.send(JSON.stringify({action: 'pong'}));
		e.length
		console.log(e + e.length);
		console.log("Pong received");
	};

	socket.onclose = (event) => {
		if (event.wasClean) {
			console.log(`Connection closed cleanly, code=${event.code}, reason=${event.reason}`);
		  } else {
			// 连接中断，可能是由于网络问题等
			console.log(`Connection was not closed cleanly, code=${event.code}, reason=${event.reason}`);
		  }
		console.log("We did not expect any client to disconnect, exiting!");
		process.exit();
	}
}

establishConnections(numClients);