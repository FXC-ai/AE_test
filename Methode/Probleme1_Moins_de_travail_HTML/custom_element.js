class MyOwnP extends HTMLParagraphElement
{
	constructor() {super();}

	connectedCallback()
	{
		console.log("Custom p added to page.");
	}
}

customElements.define("my-own-p", MyOwnP, { extends: "p" });