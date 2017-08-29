var MinPreHeight = 450;
var MinPreChars  = 750;

var PreOpen = new Image();
var PreClose = new Image();
PreOpen.src="/images/plus.gif";
PreClose.src="/images/minus.gif";

function togglePre()
{
	var id = this.getAttribute("preid");
	var preelm = document.getElementById("pre" + id);
	var imgelm = document.getElementById("preimg" + id);
	var togelm = document.getElementById("precollapse" + id);

	if (preelm.style.display != 'none') 
	{
		if (document.all) togelm.innerText = " Expand code snippet";
		else 
		{
			document.getElementById("premain" + id).className = "precollapse";
			togelm.firstChild.nodeValue = " Expand code snippet";
		}
		preelm.style.display = 'none';
		imgelm.setAttribute("src", PreOpen.src);
	}
	else 
	{
		if (document.all) togelm.innerText = " Collapse";
		else 
		{	
			document.getElementById("premain" + id).className = "smallText";
			togelm.firstChild.nodeValue = " Collapse";
		}
		preelm.style.display = 'block';
		imgelm.setAttribute("src", PreClose.src);
	}
}

function InitTogglePre()
{
	var articleText = document.getElementById("contentdiv");
	var pres = articleText.getElementsByTagName("pre");

	for (var i=0; i<pres.length; i++)
	{	
		if (pres[i].offsetHeight == 0)
		{
			if (pres[i].innerText.length < MinPreChars) continue;
		}
		else if (pres[i].offsetHeight < MinPreHeight)
			continue;
		
		var main = document.createElement("div");
		main.style.width="100%";
		main.setAttribute("id", "premain" + i.toString());

		elm = document.createElement("img");
		elm.setAttribute("id", "preimg" + i.toString());
		elm.setAttribute("src", PreClose.src);
		if (document.all) elm.style.cursor = "hand";
		elm.setAttribute("height", 9);
		elm.setAttribute("width", 9);
		elm.setAttribute("preid", i);
		elm.onclick = togglePre;

		main.appendChild(elm);	
	
		elm = document.createElement("span");
		elm.setAttribute("id", "precollapse" + i.toString());

		if (document.all)
		{
			main.className = "precollapse";
			elm.innerText = " Collapse";
			elm.style.cursor = "hand";
		}
		else
		{
			main.className = "smallText";
			//This is lame. Why can't W3C just allow innerText on spans??
			var new_el = document.createTextNode(" Collapse");
			elm.appendChild(new_el);
		}
		
		elm.style.marginBottom = 0;
		elm.onclick = togglePre;
		elm.setAttribute("preid", i);
	
		main.appendChild(elm);
		
		pres[i].setAttribute("id", "pre" + i.toString());
		pres[i].style.marginTop = 0;

		var parent = pres[i].parentNode;
		parent.insertBefore(main, pres[i]);
	}
}

InitTogglePre();