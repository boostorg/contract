

var gBVType='firefox',gBVVersion='15',gOSType='linux';

/* This source code is Copyright (c) Vibrant Media 2001-2007 and forms part of the
patent-pending Vibrant Media product "IntelliTXT" (sm). */
function cpl(s){
var p=s.indexOf(' '),c=1;
while(p>=0){
p=s.indexOf(' ',p+1);
c++;}
return c;
}

function iG(){
gHN=new Array('container');
gAN=new Array();

gSN=new Array('<b>','<h1>','<h2>','<h3>','<h4>','<h5>','<strong>','<em>','<i>','!header','!mainNav','adBox','newsLetter','sponsor','!footer','!copyright','titleLink','author','splitBox','left','right');
gUPN=new Array('<b>','<i>','<u>');
gBPN=new Array();
}

function kwM(){
var ad=fABDID(aAD,gDI);
if(null==ad)return;
window.status=ad.t.replace(/\&pound\;/, '?');
}
var gCLM=1,
gK=new Array(),
gKL=new Array(),
gOHk=new Array();
gITXTNIdx=0;
for(var i=0;i<gK.length;i++)gKL[i]=cpl(gK[i]);

document.gEsBCN=function(cl){
var retnode=[],myclass=new RegExp('\\b'+cl+'\\b'),elem=this.getElementsByTagName('*');
for(var i=0;i<elem.length;i++){if(myclass.test(elem[i].className)) retnode.push(elem[i]);}
return retnode;
};
function doIt(){

ipartid=1410;
ibid=2862;
ipid=5260;
t_s='20070923161256';
mk=4;
server='adtmag.us.intellitxt.com';
cc='us';
rcc='us';
itxtreg='mi';
itxtdma='505';
ulS='font-weight:normal;font-size:100%;text-decoration:underline;border-bottom:darkgreen 0.075em solid;padding-bottom: 1px;color:darkgreen;background-color:transparent;;padding-bottom:1px';
hS='font-weight:normal;font-size:100%;text-decoration:underline;border-bottom:darkgreen 0.2em solid;padding-bottom: 1px;color:darkgreen;background-color:transparent; ;padding-bottom:1px';
iEulS='';
iEhS='';
sWTU='';
sIEWTU='';
iCF=3;
gDBL=0;
kwpn=2.0;
kwpp=-1.0;
gSkp=0;
ppp=false;
gTI='';
gEATI=0;
gATIr='http://images.intellitxt.com/ast/adTypes/';
gATIs='height:10px;width:10px;position:relative;top:1px;left:1px;padding:0;margin:0;float:none;border:0;';
gATIg= new parr('');gATIg.set(0,'mag-glass_10x10.gif');
gFTTm= new parr('');gFTTm.set(34,'preloader.swf$$320$$200$$8');gFTTm.set(32,'preloader.swf$$320$$200$$8');gFTTm.set(17,'preloader.swf$$320$$200$$8');gFTTm.set(48,'preloader.swf$$300$$250$$8');gFTTm.set(46,'preloader.swf$$320$$200$$8');

gFTTr='http://images.intellitxt.com/ast/allflash_adunit/prod/';
gFOJBG='#FFFFFF';
gFFMF='0';
gSVURL='';
gSVIMG='';
gFdBck='';
gSI=1;
gSID='1c812990125c30c68adf71e540e690aa';
gMiFo=0;
mTL=50;
gDrag=1;
gMSNsb=-1;
gOFlt=0;
gIRB=0;
gTTt=1500;
gDASB=3;
gAUAT=0;
gHLN=1;
gKWPF=0;
gPVU='b5ecf43426364157b432ff31a3e28250';
gPVM='e615371f22f59caf354b962be277dde6';
gIPL=0;
iTTC=0;
gCSc='';

gLCL=0;
if('v1'==gCM)mTL=0;
ndbST=new Date().getTime();
iDW();
if(gCM=='v1')
gITXTN=gIA2();
else
gITXTN=gIA(gdB, gCM, 0);
skippinder();
var bCF=1;

var aCs=new Array();
gCntIP(aCs);

if( (true) && (true && ((bCF==1 && gCL) || (gIRB==1 && bCF==0 && gCL>=(gLCL * 1.1)) || (gDTo==false && gIRB==1 && bCF==0 && Math.abs(gCL-gLCL)>=(gLCL * 10) / 100)))) {

// this only needs to be done if we're SPITing and we're running IntelliEdit
var tTXT='',aIEE,dDate='';

if(tTXT.length==0)tTXT=document.title;

gINt=' zxz ';
for(var i=0;i<aCs.length;i++)
    gINt+=aCs[i];

var p=new Object();
p.ipid=ipid;
p.sid=gSID;
p.nbc=iNBc;
p.enc=gENC;
p.tx=gINt;
p.pagecl=37543;
p.cc=cc;
p.rcc=rcc;
p.reg=itxtreg;
p.dma=itxtdma;
p.dfr=false;
p.fdt=0;
p.ign86=false;
p.cf=iCF;
p.mk=mk;
p.kwpn=kwpn;
p.ppp=ppp;
p.kwpp=kwpp;
p.si=gSI;
p.dfc=iDFC;
p.rp=bYCR;
p.so=iSo;
p.adi=iADi;
p.irb=gIRB;
p.ims=2;
p.iek=0;
p.iel=4;
p.ieak=0;
p.ieix=true;
p.iedm=0;
p.ttxt=encodeURIComponent(tTXT);
while (p.ttxt.indexOf('\'')>-1) p.ttxt=p.ttxt.replace('\'', '%27');
p.auat=0;
p.lpgv=0;
p.ddate=dDate;
p.pvu=gPVU;
p.pvm=gPVM;
p.ias=itxtIas;
p.ru=encodeURIComponent(sRU);
cAs(server,p);
} else if (gCL)

 {

if((gITXTN==null)||(gITXTN!=null && gITXTN.length==0))
gITXTN=gIA(gdB,gCM,0);
if(gITXTN!=null && gITXTN.length)
if(gCL>0) rKWL(250);

}
}
var ndbST,
iRCLM=1,
iDFC=0,
iTTl=1,
iTTp=0,
iSo=0,
iNBc=0,
iADi=0,
sRU='http://www.adtmag.com/joop/article.aspx?id=4593',
gMR=1000,
bWAC=0,
bYCR=0,
gMNC=255,
gTTD=50,
iIEK=0,
sIEFH='',
ieslu='',
iessu='',
iesbu='',
iesfid='',
iesfin='',
iesfig='',
iett='Adtmag.com',
iDAH=0,
gFES=0,
gFAo=1,
gPmoe=0,
gTlpC=new Object();
gTlpC.tttc='#000099';gTlpC.ttht='#0000DE';
gTlpC.ttdc='#000000';gTlpC.tthdc='#000000';
gTlpC.ttac='#008000';gTlpC.ttha='#008000';
gTlpC.ttbg='#F0F0F0';gTlpC.tthv='#FFFFFF';
var sspl='Advertisement',
swti='What\'s this?',
slm='LEARN MORE',
ssch='Searching...',
sbn='Buy now',
scls='Close',
sCC='$',
sEet='End time',
sEcb='Place bid',
sEsn='Seller',
iert='Related Articles';
var gNeedProtos=1;

var prevOnload=(window.onload?window.onload:new Function()),
itxtInited=0,
itxtPrevOnloadCalled=0;
function itxtOnloader() {
 
startIntelliTXT(0);
}
function itxtStateChange() {
 
startIntelliTXT(1);
}
function startIntelliTXT(v) {
 
if (!v) {
if( itxtPrevOnloadCalled )
return;
itxtPrevOnloadCalled=1;
prevOnload();
}
if (itxtInited) return;
 
itxtInited=1;
itxtLES('http://images.intellitxt.com/ast/js/vm/func_200709182130.js');
}
window.onload=itxtOnloader;
window.setTimeout('startIntelliTXT(1);',3000);

