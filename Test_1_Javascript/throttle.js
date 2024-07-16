function throttle(f, milliseconds) 
{
    let last;
    let timer;

    return function () 
    {
        let context = this;
        let now = +new Date();
        let args = arguments;

        if (last && now < last + milliseconds) 
        {
            // le délai n'est pas écoulé on reset le timer
            clearTimeout(timer);
            timer = setTimeout(function () {last = now; f.apply(context, args);}, milliseconds);
        } 
        else 
        {
            last = now;
            f.apply(context, args);
        }
    };
}

let t = throttle(function() {console.log("Run!");}, 1000);


// Compteur pour annulation
let counter = 0;
// Un intervalle de 200ms pour le lancement avec une cadance inférieur au délai de lancement.
let i;

// chaque 200 ms on appelle la fonction qui est rythmé par throttle
// _ | _ | _ | _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _

i = setInterval(function() {t(); counter++; if (counter > 20) {clearInterval(i);}}, 200);