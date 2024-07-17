function regulate(f, milliseconds) 
{
	let timer;

	return function()
	{
		clearTimeout(timer);
		timer = setTimeout(function(){f.apply();}, milliseconds);
	}
}

// test

let r = regulate(function() {console.log("Run!");}, 300);

let counter = 0;
let i;

i = setInterval(function() {r(); counter++; if (counter > 20) {clearInterval(i);}}, 200);
