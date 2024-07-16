// Selectionne le noeud dont les mutations seront observées
var targetNode = document.getElementById("some-id");


// Options de l'observateur (quelles sont les mutations à observer)
var config = { attributes: true, childList: true };

// Fonction callback à éxécuter quand une mutation est observée
var callback = function (mutationsList) {
  for (var mutation of mutationsList) {
    if (mutation.type == "childList") {
      console.log("Un noeud enfant a été ajouté ou supprimé.");
    } else if (mutation.type == "attributes") {
      console.log("L'attribut '" + mutation.attributeName + "' a été modifié.");
    }
  }
};

// Créé une instance de l'observateur lié à la fonction de callback
var observer = new MutationObserver(callback);

// Commence à observer le noeud cible pour les mutations précédemment configurées
observer.observe(targetNode, config);


const para = document.createElement("p");
const node = document.createTextNode("This is new.");
para.appendChild(node);

targetNode.appendChild(para);


// L'observation peut être arrêtée par la suite
// observer.disconnect();
