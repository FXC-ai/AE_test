function throttle(f, milliseconds) 
{
    let last;
    let timer;

    let ori = Date.now();
    

    return function () 
    {
        console.log("--------------- counter = " + (counter + 1) + " ------------------")
        let now = Date.now();

        if (last && now < last + milliseconds) 
        {
            console.log("if now = " + (now - ori) + " last = " + (last - ori));
            clearTimeout(timer);
            timer = setTimeout(function () {last = now; f.apply();}, milliseconds);
        } 
        else 
        {
            console.log("else now = " + (now - ori) + " last = " + (last - ori));

            last = now;
            f.apply();
        }
        console.log("------------------ end execution ------------------")
    };
}

let t = throttle(function() {console.log("Run!");}, 1000);

let counter = 0;
let i;

i = setInterval(function() {t(); counter++; if (counter > 20) {console.log("ici "+ counter); clearInterval(i);}}, 200);