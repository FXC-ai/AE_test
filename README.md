# Test Technique

Ceci est le premier test technique que j'ai effectué dans le but de décrocher ma prmière mission entant que développeur.

# Test 1: Javascript

## Problème

Nous avons parfois besoin qu’un fonction puisse être associée à un événement sans pour autant se déclencher en permanence.

*Par exemple, associé à l’événement de scroll, la fonction va, sur les plateforme moderne, s’exécuter des centaines de fois si l’utilisateurs scrolle en continue et longtemps. Nous avons parfois besoin que la fonction ne s’exécute qu’une fois à la fin.*

## Proposition

Le problème est intuitivement résolut par un code local lors du processus de développement mais il est utile d’avoir une solution générale à ce problème.

## Code

Nous nous proposons de rationaliser cette approche à l’aide d’une fonction utilitaire qui nous permet de temporiser le lancement du code. La signature est la suivante:

- f: Le code à lancer
- millisecondes: le temps en millisecondes de délai avant le lancement après que le dernier événement ait eu lieu.

```tsx
const regulate = (f: Function, milliseconds : number): Function => {...}
```

```jsx
function regulate(f, milliseconds) {...}
```

### Exemple d’utilisation

```tsx
let r = regulate(function() {
console.log("Run!");
/* Appel de n'importe quoi d'utile par exemple mettre à jour le menu déroulant qui indique où nous nous trouvons dans le texte.
*/
}, 300);
// Compteur pour annulation
let counter = 0;
// Un intervalle de 200ms pour le lancement avec une cadance inférieur au délai de
// lancement.
let i;
i = setInterval(function() {
r();
counter++;
if (counter > 20) {
clearInterval(i); }
, 200);
// Le code devrait afficher "Run!" une seule fois au bout de 4.5 secondes (si je
// calcule bien).
```

## Question

### Pouvez-vous écrire cette fonction (Typescript ou Javascript accepté ou autre
transpileur à choix) ?

La fonction doit être exécutée uniquement après un délai de “millisecondes” après sa dernière execution. Ce délai est remis à 0 à chaque nouvel appel de cette fonction. Cela explique pourquoi le code de test ci-dessous attend 4.5 secondes avant d’afficher “Run!” dans le terminal.

En effet la fonction r doit s’exécuter au maximum chaque 300 ms. Cependant elle est appellée 21 fois toutes les 200 ms par la fonction setInterval. Aucun des 20 premiers appels n’a donc le temps d’aboutir. Il y a donc 20 * 200 ms qui s’écoulent sans aucun affichage dans la console (soit 4 secondes). Le 21éme appel étant le dernier, la fonction `setInterval` impose un dernier délai de 200 ms avant de demander une dernière exécution de la fonction r qui affichera `“Run!”` après les 300 ms de délai imposés par la fonction regulate. On obtient donc bien un délai de 4s + 200 ms +300 ms = 4.5 s.

Voici le code et le test de la fonction regulate (en javascript) :

```jsx
function regulate(f, milliseconds) 
{
	let timer;

	return function()
	{
		clearTimeout(timer);
		timer = setTimeout(function(){f.apply();}, milliseconds);
	}
}

let r = regulate(function() {console.log("Run!");}, 300);

let counter = 0;
let i;

i = setInterval(function() {r(); counter++; if (counter > 20) {clearInterval(i);}}, 200);
```

Le point important de ce code se trouve à cette ligne : `let r = regulate(function() {console.log("Run!");}, 300);`

Nous pourrions écrire le code de la fonction anonyme contenu dans la variable r comme suit (pseudocode !):

```jsx
	r()
	{
		clearTimeout(timer);
		timer = setTimeout(function() {console.log("Run!");}, 300);
	}
```

A chaque exécution de cette fonction anonyme, le timer (qui a été déclaré dans le scope de la fonction regulate !) est remis à 0. Ensuite on appel la fonction `setTimeout` qui se charge d’attendre 300 ms avant d’exécuter le `console.log` . Si la fonction `“r”` est rappellé avant que les 300 ms se soit écoulé alors `timer` est remis à 0.

### Quelles autres fonctions dans le même esprit seraient utiles ? Pourquoi ?

1. **throttle** : peut également être utile pour gérer un évenement qui se déclencherait de manière intempestive. Elle permet d’ ”autoriser” l’événement avec un certain intervalle de temps défini.
2. À l'opposé, une fonction **exec_if_no_event** exécuterais une action seulement après un certain délai si un événement n'a été déclenché par l’utilisateur pendant ce délai. Par exemple, si une information importante se trouve à la fin d'une page et que l'utilisateur n'a pas scrollé après un certain temps, une fonction pourrait être appelée pour l'informer. Cette technique peut également être utilisée pour des systèmes de paiement où le prix varie rapidement (comme les billets de train SNCF) ; si l'utilisateur n'a pas confirmé son achat après un certain délai, une alerte peut être envoyée pour le notifier.
3. **Limiter le Nombre de Déclenchements** **(limit_nb_events)**: Il peut aussi être nécessaire de limiter le nombre de fois qu'un événement peut se déclencher dans une période donnée. On pourrait coder une fonction qui permet de déclencher l'événement uniquement un certain nombre de fois toutes les 5 secondes, par exemple. Cela peut être utile pour restreindre le nombre de requêtes qu'un utilisateur peut envoyer à un serveur.
4. **Exécution à un Timestamp Précis** **(exec_et_timestamp)**: Une autre fonction utile pourrait permettre l'exécution d'une action à un moment précis. Ceci est particulièrement pertinent dans le cadre d'un jeu multijoueur, où la partie doit commencer à une heure précise. Tous les utilisateurs peuvent cliquer sur le bouton d'inscription, mais l'action ne sera exécutée qu'au moment où la partie débute.

### Pouvez-vous en écrire une ?

Voici un exemple d’implémentation de la fonction throttle :

```jsx
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
```

Pour que l’exemple soit plus facile à expliquer, j’ai pris la liberté de modifier les paramètres du test. J’ai paramétré la fonction throttle à milliseconds = 1000.

La fonction `setInterval` appelle la fonction anonyme contenu dans la variable t chaque 200 ms, et ce, 21 fois. Cependant tous ces appels n’aboutiront pas à l’affichage de `“Run!”` dans la console. Seul les appels possédant un délai de minimum 1000 ms avec l’appel précédent permettront l’affichage.

Le test parvient à exécuter le `console.log(”Run!”)` 6 fois. C’est un fonctionnement normal. Nous allons détailler le fonctionnement étape par étape :

- **Premier appel :** affichage de run : `last = NaN` à cette exécution, c’est donc la condition `else` qui se charge d’afficher le premier `Run!`
- **Appels 2 3 4 et 5 :** la fonction entre dans le if à chaque appel et réinitialise le `timer` à 0. La fonction f ne pourra pas s’exécuter puisque l’appel suivant sera fait seulement 200 ms plus tard. Donc last reste à 200 ms ! Quand à now il est incrémenté de 200 à chaque appel.
- **Appel 6 :** désormais `now = 1200` et `last = 200` , `now` n’est donc plus strictement inférieur à `last + milliseconds` (1200). C’est donc le `else` qui se charge d’afficher le deuxième `run!`
- **Les appels 11, 16 et 21** obéissent à la même logique que l’appel 6. Ils affichent donc également `Run!`
- **Enfin le 6 ème** et dernier affichage de `run!` correspond à l’appel 20 qui aboutit puisque qu’aucun autre appel n’est venu réinitialiser le timer après.

En résumé, il y a 6 affichages de run dans le terminal. Ces affichages correspondent aux appels `1,6,11,16,20 et 21`.

Pour visualiser tous cela, voici une fonction throttle avec un affichage qui détaille son fonctionnement :

```jsx
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
```

### En extension de l’exemple du scroll, comment pourrait-on gérer le cas où le calcul de mise à jour selon l’état de scroll est lourd mais où nous aimerions quand même qu’il suive un peu en temps réel le mouvement de l’utilisateur ?

En combinant l’utilisation des fonctions regulate et throttle, il est tout a fait possible de gérer le cas ou le calcule de mise à jour en fonction du scroll est lourd.
Par exemple, on pourrait :

1. Charger throttle d’assurer une mise à jour minimale avec un délai assez court.
2. Charger regulate d’appeler une fonction de mise à jour plus lourde en lui paramétrant un délai beaucoup plus long que throttle

Voici un exemple en pseudocode :

```jsx
function fct_update_scroll_heavy (){// Calculs de Màj très longs}
function fct_update_scroll_light (){// Calculs de Màj très courts}

let throttle_update = throttle(fct_update_scroll_light, 200);
let regulate_update = regulate(fct_update_scroll_heavy, 1000);
```

Ainsi, la fonction la moins gourmande en ressources est exécutée plus fréquemment que la fonction la plus gourmande en ressources pendant le scroll.

### Sources

[setInterval() global function - Web APIs | MDN](https://developer.mozilla.org/en-US/docs/Web/API/setInterval)

[setTimeout() global function - Web APIs | MDN](https://developer.mozilla.org/en-US/docs/Web/API/setTimeout)

[Tutoriel vidéo JavaScript : Debounce & Throttle](https://grafikart.fr/tutoriels/debounce-throttle-642)

# Test 2: Méthode

## Problème 1: Moins de travail HTML

Une des complication, quand on n’utilise pas de framework, est la charge de travail pour initialiser les événements d’un élément HTML après son chargement.

### Quelles sont les pistes qui permettent d’automatiser l’activation de comportement sur les nouveaux nœuds HTML chargé depuis le serveur sans devoir gérer en Javascript chaque cas ?

- **Event Delegation**

Il s’agit d’ajouter un listener pour un certain évènement à toutes les balises HTML d’un certain type.

Dans l’exemple ci-dessous toutes les images déclencheront un `console.log` lorsque l’utilisateur cliquera dessus.

```jsx
document.body.addEventListener('click', function (event) {if(event.target.tagName === 'IMG')
												{
													console.log(event.target.alt);
												}});
```

Il n’est donc plus nécessaire d’ajouter l’événement `click` a toutes les images de la page.

- **Mutation Observer**

Cette méthode consiste à surveiller les éléments du DOM et à modifier le comportement de ces éléments à chaque fois que le DOM est modifié.

Cette technique est permise grâce à l’objet `MutationObserver` qui fournit un moyen d'intercepter les changements dans le DOM. Cet classe prends en paramètre une fonction `callback` qui sera appelée chaque fois que le DOM est modifié. Dans l’exemple qui suit j’utilise la fonction callback pour accrocher un événement de `click` à chaque élément enfant qui sera ajouté à l’élément parent.

Dans l’exemple suivant, le fichier HTML contient une div avec un attribut `id=some-id`.

```html
<div class="content-box" id="some-id">
     <h2>Démonstration 2 : Mutation Observer</h2>
</div>
```

Grâce à l’objet MutationObserver, nous allons surveiller tous les enfants qui seront ajoutés à cette `div` parent. A chaque fois qu’un élément HTML sera ajouté, notre MutationObserver appellera la fonction callback. Voici le code : 

```jsx
// Selectionne le node dont les mutations seront observées
var targetNode = document.getElementById("some-id");

// Options de l'observateur (quelles sont les mutations à observer)
var config = {childList: true};

// Fonction callback à éxécuter quand une mutation est observée
var callback = function (mutationsList, observer) 
{
	for (var mutation of mutationsList)
	{
		if (mutation.type == "childList") // Vérification NON indispensable...
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

// Ajout d'un premier enfant est ajouté
const new_p = document.createElement("p");
const text = document.createTextNode("Cliquez en regardant la console");
new_p.appendChild(text);
targetNode.appendChild(new_p);

// Ajout d'un second enfant
const new_p2 = document.createElement("p");
const text2 = document.createTextNode("Cliquez sur moi en regardant la console");
new_p2.appendChild(text2);
targetNode.appendChild(new_p2);

// L'observation peut être arrêtée par la suite
// observer.disconnect();

```

Concernant la fonction callback, elle se charge d’ajouter un événement à tous les enfants. Ici la seul modification du DOM qui est observée est l’ajout d’enfant (`var config = {childList: true};`). Ensuite la fonction se charge de parcourir tous les noeuds ajoutés et de leur accrocher une événement `click` à chacun :

```jsx
for (let child of mutation.addedNodes)
{
	child.addEventListener('click', function (event) {console.log(event.target.textContent);});
}
```

Ainsi cette technique permet d’éviter d’ajouter un à un l’événement `click` à chaque nouvel élément.

- **Custom Element**

Les éléments custom sont des éléments qui héritent des éléments standards HTML. Ensuite il est possible de modifier le comportement de ces éléments customisés. Dans l’exemple qui suit, il s’agit d’un élément customisé `MyOwnP` auquel est accroché l’événement `click` à chaque fois que cet élément est ajouté dans le DOM. Ainsi il n’est plus nécessaire d’accrocher manuellement l’événement à chaque fois que l’on crée un `MyOwnP` dans le HTML.

Voici un exemple d’implémentation :

```jsx
class MyOwnP extends HTMLParagraphElement
{
	constructor() {super();}

	connectedCallback()
	{
		console.log("Custom p added to page.");
		this.addEventListener('click', this.handleClick);
	}

	handleClick()
	{
		alert("Vous avez cliqué sur un p custom !");
	}

}

customElements.define("my-own-p", MyOwnP, { extends: "p" });
```

Chaque élément `MyOwnP` lancera une `alert` lorsque l’utilisateur cliquera dessus.

### Sources

[Understanding Event Delegation in JavaScript](https://www.linkedin.com/pulse/understanding-event-delegation-javascript-adekola-olawale-4bzbf/)

[MutationObserver - Les API Web | MDN](https://developer.mozilla.org/fr/docs/Web/API/MutationObserver)

[Using custom elements - Web APIs | MDN](https://developer.mozilla.org/en-US/docs/Web/API/Web_components/Using_custom_elements)

## Problème 2: Copy on Write

Sans demander un développement complet, dans un langage algorithmique (Rust, C/Cpp) comment implémenter une classe qui supporte la copie légère (i.e les données internes ne sont pas copiées) mais le sont au moment même ou une méthode d’écriture est appelée.

*Un exemple est la classe SubString du Swift d’Apple qui permet de prendre une sous-chaîne en économisant au CPU le travail de copie de la sous-chaine, mais fait la copie mémoire si le développeur modifie ou manipule en écriture la sous-chaîne résultant. Une sorte de LazyCopy.*

### Décrire la méthode générale et ses optimisations possibles, avec des fragments de code (langage à choix).

La méthode générale consiste à copier les données en mémoire uniquement lorsqu'elles sont modifiées, ce qui permet d’économiser de la mémoire. Plusieurs objets peuvent ainsi partager le même segment de mémoire (par exemple, une chaîne de caractères). Si l’un d’eux tente de modifier le contenu de ce segment, une copie est effectuée. Cette copie est placée à un autre endroit de la mémoire, permettant à l’objet de modifier cette nouvelle mémoire allouée spécifiquement. En pratique, cela fonctionne comme si le segment de mémoire partagé était en lecture seule, mais uniquement lorsque la mémoire est partagée par au moins deux objets. Si un seul objet fait référence à ce segment de mémoire, il peut le modifier librement.

Dans le cadre d’une implémentation en C++, la classe `Copy_on_write` possède en attribut un pointeur. Ce pointeur contient une addresse mémoire. Si toutefois cette adresse mémoire a été assigné ailleurs dans un autre objet alors le contenu de la mémoire vers lequel elle pointe n’est plus modifiable. Cela est permis grâce à l’utilisation du smart pointer `std::shared_ptr<T>`. C’est une classe qui enveloppe un pointeur de n’importe que type. Cette classe possède notamment une méthode appelée `unique()` qui renvoie `false` si le pointeur a été assigné plusieurs fois.

Voici un code élémentaire d’une classe qui utilise le principe de “copy on write” :

```cpp
#include <iostream>
#include <string>

template <class T>
class Copy_on_write
{

	private :
		std::shared_ptr<T> _ptr;
		void create_new_allocation();

	public :
		Copy_on_write(T* ptr);

		T& get() const;
		void set(T value);
		
};

template <class T>
void Copy_on_write<T>::create_new_allocation()
{
	T* tmp = this->_ptr.get();
	if (!(tmp == 0 || this->_ptr.unique()))
	{
		this->_ptr = std::shared_ptr<int>(new T(*tmp));
	}
}

template <class T>
Copy_on_write<T>::Copy_on_write (T* ptr) : _ptr(ptr) {}

template <class T>
T& Copy_on_write<T>::get () const
{
	return *(this->_ptr);
}

template <class T>
void Copy_on_write<T>::set(T value)
{
	this->create_new_allocation();
	*(this->_ptr) = value;
}

int main()
{

	int *test0 = new int(24);

	Copy_on_write<int> obj_cp_on_wr0(test0);
	
	Copy_on_write<int> obj_cp_on_wr1(obj_cp_on_wr0);

	std::cout << "Avant set()" << std::endl;
	std::cout << obj_cp_on_wr0.get() << " " << &obj_cp_on_wr0.get() << std::endl;
	std::cout << obj_cp_on_wr1.get() << " " << &obj_cp_on_wr1.get() << std::endl;

	obj_cp_on_wr1.set(42);

	std::cout << "Apres set()" << std::endl;
	std::cout << obj_cp_on_wr0.get() << " " << &obj_cp_on_wr0.get() << std::endl;
	std::cout << obj_cp_on_wr1.get() << " " << &obj_cp_on_wr1.get() << std::endl;

	return 1;	
}
```

Voici le résultat obtenu dans le terminal :

```bash
fcoindre@c2r7s3 Probleme2_Copy_on_write % c++ main.cpp && ./a.out
Avant set()
24 0x7fd29ec05850
24 0x7fd29ec05850
Apres set()
24 0x7fd29ec05850
42 0x7fd29ec05880
```

On peut constater que le pointeur a bien été modifié : `0x7fd29ec05850 ≠ 0x7fd29ec05880`

Avant que l’on essaie de modifier le contenu de la mémoire pointée par l’attribut _ptr, on constate que les 2 objets pointent vers le même segment de mémoire. Dés que l’on modifie le contenu de la mémoire pointée par _ptr alors une copie est effectuée et _ptr a changé de valeur.

Voici 2 optimisations possibles :

- **Copie conditionelle** : Effectuer une copie si et seulement si les données sont effectivement modifiées. L’utilisateur pourrait fournir au setter `set()` une valeur exactement égale à la valeur déjà présente. Dans ce cas une copie est inutile.
- Eviter une allocation dynamique si les données sont de taille suffisament petite. Pour cela il faudrait ajouter un attribut privé `small_size_data[MAX_SIZE]` de type `T` et l’initialiser si la taille des datas ne dépasse pas `MAX_SIZE`.

### Sources

https://www.notion.so/Atelier-Eveil-Test-Technique-ab1ed61d735e46e6b83ce08589f69a7c?source=copy_link#19ddf010593a4cbaaa5d4b56d336fe21

https://www.notion.so/Atelier-Eveil-Test-Technique-ab1ed61d735e46e6b83ce08589f69a7c?source=copy_link#2a001ef27f554795b5cca31625cf6865

https://www.notion.so/Atelier-Eveil-Test-Technique-ab1ed61d735e46e6b83ce08589f69a7c?source=copy_link#c73c100db1f449f08af4dd7062e577f6

https://www.notion.so/Atelier-Eveil-Test-Technique-ab1ed61d735e46e6b83ce08589f69a7c?source=copy_link#eef5f29223f44125a0904b857ea91dea
