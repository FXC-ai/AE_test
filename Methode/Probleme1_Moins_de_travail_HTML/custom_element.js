class MyOwnP extends HTMLParagraphElement
{
	constructor() {super();}

	connectedCallback()
	{
		console.log("P custom ajouté à la page.");
		this.addEventListener('click', this.handleClick);
	}

	handleClick()
	{
		alert("Vous avez cliqué sur un p custom !");
	}

}

customElements.define("my-own-p", MyOwnP, { extends: "p" });