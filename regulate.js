

function regulate(f, milliseconds) {
    let timer;

    return function()
	{
        let args = arguments;
        let context = this;
        clearTimeout(timer);
        timer = setTimeout(function(){f.apply(context, args);}, milliseconds);
    }
}

let r = regulate(function() {console.log("Run!");}, 300);


// Compteur pour annulation
let counter = 0;
// Un intervalle de 200ms pour le lancement avec une cadance inférieur au délai de lancement.
let i;


// Chaque 200 ms la fonction r est appelée et chaque appel à cette fonction incrémente la variable counter
// Dés que la variable counter est superieure à 20 clearInterval est appelé et tout s arrête
// Au premier appel regulate est appelé avec les paramêtres qui lui sont donnés
// comme le paramêtre miliseconds de regulate est de 300, il n'as pas le temps d'appeler 
// la fonction qui lui est donnée en premier paramêtre
// Cela va être le cas 20 fois soit 20*200 = 4000 ms
// Au 21eme appel au bout de 200 ms il n y a pas d'appel supplémentaire à regulate
// du coup regulate a le temps de lancer la fonction apres 300 ms

i = setInterval(function() {r(); counter++; if (counter > 20) {clearInterval(i);}}, 200);

// Le code devrait afficher "Run!" une seule fois au bout de 4.5 secondes (si je calcule bien).