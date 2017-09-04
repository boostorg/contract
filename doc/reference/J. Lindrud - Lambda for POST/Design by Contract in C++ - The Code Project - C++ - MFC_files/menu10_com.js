/***********************************************
*	(c) Ger Versluis 2000 version 13.11 April 13, 2005       *
*	You may use this script on non commercial sites.	          *
*	www.burmees.nl/menu			          *
************************************************/

if(document.getElementById){
	var AgntUsr=navigator.userAgent.toLowerCase(),AppVer=navigator.appVersion.toLowerCase(),
	Opr7=AgntUsr.indexOf("opera")!=-1&&parseInt(AgntUsr.substring(AgntUsr.indexOf("opera")+6))>6?true:false;
	if((AgntUsr.indexOf("opera")==-1||Opr7)){
		var NavYes=((AgntUsr.indexOf("mozilla")!=-1&&AgntUsr.indexOf("compatible")==-1)||Opr7)?true:false,ExpYes=(AgntUsr.indexOf("msie")!=-1&&!Opr7)?	true:false;
		if(MenuUsesFrames&&!parent.frames[0])MenuUsesFrames=0;
		var Exp6Plus=((AppVer.indexOf("msie 6")!=-1||AppVer.indexOf("msie 7")!=-1)&&!Opr7)?true:false,MacExp5=(AppVer.indexOf("mac")!=-1&&AppVer.indexOf("msie 5")!=-1)?true:false,
		FLoc,ScLoc,DcLoc,SLdAgnWin,FWinH,FColW,SColW,DColW,SWinW,SWinH,FWinW,RLvl=0,FntFc=1,StaticPos=0,Ztop=100,FrstCreat=true,Ldd=false,
		Crtd=false,FCmplnt=false,SCmplnt=false,M_Clckd=false,IniFlg=false,ShwFlg=false,AcrssFrms=true,FrstCntnr=null,CurOvr=null,FHtml=null,ScHtml=null,
		CloseTmr=null,OpnTmr=null,RmbrNow=null,FStr="",M_Hide="hidden",M_Show="visible",P_X="px",M_StrtTp=StartTop,M_StrtLft=StartLeft,
		Par=MenuUsesFrames?parent:window,Doc=Par.document,Bod=Doc.body,Trigger=NavYes?Par:Bod,
		Nav_Op=NavYes&&AgntUsr.indexOf("gecko/")!=-1&&AgntUsr.indexOf("mac")==-1&&parseInt(AgntUsr.substring(AgntUsr.indexOf("gecko/")+6,AgntUsr.indexOf("gecko/")+12))>=200303?true:false,
		InitLdd,MstSz=0;LdTmr=setInterval("ChckInitLd()",100)}}

function ChckInitLd(){
	InitLdd=ExpYes?
		MenuUsesFrames?Par.frames[FirstLineFrame].document.readyState=="complete"&&Par.frames[SecLineFrame].document.readyState=="complete"?
		1:0:Par.document.readyState=="complete"?
		1:0:MenuUsesFrames?Par.frames[FirstLineFrame].document.body&&Par.frames[SecLineFrame].document.body?1:0:Par.document.body?1:0;
	if(InitLdd)	{clearInterval(LdTmr);Go()}}

function CnclSlct(){return false}

function RePos(){
	FWinW=ExpYes?FCmplnt?FHtml.clientWidth:FLoc.document.body.clientWidth:FLoc.innerWidth;
	FWinH=ExpYes?FCmplnt?FHtml.clientHeight:FLoc.document.body.clientHeight:FLoc.innerHeight;
	SWinW=ExpYes?SCmplnt?ScHtml.clientWidth:ScLoc.document.body.clientWidth:ScLoc.innerWidth;
	SWinH=ExpYes?SCmplnt?ScHtml.clientHeight:ScLoc.document.body.clientHeight:ScLoc.innerHeight;
	if(MstSz)SizeMenu(FrstCntnr);
	StaticPos=-1;
	ClcRl();if(TargetLoc)ClcTrgt();ClcLft();ClcTp();
	PosMenu(FrstCntnr,StartTop,StartLeft);
	if(RememberStatus)StMnu()}

function UnLdd(){
	Ldd=Crtd=false;
	SetMenu="0";
	var M=FrstCntnr?FrstCntnr.FrstMbr:null;
	if(ExpYes){while(M!=null){if(M.CCn){MakeNull(M.CCn);M.CCn=null}M=M.PrvMbr}}
	LdTmr=setInterval("ChckLdd()",100)}

function UnLddTotal(){
	MakeNull(FrstCntnr);
	FrstCntnr=RmbrNow=FLoc=ScLoc=DcLoc=SLdAgnWin=CurOvr=CloseTmr=Doc=Bod=Trigger=null}

function MakeNull(P){
	var M=P.FrstMbr,Mi;
	while(M!=null){Mi=M;if(M.CCn){MakeNull(M.CCn);M.CCn.mif=null;M.CCn=null}M=M.PrvMbr;Mi.PrvMbr=null;Mi=null}
	P.FrstMbr=null}

function ChckLdd(){if(!ExpYes){
	if(ScLoc.document.body){clearInterval(LdTmr);Go()}}
	else if(ScLoc.document.readyState=="complete"){if(LdTmr)clearInterval(LdTmr);Go()}}

function Go(){
	if(!Ldd){	Crtd=false;Ldd=true;
		BeforeStart();
		if(ScaleMenu){
			if(document.defaultView&&document.defaultView.getComputedStyle)FntFc=parseInt(document.defaultView.getComputedStyle(document.body,'').getPropertyValue("font-size"))/16;
			else if(ExpYes&&document.body.currentStyle)FntFc=parseInt(document.body.currentStyle.fontSize)/12}
		status="Building menu";
		FLoc=MenuUsesFrames?parent.frames[FirstLineFrame]:window;
		ScLoc=MenuUsesFrames?parent.frames[SecLineFrame]:window;
		DcLoc=MenuUsesFrames?parent.frames[DocTargetFrame]:window;
		if(MenuUsesFrames){if(!FLoc)FLoc=window;if(!ScLoc)ScLoc=window;if(!DcLoc)DcLoc=window}
		if(FLoc==ScLoc)AcrssFrms=false;
		if(AcrssFrms)FirstLineHorizontal=MenuFramesVertical?0:FirstLineHorizontal?FirstLineHorizontal:1;
		if(Exp6Plus||Opr7){
			FHtml=FLoc.document.getElementsByTagName("HTML")[0];ScHtml=ScLoc.document.getElementsByTagName("HTML")[0];
			FCmplnt=FLoc.document.compatMode.indexOf("CSS")==-1?false:true;SCmplnt=ScLoc.document.compatMode.indexOf("CSS")==-1?false:true}
		FWinW=ExpYes?FCmplnt?FHtml.clientWidth:FLoc.document.body.clientWidth:FLoc.innerWidth;
		FWinH=ExpYes?FCmplnt?FHtml.clientHeight:FLoc.document.body.clientHeight:FLoc.innerHeight;
		SWinW=ExpYes?SCmplnt?ScHtml.clientWidth:ScLoc.document.body.clientWidth:ScLoc.innerWidth;
		SWinH=ExpYes?SCmplnt?ScHtml.clientHeight:ScLoc.document.body.clientHeight:ScLoc.innerHeight;
		FColW=FLoc.document.body;SColW=ScLoc.document.body;DColW=ScLoc.document.body;
		if(TakeOverBgColor)FColW.style.backgroundColor=AcrssFrms?SColW.bgColor:DColW.bgColor;
		if(FrstCreat||FLoc==ScLoc)FrstCntnr=CreateMenuStructure("Menu",NoOffFirstLineMenus,null);
		else CreateMenuStructureAgain("Menu",NoOffFirstLineMenus);
		SizeMenu(FrstCntnr);
		ClcRl();if(TargetLoc)ClcTrgt();ClcLft();ClcTp();
		PosMenu(FrstCntnr,StartTop,StartLeft);
		Crtd=true;
		SLdAgnWin=ExpYes?ScLoc.document.body:ScLoc;SLdAgnWin.onunload=UnLdd;
		if(ExpYes)Trigger.onunload=UnLddTotal;
		Trigger.onresize=RePos;
		AfterBuild();
		if(RememberStatus)StMnu();
		FrstCreat=false;
		if(MenuVerticalCentered=="static"&&!AcrssFrms)setInterval("KeepPos()",50);
		if(!ExpYes){FWinW=-1;RePos()}
		IniFlg=true;Initiate();
		status="Menu ready for use"}}

function KeepPos(){
	var TS=ExpYes?SCmplnt?ScHtml.scrollTop:ScLoc.document.body.scrollTop:ScLoc.pageYOffset;
	if(TS!=StaticPos){
		StaticPos+=(TS-StaticPos)*.2;
		if(Math.abs(StaticPos-TS)<=1)StaticPos=TS;
		FrstCntnr.OrgTop=StartTop+StaticPos;
		FrstCntnr.style.top=FrstCntnr.mif.style.top=FrstCntnr.OrgTop+P_X}}

function ClcRl(){StartTop=M_StrtTp<1&&M_StrtTp>0?M_StrtTp*FWinH:M_StrtTp;StartLeft=M_StrtLft<1&&M_StrtLft>0?M_StrtLft*FWinW:M_StrtLft}

function ClcTrgt(){
	var TLoc=FLoc.document.getElementById(TargetLoc);
	while(TLoc){StartTop+=TLoc.offsetTop;StartLeft+=TLoc.offsetLeft;TLoc=TLoc.offsetParent}}

function ClcLft(){
	if(MenuCentered.indexOf("left")==-1){
		var Sz=FWinW-parseInt(FrstCntnr.style.width);
		StartLeft+=MenuCentered.indexOf("right")!=-1?Sz:Sz/2;if(StartLeft<0)StartLeft=0}}

function ClcTp(){
	if(MenuVerticalCentered!="top"&&MenuVerticalCentered!="static"){
		var Sz=FWinH-parseInt(FrstCntnr.style.height);
		StartTop+=MenuVerticalCentered=="bottom"?Sz:Sz/2;if(StartTop<0)StartTop=0}}

function SizeMenu(C){
	var Cmplnt=C.Lvl==1?FCmplnt:SCmplnt,M=C.FrstMbr,Mi,i,W=0,H=0,Wd,Ht,RI,BRW=C.Lvl==1?BorderWidthMain:BorderWidthSub,BTWn=C.Lvl==1?BorderBtwnMain:BorderBtwnSub;
	if(C.Lvl<=FirstLineHorizontal){
		while(M!=null){W+=Math.round((M.Arr[5]<1?(M.Arr[5]*(M.Lvl==1?FWinW:SWinW)):(M.Arr[5]*FntFc)));Mi=M;M=M.PrvMbr}
		W+=((C.NrItms-1)*BTWn+2*BRW);
		Ht=H=Math.round((Mi.Arr[4]<1?(Mi.Arr[4]*(Mi.Lvl==1?FWinH:SWinH)):(Mi.Arr[4]*FntFc)));H+=(2*BRW)}
	else {	while(M!=null){H+=Math.round((M.Arr[4]<1?(M.Arr[4]*(M.Lvl==1?FWinH:SWinH)):(M.Arr[4]*FntFc)));Mi=M;M=M.PrvMbr}
		H+=((C.NrItms-1)*BTWn+2*BRW);
		Wd=W=Math.round((Mi.Arr[5]<1?(Mi.Arr[5]*(Mi.Lvl==1?FWinW:SWinW)):(Mi.Arr[5]*FntFc)));W+=(2*BRW)}
	C.style.width=C.mif.style.width=W+P_X;C.style.height=C.mif.style.height=H+P_X;
	M=C.FrstMbr;
	while(M!=null){
		if(M.Arr[5]<1){W=C.Lvl<=FirstLineHorizontal?(M.Arr[5]*(M.Lvl==1?FWinW:SWinW)):Wd;MstSz=1}
		else W=(C.Lvl<=FirstLineHorizontal?M.Arr[5]:Wd)*FntFc;
		if(M.Arr[4]<1){H=C.Lvl<=FirstLineHorizontal?Ht:(M.Arr[4]*(M.Lvl==1?FWinH:SWinH));MstSz=1}
		else H=(C.Lvl<=FirstLineHorizontal?Ht:M.Arr[4])*FntFc;
		W=Math.round(W);H=Math.round(H);
		if(M.value.indexOf("<")==-1){
			M.tpd=TopPaddng<0?(Math.round(H*.5-M.Arr[12]*FntFc)):TopPaddng;if(M.tpd<0||M.tpd>H)M.tpd=0;
			M.ltp=LeftPaddng;if(M.ltp<0||M.ltp>W)M.ltp=0;
			if((NavYes&&!Opr7)||MacExp5||Cmplnt){M.lx=M.ltp;M.tx=M.tpd}}
		M.style.width=W-M.lx+P_X;M.style.height=H-M.tx+P_X;
		M.style.paddingLeft=M.ltp+P_X;M.style.paddingTop=M.tpd+P_X;
		if(M.ro){RI=(M.Lvl==1?FLoc:ScLoc).document.images[M.rid];RI.style.width=W+P_X;RI.style.height=H+P_X}
		if(M.CCn)SizeMenu(M.CCn);
		M=M.PrvMbr}}

function PosMenu(Ct,Tp,Lt){
	RLvl++;
	var a,Mb=Ct.FrstMbr,MWt=parseInt(Mb.style.width)+Mb.lx,
	MHt=parseInt(Mb.style.height)+Mb.tx,CWt=parseInt(Ct.style.width),CHt=parseInt(Ct.style.height),CCw,CCh,STp,SLt,Ti,Li,Hi,
	BRW=RLvl==1?BorderWidthMain:BorderWidthSub,BTWn=RLvl==1?BorderBtwnMain:BorderBtwnSub;
	if(RLvl==1&&AcrssFrms)!MenuFramesVertical?Tp=BottomUp?DistFrmFrameBrdr:FWinH-CHt-DistFrmFrameBrdr:Lt=RightToLeft?DistFrmFrameBrdr:FWinW-CWt-DistFrmFrameBrdr;
	if(RLvl==2&&AcrssFrms)!MenuFramesVertical?Tp=BottomUp?SWinH-CHt:0:Lt=RightToLeft?SWinW-CWt:0;
	if(RLvl==2){Tp+=VerCorrect;Lt+=HorCorrect}
	Ct.style.top=Ct.mif.style.top=RLvl==1?Tp+P_X:0;Ct.OrgTop=Tp;
	Ct.style.left=Ct.mif.style.left=RLvl==1?Lt+P_X:0;Ct.OrgLeft=Lt;
	if(RLvl<=FirstLineHorizontal){Hi=1;Li=CWt-MWt-2*BRW;Ti=0}
	else{Hi=Li=0;Ti=CHt-MHt-2*BRW}
	while(Mb!=null){
		Mb.style.left=Li+BRW+P_X;Mb.style.top=Ti+BRW+P_X;
		if(Mb.CCn){
			if(RightToLeft)CCw=parseInt(Mb.CCn.style.width);
			if(BottomUp)CCh=parseInt(Mb.CCn.style.height);
			if(Hi){STp=BottomUp?Ti-CCh:Ti+MHt+2*BRW;SLt=RightToLeft?Li+MWt-CCw:Li}
			else{	SLt=RightToLeft?Li-CCw+ChildOverlap*MWt+BRW:Li+(1-ChildOverlap)*MWt+BRW;
				STp=RLvl==1&&AcrssFrms?BottomUp?Ti-CCh+MHt:Ti:BottomUp?Ti-CCh+(1-ChildVerticalOverlap)*MHt+2*BRW:Ti+ChildVerticalOverlap*MHt}
			PosMenu(Mb.CCn,STp,SLt)}
		a=RLvl<=FirstLineHorizontal?BottomUp?9:3:RightToLeft?6:0;
		if(Mb.ai){	Mb.ai.style.top=(RLvl<=FirstLineHorizontal?BottomUp?2:MHt-Arrws[a+2]-2:(MHt-Arrws[a+2])/2)+P_X;Mb.ai.style.left=(RightToLeft?2:MWt-Arrws[a+1]-2)+P_X}
		Mb=Mb.PrvMbr;
		if(Mb){MWt=parseInt(Mb.style.width)+Mb.lx;MHt=parseInt(Mb.style.height)+Mb.tx;Hi?Li-=MWt+BTWn:Ti-=MHt+BTWn}}
	RLvl--}

function StMnu(){
	if(Crtd){	var i,Pntr=FrstCntnr,Str=ScLoc.SetMenu?ScLoc.SetMenu:"0";
		while(Str.indexOf("_")!=-1&&RememberStatus==1){
			i=Pntr.NrItms-parseInt(Str.substring(0,Str.indexOf("_")));Str=Str.slice(Str.indexOf("_")+1);
			Pntr=Pntr.FrstMbr;for(i;i;i--)Pntr=Pntr.PrvMbr;Pntr.OM();Pntr=Pntr.CCn}
		i=Pntr.NrItms-parseInt(Str);Pntr=Pntr.FrstMbr;
		for(i;i;i--)	Pntr=Pntr.PrvMbr;
		if(RmbrNow!=null){SetItem(RmbrNow,0);RmbrNow.Clckd=0}
		if(Pntr!=null){SetItem(Pntr,1);Pntr.Clckd=1;if(RememberStatus==1)Pntr.OM()}
		RmbrNow=Pntr;
		ClrAllChlds(FrstCntnr.FrstMbr);
		Rmbr(FrstCntnr)}}

function Initiate(){
	if(IniFlg&&Ldd){
		Init(FrstCntnr);IniFlg=false;if(RememberStatus)Rmbr(FrstCntnr);
		if(ShwFlg)AfterCloseAll();ShwFlg=M_Clckd=false}}

function Rmbr(CntPtr){
	var Mbr=CntPtr.FrstMbr,St;
	while(Mbr!=null){
		if(Mbr.DoRmbr){
			HiliteItem(Mbr);if(Mbr.CCn&&RememberStatus==1){St=Mbr.CCn.style;St.visibility=M_Show;Rmbr(Mbr.CCn)}break}
		else Mbr=Mbr.PrvMbr}}

function Init(CPt){
	var Mb=CPt.FrstMbr;
	RLvl++;
	CPt.style.visibility=CPt.mif.style.visibility=RLvl==1?M_Show:M_Hide;
	CPt.Shw=RLvl==1?1:0;
	while(Mb!=null){if(Mb.Hilite)LowItem(Mb);if(Mb.CCn)Init(Mb.CCn);Mb=Mb.PrvMbr}
	RLvl--}

function ClrAllChlds(Pt){
	var PSt,Pc;
	while(Pt){
		if(Pt.Hilite){
			Pc=Pt;if(Pc!=CurOvr)LowItem(Pt);
			if(Pt.CCn)	{PSt=Pt.CCn.style;if(Pc!=CurOvr){PSt.visibility=Pt.CCn.mif.style.visibility=M_Hide;Pt.CCn.Shw=0}ClrAllChlds(Pt.CCn.FrstMbr)}
			break}
		Pt=Pt.PrvMbr}}

function SetItem(Pntr,x){while(Pntr!=null){Pntr.DoRmbr=x;Pntr=Pntr.Ctnr.Cllr}}

function GoTo(){
	if(UnfoldsOnClick&&!M_Clckd&&this.Arr[3]){M_Clckd=true;OpenMenuII(this)}
	else if(this.Arr[1]){
		status="";LowItem(this);IniFlg=true;Initiate();
		if(this.Arr[1].indexOf("javascript:")!=-1)eval(this.Arr[1]);
		else if(DcLoc.location.href!=BaseHref+this.Arr[1])DcLoc.location.href=BaseHref+this.Arr[1]}}

function HiliteItem(P){
	if(P.rob)P.style.backgroundImage="url(\""+P.rib2+"\")";
	if(P.ro){var Lc=P.Lvl==1?FLoc:ScLoc;Lc.document.images[P.rid].src=P.ri2}
	else{	if(P.Arr[7])P.style.backgroundColor=P.Arr[7];if(P.Arr[9])P.style.color=P.Arr[9];
		if(HoverBold)P.style.fontWeight="bold";if(HoverItalic)P.style.fontStyle="italic";
		if(HoverUnderLine)P.style.textDecoration="underline";
		if(HoverTextSize)P.style.fontSize=parseInt(P.style.fontSize)+HoverTextSize+P_X;
		if(HoverVariant)P.style.fontVariant="small-caps"}
		if(HoverBorder){P.style.borderColor=HoverBorderColor;P.style.borderWidth=BorderWidthHover;P.style.borderStyle='solid';}		
	P.Hilite=1}

function LowItem(P){
	P.Hilite=0;
	if(P.rob)P.style.backgroundImage="url(\""+P.rib1+"\")";
	if(P.ro){var Lc=P.Lvl==1?FLoc:ScLoc;Lc.document.images[P.rid].src=P.ri1}
	else{	if(P.Arr[6])P.style.backgroundColor=P.Arr[6];if(P.Arr[8])P.style.color=P.Arr[8];
		if(HoverBold)P.style.fontWeight="normal";if(HoverItalic)P.style.fontStyle="normal";
		if(HoverUnderLine)P.style.textDecoration="none";
		if(HoverTextSize)P.style.fontSize=parseInt(P.style.fontSize)-HoverTextSize+P_X;
		if(HoverVariant)P.style.fontVariant="normal"}
		if(HoverBorder){P.style.borderColor=P.style.backgroundColor;P.style.borderWidth=0;P.style.borderStyle='none';}	
		}

function OpenMenu(){
	if(Ldd&&Crtd){
		if(UnfoldsOnClick&&!M_Clckd){CurOvr=this;IniFlg=false;ClrAllChlds(this.Ctnr.FrstMbr);HiliteItem(this);status=this.Arr[16]}
		else OpenMenuII(this)}}

function OpenMenuII(Ptr){
	if(OpnTmr)clearTimeout(OpnTmr);
	if(Ptr.Arr[3]&&!Ptr.CCn){
		RLvl=Ptr.Lvl;
		Ptr.CCn=CreateMenuStructure(Ptr.MN+"_",Ptr.Arr[3],Ptr);
		SizeMenu(Ptr.CCn);
		var Ti,Li,Hi,CCw,CCh,STp,SLt,
		MWt=parseInt(Ptr.style.width)+Ptr.lx,MHt=parseInt(Ptr.style.height)+Ptr.tx,BRW=RLvl==1?BorderWidthMain:BorderWidthSub;
		if(RightToLeft)CCw=parseInt(Ptr.CCn.style.width);
		if(BottomUp)CCh=parseInt(Ptr.CCn.style.height);
		if(RLvl<=FirstLineHorizontal){Hi=1;Li=parseInt(Ptr.style.left)-BRW;Ti=0}
		else{Hi=Li=0;Ti=parseInt(Ptr.style.top)-BRW}
		if(Hi){STp=BottomUp?Ti-CCh:Ti+MHt+2*BRW;SLt=RightToLeft?Li+MWt-CCw:Li}
		else{	SLt=RightToLeft?Li-CCw+ChildOverlap*MWt+BRW:Li+(1-ChildOverlap)*MWt;
			STp=RLvl==1&&AcrssFrms?BottomUp?Ti-CCh+MHt:Ti:BottomUp?Ti-CCh+(1-ChildVerticalOverlap)*MHt+2*BRW:Ti+ChildVerticalOverlap*MHt+BRW}
		PosMenu(Ptr.CCn,STp,SLt);
		RLvl=0}
	CurOvr=Ptr;
	IniFlg=false;ClrAllChlds(Ptr.Ctnr.FrstMbr);
	if(!Ptr.Hilite)HiliteItem(Ptr);
	//if(Exp6Plus){FStr="";if(MenuShadow)FStr+=MenuShadow;if(FStr!="")Ptr.filter=FStr}
	if(Ptr.CCn!=null&&!Ptr.CCn.Shw)RememberStatus?Unfld():OpnTmr=setTimeout("Unfld()",UnfoldDelay);
	status=Ptr.Arr[16]}

function Unfld(){
	var P=CurOvr,CSt=P.Ctnr.style,CCnt=P.CCn,CCSt=CCnt.style,CCmSt=CCnt.mif.style,
	THt=parseInt(P.style.height),TWt=parseInt(P.style.width),TLt=AcrssFrms&&P.Lvl==1&&!FirstLineHorizontal?0:parseInt(CSt.left),
	TTp=AcrssFrms&&P.Lvl==1&&FirstLineHorizontal?0:parseInt(CSt.top),CCW=parseInt(CCSt.width),CCH=parseInt(CCSt.height),
	TS=ExpYes?SCmplnt?ScHtml.scrollTop:ScLoc.document.body.scrollTop:ScLoc.pageYOffset,
	LS=ExpYes?SCmplnt?ScHtml.scrollLeft:ScLoc.document.body.scrollLeft:ScLoc.pageXOffset,
	SLt=AcrssFrms&&P.Lvl==1?CCnt.OrgLeft+TLt+LS:CCnt.OrgLeft+TLt,	STp=AcrssFrms&&P.Lvl==1?	CCnt.OrgTop+TTp+TS:CCnt.OrgTop+TTp;
	if(!ShwFlg){ShwFlg=true;BeforeFirstOpen()}
	if(MenuWrap){
		if(RightToLeft){if(SLt<LS)SLt=P.Lvl==1?LS:SLt+(CCW+(1-2*ChildOverlap)*TWt);if(SLt+CCW>SWinW+LS)SLt=SWinW+LS-CCW}
		else{if(SLt+CCW>SWinW+LS)SLt=P.Lvl==1?SWinW+LS-CCW:SLt-(CCW+(1-2*ChildOverlap)*TWt);if(SLt<LS)SLt=LS}
		if(BottomUp){if(STp<TS)STp=P.Lvl==1?TS:STp+(CCH-(1-2*ChildVerticalOverlap)*THt);if(STp+CCH>SWinH+TS)STp=SWinH+TS-CCH+0}
		else{if(STp+CCH>TS+SWinH)STp=P.Lvl==1?STp=TS+SWinH-CCH:STp-CCH+(1-2*ChildVerticalOverlap)*THt;if(STp<TS)STp=TS}}
	CCSt.top=CCmSt.top=STp+P_X;CCSt.left=CCmSt.left=SLt+P_X;
	if(Exp6Plus&&MenuSlide){CCnt.filters[0].Apply();CCnt.filters[0].play()}
	CCSt.visibility=CCmSt.visibility=M_Show}

function CloseMenu()
{
	if(Ldd&&Crtd){status="";
	if(this==CurOvr) {
	if(OpnTmr)clearTimeout(OpnTmr);
	if(CloseTmr)clearTimeout(CloseTmr);
		IniFlg=true;
		CloseTmr=setTimeout("Initiate(CurOvr)",DissapearDelay)
		//if(Exp6Plus)TS.filter=""
	}}}

function CntnrSetUp(NoOff,WMu,Mc,TL){
	var x=eval(WMu+"[10]")!=""?eval(WMu+"[10]"):BorderColor,TS=this.style;
	this.Lvl=RLvl;this.FrstMbr=null;this.NrItms=NoOff;this.Cllr=Mc;this.Shw=0;this.OrgLeft=this.OrgTop=0;
	if(x)TS.backgroundColor=x;
	TS.zIndex=RLvl+Ztop;if(ExpYes&&!MacExp5)this.mif.style.zIndex=TS.zIndex-1;
	if(Nav_Op&&!Opr7&&MenuOpacity)TS.MozOpacity=parseInt(MenuOpacity.substring(MenuOpacity.indexOf("=")+1,MenuOpacity.indexOf(")")))/105;
	if(Exp6Plus)
	{
		if (!TL) {
			FStr="";
			if(MenuSlide&&RLvl!=1)FStr=MenuSlide;
			if(DropMenuShadow)FStr+=DropMenuShadow;
			if(MenuOpacity)FStr+=MenuOpacity;
			if(FStr!="")TS.filter=FStr
		}
	}
	if(ExpYes&&!MacExp5&&OverFormElements)this.mif.style.filter="Alpha(Opacity=0)"}

function MbrSetUp(MbC,PrMmbr,WMu,TL){
	var Lctn=RLvl==1?FLoc:ScLoc,t,a,ta2=this.Arr[2],Tfld=this.Arr[0];
	this.PrvMbr=PrMmbr;this.Lvl=RLvl;this.Ctnr=MbC;this.CCn=this.ai=null;this.Hilite=this.DoRmbr=this.Clckd=this.ro=this.rob=this.lx=this.tx=this.ltp=this.tpd=0;
	this.OM=OpenMenu;this.MN=WMu;this.style.overflow="hidden";
	this.style.cursor=(this.Arr[1]||(RLvl==1&&UnfoldsOnClick))?ExpYes?"hand":"pointer":"default";
	if(Tfld.indexOf("rollover")!=-1){
		this.ro=1;this.ri1=Tfld.substring(Tfld.indexOf("?")+1,Tfld.lastIndexOf("?"));this.ri2=Tfld.substring(Tfld.lastIndexOf("?")+1,Tfld.length);this.rid=WMu+"i";
		Tfld="<img src=\""+this.ri1+"\" name=\""+this.rid+"\">"}
	this.value=Tfld;
	if(!this.Arr[6])this.Arr[6]=LowBgColor;if(this.Arr[6]&&!this.ro)this.style.backgroundColor=this.Arr[6];
	if(!this.Arr[7])this.Arr[7]=HighBgColor;
	if(!this.Arr[8])this.Arr[8]=FontLowColor;this.style.color=this.Arr[8];
	if(!this.Arr[9])this.Arr[9]=FontHighColor;
	if(!this.Arr[11])this.Arr[11]=FontFamily;this.style.fontFamily=this.Arr[11];
	if(this.Arr[12]==-1)this.Arr[12]=FontSize;this.style.fontSize=this.Arr[12]*(NavYes?1:FntFc)+"px";
	if(this.Arr[13]==-1)this.Arr[13]=FontBold;this.style.fontWeight=this.Arr[13]?"bold":"normal";
	if(this.Arr[14]==-1)this.Arr[14]=FontItalic;this.style.fontStyle=this.Arr[14]?"italic":"normal";
	if(!this.Arr[15])this.Arr[15]=MenuTextCentered;this.style.textAlign=this.Arr[15];
	if(!this.Arr[16])this.Arr[16]=this.Arr[1];
	if(ta2){	if(ta2.indexOf("rollover")==-1)this.style.backgroundImage="url(\""+ta2+"\")";
		else{	this.rob=1;this.rib1=ta2.substring(ta2.indexOf("?")+1,ta2.lastIndexOf("?"));this.rib2=ta2.substring(ta2.lastIndexOf("?")+1,ta2.length);
			this.style.backgroundImage="url(\""+this.rib1+"\")";
			this.style.backgroundRepeat="no-repeat";
			this.style.backgroundPosition=BgImgLeftOffset+"px"}}
	if(Tfld.indexOf("<")==-1){t=Lctn.document.createTextNode(Tfld);this.appendChild(t)}
	else this.innerHTML=Tfld;
	if(this.Arr[3]){
		a=RLvl<=FirstLineHorizontal?BottomUp?9:3:RightToLeft?6:0;
		if(Arrws[a]){
			t=Lctn.document.createElement("img");this.appendChild(t);
			t.style.position="absolute";t.src=Arrws[a];t.style.width=Arrws[a+1]*FntFc+P_X;t.style.height=Arrws[a+2]*FntFc+P_X;this.ai=t}}
	if(ExpYes){this.onselectstart=CnclSlct;this.onmouseover=OpenMenu;this.onmouseout=CloseMenu;this.onclick=GoTo}
	else{this.addEventListener("mouseover",OpenMenu,false);	this.addEventListener("mouseout",CloseMenu,false);
		this.addEventListener("click",GoTo,false)}
}

function CreateMenuStructure(MNm,No,Mcllr){
	RLvl++;
	var i,Mbr,PMb=null,WMnu=MNm+"1",MWd=eval(WMnu+"[5]")*FntFc,MHt=eval(WMnu+"[4]")*FntFc,
	Lctn=RLvl==1?FLoc:ScLoc,MbC=Lctn.document.createElement("div"),MIF=!ExpYes||MacExp5||!OverFormElements?MbC:Lctn.document.createElement("iframe");
	Lctn.document.body.appendChild(MbC);
	if(ExpYes&&!MacExp5&&OverFormElements){MIF.src="http://www.codeproject.com/script/HVMenu/blank.html";Lctn.document.body.appendChild(MIF)}
	MbC.style.position=MIF.style.position="absolute";
	MbC.style.visibility=MIF.style.visibility=M_Hide;
	MbC.mif=MIF;
	MbC.SetUp=CntnrSetUp;MbC.SetUp(No,MNm+"1",Mcllr,(MNm=="Menu"));
	for(i=1;i<No+1;i++){
		WMnu=MNm+eval(i);
		Mbr=Lctn.document.createElement("div");Mbr.style.position="absolute";Mbr.style.visibility="inherit";MbC.appendChild(Mbr);
		Mbr.Arr=eval(WMnu);if(!Mbr.Arr[4])Mbr.Arr[4]=MHt;if(!Mbr.Arr[5])Mbr.Arr[5]=MWd;
		Mbr.SetUp=MbrSetUp;Mbr.SetUp(MbC,PMb,WMnu, (MNm=="Menu"));
		if(Mbr.Arr[3]&&!BuildOnDemand){Mbr.CCn=CreateMenuStructure(WMnu+"_",Mbr.Arr[3],Mbr)}
		PMb=Mbr}
	MbC.FrstMbr=Mbr;
	RLvl--;return(MbC)}

function CreateMenuStructureAgain(MNm,No){
	var Mbr=FrstCntnr.FrstMbr,i,WMnu;
	if(!BuildOnDemand)	{RLvl++;for(i=No;i>0;i--){WMnu=MNm+eval(i);if(Mbr.Arr[3])Mbr.CCn=CreateMenuStructure(WMnu+"_",Mbr.Arr[3],Mbr);Mbr=Mbr.PrvMbr}RLvl--}
	else{while(Mbr){Mbr.CCn=null;Mbr=Mbr.PrvMbr}}}