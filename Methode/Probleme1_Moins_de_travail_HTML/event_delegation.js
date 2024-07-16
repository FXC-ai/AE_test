// HTML <ul id="itemList"> <li>Item 1</li> <li>Item 2</li> <li>Item 3</li> </ul>

document.body.addEventListener('click', function (event) {if(event.target.tagName === 'LI'){console.log(event.target.textContent);}});