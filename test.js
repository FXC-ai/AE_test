
let i;
let counter = 0;

// Chaque 2 secondes on relance un setInterval de hello
// 
// i = setInterval(function() {console.log("AAAA " + counter);setTimeout(function (){console.log("hello");}, 2000); counter++; if (counter > 20) {clearInterval(i);}}, 1000);


// let date_call = 0;
// // alert("date_last_event = " + date_last_event);
let last_call = 0;

function regulate(f, milliseconds)
{
    let timer;

    return function()
	{
        let args = arguments;
        let context = this;
        clearTimeout(timer);
        timer = setTimeout(function(){f.apply(context, args);}, milliseconds);
    }
}


// let counter = 0;
// let interval;

// let test_ID = setTimeout(function(){alert("test_ID = " + test_ID)}, 500);


// function fct_test ()
// {
// 	counter++;
// 	if (counter > 2){clearInterval(interval);}
// 	alert("Hello " + interval);
// };

// interval = setInterval(fct_test, 2000);


//document.addEventListener("scroll", (event) => {
//	alert("Vous êtes en train de scroller.")
//});


