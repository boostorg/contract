<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html><head><title>Application Development Trends - Supporting Design by Contract in C++</title>



	
		
		<meta http-equiv="Content-Type" content="text/html; charset=utf-8">
		
<meta name="description" content="Most OO practitioners recognize the value of Design by Contract as a methodology for improving software quality. It is at the heart of the Eiffel language and the Object Constraint Language of UML. However, there are precious few languages that provide such intrinsic support for Design by Contract, and C++ is one language that does not. This article presents two new mechanisms for emulating Design by Contract in C++ that take advantage of language features defined in the recent standard, and for which widespread compiler support is now becoming available. One mechanism has been used in the development of software components in Computational Physics and is based on the Standard Template Library (STL); the other provides Design by Contract support across an inheritance hierarchy in C++ in accordance with the Liskov Substitutability Principle.">
<meta name="keywords" content="application development managers, IT managers, integration, components, data management, XML, application management, application engineering, component-based development, e-business application development, e-business, middleware, application integration, data warehousing, application development, development, development tools, application development trends, application development trends magazine, ADT, application components, software components, software development, software development management, software management, Java, .NET, SOA, service-oriented architecture, software testing, software trends, open source, business intelligence, BI, outsourcing">
<link rel="shortcut icon" href="http://www.adtmag.com/favicon.ico" type="image/x-icon">
<link rel="alternate" type="application/rss+xml" title="Application Developement Trends - News" href="http://www.adtmag.com/RSS/news.xml">
<link rel="alternate" type="application/rss+xml" title="Developer Central Blog" href="http://www.adtmag.com/blogs/RSS/devCentral.xml">
<link rel="alternate" type="application/rss+xml" title="WatersWorks" href="http://www.adtmag.com/blogs/RSS/WatersWorks.xml"><!-- START OF SDC Advanced Tracking Code --><!-- Copyright (c) 1996-2005 WebTrends Inc.  All rights reserved. --><!-- V7.5 --><!-- $DateTime: 2005/09/22 12:07:59 $ -->





<script language="Javascript"><!--
var gService = false;
var gTimeZone = -8;
// Code section for Enable First-Party Cookie Tracking
function dcsCookie(){
	if (typeof(dcsOther)=="function"){
		dcsOther();
	}
	else if (typeof(dcsPlugin)=="function"){
		dcsPlugin();
	}
	else if (typeof(dcsFPC)=="function"){
		dcsFPC(gTimeZone);
	}
}
function dcsGetCookie(name){
	var pos=document.cookie.indexOf(name+"=");
	if (pos!=-1){
		var start=pos+name.length+1;
		var end=document.cookie.indexOf(";",start);
		if (end==-1){
			end=document.cookie.length;
		}
		return unescape(document.cookie.substring(start,end));
	}
	return null;
}
function dcsGetCrumb(name,crumb){
	var aCookie=dcsGetCookie(name).split(":");
	for (var i=0;i<aCookie.length;i++){
		var aCrumb=aCookie[i].split("=");
		if (crumb==aCrumb[0]){
			return aCrumb[1];
		}
	}
	return null;
}
function dcsGetIdCrumb(name,crumb){
	var cookie=dcsGetCookie(name);
	var id=cookie.substring(0,cookie.indexOf(":lv="));
	var aCrumb=id.split("=");
	for (var i=0;i<aCrumb.length;i++){
		if (crumb==aCrumb[0]){
			return aCrumb[1];
		}
	}
	return null;
}
function dcsFPC(offset){
	if (typeof(offset)=="undefined"){
		return;
	}
	var name=gFpc;
	var dCur=new Date();
	dCur.setTime(dCur.getTime()+(dCur.getTimezoneOffset()*60000)+(offset*3600000));
	var dExp=new Date(dCur.getTime()+315360000000);
	var dSes=new Date(dCur.getTime());
	if (document.cookie.indexOf(name+"=")!=-1){
		var id=dcsGetIdCrumb(name,"id");
		var lv=parseInt(dcsGetCrumb(name,"lv"));
		var ss=parseInt(dcsGetCrumb(name,"ss"));
		if ((id==null)||(id=="null")||isNaN(lv)||isNaN(ss)){
			return;
		}
		WT.co_f=id;
		var dLst=new Date(lv);
		dSes.setTime(ss);
		if ((dCur.getTime()>(dLst.getTime()+1800000))||(dCur.getTime()>(dSes.getTime()+28800000))){
			dSes.setTime(dCur.getTime());
			WT.vt_f_s="1";
		}
		if ((dCur.getDay()!=dLst.getDay())||(dCur.getMonth()!=dLst.getMonth())||(dCur.getYear()!=dLst.getYear())){
			WT.vt_f_d="1";
		}
	}
	else{
		var tmpname=name+"_TMP=";
		document.cookie=tmpname+"1";
		if (document.cookie.indexOf(tmpname)!=-1){
			document.cookie=tmpname+"; expires=Thu, 01-Jan-1970 00:00:01 GMT";
			if ((typeof(gWtId)!="undefined")&&(gWtId!="")){
				WT.co_f=gWtId;
			}
			else if ((typeof(gTempWtId)!="undefined")&&(gTempWtId!="")){
				WT.co_f=gTempWtId;
				WT.vt_f="1";
			}
			else{
				WT.co_f="2";
				var cur=dCur.getTime().toString();
				for (var i=2;i<=(32-cur.length);i++){
					WT.co_f+=Math.floor(Math.random()*16.0).toString(16);
				}
				WT.co_f+=cur;
				WT.vt_f="1";
			}
			if (typeof(gWtAccountRollup)=="undefined"){
				WT.vt_f_a="1";
			}
			WT.vt_f_s="1";
			WT.vt_f_d="1";
		}
		else{
			WT.vt_f="2";
			WT.vt_f_a="2";
			return;
		}
	}
	WT.co_f=escape(WT.co_f);
	WT.vt_sid=WT.co_f+"."+dSes.getTime();
	var expiry="; expires="+dExp.toGMTString();
	document.cookie=name+"="+"id="+WT.co_f+":lv="+dCur.getTime().toString()+":ss="+dSes.getTime().toString()+expiry+"; path=/"+(((typeof(gFpcDom)!="undefined")&&(gFpcDom!=""))?("; domain="+gFpcDom):(""));
}

// Code section for Use the new first-party cookie generated with this tag.
var gFpc="WT_FPC";
var gWtId="";
var gTempWtId="";
var gConvert=true;

// Code section for Set the First-Party Cookie domain
var gFpcDom=".adtmag.com";

function dcsAdv(){
	dcsFunc("dcsET");
	dcsFunc("dcsCookie");
	dcsFunc("dcsAdSearch");
	dcsFunc("dcsTP");
}

//-->
</script><!-- END OF SDC Advanced Tracking Code --><!-- START OF SmartSource Data Collector TAG --><!-- Copyright (c) 1996-2005 WebTrends Inc.  All rights reserved. --><!-- V7.5 --><!-- $DateTime: 2005/10/21 15:53:12 $ -->






<script language="Javascript"><!--
gVersion="1.0";
//-->
</script>
<script language="Javascript1.1"><!--
gVersion="1.1";
//-->
</script>
<script language="Javascript1.2"><!--
gVersion="1.2";
var RE={"%09":/\t/g,"%20":/ /g,"%23":/\#/g,"%26":/\&/g,"%2B":/\+/g,"%3F":/\?/g,"%5C":/\\/g};
//-->
</script>
<script language="Javascript1.3"><!--
gVersion="1.3";
if (window.ActiveXObject){
	var gFV="";
	for (var gVer=2;gVer<=10;gVer++){
		try{
			var gFlash = eval("new ActiveXObject('ShockwaveFlash.ShockwaveFlash."+gVer+"');");
			if (gFlash){
				gFV=gVer+".0";
				break;
			}
		}
		catch(e){
		}
	}
}
//-->
</script>
<script language="Javascript1.4"><!--
gVersion="1.4";
//-->
</script>
<script language="Javascript1.5"><!--
gVersion="1.5";
//-->
</script>

<script language="JavaScript"><!--
var gImages=new Array;
var gIndex=0;
var DCS=new Object();
var WT=new Object();
var DCSext=new Object();
var gQP=new Array();

var gDomain="wtrs.101com.com";
var gDcsId="dcs5zy07n1000047s9x2kzeeq_6m4s";

if ((typeof(gConvert)!="undefined")&&gConvert&&(document.cookie.indexOf(gFpc+"=")==-1)){
	document.write("<SCR"+"IPT Language='JavaScript' SRC='"+"http"+(window.location.protocol.indexOf('https:')==0?'s':'')+"://"+gDomain+"/"+gDcsId+"/wtid.js"+"'></SCR"+"IPT>");
}
//-->
</script><script language="JavaScript" src="article_files/wtid.js"></script>

<script language="Javascript"><!--
function dcsVar(){
	var dCurrent=new Date();
	WT.tz=dCurrent.getTimezoneOffset()/60*-1;
	if (WT.tz==0){
		WT.tz="0";
	}
	WT.bh=dCurrent.getHours();
	WT.ul=navigator.appName=="Netscape"?navigator.language:navigator.userLanguage;
	if (typeof(screen)=="object"){
		WT.cd=navigator.appName=="Netscape"?screen.pixelDepth:screen.colorDepth;
		WT.sr=screen.width+"x"+screen.height;
	}
	if (typeof(navigator.javaEnabled())=="boolean"){
		WT.jo=navigator.javaEnabled()?"Yes":"No";
	}
	if (document.title){
		WT.ti=document.title;
	}
	WT.js="Yes";
	if (typeof(gVersion)!="undefined"){
		WT.jv=gVersion;
	}
	if (document.body&&document.body.addBehavior){
		document.body.addBehavior("#default#clientCaps");
		if (document.body.connectionType){
			WT.ct=document.body.connectionType;
		}
		document.body.addBehavior("#default#homePage");
		WT.hp=document.body.isHomePage(location.href)?"1":"0";
	}
	if (parseInt(navigator.appVersion)>3){
		if ((navigator.appName=="Microsoft Internet Explorer")&&document.body){
			WT.bs=document.body.offsetWidth+"x"+document.body.offsetHeight;
		}
		else if (navigator.appName=="Netscape"){
			WT.bs=window.innerWidth+"x"+window.innerHeight;
		}
	}
	WT.fi="No";
	if (window.ActiveXObject){
		if ((typeof(gFV)!="undefined")&&(gFV.length>0)){
			WT.fi="Yes";
			WT.fv=gFV;
		}
	}
	else if (navigator.plugins&&navigator.plugins.length){
		for (var i=0;i<navigator.plugins.length;i++){
			if (navigator.plugins[i].name.indexOf('Shockwave Flash')!=-1){
				WT.fi="Yes";
				WT.fv=navigator.plugins[i].description.split(" ")[2];
				break;
			}
		}
	}
	WT.sp="@@SPLITVALUE@@";
	DCS.dcsdat=dCurrent.getTime();
	DCS.dcssip=window.location.hostname;
	DCS.dcsuri=window.location.pathname;
	if (window.location.search){
		DCS.dcsqry=window.location.search;
		if (gQP.length>0){
			for (var i=0;i<gQP.length;i++){
				var pos=DCS.dcsqry.indexOf(gQP[i]);
				if (pos!=-1){
					var front=DCS.dcsqry.substring(0,pos);
					var end=DCS.dcsqry.substring(pos+gQP[i].length,DCS.dcsqry.length);
					DCS.dcsqry=front+end;
				}
			}
		}
	}
	if ((window.document.referrer!="")&&(window.document.referrer!="-")){
		if (!(navigator.appName=="Microsoft Internet Explorer"&&parseInt(navigator.appVersion)<4)){
			DCS.dcsref=window.document.referrer;
		}
	}
}

function A(N,V){
	return "&"+N+"="+dcsEscape(V);
}

function dcsEscape(S){
	if (typeof(RE)!="undefined"){
		var retStr = new String(S);
		for (R in RE){
			retStr = retStr.replace(RE[R],R);
		}
		return retStr;
	}
	else{
		return escape(S);
	}
}

function dcsCreateImage(dcsSrc){
	if (document.images){
		gImages[gIndex]=new Image;
		if ((typeof(gHref)!="undefined")&&(gHref.length>0)){
			gImages[gIndex].onload=gImages[gIndex].onerror=dcsLoadHref;
		}
		gImages[gIndex].src=dcsSrc;
		gIndex++;
	}
	else{
		document.write('<IMG BORDER="0" NAME="DCSIMG" WIDTH="1" HEIGHT="1" SRC="'+dcsSrc+'">');
	}
}

function dcsMeta(){
	var elems;
	if (document.all){
		elems=document.all.tags("meta");
	}
	else if (document.documentElement){
		elems=document.getElementsByTagName("meta");
	}
	if (typeof(elems)!="undefined"){
		for (var i=1;i<=elems.length;i++){
			var meta=elems.item(i-1);
			if (meta.name){
				if (meta.name.indexOf('WT.')==0){
					WT[meta.name.substring(3)]=meta.content;
				}
				else if (meta.name.indexOf('DCSext.')==0){
					DCSext[meta.name.substring(7)]=meta.content;
				}
				else if (meta.name.indexOf('DCS.')==0){
					DCS[meta.name.substring(4)]=meta.content;
				}
			}
		}
	}
}

function dcsTag(){
	var P="http"+(window.location.protocol.indexOf('https:')==0?'s':'')+"://"+gDomain+(gDcsId==""?'':'/'+gDcsId)+"/dcs.gif?";
	for (N in DCS){
		if (DCS[N]) {
			P+=A(N,DCS[N]);
		}
	}
	for (N in WT){
		if (WT[N]) {
			P+=A("WT."+N,WT[N]);
		}
	}
	for (N in DCSext){
		if (DCSext[N]) {
			P+=A(N,DCSext[N]);
		}
	}
	if (P.length>2048&&navigator.userAgent.indexOf('MSIE')>=0){
		P=P.substring(0,2040)+"&WT.tu=1";
	}
	dcsCreateImage(P);
}

function dcsFunc(func){
	if (typeof(window[func])=="function"){
		window[func]();
	}
}

dcsVar();
dcsMeta();
dcsFunc("dcsAdv");
dcsTag();
//-->
</script><!-- END OF SmartSource Data Collector  TAG -->


	

<script type="text/Javascript" src="article_files/utils.js"></script>
		<meta name="pubDate" content="2001/8/01">
		<meta name="pubDisDate" content="8/01/01">
		<meta name="summary" content="Most OO practitioners recognize the value of Design by Contract as a methodology for improving software quality. It is at the heart of the Eiffel language and the Object Constraint Language of UML. However, there are precious few languages that provide such intrinsic support for Design by Contract, and C++ is one language that does not. This article presents two new mechanisms for emulating Design by Contract in C++ that take advantage of language features defined in the recent standard, and for which widespread compiler support is now becoming available. One mechanism has been used in the development of software components in Computational Physics and is based on the Standard Template Library (STL); the other provides Design by Contract support across an inheritance hierarchy in C++ in accordance with the Liskov Substitutability Principle.">
		
<script type="text/javascript">
<!--
	var AAMB1 = "";
	var AAMB2 = "";
	var AAMB3 = "";
	var AAMB4 = "";
	var AAMB5 = "";
	var AAMB6 = "";
	var AAMB7 = "";
	var AAMB8 = "";
	var AAMB9 = "";
	var AAMB10 = "";
	var AAMB11 = "";
	var AAMB12 = "";
	var AAMB13 = "";
	var AAMB14 = "";
	var AAMB15 = "";
	var AAMB16 = "";
	var AAMB17 = "";
	var AAMB18 = "";
	var AAMB19 = "";
	var AAMB20 = "";
	var AAMB21 = "";
	var AAMB22 = "";
	var AAMB23 = "";
	var AAMB24 = "";
	var AAMB25 = "";
	
//-->
</script>

<script type="text/javascript"> 
	<!-- Hide from old browsers
	var aamRnd = Math.round(Math.random() * 100000000);
	adserver = "http://ad101com.adbureau.net/bserver";
	
	
	allAdTags = "/AAMALL/site=adt/area=article/aID=4593/TOPIC=/acc_random=" + aamRnd + "/pageid=" + aamRnd;
	
	var zone = "article/aID=4593/TOPIC="
	 
	ad1 = "/AAMB1/aamsz=160x600/pos=l01"
	
	//ad2 = "/AAMB2/aamsz=160x300/pos=l02";
	ad3 = "/AAMB3/aamsz=336x280/pos=m02";	
	ad4 = "/AAMB4/aamsz=728x90/pos=m03";
	
	ad5 = "/AAMB5/aamsz=160x600/pos=r01";
	ad6 = "/AAMB6/aamsz=336x280/pos=r02";	
	ad7 = "/AAMB7/aamsz=125x125/pos=r03";
	ad8 = "/AAMB8/aamsz=125x125/pos=r04";
	ad9 = "/AAMB9/aamsz=160x74/pos=r05";
	
	ad10  = "/AAMB10/aamsz=textlink/pos=tx01";
	ad11  = "/AAMB11/aamsz=textlink/pos=tx02";
	ad12  = "/AAMB12/aamsz=textlink/pos=tx03";
	ad13 = "/AAMB13/aamsz=textlink/pos=tx04";
	ad14 = "/AAMB14/aamsz=textlink/pos=tx05";
	ad15 = "/AAMB15/aamsz=textlink/pos=tx06";
	ad16 = "/AAMB16/aamsz=textlink/pos=tx07";
	ad17 = "/AAMB17/aamsz=textlink/pos=tx08";
	ad18 = "/AAMB18/aamsz=textlink/pos=tx09";
	ad19 = "/AAMB19/aamsz=textlink/pos=tx10";	
	ad21 = "/AAMB21/aamsz=textlink/pos=tx11";
	ad22 = "/AAMB22/aamsz=textlink/pos=tx12";
	ad23 = "/AAMB23/aamsz=textlink/pos=tx13";
	ad24 = "/AAMB24/aamsz=textlink/pos=tx14";
	ad25 = "/AAMB25/aamsz=textlink/pos=tx15";	
	
	ad20 = "/AAMB20/aamsz=wptextlink/pos=wptx01";
	
	//ad21 = "/AAMB21/aamsz=dogear/pos=dog01"
	
	document.write('<SCR' + 'IPT SRC="' + adserver + allAdTags  + ad1 + ad3 + ad4 + ad5 + ad6 + ad7 + ad8 + ad9 + ad10 + ad11 + ad12 + ad13 + ad14 + ad15 + ad16 + ad17 + ad18 + ad19 + ad20 + ad21 + ad22 + ad23 + ad24 + ad25 + '?" type="text/JavaScript" language="JavaScript">');
	document.write('</SCR' + 'IPT>');

	// End Hide -->
</script><script src="article_files/postx15" type="text/JavaScript" language="JavaScript"></script>

		
		<style type="text/css">
		<!--
		@import url(../css/appTrends.css);
		--></style><!--[if IE]>
            <script type="text/javascript" src="script/iefix.js"></script>
        <![endif]-->
		
		
        		
		<script type="text/javascript">
		function validateComment()   {
			var frm = document.frmComment;
			if (frm.comment.value=='') {
				alert("Please enter a comment before submitting.");
				frm.comment.focus();
				return false;
			}
			
			if (frm.comment.value.length > 2000) {
				alert("The comments cannot be more than 2000 characters including spaces");
				frm.comment.focus();
				return false;
			}
			
			return true;
		}
		
		</script></head><noscript>
<IMG ALT="" BORDER="0" NAME="DCSIMG" WIDTH="1" HEIGHT="1"
SRC="http://wtrs.101com.com/dcs5zy07n1000047s9x2kzeeq_6m4s/njs.gif?dcsuri=/nojavascript&amp;WT.js=No">
</noscript><body class="article">
		<div id="outerWrap">
			<!-- HEADER -->
			
<div id="dogear"></div>
<div id="header">
	<h1><a href="http://www.adtmag.com/index.aspx"><span>Application Trends</span></a></h1>
	<!-- BEGIN SEARCH NAV -->
	<div id="adtSearch">
		<form method="get" id="searchForm" action="http://search.adtmag.com/search.asp">
			<fieldset>
				<label for="ssite">SEARCH:</label> <input name="cmd" value="search" type="hidden">
				<input name="SearchForm" value="%%SearchForm%%" type="hidden"> 				
				<input name="fuzzy" value="" type="hidden"> 
				<input name="fuzziness" value="4" type="hidden">
				<input name="stemming" value="" type="hidden"> 
				<input name="phonic" value="" type="hidden">
				<input name="natLang" value="" type="hidden"> 
				<input name="maxFiles" value="500" type="hidden">
				<input name="autoStopLimit" value="500" type="hidden"> 
				<input name="sort" value="Date" type="hidden">
				<input id="srcrequest" name="srcrequest" class="txt" type="text"> 
				<input name="submit" value="Go" src="article_files/adt_btn_go2.gif" alt="GO" class="btn" type="image">
			</fieldset>
		</form>
	</div>
	<!-- END SEARCH NAV -->
	<div id="subNav">
	<a href="http://www.adtmag.com/advertise.aspx">Advertise</a> 
	| <a href="https://newsletters.1105pubs.com/nl/SDG.do?NL=4904,4905,4906,4907,4908,5480&amp;PC=HWEB05" target="_blank">Subscribe</a> 
	| <a href="http://www.adtmag.com/about.aspx">About Us</a></div>
</div>
<script language="JavaScript">
	<!-- Hide from old browsers
	// Modify to reflect site specifics
	adserver = "http://ad101com.adbureau.net";
	target = "/site=adt/area="+ zone + "/aamsz=dogear/pos=dog01";
	// Cache-busting and pageid values
	random = Math.round(Math.random() * 100000000);
	if (!pageNum) var pageNum = Math.round(Math.random() * 100000000);
	document.write('<SCR');
	document.write('IPT SRC="' + adserver + '/jserver/acc_random=' + random +
	target + "/pageid=" + pageNum + '">');
	document.write('</SCR');
	document.write('IPT>');
	// End Hide -->
</script><script src="article_files/pageid97781495"></script><a href="http://ad101com.adbureau.net/accipiter/adclick/CID=fffffffcfffffffcfffffffc/acc_random=33256635/site=adt/area=article/aID=4593/TOPIC=/aamsz=dogear/pos=dog01/pageid=97781495" target="_BLANK"><img src="article_files/AE0.gif" border="0"></a>


			<!-- HEADER -->
			<!-- TOP NAV -->
			
<div id="mainNav">
	<ul>
		<li class="home" id="first">
			<a href="http://www.adtmag.com/index.aspx">HOME</a></li>
		<li class="xfrm">
			<a href="http://www.adtmag.com/section.aspx?c=72">SPECIAL REPORT</a></li>
		<li class="nws">
			<a href="http://www.adtmag.com/section.aspx?t=6">NEWS</a></li>
	</ul>
	<div style="padding: 3px 10px; color: white;" align="right"><i>Welcome to Application Development Trends Online</i></div>
</div>

			<!-- TOP NAV -->
			<!-- BEGIN MAIN CONTENT -->
			<div id="sideBar">
				<!-- LEFT COLUMN -->
				
<div class="module">
	<h4>Topics</h4>
	<ul>
		<li><a href="http://www.adtmag.com/topic.aspx?k=SOA">SOA</a></li>
		<li><a href="http://www.adtmag.com/topic.aspx?k=JAVA">Java</a></li>
		<li><a href="http://www.adtmag.com/topic.aspx?k=IT+Management">IT Management</a></li>
		<li><a href="http://www.adtmag.com/topic.aspx?k=Application+Development">App Development</a></li>
		<li><a href="http://www.adtmag.com/topic.aspx?k=Open+Source">Open Source</a></li>
		<li><a href="http://www.adtmag.com/topic.aspx?k=Security">Security</a></li>
		<li><a href="http://www.adtmag.com/topic.aspx?k=Business+Intelligence">Business Intelligence</a></li>
		<li><a href="http://www.adtmag.com/topic.aspx?k=Outsourcing">Outsourcing</a></li>
		<li><a href="http://www.adtmag.com/topic.aspx?k=Collaboration">Collaboration</a></li>
		<li><a href="http://www.adtmag.com/topic.aspx?k=Web+Services">Web Services</a></li>
	</ul>
</div>
<div class="module">
	<h4><a href="http://www.adtmag.com/newsletter/index.aspx" class="titleLink">Newsletters</a></h4>
	<ul>
		<li><a href="http://www.adtmag.com/newsletter/newsletter.aspx?nl=EADT">AppTrends</a></li>
		<li><a href="http://www.adtmag.com/newsletter/newsletter.aspx?nl=datatrends">DataTrends</a></li>
		<li><a href="http://www.adtmag.com/newsletter/newsletter.aspx?nl=JDT">JavaTrends</a></li>
		<li><a href="http://www.adtmag.com/newsletter/newsletter.aspx?nl=PRT">ProgrammingTrends</a></li>
		<li><a href="http://www.adtmag.com/newsletter/newsletter.aspx?nl=SOATrends">SOATrends</a></li>
	</ul>
</div>
<div class="module">
	<h4>Resources</h4>
	<ul>
		<li><a href="http://www.adtmag.com/techlib/index.aspx">Tech Library</a></li>		
		<li><a href="http://www.adtmag.com/techlib/landing.aspx?t=2">Webinars</a></li>			
	</ul>
</div>

<!-- BEGIN LEFT COLUMN SKYSCRAPER -->
	

<div style="padding-top: 2px;"><a href="http://reddevnews.com/techbusiness/" target="_blank"><img src="article_files/mtb_techbusiness_go_160.gif" alt="TechBusiness: Resources for Innovation Through Software Technology" border="0" height="60" width="160"></a></div>

<div class="skyScraper">
	<script type="text/javascript">
		  <!-- Hide from old browsers
			document.write (AAMB1)
		  // End Hide -->
	</script><iframe src="article_files/relocate." marginwidth="0" marginheight="0" hspace="0" vspace="0" bordercolor="#000000" frameborder="0" height="600" scrolling="no" width="160">&lt;SCRIPT
language='JavaScript1.1'
SRC='http://ad.doubleclick.net/adj/N815.adtmag/B2382392.2;abr=!ie;;click=http://ad101com.adbureau.net/accipiter/adclick/CID=0000320760246e6600000000/aamsz=160x600/pos=l01/site=adt/area=article/aID=4593/TOPIC=/acc_random=76799364/pageid=76799364/relocate=;sz=160x600;ord=76799364?'&gt;&lt;/SCRIPT&gt;&lt;NOSCRIPT&gt;&lt;A
HREF='http://ad101com.adbureau.net/accipiter/adclick/CID=0000320760246e6600000000/aamsz=160x600/pos=l01/site=adt/area=article/aID=4593/TOPIC=/acc_random=76799364/pageid=76799364'TARGET='_blank'&gt;&lt;IMG
SRC='http://ad.doubleclick.net/ad/N815.adtmag/B2382392.2;abr=!ie4;abr=!ie5;sz=160x600;ord=76799364?'BORDER=0
WIDTH=160 HEIGHT=600 ALT="Click Here"&gt;&lt;/A&gt;&lt;/NOSCRIPT&gt;</iframe><img src="article_files/pageid76799364_002" border="0" height="1" width="1">
</div>

<script type="text/javascript" src="article_files/swfobject.js"></script>

<div id="flashcontent" class="skyScraper">
		<object classid="clsid:d27cdb6e-ae6d-11cf-96b8-444553540000" codebase="http://fpdownload.macromedia.com/pub/shockwave/cabs/flash/swflash.cab#version=6,0,0,0" id="dice" viewastext="" align="middle" height="300" width="160"> 
        <param name="movie" value="/graphics/flash/dice_utility.swf?flash_style=adtmag&amp;flash_width=160&amp;flash_height=300&amp;clickTag=http://ad.doubleclick.net/clk;63339104;15510779;h?http://www.dice.com/">

        <param name="quality" value="high"> 
        <param name="scale" value="noscale"> 
        <param name="bgcolor" value="#E9E8E8"> 
        <embed src="article_files/dice_utility.swf" quality="high" bgcolor="#E9E8E8" name="dice" type="application/x-shockwave-flash" pluginspage="http://www.macromedia.com/go/getflashplayer" align="middle" height="300" width="160"> 
</object>
<br>
<script type="text/javascript">
 <!-- Hide from old browsers
	document.write ('<a href="http://ad.doubleclick.net/jump/N1841.1105Media/B2100571.21;sz=1x1;ord=' + aamRnd + '?">')
	document.write ('<img src="http://ad.doubleclick.net/ad/N1841.1105Media/B2100571.21;sz=1x1;ord=' + aamRnd + '?" border=0 width=1 height=1 alt="Click Here"></a>')
// End Hide -->
	</script><a href="http://ad.doubleclick.net/jump/N1841.1105Media/B2100571.21;sz=1x1;ord=76799364?"><img src="article_files/B2100571.21" alt="Click Here" border="0" height="1" width="1"></a>
</div>

<script type="text/javascript">
	var so = new SWFObject("/graphics/flash/dice_utility.swf", "dice", "160", "300", "8", "#ffffff"); 
	so.addVariable("flash_width", "160"); 
	so.addVariable("flash_height", "300"); 
	so.addVariable("flash_style", "redmond"); 
	so.addVariable("clickTag", "http://ad.doubleclick.net/clk;63339104;15510779;h?"); 
	so.write("flashcontent");
</script>

<!-- BEGIN LEFT COLUMN SKYSCRAPER -->

<div class="module">
	<h4>Services</h4>
	<ul>
		<li><a href="https://newsletters.1105pubs.com/nl/SDG.do?NL=4904,4905,4906,4907,4908&amp;PC=HWEB05" target="_blank">Customer Service</a></li>
		<li><a href="http://www.adtmag.com/contact.aspx">Contact Us</a></li>
		<li><a href="http://www.adtmag.com/about.aspx">About Us</a></li>
		<li><a href="http://www.adtmag.com/advertise.aspx">Advertise</a></li>
		<li><a href="http://www.adtmag.com/services/servicesList.aspx?t=58">Press Releases</a></li>
	</ul>
</div>
<div class="module">
	<h4>Archives</h4>
	<ul>
		<li><a href="http://www.adtmag.com/magazine/toc.aspx">App Development Trends</a></li>
		<li><a href="http://www.adtmag.com/java/index.aspx">Java Report</a></li>
		<li><a href="http://www.adtmag.com/joop/index.aspx">JOOP</a></li>
	</ul>
</div>
				<!-- LEFT COLUMN -->
			</div>
			<div name="container" id="container">
				<!-- TOP LEADERBOARD -->
				
<div class="banners" id="topleader">
	<script language="JavaScript">
	<!-- Hide from old browsers
		// Modify to reflect site specifics
		adserver = "http://ad101com.adbureau.net";
		target = "/site=adt/area="+ zone + "/aamsz=728x90/pos=m01";
		// Cache-busting and pageid values		
		document.write('<SCR');
		document.write('IPT SRC="' + adserver + '/jserver/acc_random=' + aamRnd +
		target + "/pageid=" + aamRnd + '">');
		document.write('</SCR');
		document.write('IPT>');
	// End Hide -->
	</script><script src="article_files/pageid76799364_003"></script><a href="http://ad101com.adbureau.net/accipiter/adclick/CID=0000367460246e6600000000/acc_random=76799364/site=adt/area=article/aID=4593/TOPIC=/aamsz=728x90/pos=m01/pageid=76799364"><img src="article_files/hero_banner_728x90.gif" alt="Curl" border="0" height="90" width="728"></a>
<noembed>&lt;A
HREF="http://ad101com.adbureau.net/accipiter/adclick/CID=0000367460246e6600000000/acc_random=76799364/site=adt/area=article/aID=4593/TOPIC=/aamsz=728x90/pos=m01/pageid=76799364"&gt;&lt;IMG
SRC="http://ad101com-images.adbureau.net/ad101com/adt/Curl/hero_banner_728x90.gif"
ALT="Curl" WIDTH="728" HEIGHT="90" BORDER="0"&gt;&lt;/A&gt;</noembed>
<noscript><A
HREF="http://ad101com.adbureau.net/accipiter/adclick/CID=0000367460246e6600000000/acc_random=76799364/site=adt/area=article/aID=4593/TOPIC=/aamsz=728x90/pos=m01/pageid=76799364"><IMG
SRC="http://ad101com-images.adbureau.net/ad101com/adt/Curl/hero_banner_728x90.gif"
ALT="Curl" WIDTH="728" HEIGHT="90" BORDER="0"></A></noscript>

</div>

				<!-- TOP LEADERBOARD -->
				<!-- BEGIN EXTRA CONTENT -->
				<div id="xContent">
					<div class="pContent">
						<h2>Application Development Trends Articles</h2>
						
						<!-- ARTICLE -->
						<div>
							<h3>Supporting Design by Contract in C++</h3>
<p class="date">8/1/2001</p>
<p class="author">By David Maley, Ivor Spence</p>

<b>Most object-oriented (OO) practitioners recognize the value of
Design by Contract as a methodology for improving software quality. It
is at the heart of the Eiffel language and of the Object Constraint
Language (OCL) of UML. However, there are precious few languages that
provide such intrinsic support for Design by Contract, and C++ is one
language that does not. This article presents two new mechanisms for
emulating Design by Contract in C++ that take advantage of language
features defined in the recent standard, and for which widespread
compiler support is now becoming available. One mechanism has been used
in the development of software components in Computational Physics and
is based on the Standard Template Library (STL); the other provides
Design by Contract support across an inheritance hierarchy in C++ in
accordance with the Liskov Substitutability Principle(LSP).<sup><font color="#cc3300">1</font></sup></b><p>

Click <a href="http://www.101com.com/files/pub/joopmag/maleyappendix1.zip">here</a> to download the Appendix to this article.</p><p>
Contracts document the benefits and obligations of an agreement
involving two parties. The document protects both parties. It protects
the client by specifying the minimum that should be done and states
that the client is entitled to receive a certain result. It protects
the supplier by specifying how little is acceptable and that the
contractor must not be liable for failing to carry out tasks outside of
the specified scope. When things go wrong, the contract indicates where
the blame lies.</p><p>
Design by Contract relies on the programmer making assertions about the behavior of <a itxtdid="4422588" target="_blank" href="#" style="border-bottom: 0.075em solid darkgreen; font-weight: normal; font-size: 100%; text-decoration: underline; color: darkgreen; background-color: transparent; padding-bottom: 1px;" classname="iAs" class="iAs">software</a>,
both at the level of individual function execution and object state,
and also at higher levels. These assertions may be considered to form a
contract between the software supplier and the software client.</p><p>
There are three principal types of assertion in a software contract:
postconditions, preconditions, and invariants. Functions must have
desirable properties in order to attract clients, and these are
documented in the function's postcondition. Functions are also able to
state the conditions under which those desirable properties will be
delivered; these are documented in the function's precondition.
Properties that remain unaltered after function execution (although
they may not be satisfied at some intermediate stage) are captured by
invariants.</p><p>
The notion of assertions was developed by Hoare,<sup><font color="#cc3300">2,3</font></sup> Floyd,<sup><font color="#cc3300">4</font></sup> and Dijkstra,<sup><font color="#cc3300">5</font></sup>
after initial work (according to Hoare) by Alan Turing. Unfortunately,
many programming languages are very limited in the support they provide
for assertion checking, and C++ is one of them. However, C++ is a rich
and diverse language supporting a multi-paradigm approach to design.
The more recent features of the language provide new opportunities to
add Design by Contract support. In this article, following a survey of
previous suggestions, two techniques for supporting Design by Contract
in C++ are outlined.</p><p>
The first technique deals with the need to observe the Liskov
Substitutability Principle when applying Design by Contract across an
inheritance hierarchy. Out of necessity, it makes some rudimentary
requirements on the declaration of the classes involved. The second
technique, while being less general (it is intended for classes whose
internal <a itxtdid="4241528" target="_blank" href="#" style="border-bottom: 0.075em solid darkgreen; font-weight: normal; font-size: 100%; text-decoration: underline; color: darkgreen; background-color: transparent; padding-bottom: 1px;" classname="iAs" class="iAs">data</a>
structure is based on the containers of the STL), makes no requirements
on the client. It can be extended to automatically generate (simply by
instantiation) an object hierarchy that parallels the data
sub-structure of an existing object, and can provide a platform from
which to administer tasks such as constraint monitoring, object update,
and object display.<sup><font color="#cc3300">6</font></sup></p><p>
There is no consideration given to the issue of what is to be done once
constraint violation is detected: an exception is thrown as a default
action, and the opportunity to define what action should be taken is
provided. This is not because the issue is insignificant, but because
it is beyond the scope of the discussion.</p><p>
<b>Previous work on supporting Design by Contract in C++</b><br>
There have been a number of different approaches to supporting Design
by Contract in C++: use the existing language constructs to provide a
support mechanism; use macros to support the inclusion and monitoring
of constraints; effectively extend the syntax of the language by
writing a PreProcessor that converts non-C++ constraint expressions
into C++ before compilation; and proposing language extensions.</p><p>
The Percolation pattern<sup><font color="#cc3300">7</font></sup>
uses existing language constructs in a straightforward structure that
yields the same checking as built-in assertion inheritance. The pattern
relies on the redefinitions observing a protocol in which they
incorporate calls to base <a itxtdid="4499192" target="_blank" href="#" style="border-bottom: 0.075em solid darkgreen; font-weight: normal; font-size: 100%; text-decoration: underline; color: darkgreen; background-color: transparent; padding-bottom: 1px;" classname="iAs" class="iAs">class</a>
functions and observe the Liskov Substitutability Principle in doing
so. The Liskov Substitutability Principle states the conditions under
which the constraints on a class method of a derived class may be
redefined. If the derived class is to be considered a subtype of the
base class (and an instance of it can therefore be substituted wherever
an instance of the base class occurs), the following must apply:
preconditions get no stronger, invariants and postconditions get no
weaker. The Percolation pattern requires discipline on the part of the
programmer that can have implications for maintenance.</p><p>
A simulation of the Eiffel mechanism using macros has been put forward by Welch and Strong.<sup><font color="#cc3300">8</font></sup> Macros are defined that serve the purpose of the corresponding Eiffel language constructs.</p><p>
App.<sup><font color="#cc3300">9</font></sup>
is an Annotation PreProcessor for C/C++ programs developed in Unix
environments. It recognizes assertions that appear as annotations of
the source text, written using extended comment indicators. It
recognizes three assertion constructs: <i>assume</i> (preconditions), <i>promise</i> (postconditions), <i>return</i> (specifies a constraint on the return value of a function), and a fourth construct, <i>assert,</i>
that specifies a constraint on an intermediate state of a function
body. It also provides three constructs additional to C/C++ syntax to
enhance the expressivity of constraints: <i>all, some,</i> and <i>in</i>
provide universal quantification, existential quantification, and
reference to the value of a variable prior to function execution
respectively.</p><p>
Gnu's Nana<sup><font color="#cc3300">10</font></sup>
is a library that provides support for assertion checking and logging
in a space- and time-efficient manner. The aim is to put common good
practice into a library that can be reused. It was inspired by App.
Assertion checking and logging code can be implemented using a
debugger, rather than inline code with a large saving in code space.
There is some STL support in that there is a special version of the
macros involved that uses the iteration protocol to process containers.</p><p>
Annotated C++<sup><font color="#cc3300">11</font></sup>
was a research project undertaken by Marshall Cline and Doug Lea. A++
was intended to provide designers with a means to express a variety of
semantic constraints and properties of C++ classes. It extends the base
type <a itxtdid="4392222" target="_blank" href="#" style="border-bottom: 0.075em solid darkgreen; font-weight: normal; font-size: 100%; text-decoration: underline; color: darkgreen; background-color: transparent; padding-bottom: 1px;" classname="iAs" class="iAs">system</a>
to support several forms each of preconditions, postconditions,
assertions, and invariants, along with a richer set of "primitive"
types and constructs that are useful for expressing such constraints.</p><p>
Although exlC++<sup><font color="#cc3300">12</font></sup>
is a language extension that bears a lot of similarity to much of the
work discussed so far, the work of Porat and Fertig includes a number
of new and interesting observations. Some of these are a result of
taking the freedom to work outside of the existing language. Subsequent
to the agreement of the ISO/ANSI C++ Standard, this decision means
exlC++ is unlikely to make further contributions to the debate.</p><p>
None of the approaches outlined save the user from having to explicitly
deal with handling the consequences of inheritance on assertions. The
approach outlined in this article overcomes this by using constrained
genericity, utilizing new language features such as partial
specialization and inner template classes.</p><p>


</p><table border="2" bordercolor="Black" cellpadding="2" cellspacing="0" frame="box" width="500">
<tbody><tr>
    <td colspan="7" bgcolor="Black"><font color="white" face="Arial, Helvetica" size="2"><b>Table 1. Characteristics of the different approaches to design by contract.</b></font></td>
</tr>
<tr>
    <td>&nbsp;</td>
    <td><font face="Arial, Helvetica" size="2"><b>Percolation (Binder)</b></font></td>
    <td><font face="Arial, Helvetica" size="2"><b>App (Rosenblum)</b></font></td>
    <td><font face="Arial, Helvetica" size="2"><b>A++ (Cline &amp; Lea)</b></font></td>
    <td><font face="Arial, Helvetica" size="2"><b>exlC++ (Porat &amp; Fertig)</b></font></td>
    <td><font face="Arial, Helvetica" size="2"><b>Nana (GNU)</b></font></td>
    <td><font face="Arial, Helvetica" size="2"><b>Macros (Welch &amp; Strong)</b></font></td>
</tr>
<tr>
    <td><font face="Arial, Helvetica" size="2"><b>UNDESIRABLE</b></font></td>
    <td>&nbsp;</td>
    <td>&nbsp;</td>
    <td>&nbsp;</td>
    <td>&nbsp;</td>
    <td>&nbsp;</td>
    <td>&nbsp;</td>
</tr>
<tr>
    <td><font face="Arial, Helvetica" size="2">Requires explicit coding to support the Liskov Substitutability Principle.</font></td>
    <td><font face="Arial, Helvetica" size="2">Yes</font></td>
    <td><font face="Arial, Helvetica" size="2">Yes</font></td>
    <td>&nbsp;</td>
    <td>&nbsp;</td>
    <td><font face="Arial, Helvetica" size="2">Yes</font></td>
    <td><font face="Arial, Helvetica" size="2">Yes</font></td>
</tr>
<tr>
    <td><font face="Arial, Helvetica" size="2">Clutters the class namespace with additional names for precondition and
postcondition functions.</font></td>
    <td><font face="Arial, Helvetica" size="2">Yes</font></td>
    <td>&nbsp;</td>
    <td>&nbsp;</td>
    <td>&nbsp;</td>
    <td>&nbsp;</td>
    <td>&nbsp;</td>
</tr>
<tr>
    <td><font face="Arial, Helvetica" size="2">Can affect program execution (potentially has side-effects-"letting the
imperative fox into the applicative chicken coop").</font></td>
    <td><font face="Arial, Helvetica" size="2">Yes</font></td>
    <td><font face="Arial, Helvetica" size="2">Yes</font></td>
    <td><font face="Arial, Helvetica" size="2">Yes</font></td>
    <td><font face="Arial, Helvetica" size="2">Yes</font></td>
    <td><font face="Arial, Helvetica" size="2">Yes</font></td>
    <td><font face="Arial, Helvetica" size="2">Yes</font></td>
</tr>
<tr>
    <td><font face="Arial, Helvetica" size="2">Does not offer granularity of control over which assertions are executed.</font></td>
    <td><font face="Arial, Helvetica" size="2">Yes</font></td>
    <td><font face="Arial, Helvetica" size="2">Yes</font></td>
    <td>&nbsp;</td>
    <td>&nbsp;</td>
    <td>&nbsp;</td>
    <td>&nbsp;</td>
</tr>
<tr>
    <td><font face="Arial, Helvetica" size="2">DEBATABLE</font></td>
    <td>&nbsp;</td>
    <td>&nbsp;</td>
    <td>&nbsp;</td>
    <td>&nbsp;</td>
    <td>&nbsp;</td>
    <td>&nbsp;</td>
</tr>
<tr>
    <td><font face="Arial, Helvetica" size="2">Recognizes and supports the distinction between legality and coherence.</font></td>
    <td><font face="Arial, Helvetica" size="2">No</font></td>
    <td><font face="Arial, Helvetica" size="2">No</font></td>
    <td>&nbsp;</td>
    <td><font face="Arial, Helvetica" size="2">No</font></td>
    <td><font face="Arial, Helvetica" size="2">No</font></td>
    <td><font face="Arial, Helvetica" size="2">No</font></td>
</tr>
<tr>
    <td><font face="Arial, Helvetica" size="2">Groups semantic information</font></td>
    <td><font face="Arial, Helvetica" size="2">No</font></td>
    <td>&nbsp;</td>
    <td>&nbsp;</td>
    <td>&nbsp;</td>
    <td><font face="Arial, Helvetica" size="2">No</font></td>
    <td><font face="Arial, Helvetica" size="2">No</font></td>
</tr>
<tr>
    <td><font face="Arial, Helvetica" size="2">DESIRABLE</font></td>
    <td>&nbsp;</td>
    <td>&nbsp;</td>
    <td>&nbsp;</td>
    <td>&nbsp;</td>
    <td>&nbsp;</td>
    <td>&nbsp;</td>
</tr>
<tr>
    <td><font face="Arial, Helvetica" size="2">Implementation readily available.</font></td>
    <td>&nbsp;</td>
    <td><font face="Arial, Helvetica" size="2">No</font></td>
    <td><font face="Arial, Helvetica" size="2">No</font></td>
    <td><font face="Arial, Helvetica" size="2">No</font></td>
    <td>&nbsp;</td>
    <td>&nbsp;</td>
</tr>
<tr>
    <td><font face="Arial, Helvetica" size="2">Provides postconditions with access to the return value of the function.</font></td>
    <td><font face="Arial, Helvetica" size="2">No</font></td>
    <td>&nbsp;</td>
    <td>&nbsp;</td>
    <td>&nbsp;</td>
    <td><font face="Arial, Helvetica" size="2">No</font></td>
    <td><font face="Arial, Helvetica" size="2">No</font></td>
</tr>
<tr>
    <td><font face="Arial, Helvetica" size="2">Provides postconditions with access to the state of the object at the
commencement of the function (the old value) without explicit coding.</font></td>
    <td><font face="Arial, Helvetica" size="2">No</font></td>
    <td>&nbsp;</td>
    <td>&nbsp;</td>
    <td>&nbsp;</td>
    <td><font face="Arial, Helvetica" size="2">No</font></td>
    <td><font face="Arial, Helvetica" size="2">No</font></td>
</tr>
<tr>
    <td><font face="Arial, Helvetica" size="2">Checking of the invariant is carried out in the precondition and
postcondition.</font></td>
    <td><font face="Arial, Helvetica" size="2">No</font></td>
    <td><font face="Arial, Helvetica" size="2">No</font></td>
    <td>&nbsp;</td>
    <td>&nbsp;</td>
    <td><font face="Arial, Helvetica" size="2">No</font></td>
    <td><font face="Arial, Helvetica" size="2">No</font></td>
</tr>
<tr>
    <td><font face="Arial, Helvetica" size="2">Accommodates functions other than regular class member functions
(static members, friends, global functions).</font></td>
    <td><font face="Arial, Helvetica" size="2">No</font></td>
    <td>&nbsp;</td>
    <td><font face="Arial, Helvetica" size="2">No</font></td>
    <td>&nbsp;</td>
    <td>&nbsp;</td>
    <td>&nbsp;</td>
</tr>
<tr>
    <td><font face="Arial, Helvetica" size="2">Supports arbitrary numbers of parameters to member functions without
requiring extension.</font></td>
    <td><font face="Arial, Helvetica" size="2">No</font></td>
    <td>&nbsp;</td>
    <td>&nbsp;</td>
    <td>&nbsp;</td>
    <td><font face="Arial, Helvetica" size="2">No</font></td>
    <td><font face="Arial, Helvetica" size="2">No</font></td>
</tr>
<tr>
    <td><font face="Arial, Helvetica" size="2">Takes advantage of non-strictness in the evaluation of preconditions
and postconditions.</font></td>
    <td><font face="Arial, Helvetica" size="2">No</font></td>
    <td><font face="Arial, Helvetica" size="2">No</font></td>
    <td><font face="Arial, Helvetica" size="2">No</font></td>
    <td><font face="Arial, Helvetica" size="2">No</font></td>
    <td><font face="Arial, Helvetica" size="2">No</font></td>
    <td><font face="Arial, Helvetica" size="2">No</font></td>
</tr>
</tbody></table><p>
Table 1 summarizes the characteristics of the different approaches.
Consideration of Table 1 permits general observations to be made, such
as:</p><p>
</p><ul>
<li>Automatically providing postconditions with access to the return
value of the function (or the old value of a data item) has only been
possible with language extensions.</li>
<li>It is not possible to provide full expressivity in the
assertion-checking mechanism without using functions that may have
side-effects on program execution ("letting the imperative fox into the
applicative chicken coop").</li>
<li>Automatically checking the invariant in conjunction with
precondition and postcondition evaluation only makes sense in the OO
schemes (i.e., those that were not originally C-based).</li>
</ul>
The contents of Table 1 as a whole serve as a wish list for any new attempt to provide support for Design by Contract in C++.<p>
<b>Supporting DBC across an inheritance hierarchy</b><br>
This section develops generic classes that can be provided in library
form, and that minimize the amount of effort required by a programmer
to enjoy Design by Contract support across an inheritance hierarchy of
arbitrary depth in C++. The effort involved when there is no intrinsic
language support for Design by Contract is twofold: first, the same
skeleton code structure must be rewritten every time a function needs
to be predicated (see Figure 1).</p><p>


<img src="article_files/aug01maleyfig1.gif" alt="Figure 1" border="2"><br>
<b>Figure 1. Structure of a predicated function.</b></p><p>
Figure 1 shows the execution of the body of the function must be
preceded by code that checks the precondition and invariant, and must
be followed by code that checks the postcondition and invariant. In
addition, the current object value must be stored prior to execution of
the body, and this value—along with the return value of the
function—must be made available to the postcondition.</p><p>
Secondly, repetitive effort is required in maintaining the discipline
of checking effective rather than local constraints. Thus, for a
function precondition, adherence to the LSP can only be assured by
defining the effective precondition to be the disjunction of the local
preconditions at each level of the hierarchy (see Figure 2).</p><p>

<img src="article_files/aug01maleyfig2a.gif" alt="Figure 2" border="2"><br>
<b>Figure 2. Precondition disjunction.</b></p><p>
This process becomes tedious and potentially error-prone for a large
number of methods across various hierarchies. It can be made much more
straightforward and shorter by using templates that rely on two ideas:</p><p>
</p><ul>
<li>The functionality required to provide precondition and
postcondition monitoring can be encapsulated into a generic function
object;</li>
<li>A single primary template can be used to generate classes that parallel an inheritance hierarchy of arbitrary depth.</li>
</ul>
<b>Defining a Function Object</b><br>
To support assertion checking, the execution of a function needs to be
preceded and followed by particular actions, and all three stages are
interconnected. This interconnection is most apparent in that values
that are available in the first two stages (the value of the object
prior to function execution and the return value of the function) are
required by the third stage. Hence, it is clear that some encapsulating
of functionality is required, and this suggests the use of function
objects.<p>
To construct a suitable function object, the standard approach is to
compare two or more examples of specific cases of functions that deal
with all the stages of precondition and postcondition handling, and to
create an abstraction by identifying similarities and differences. The
template code captures the common features of predicated methods, while
the differences are recognized in the template's type parameters.</p><p>
Therefore, consider the two code examples in Listing 1. Clearly, the
similarity lies in the steps that are performed and in the order in
which they take place. The differences are in the types of the objects
involved: first, the return type of the function; and second, the
function's formal parameters. In addition, the class of which this
function is a member constitutes a type parameter, because it
determines the type of <font face="Courier">old</font>.
Since the number of formal parameters is variable, the total number of
type parameters on which the function depends is variable. There is no
mechanism in C++ to handle an arbitrary number of parameters in one
template, so different templates will be required for each possible
number of function parameters (within reason). The definition of the
function object and associated <font face="Courier">operator() (..)</font>
for the case of a function with a single parameter is shown in Listings
2, 3, 4, and 5, along with an example of its use (the definition of the
class <font face="Courier">Assertion</font> is given in Appendix I).</p><p>
In order to use the function object in the examples shown above, it is
necessary to rename the original function. This function is called
during the course of the execution of the function object if the
precondition has been found to be satisfied; the code remains
unaltered. This arrangement can easily be delimited by conditional
preprocessing directives so that the checking can be turned off if
desired and the original code executed in its original form.</p><p>
The body of the method <font face="Courier">Complex::operator/(..)</font>
must declare an instance of the function object, passing pointers to
the current object and the renamed function to the constructor, and the
function object must then be called passing the function parameters. If
brevity is paramount, it is possible to combine these two steps by
providing additional function templates that take the parameters to the
function object constructor and the parameters to the call of the
function object. (This can be seen in the sample code in Maley.<sup><font color="#cc3300">13</font></sup>)</p><p>
A convention of naming the object the same as the function except for
capitalizing the first letter is suggested (This of course assumes that
the convention of using lower case for function names has been adopted
in the first place). In addition, names of user-redefined, built-in
operators cannot use the operator symbols, hence, the name <font face="Courier">OperatorDivide</font>.</p><p>
An alternative to renaming the original function is to define a member <font face="Courier">body(..)</font> in the function object, and move the code of the body of the existing function to the body of the function <font face="Courier">body(..)</font>. However, referring to the example, since this function would not be a method of class <font face="Courier">Complex</font>, it must be given access to the <font face="Courier">Complex</font> object through a pointer, and the code must be adjusted accordingly (i.e., method calls must be prefixed by <font face="Courier">_object-&gt;</font>). It may therefore be necessary to declare the function object class to be a <font face="Courier">friend</font> of <font face="Courier">Complex</font> if access to non-public members in the body of the function is required.</p><p>
There is only one constraint on the instantiating types: the enclosing class must define the function <font face="Courier">invariant(..)</font>.</p><p>
Specific predicates are defined by the client by providing an encoding of the <font face="Courier">pre(..)</font>, <font face="Courier">post(..)</font>
functions; the compiler automatically selects these specializations
over the general definitions given in the primary template that are
universally satisfied. These functions are provided with a means of
accessing the object and the parameters of the method being called, and
the postcondition is provided with the "old" object (the state of the
object before function execution) and the return value of the function.
The integrity of the conditions themselves may be subjected to improved
integrity assurance.<sup><font color="#cc3300">14</font></sup> There is no way to ensure that the checking of constraints is side-effect free. The functions to be specialized are declared <font face="Courier">const</font>
(and therefore so must the specializations provided by the client), but
it is the function object that cannot be changed, the actual object is
referenced through the <font face="Courier">_object</font> pointer,
which could be const_casted by the client. Not all languages with
Design by Contract support a built-in guarantee of freedom from side
effects. For example, the Object Constraint Language of UML does, but
Eiffel does not.</p><p>
<b>Using Genericity to Span an Inheritance Hierarchy</b><br>
A single primary template can be used to generate classes that parallel
a single inheritance hierarchy of arbitrary depth; for example,
consider the generic class:</p><p>
</p><pre><code><font face="Courier">
template <typename derived="">
class DBC : public
     DBC<typename derived::base=""> { /* .. */ };
</typename></typename></font></code></pre>
It displays constrained genericity, in that the instantiating class <font face="Courier">Derived</font> must declare a name <font face="Courier">(Base)</font> in order for instantiation to succeed at compile time. If the name <font face="Courier">Base</font> is defined to be the name of the class <font face="Courier">Derived</font> is derived from, which can be done by using a <font face="Courier">typedef</font>,
then the template defines a generic class that inherits from that
instantiation of itself which is instantiated using the base class of
the class that instantiates it.<p>
Clearly, the construction requires a mechanism by which it can be
"terminated" in the case of the root class. The root class is not
derived from any other class, and the chain of inheritance comes to an
end. This can be accomplished by introducing an additional type
parameter <font face="Courier">Terminator</font> into the definition:</p><p>
</p><pre><code><font face="Courier">
template <typename derived="" typename="" terminator="typename" derived::base="">
class DBC : public DBC<typename derived::base="" derived::base::base=""> { /* .. */ };
</typename></typename></font></code></pre>
and then defining a partial specialization of the primary template that will be used in the root case:<p>
</p><pre><code><font face="Courier">
template <typename derived="">
     class DBC<derived, derived=""> { /* .. */ };
</derived,></typename></font></code></pre>
The <font face="Courier">Terminator</font>
parameter need only be included explicitly in one instantiation, where
it is used to identify the root of the hierarchy: the default suffices
in derived classes.<p>
The generic class <font face="Courier">DBC&lt;..&gt;</font>
will be used as the basis for an inner template class of the function
object template. It brings the name of the base class into the scope of
the derived class, which facilitates the template definition,
eliminates the need for much explicit coding, and shifts the work from
the client to the template supplier.</p><p>
The specific precondition and postcondition functions <font face="Courier">pre(..)</font> and <font face="Courier">post(..)</font> used in the definition of <font face="Courier">operator()(..)</font> are replaced by <font face="Courier">effectivePre(..)</font> and <font face="Courier">effectivePost(..)</font>,
respectively. These functions evaluate the necessary disjunction and
conjunction of local preconditions and postconditions, respectively.
Likewise for invariants. Inspection of these functions in the templates
in Appendix I shows that great care must be taken with scoping at
intermediate levels in the inheritance hierarchy. The complete function
object for any method may have an arbitrarily long chain of ancestors.
In the primary template (denoted here as <font face="Courier">PT</font>), a call to method <font face="Courier">pre(..)</font> in the definition of <font face="Courier">effectivePre(..)</font> might appear, for a method <font face="Courier">Bar(..)</font> and an intermediate class <font face="Courier">Foo</font>, to be a call to <font face="Courier">PT<foo, .="">::Bar::pre(..)</foo,></font>. However, polymorphism dictates that if the class at the top of the hierarchy (the one that has no derivative) is <font face="Courier">Fum</font>, then it is <font face="Courier">PT<fum, .="">::Bar::pre(..)</fum,></font> that is called. Hence, a scoping operator must be introduced into the definition.</p><p>
The additional template parameter <font face="Courier">Top</font> is included. Its default value is <font face="Courier">false</font>, and the top of the hierarchy is indicated by including the value <font face="Courier">true</font>
for this parameter. Identifying the top of the hierarchy is necessary
to handle the "old" object efficiently. The "old" object is referenced
through a pointer in the base class of the function object, but this
points to an object of the most derived type in the class hierarchy.
Therefore, at each level in the hierarchy, an "old" object of the right
type for that level can be accessed.</p><p>
For a given method, the template client optionally provides definitions for the methods <font face="Courier">pre()</font> and <font face="Courier">post()</font>
for each class in the hierarchy. When a function is called for a given
object in the hierarchy, the body defined for objects of that class is
executed; in addition, the full precondition and postcondition across
the whole of the hierarchy from that class to the root is checked.
(Obviously, if the precondition is not satisfied then the body may not,
in fact, be executed).</p><p>
In the combined template scheme, it is no longer necessary for the type
of the current object to be a template parameter of the function object
template (the outer class), because it is provided by the inner class.</p><p>
In order to support class invariant, method precondition, and method
postcondition monitoring across an inheritance hierarchy, it is
necessary to provide a <font face="Courier">typedef</font> in each class in the hierarchy to define the name "<font face="Courier">Base</font>."
This step brings the name of the base class into the scope of the
derived class, making it accessible within the template. For all
classes except the root of the hierarchy, the name "<font face="Courier">Base</font>"
is defined to be the class from which the class is derived. For the
root class, it is defined to be the class itself. This distinction is
vital when utilizing partial specialization to identify the root of the
hierarchy.</p><p>
Optionally, the following <font face="Courier">typedefs</font> can be added to make function names shorter and clearer:</p><p>
</p><ul>
<li>A global <font face="Courier">typedef</font> for each predicated
method, which instantiates the outer template class with the types of
the return value and the parameters of the predicated method.</li>
<li>A <font face="Courier">typedef</font> per class, per predicated method that instantiates the inner template class with the types in the inheritance hierarchy.</li>
</ul>
<p>
<i><b>Distinguishing between methods with identical signatures</b></i><br>
If two methods in the same hierarchy have the same signature, clients
of the templates must be aware that they must differentiate between
them. Consider, for example, a definition:</p><p>
</p><pre><code><font face="Courier">
bool Derived2::MethodA::pre(..) { /* ... */ }
</font></code></pre>
The use of the global <font face="Courier">typedef</font><p>
</p><pre><code><font face="Courier">
typedef ::DBC1<double, float=""> MethodA;
</double,></font></code></pre>
and the local<p>
</p><pre><code><font face="Courier">
typedef ::MethodA::DBC<derived2> MethodA;
</derived2></font></code></pre>
in class <font face="Courier">Derived2</font><sup><font color="#cc3300">13</font></sup> mask the fact that this definition is actually<p>
</p><pre><code><font face="Courier">
bool ::DBC1<double, float="">::DBC<derived2>::pre(..) { /* ... */ }
</derived2></double,></font></code></pre>
which would be indistinguishable from the definition of another method
in the same hierarchy with the same signature. Therefore, in such a
case, it would be necessary to include an integer value in the type
parameters of one instantiation of <font face="Courier">DBC1&lt;..&gt;</font> in order to make the distinction apparent, for example:<p>
</p><pre><code><font face="Courier">
typedef ::DBC1<double, float="" 1=""> MethodC;
</double,></font></code></pre>
The <font face="Courier">MethodNumber</font> type parameter, which defaults to zero, is provided for this purpose.<p>
<i><b>Void functions</b></i><br>
The current state of compiler technology means different solutions to
the problem caused by functions with no return value must be
considered, and the appropriate templates for the capabilities of the
compiler chosen. In the standard template definitions, the type
parameter <font face="Courier">ReturnType</font> is used to declare the type of the parameter used to pass the return value of the function to the postcondition, in the form <font face="Courier">const ReturnType&amp;</font>. However, if <font face="Courier">ReturnType</font> is instantiated to <font face="Courier">void</font>, this declaration when instantiated is illegal.</p><p>
There are a number of ways around this. Ideally, a specialization of
the templates is written that the compiler can automatically select
whenever a function with no return value is declared as a function
object. The return value parameter can be eliminated from the
declaration of <font face="Courier">post(..)</font>
in this specialization. However, not all compilers will recognize the
specialization as valid. The alternatives involve defining the
templates in terms of a pointer to the return value instead of to the
value itself.</p><p>
<i><b>Point of declaration</b></i><br>
It is possible to declare the supporting function objects in the class,
rather than in the class method (and not declare the class methods at
all). This can reduce considerably the amount of housekeeping code that
needs to be written. However, it does have drawbacks. First,
polymorphic behavior is lost unless wrapper methods are also declared,
since function objects cannot be declared virtual. Second, all class
constructor definitions must be amended to ensure that the object
pointer is passed to each of the declared function objects.</p><p>
<i><b>Multiple inheritance</b></i><br>
It is possible to extend this scheme to multiple inheritance
hierarchies, and the best way to accomplish this is still being
investigated. The definition of the name "<font face="Courier">Base</font>"
in each class is no longer useful, since methods no longer share a
common heritage. As a result, some of the declarations are lengthier,
as function objects must be instantiated with essentially their entire
ancestry. In each case, this is a chain of single inheritance, but the
chain is not common to all methods. As with the practical limit on the
number of formal parameters, the template writer must impose a
practical limit on the depth of the inheritance lattice.</p><p>
<b>Supporting the STL</b><br>
Many data types are now based on hierarchies of containers, and the containers are provided by the STL.<sup><font color="#cc3300">15</font></sup>
In such cases, there need be no requirements on the client for DBC
support to be provided. Monitoring constraints on these types can be
handled by extending the capabilities of the STL containers. In brief,
this is done by creating new containers that inherit from the originals
in a new namespace. Support for verifying preconditions and
postconditions on the operation of functions is provided by redefining
the operations so that in the new operation, the precondition is
checked prior to a call to the original operation, and similarly the
postcondition is checked afterwards. Invariants can be handled in a
straightforward manner, as each generic container definition can
include code that calculates the conjunction of the invariants of the
elements it contains, together with its own invariant (ordering in a <font face="Courier">vector<t, alloc=""></t,></font>, for example).</p><p>
There are really two separate cases to consider for preconditions and
postconditions. First, there is the case of preconditions and
postconditions that are inherent to a container operation because of
the properties of the container. For example, it is an error to try to
erase an element from an empty vector, so there should be a
precondition on erasing from a vector that states the iterator
parameter lies in the range of iterators of the vector. Second, there
are the preconditions and postconditions that are specific to the
instantiation of an operation for a particular type. Both can be
accommodated.</p><p>
Each container operation for which a client may wish to define a
precondition or postcondition (i.e., those that modify the container;
no client is likely to want to stipulate a specific precondition for a
query operation such as <font face="Courier">size()</font>) is redefined within the namespace '<font face="Courier">stdpp</font>' to check conditions that can be redefined for specific type instantiations by the client. For example, methods <font face="Courier">pre_erase(..)</font> and <font face="Courier">post_erase(..)</font> are declared in the redeclaration of <font face="Courier">vector<t, alloc=""></t,></font> (see Listing 6). This leads to the definition of <font face="Courier">stdpp::vector<t>::erase(iterator)</t></font> as shown in Listing 7.</p><p>
The client then has the option of supplying specific definitions of <font face="Courier">stdpp::vector<t>::pre_erase() const</t></font> or <font face="Courier">stdpp::vector<t>::post_erase() const</t></font> as necessary. Clearly, granularity of control over which checks are employed can be introduced.</p><p>
One potential issue concerns versions of the STL. There is no
recognized canonical STL implementation, and even if there were, there
is no guarantee it could not be superseded. The library adaptation
described above works with both the HP and the SGI implementations of
the STL.</p><p>
<b>Conclusion</b><br>
This work has been the result of endeavoring to apply modern software
engineering techniques to problems in Computational Physics. Formal
specifications of the problems were written in order to state precisely
and unambiguously the functionality of the components.</p><p>
While it was desired to make maximum use of existing code and libraries
in the implementation of the component, it was recognized that
libraries such as the STL only provided support for the statement of
data structure given in the specification, not for the monitoring of
the stated constraints on that data. Similarly, the generic algorithms
of the STL provide an immediate implementation of some of the
operations defined in the specification, but no mechanism for verifying
their behavior is that which is required.</p><p>
It was therefore necessary to provide Design by Contract support for
the chosen implementation language, C++, which has been done by taking
advantage of new language features that reduce the effort required by
the programmer to a minimum. These new features constitute part of the
multiparadigm design capability of C++.</p><p>
The genericity paradigm was employed in tandem with one of the most
basic techniques of analysis—identifying similarities and differences,
and creating abstractions—to develop templates that capture the common
features of predicated methods, while the differences are recognized in
the template's type parameters; constraints on which types can
instantiate a given template indicate that some of the commonality that
has been identified is not embedded in the code of the algorithm, but
in the type requirements. This approach results in a significant amount
of implementation simply by declaration.</p><p>
Referring back to the table of desirable and not-so-desirable
characteristics of Design by Contract support mechanisms (Table 1), the
templates shown provide most of the significant players in the wish
list and, with minor adaptations could provide more if required. The
one desirable characteristic that cannot be ensured is that checking of
constraints is side-effect free.</p><p>
<b>References</b><br>
</p><ol>
<li>Liskov, Barbara H. and Jeannette M. Wing. "A Behavioral Notion of Subtyping," <i>ACM Transactions on Programming Languages and Systems,</i> 16(6):1811–1841, Nov. 1994.</li>
<li>Hoare, C.A.R. "An Axiomatic Basis for Computer Programming," <i>Communications of the ACM,</i> 12(10):576–583, Oct. 1969.</li>
<li>Hoare, C.A.R. "Proof of Correctness of Data Representations," <i>Acta Informatica,</i> 1(4):271–281, 1972.</li>
<li>Floyd, Robert F. "Assigning Meanings to Programs," <i>Proceedings of the American Mathematical Society Symposium in Applied Mathematics,</i> Volume XIX, 19–31, 1967.</li>
<li>Dijkstra, Edsger W. <i>A Discipline of Programming,</i> Prentice Hall, Englewood Cliffs, New Jersey, 1976.</li>
<li>Maley, David and Ivor Spence. "Emulating Design by Contract in C++," <i>TOOLS 29,</i> IEEE.</li>
<li>Binder, Robert V. <i>Testing Object-Oriented Systems: Models, Patterns and Tools,</i> Addison–Wesley, Reading, MA, 1999.</li>
<li>Welch, David and Scott Strong. "An Exception-Based Assertion Mechanism for C++," <i>JOOP,</i> July/Aug 1998.</li>
<li>Rosenblum, David. "A Practical Approach to Programming with Assertions," <i>IEEE Transactions on Software Engineering,</i> 21(1), Jan. 1995.</li>
<li>See <a href="http://www.gnu.org/software/nana/manual/nana.html">http://www.gnu.org/software/nana/manual/nana.html</a>.</li>
<li>Cline, Maurice and Doug Lea. "Using Annotated C++," <i>Proceedings of C++ at Work,</i> Sept. 1990.</li>
<li>Porat, Sara and Paul Fertig. "Class Assertions in C++," <i>Journal of Object-Oriented Programming,</i> 8(2):30–37, May 1995.</li>
<li>See www.stmarys-belfast.ac.uk/~d.maley/dbc.cpp.</li>
<li>Maley, David and Ivor Spence. "But Who Will Guard the Guardians?," <i>TOOLS USA 2000,</i> IEEE.</li>
<li>Plauger, P. J., Ed., et al. <i>C++ Standard Template Library,</i> Prentice Hall, Englewood Cliffs, NJ, 1995.</li>
</ol><p>


</p><p class="summary">David Maley is with St. Mary's University College, Belfast. He can be contacted at <a href="mailto:d.maley@stmarys-belfast.ac.uk">d.maley@stmarys-belfast.ac.uk</a>.Ivor Spence is with Queen's University of Belfast. He can be contacted at <a href="mailto:i.spence@qub.ac.uk">i.spence@qub.ac.uk</a>.</p>

						</div>
						<!-- ARTICLE -->
						
						
						<!-- SPONSOR SECTION -->
						

<div class="sponsor">
	<h2>Sponsored Links</h2>
	<ul>
		<li>
		<script type="text/javascript">
		  <!-- Hide from old browsers
			document.write (AAMB10)
		  // End Hide -->
			</script><a href="http://ad101com.adbureau.net/accipiter/adclick/CID=0000341a60246e6600000000/aamsz=textlink/pos=tx01/site=adt/area=article/aID=4593/TOPIC=/acc_random=76799364/pageid=76799364" target="_blank"><strong>Defy all challenges</strong></a>: Microsoft� Visual Studio 2005.
		</li>
		<li>
			<script type="text/javascript">
		  <!-- Hide from old browsers
			document.write (AAMB11)
		  // End Hide -->
			</script><a href="http://ad101com.adbureau.net/accipiter/adclick/CID=000034d960246e6600000000/aamsz=textlink/pos=tx02/site=adt/area=article/aID=4593/TOPIC=/acc_random=76799364/pageid=76799364" target="_blank"><strong>VMware Workstation</strong></a>: The gold standard in desktop virtualization
		</li>
		<li>
			<script type="text/javascript">
		  <!-- Hide from old browsers
			document.write (AAMB12)
		  // End Hide -->
			</script><a href="http://ad101com.adbureau.net/accipiter/adclick/CID=000034d960246e6600000000/aamsz=textlink/pos=tx03/site=adt/area=article/aID=4593/TOPIC=/acc_random=76799364/pageid=76799364" target="_blank"><strong>VMware Workstation</strong></a>: The gold standard in desktop virtualization</li>
		 <li>
<script type="text/javascript">
		  <!-- Hide from old browsers
			document.write (AAMB13)
		  // End Hide -->
			</script><a href="http://ad101com.adbureau.net/accipiter/adclick/CID=000034d960246e6600000000/aamsz=textlink/pos=tx04/site=adt/area=article/aID=4593/TOPIC=/acc_random=76799364/pageid=76799364" target="_blank"><strong>VMware Workstation</strong></a>: The gold standard in desktop virtualization</li>
		
		
		
	</ul>
</div>

						<!-- SPONSOR SECTION -->
					</div>
					<div class="sContent">						
						<!-- LEFT COLUMN SKYSCRAPER -->
						

<div class="skyScraperRight">
	<script type="text/javascript">
		  <!-- Hide from old browsers
			document.write (AAMB5)
		  // End Hide -->
	</script><iframe src="article_files/relocate_002." marginwidth="0" marginheight="0" hspace="0" vspace="0" bordercolor="#000000" frameborder="0" height="600" scrolling="no" width="160">&lt;SCRIPT
language='JavaScript1.1'
SRC='http://ad.doubleclick.net/adj/N815.adtmag/B2382392.2;abr=!ie;;click=http://ad101com.adbureau.net/accipiter/adclick/CID=0000320760246e6600000000/aamsz=160x600/pos=r01/site=adt/area=article/aID=4593/TOPIC=/acc_random=76799364/pageid=76799364/relocate=;sz=160x600;ord=76799364?'&gt;&lt;/SCRIPT&gt;&lt;NOSCRIPT&gt;&lt;A
HREF='http://ad101com.adbureau.net/accipiter/adclick/CID=0000320760246e6600000000/aamsz=160x600/pos=r01/site=adt/area=article/aID=4593/TOPIC=/acc_random=76799364/pageid=76799364'TARGET='_blank'&gt;&lt;IMG
SRC='http://ad.doubleclick.net/ad/N815.adtmag/B2382392.2;abr=!ie4;abr=!ie5;sz=160x600;ord=76799364?'BORDER=0
WIDTH=160 HEIGHT=600 ALT="Click Here"&gt;&lt;/A&gt;&lt;/NOSCRIPT&gt;</iframe><img src="article_files/pageid76799364" border="0" height="1" width="1">
</div>

						<!-- LEFT COLUMN SKYSCRAPER -->
						
						<!-- NEWSLETTER SUBSSCRIPTION -->
						
<!-- NEWSLETTER SUBSCRIPTION -->
<div class="newsLetter">
	<h2>Free Newsletters</h2>
	<div id="newsImg"></div>
	<div class="splitBox">
		<div class="left">
			<ul>
				<li>
					<a href="http://www.adtmag.com/newsletter/newsletter.aspx?nl=EADT">AppTrends</a></li>
				<li>
					<a href="http://www.adtmag.com/newsletter/newsletter.aspx?nl=PRT">ProgrammingTrends</a></li>
				<li>
					<a href="http://www.adtmag.com/newsletter/newsletter.aspx?nl=JDT">JavaTrends</a></li>
			</ul>
		</div>
		<div class="right">
			<ul>
				<li>
					<a href="http://www.adtmag.com/newsletter/newsletter.aspx?nl=datatrends">DataTrends</a></li>
				<li>
					<a href="http://www.adtmag.com/newsletter/newsletter.aspx?nl=SOATrends">SOATrends</a></li>
			</ul>
		</div>
		<p class="subscribe"><a href="https://newsletters.1105pubs.com/nl/SDG.do?NL=4904,4905,4906,4907,4908&amp;PC=HWEB03" target="_blank"><img src="article_files/subscribe.gif" border="0"></a></p>
	</div>
</div>
<!-- NEWSLETTER SUBSCRIPTION -->
						<!-- NEWSLETTER SUBSSCRIPTION -->
					</div>
				</div>
				<!-- END EXTRA CONTENT -->
				<!-- BOTTOM LEADERBOARD -->
				
<div class="clear"></div>
<div class="banners" id="googleAd">
	<!-- BOTTOM LEADERBOARD -->
	<script type="text/javascript">
	<!-- Hide from old browsers
		document.write (AAMB4)
	// End Hide -->
	</script><script language="JAVASCRIPT">var plugin = 0;if (navigator.mimeTypes && navigator.mimeTypes['application/x-shockwave-flash'] && navigator.mimeTypes['application/x-shockwave-flash'].enabledPlugin) {	if (navigator.plugins && navigator.plugins['Shockwave Flash'] && (parseInt(navigator.plugins['Shockwave Flash'].description.substring(navigator.plugins['Shockwave Flash'].description.indexOf('.')-1)) >= 5) )		plugin = 1;}else if (navigator.userAgent && navigator.userAgent.indexOf('MSIE') >= 0 && (navigator.userAgent.indexOf('Windows') >= 0) && (navigator.userAgent.indexOf("Windows 3.1") < 0)) {	document.writeln('<SCR' + 'IPT LANGUAGE="VBScript">');	document.writeln('on error resume next ');	document.writeln('if ( 5 = 3 ) then plugin = ( IsObject(CreateObject("ShockwaveFlash.ShockwaveFlash.3")))');	document.writeln('if (( 5 <= 4) and (plugin <= 0 )) then plugin = ( IsObject(CreateObject("ShockwaveFlash.ShockwaveFlash.4")))');	document.writeln('if (( 5 <= 5) and (plugin <= 0 )) then plugin = ( IsObject(CreateObject("ShockwaveFlash.ShockwaveFlash.5")))');	document.writeln('if (( 5 <= 6) and (plugin <= 0 )) then plugin = ( IsObject(CreateObject("ShockwaveFlash.ShockwaveFlash.6")))');	document.writeln('</SCR'+'IPT> ');}if ( plugin ) {	document.write('<OBJECT CLASSID=\"clsid:D27CDB6E-AE6D-11cf-96B8-444553540000\"');	document.write('  CODEBASE=\"http://download.macromedia.com/pub/shockwave/cabs/flash/swflash.cab#version=3,0,0,0\" ');	document.writeln(' ID=\"Ad\" WIDTH=\"728\" HEIGHT=\"90\">');	document.writeln('<PARAM NAME=\"movie\" VALUE=\"http://ad101com-images.adbureau.net/ad101com/adt/Curl/hero_banner_336x280.swf?clickTAG=http://ad101com.adbureau.net/accipiter/adclick/CID=0000367460246e6600000000/aamsz=728x90/pos=m03/site=adt/area=article/aID=4593/TOPIC=/acc_random=76799364/pageid=76799364\"> <PARAM NAME=\"wmode\" VALUE=\"transparent\"> <PARAM NAME=\"quality\" VALUE=\"autohigh\"> <PARAM NAME=\"bgcolor\" VALUE=\"none\">'); 	document.write(' <EMBED src=\"http://ad101com-images.adbureau.net/ad101com/adt/Curl/hero_banner_336x280.swf?clickTAG=http://ad101com.adbureau.net/accipiter/adclick/CID=0000367460246e6600000000/aamsz=728x90/pos=m03/site=adt/area=article/aID=4593/TOPIC=/acc_random=76799364/pageid=76799364\" wmode=\"transparent\" quality=\"autohigh\"  ');	document.write(' swLiveConnect=\"FALSE\" WIDTH=\"728\" HEIGHT=\"90\"');	document.writeln(' TYPE=\"application/x-shockwave-flash\" PLUGINSPAGE=\"http://www.macromedia.com/shockwave/download/index.cgi?P1_Prod_Version=ShockwaveFlash\">');	document.writeln(' </EMBED>');	document.writeln(' </OBJECT>');} else if (!(navigator.appName && navigator.appName.indexOf("Netscape")>=0 && navigator.appVersion.indexOf("2.")>=0)){	document.writeln('<A href=\"http://ad101com.adbureau.net/accipiter/adclick/CID=0000367460246e6600000000/aamsz=728x90/pos=m03/site=adt/area=article/aID=4593/TOPIC=/acc_random=76799364/pageid=76799364\"><IMG SRC=\"http://ad101com-images.adbureau.net/ad101com/adt/Curl/hero_banner_728x90.gif\" ALT=\"Curl\" WIDTH=\"728\" HEIGHT=\"90\" BORDER=\"0\"></A>');}</script><a href="http://ad101com.adbureau.net/accipiter/adclick/CID=0000367460246e6600000000/aamsz=728x90/pos=m03/site=adt/area=article/aID=4593/TOPIC=/acc_random=76799364/pageid=76799364"><img src="article_files/hero_banner_728x90.gif" alt="Curl" border="0" height="90" width="728"></a>
<noembed>&lt;A
HREF="http://ad101com.adbureau.net/accipiter/adclick/CID=0000367460246e6600000000/aamsz=728x90/pos=m03/site=adt/area=article/aID=4593/TOPIC=/acc_random=76799364/pageid=76799364"&gt;&lt;IMG
SRC="http://ad101com-images.adbureau.net/ad101com/adt/Curl/hero_banner_728x90.gif"
ALT="Curl" WIDTH="728" HEIGHT="90" BORDER="0"&gt;&lt;/A&gt;</noembed><noscript><A
HREF="http://ad101com.adbureau.net/accipiter/adclick/CID=0000367460246e6600000000/aamsz=728x90/pos=m03/site=adt/area=article/aID=4593/TOPIC=/acc_random=76799364/pageid=76799364"><IMG
SRC="http://ad101com-images.adbureau.net/ad101com/adt/Curl/hero_banner_728x90.gif"
ALT="Curl" WIDTH="728" HEIGHT="90" BORDER="0"></A></noscript>	
</div>
				<!-- BOTTOM LEADERBOARD -->
			</div>
			<!-- END MAIN CONTENT -->
			<!-- BEGIN FOOTER -->
			
<div class="clear"></div>
<div id="footer">
	<!-- bottom Nav -->
	<div id="footerNav">
		<ul>
			<li>
				<a href="http://www.adtmag.com/index.aspx">HOME</a>
			</li>
			<li>
				<a href="http://www.adtmag.com/section.aspx?c=72">SPECIAL REPORT</a>
			</li>
			<li id="last">
				<a href="http://www.adtmag.com/section.aspx?t=6">NEWS</a>
			</li>
		</ul>
	</div>
	<!-- bottom Nav -->
	<!-- BEGIN ADDITONAL NAV LINKS -->
	<div id="moreLinks">
		<ul>
			<li>
				<a href="https://newsletters.1105pubs.com/nl/SDG.do?NL=4904,4905,4906,4907,4908,5480&amp;PC=HWEB05" target="_blank">Subscribe</a></li>
			|
			<li>
				<a href="http://www.adtmag.com/advertise.aspx">Advertise</a></li>
			|
			<li>
				<a href="http://www.adtmag.com/about.aspx">About Us</a></li>
			|
			<li>
				<a href="http://www.adtmag.com/services/sitemap.aspx">Site Map</a></li>
			|
			<li>
				<a href="http://www.adtmag.com/contact.aspx">Contact Us</a></li>
		</ul>
	</div>
	<!-- END ADDITONAL NAV LINKS -->
	<!-- 101com copyright -->
	<!-- Begin 101com copyright -->
	<div id="copyright">
		<div>
			<a href="http://www.adtmag.com/" target="_blank">Application Development Trends</a> | <a href="http://www.campus-technology.com/" target="_blank">
				Campus Technology</a> | <a href="http://www.certcities.com/" target="_blank">CertCities.com</a>
			| <a href="http://www.tdwi.org/" target="_blank">The Data Warehousing Institute</a>
			| <a href="http://www.e-gov.com/" target="_blank">E-Gov</a> | <a href="http://www.eduhound.com/" target="_blank">
				EduHound</a><br>
			<a href="http://www.entmag.com/" target="_blank">ENTmag.com</a> | <a href="http://www.esj.com/" target="_blank">
				Enterprise Systems</a> | <a href="http://www.fcw.com/" target="_blank">Federal 
				Computer Week</a> | <a href="http://govhealthit.com/" target="_blank">Government 
				Health IT</a> | <a href="http://www.itcinstitute.com/" target="_blank">IT 
				Compliance Institute</a> | <a href="http://www.mcpmag.com/" target="_blank">MCPmag.com</a><br>
			<a href="http://www.rechargermag.com/" target="_blank">Recharger</a> | <a href="http://www.redmondmag.com/" target="_blank">
				Redmond magazine</a> | <a href="http://reddevnews.com/" target="_blank">Redmond Developer News</a> | <a href="http://www.rcpmag.com/" target="_blank">Redmond 
				Channel Partner</a> | <a href="http://www.tcpmag.com/" target="_blank">TCPmag.com</a>
			| <a href="http://www.thejournal.com/" target="_blank">T.H.E. Journal</a> | <a href="http://www.techmentorevents.com/" target="_blank">
				TechMentor</a><br>
			Copyright 1998-2007 <a href="http://www.1105media.com/" target="_blank">1105 Media Inc.</a> See our <a href="http://www.1105media.com/privacy.aspx" target="_blank">
				<strong>Privacy Policy</strong></a></div>
		<div class="smallLogo"><a href="http://www.1105media.com/" target="_blank"><img src="article_files/1105logo_website.gif" alt="1105 Media Inc." align="middle" border="0" height="26" hspace="7" vspace="3" width="136"></a></div>
	</div>
	<!-- End 101com copyright  -->
	<!-- End 101com copyright  -->
</div>
<!-- start Vibrant Media IntelliTXT script section -->
<script type="text/javascript" src="article_files/front.asp"></script>
<!-- end Vibrant Media IntelliTXT script section -->
			<!-- END FOOTER -->
		</div><script type="text/javascript" src="article_files/door.jsp"></script>
		
	<script type="text/javascript" src="article_files/func_200709182130.js"></script><script type="text/javascript" src="article_files/chunks_003.jsp"></script><script type="text/javascript" src="article_files/chunks_006.jsp"></script><script type="text/javascript" src="article_files/chunks_004.jsp"></script><script type="text/javascript" src="article_files/chunks_002.jsp"></script><script type="text/javascript" src="article_files/chunks_005.jsp"></script><script type="text/javascript" src="article_files/chunks.jsp"></script><script type="text/javascript" src="article_files/spit.jsp"></script><script type="text/javascript" src="article_files/al.asp"></script></body></html>