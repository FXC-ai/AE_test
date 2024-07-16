document.body.addEventListener('click', function (event) {if(event.target.tagName === 'IMG')
												{
													console.log(event.target.alt);
												}});