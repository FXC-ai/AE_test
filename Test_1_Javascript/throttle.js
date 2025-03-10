function throttle(f, milliseconds) 
{
    let last;
    let timer;

    return function () 
    {
        let now = Date.now();

        if (last && now < last + milliseconds) 
        {
            clearTimeout(timer);
            timer = setTimeout(function () {last = now; f.apply();}, milliseconds);
        } 
        else 
        {
            last = now;
            f.apply();
        }
    };
}

let t = throttle(function() {console.log("Run!");}, 1000);
let counter = 0;
let i;

i = setInterval(function() {t(); counter++; if (counter > 20) {clearInterval(i);}}, 200);
