// Selectionne le noeud dont les mutations seront observées
var targetNode = document.getElementById("some-id");


// Options de l'observateur (quelles sont les mutations à observer)
var config = {childList: true};

// Fonction callback à éxécuter quand une mutation est observée
var callback = function (mutationsList, observer) 
{
	for (var mutation of mutationsList)
	{
		if (mutation.type == "childList")
		{
			for (let child of mutation.addedNodes)
			{
				child.addEventListener('click', function (event) {console.log(event.target.textContent);});
				console.log("Un noeud enfant a été ajouté ou supprimé.");
			}
		}

	}
};

// Créé une instance de l'observateur lié à la fonction de callback
var observer = new MutationObserver(callback);

// Commence à observer le noeud cible pour les mutations précédemment configurées
observer.observe(targetNode, config);


const new_p = document.createElement("p");
const text = document.createTextNode("Cliquez en regardant la console");
new_p.appendChild(text);
targetNode.appendChild(new_p);

const new_p2 = document.createElement("p");
const text2 = document.createTextNode("Cliquez sur moi en regardant la console");
new_p2.appendChild(text2);
targetNode.appendChild(new_p2);

// L'observation peut être arrêtée par la suite
// observer.disconnect();
