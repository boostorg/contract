function toolTip(X,Y,boxWidth,ID) {
	theTip = document.getElementById(ID);
	theTip.style.left = (X == "") ? "auto" : X + "px";
	theTip.style.top = (Y == "") ? "auto" : Y + "px";
	theTip.style.width = (boxWidth == "") ? "auto" : boxWidth + "px";

	var display = theTip.style.display;

	theTip.style.display = (display == "block") ? "none" : "block";
}

function showHide(ID) {
	var oDiv = document.getElementById(ID)
	var display = oDiv.style.display;
	oDiv.style.display = (display == "block") ? "none" : "block";
}	

function hideDivsInaBlock(ID) {	var toc = document.getElementById(ID);	var divs = toc.getElementsByTagName("div");	for (var i = 0; i < divs.length; i++) {		divs[i].style.display = "none";	}			}