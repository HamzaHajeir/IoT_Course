var source;
var tab;
var ticker;
var pins=[];
var lbls=[];
var dlys=[];
var ephs=[];
var ths=[];
var chx=[];
var grfs = new Map();
var client=0;
var kafq=0;
var grow=0;
var ping=0;

var pinstyle=[
	"UNUSED",
	"RAW",
	"OUTPUT",
	"DEBOUNCED",
	"FILTERED",	
	"LATCHING",
	"COUNT_LATCH",
	"CIRCLE_LATCH",
	"RETRIGGERING",
	"ENCODER",
	"ENCODER_AUTO",
	"REPORTING",
	"TIMED",
	"POLLED",
  "DEFAULT_OUT",
  "DEFAULT_IN",
  "ENCODER_B",
  "MULTI-STAGE"
  ];

var ajf=new Map([
  ["ajok",function(){}],
  ["aso",gpSelect],
  ["beat",doBeat],
  ["die",doDie],
  ["dpin",doDpin],
  ["dynx",doDynx],
  ["gear",doGear],
  ["gpio",doGPIO],
  ["init",doInit],
  ["kill",doKill],
  ["lex",doLex],
  ["logs",doLogs],
  ["ota",doOta],
  ["pins",doPins],
  ["plot",doPlot],  
  ["shed",doShed],
  ["stus",doStatus],
  ["tabs",doTabs],
  ["tool",doTool],
  ["cmds",doCmds],
  ["vbar",doVbar],
  ["vset",doVset]
]);

function cbi(e,v){ document.getElementById(e).setAttribute("class",v); }
function clr(e){ ibi(e,""); }
function dbi(e){ document.getElementById(e).setAttribute("disabled",""); }
function ebi(e){ document.getElementById(e).removeAttribute("disabled"); }
function ibi(e,v){ document.getElementById(e).innerHTML=v; }
function show(e,t="block"){
  var x=document.getElementById(e);
  if(x) x.style.display=t;
}
function vis(e){ document.getElementById(e).style.visibility="visible"; }

function addDphkc(th){ th.setAttribute("onclick","killclick("+parseInt(th.innerHTML)+");"); }

function addDphme(th){
    th.setAttribute("class","dph");
 		th.setAttribute("onmouseenter","dynpEnter("+parseInt(th.innerHTML)+");");
}

function addDynpHandlers(){
  document.querySelectorAll("th[X]").forEach(function(th){ addDphme(th); });
  document.querySelectorAll("th:not([class='dpu']):not([X])").forEach(function(th){ addDphkc(th); });
}

function ajaxPOST(url,params={}){
  var http = new XMLHttpRequest();
//  var fullurl="http://"+document.getElementById("IP").innerHTML+"/ajax/"+url+"/";
  var fullurl="http://"+window.location.hostname+"/ajax/"+url+"/";
  
  http.addEventListener("load", function(e){
    source.addEventListener('exec', preDespatch);
    jsonDespatch(e.currentTarget.responseText);
  },{capture: true});
  var flat = "";for(var p in params){ flat+=p+"="+params[p]+"&"; } flat.replace(/&$/,''); // reformat params
  http.open('POST', fullurl);
  http.setRequestHeader("X-Esparto-Client", client); 
  http.setRequestHeader('Content-type', 'application/x-www-form-urlencoded');
  source.removeEventListener('exec', preDespatch);
  //
  http.send(flat);  
}

function axOutputs(fld,tit){
	var data={
		name: fld,
    ho: "axdata",
    tit: tit,
    id: "aop",
		opts:[]
	};
	var ops=document.getElementsByClassName("output");

	for(var i=0;i<ops.length;i++){
		var pin=parseInt(ops[i].id.replace(/p/,""));
		if(pin<18) data.opts.push({value: pin, disp: "GPIO "+pin });
	}
	gpSelect(data);
}

function binaryRadio(name,tit,one,zero,hangoff){
	var s1=document.createElement("span");
	s1.innerHTML=one;
	
	var s2=document.createElement("span");
	s2.innerHTML=zero;
	
	var c=document.createElement("div");
	c.className="dhl";
	c.appendChild(s1);
	c.appendChild(makeRadio(name,"1"));	
	c.appendChild(s2);
	c.appendChild(makeRadio(name,"0"));
	
	gpAddField(name,tit,c,hangoff);
}

function clrPin(i){
  pins[i].removeAttribute("style");
  pins[i].removeAttribute("title");
  pins[i].removeAttribute("id");
  pins[i].innerHTML="";
}

function config(e){
  var t=e.id.replace("tab","");
	for(var i=0;i<ephs.length;i++) ephs[i].style.display=ephs[i].id==t ? "block":"none";
	if(t=="dynp") addDynpHandlers();
	else loseDynpHandlers();
  if(t!=tab){
    source.removeEventListener(tab,preDespatch);
    setTab(t);
  }
}

function doBeat(data){
  var onoff=parseInt(data.h);
  ibi("ut",data.t);
  ibi("nv",data.v);
  if(data.c!="0") {
    vis("ck"); // tidy this 1x only
    ibi("ck",data.c);
  }
  document.documentElement.style.setProperty("--heart-color",onoff ? "#777777":"#ff0000");
  var heart=document.getElementById("hb");
  heart.setAttribute("class","cmd big");
  setTimeout(function(){ heart.setAttribute("class","cmd"); },250);
  if((grow%60)===0){
    var grass=document.getElementById("grass");
    var pc=parseFloat(window.getComputedStyle(grass).backgroundSize.replace(/%$/,''));
    if(pc!=100) pc+=0.25;
    else pc=0;
    grass.style.backgroundSize=pc+"%";
  }
  grow++;
  if(client) if(!(++ping%kafq)) ajaxPOST("ping");
}

function doDie(data){
    client=0;
    source.removeEventListener(tab,preDespatch);
    source.removeEventListener('exec', preDespatch);   
}

function doCmds(data){
  var disp=[];
  for(var i=0;i<data.length;i++) disp.push({disp: data[i]});
 	gpSelect({id: "csel",clr: "1",opts:	disp });
}

function doDpin(data){
  var legend;
  var i=parseInt(data.p);
  var d=parseInt(data.d);
  var t=parseInt(data.t);
  if(t){
    ths[i].setAttribute("onclick","dynpSelect("+i+");");
    legend=pinDetails(i,t,d);
  }
  else legend="CAN'T USE";
  ths[i].setAttribute("tooltip",legend);
}

function doDynx(data){
  var p=data.pin;
  dbi("fsp");
  resetSel("selstyle");  
  resetSel("axion");
	document.getElementById("dpsel").value="click red pin #";
  ths[p].removeAttribute("X");
  loseDynpHandler(ths[p]);
  addDphkc(ths[p]);
}
// g,i,m,l,t,d
function doGear(data){
  for(var i=0;i<data.length;i++){
    gd=data[i];
    if(!grfs.has(gd.m)){
      doGraph(gd.m);
      var grf=new graph("gc"+gd.m,gd.l,2,gd.t,gd.d);
      grfs.set(gd.m,grf);
    }
  }
}

function doGPIO(data){
  for(var i=0;i<data.length;i++){
    var p=parseInt(data[i].p);
    setPin(p,data[i].r);
    setPin(p+18,data[i].c);
  }
}

function dgsDiv(c,t,i,hang){
  var dgs=document.createElement("div");
  dgs.className=c;
  dgs.innerHTML=t;
  hang.appendChild(dgs);
  
  var dgs2=document.createElement("div");
  dgs2.className="right";
  var dgs3=document.createElement("div");
  dgs3.id=i;
  dgs3.className="std";
  dgs3.innerHTML="0";
  dgs2.appendChild(dgs3);
  hang.appendChild(dgs2);  
}

function doGraph(m){
  var g=document.getElementById("gear");
  var sth=document.createElement("div");
  sth.className="sth";
  dgsDiv("stm",m+":",m,sth);
  dgsDiv("stt","min:",m+"min",sth);
  dgsDiv("stt","max:",m+"max",sth);
  dgsDiv("stt","cma:",m+"cma",sth);
  g.appendChild(sth);

  var can=document.createElement("div");
  can.className="can";
  var vas=document.createElement("canvas");
  vas.id="gc"+m;
  vas.width="360";
  vas.height="100";
  can.appendChild(vas);
  g.appendChild(can);  
}

function doInit(data){
  client=data.clid;
  kafq=data.kafq;
  document.getElementById("ota0").setAttribute("omax",data.om0);
  document.getElementById("ota100").setAttribute("omax",data.om100);
  if(parseInt(data.dio)) vis("dflt");
}

function doInvoke(){ ajaxPOST("cmd", {act: document.getElementById("invoke").value, pl:document.getElementById("payload").value }); }

function doKill(data){
  var i=parseInt(data.p);
  clrPin(i);
  lbls[i].innerHTML="";
  lbls[i].removeAttribute("title");
  clrPin(i+18);
  onePin(data);
  addDphme(ths[i]);
}

function doLex(data){
    var v=data.value;
    ibi("ptit",v);
    ibi("lex",v);
    doVset({name: "lexname", value: v});
}

function doLogs(data){
    var c=document.getElementById("clog");
    var d=new Date();
    c.innerHTML=d.toLocaleDateString()+" "+data.msg+"\r\n"+c.innerHTML;
    ibi("urg",data.msg);
    var u=document.getElementById("urg");
    u.innerHTML=data.msg;
    u.setAttribute("transform","scale(1.2)");
    setTimeout(function(){ u.removeAttribute("transform"); }, 250);  
    setTimeout(function(){ u.innerHTML=""; }, 1500);  
}

function doOta(data){
  show("urg","none");
  show("prog","inline-block");
  var color=parseInt(data.oc);
  var pcent=parseInt(data.bu);
  document.getElementById("pbar").style.width=(pcent+"%");
  document.getElementById("pbar").style.backgroundColor=color ? "orange":"red";
  ibi("pbar",pcent+"%");
  if(pcent==100) setTimeout(function(){
    show("urg","inline-block");
    show("prog","none");
    }, 250);  
}

function doPins(data){ for(var i=0;i<data.length;i++) onePin(data[i]); }

function doPlot(data){
  if(grfs.size){
    for(var i=0;i<data.length;i++){
      var pd=data[i];
      var base=pd.m;
      grfs.get(base).plot(pd.c);      
      ibi(base,pd.c);
      ibi(base+"min",pd.n);
      ibi(base+"max",pd.x);   
      ibi(base+"cma",pd.a);   
    }
  }
}

function addAlarm(){
    ajaxPOST("alrm",{
      "t": document.getElementById("rtct").value,
      "r": document.getElementById("rtcd").checked ? "1":"0",
      "b": document.getElementById("rtcl").classList.contains("led-green") ? "1":"0"
    });
}

function doShed(data){
  var o=document.getElementById("shed");
  o.innerHTML="";

  for(var i=0;i<data.length;i++){
 
    var bin=document.createElement("img");
    bin.className="hand";
    bin.src="/bin.png";
    bin.setAttribute("onclick",'ajaxPOST("shed",{k: '+data[i].k+'});');
    bin.title="Delete "+( parseInt(data[i].r) ? "daily":"1-off")+" timer @ "+data[i].d;
    
    var alm=document.createElement("img");
    alm.src=parseInt(data[i].r) ? "/alm.png":"";
    
    var divlt=document.createElement("div");
    divlt.className="lt";
    divlt.appendChild(alm);
    
    var onoff=parseInt(data[i].b);
    var divled=document.createElement("div");
    divled.className="lr"+(onoff < 0 ? "":" ld led-"+( onoff ? "green":"red"));
    divled.setAttribute("uid",onoff);
     
    var divdk=document.createElement("div");
    divdk.className="dk";
    divdk.innerHTML=data[i].d;
    
    var divsb=document.createElement("div");
    divsb.className="sb";
    
    divsb.appendChild(divdk);
    divsb.appendChild(divled);				
    divsb.appendChild(divlt);				
    divsb.appendChild(bin);
    o.appendChild(divsb);
  }
}

function _doStatus(x,n){
  vis(x+"0");
  show(x+"info");
  setLED(document.getElementById(x+"LED"),n -1);
}

function doStatus(data){
  var k=Object.keys(data);
  if(data.dio){
    var dio=parseInt(data.dio);
    document.getElementById("dio").src="/"+dio+".png";
    delete data.dio;
  }

  for(var i=0;i<k.length;i++){
    var n=parseInt(data[k[i]]);
    if(n) _doStatus(k[i],n);
  }
}

function doTabs(data){
  for(var i=0;i<data.length;i++){
    var tab=document.getElementById(data[i]+"tab");
    tab.style.display="inline-flex";
    tab.setAttribute("onclick","config(this);");
  }
}

function doTool(data){
  var o=document.getElementById("tool");
  o.innerHTML="";
  for(var i=0;i<data.length;i++){
    var k=data[i].key;
    var inp=document.createElement("input");
    inp.value=data[i].value;
    inp.id=k;
    inp.onblur=function(e){ setVar(e.target.id,e.target.value); };
    inp.required=true;
    var divlt=document.createElement("div");
    divlt.className="lt";
    divlt.appendChild(inp);
    var divdk=document.createElement("div");
    divdk.className="dk";
    divdk.innerHTML=k;
    var divsb=document.createElement("div");
    divsb.className="sb";										
    divsb.appendChild(divdk);
    divsb.appendChild(divlt);				
    o.appendChild(divsb);        
  }
}

function doVbar(data){ grfs.forEach(function(x){ x.strike(data.c); }); }

function doVset(data){
  var t=document.getElementById(data.name);
  if(t){
    t.value=data.value;
    t.setAttribute("class","big red");
    setTimeout(function(){ t.removeAttribute("class"); }, 125);      
  }
}

function dpAxionChange(e){
  clr("axdata");
	var choice=parseInt(e.value);
	switch(choice){
		case 1:
		case 2:
			break;
		case 3:
			axOutputs("dpk","PassTo");
      binaryRadio("dpl","Invert","Yes","No","axdata");
			break;
    case 4:
    case 6:
    case 7:
    case 9:
    case 10:
    case 11:
      hanger("varsh");
      ajaxPOST("vars",{fld: "dpl"});
      break;
    case 5:
      hanger("varsh");
      ajaxPOST("vars",{fld: "dpl"});
      dpscValue("dpl","Value","axdata",false);
      binaryRadio("dpm","Text / Num","Text","Numeric","axdata");
      break;
    case 8:
      hanger("topxh");
      ajaxPOST("topx",{fld: "dpl"});
      dpscValue("dpm","Payload","axdata",false,false);
      break;
    case 12:
    case 16:
      axOutputs("dpl","Pin");
      dpscValue("dpm","Rate","axdata");
      break;
    case 13:
      axOutputs("dpl","PWM_Pin");
      dpscValue("dpm","Period","axdata");
      dpscValue("dpn","Duty Cycle","axdata");
      break;
    case 14:
      axOutputs("dpl","Pattern_Pin");
      dpscValue("dpm","Timebase","axdata");
      dpscValue("dpn","Pattern","axdata",false);
      break;
    case 15:
      axOutputs("dpl","Pin");
      break;
		default:
      break;
	}
	if(choice) ebi('fsk');
	else dbi('fsk');
}

function dpscMode(){
	gpSelect({name: "dpc",
            ho: "dpextra",
            tit: "Mode",
						opts:	[{value: "0", disp: "INPUT" },{value: "2", disp: "INPUT_PULLUP" }]
						});
}

function dpscPinB(exclude){
	var data={
		name: "dpe",
    tit: "Pin B",
    ho: "dpextra",   
		opts:[]
	};
	var dph=document.getElementsByClassName("dph");
	for(var i=0;i<dph.length;i++){
		if(dph[i].tooltip!="CAN'T USE"){ // must be a better way
			var pin=parseInt(dph[i].innerHTML);
			if(pin!=exclude && pin!=17)	data.opts.push({value: pin, disp: "GPIO "+pin });
		}
	}
	gpSelect(data);		
}

function dpscValue(field,tit,id="dpextra",num=true,mand=true){
	var ipv=document.createElement("input");
	ipv.name=field;
	ipv.type=num ? "number":"text";
	if(mand) ipv.setAttribute("required","");
	ipv.setAttribute("checked","");
	gpAddField(field,tit,ipv,id);
}

function dpstyleChange(e){
	var pin=document.getElementById("dpsel").value;
	var choice=parseInt(e.value);
	clr("axdata"); 
	clr("dpextra"); 
	var dpe=document.getElementById("dpextra");
	switch(choice){
		case 2: // output
		case 12: // dfltout
      dummyMode(dpe);
			binaryRadio("dpd","Active","Hi","Lo&nbsp;","dpextra");
			binaryRadio("dpe","Initial","On","Off","dpextra");				
			break;
		case 1: // raw
			dpscMode();
			break;
		case 3: // debounced
		case 5:	// latching
		case 10: // timed
			dpscMode();
			dpscValue("dpd","Debounce");
			break;			
		case 9: // reporting
			dpscMode();
			dpscValue("dpd","Debounce");
			dpscValue("dpe","Freq'y");
			break;
		case 4: // filter
			dpscMode();
			binaryRadio("dpd","Filter","Hi","Lo","dpextra");
			break;
		case 6: // retrig		
			dpscMode();
			dpscValue("dpd","Timeout");
			binaryRadio("dpe","Active","Hi","Lo","dpextra");			
			break;
		case 7: // encoder
			dpscMode();
			dpscPinB(pin);
			break;
		case 8: // encoder auto
			dpscMode();
			dpscPinB(pin);
			dpscValue("dpe","Vmin");
			dpscValue("dpf","Vmax");
			dpscValue("dpg","Vinc");
			dpscValue("dph","Vset");
			break;
		case 11: // polled
			dpscMode();
			dpscValue("dpe","Freq'y");
			binaryRadio("dpf","A-D","ADC","Digital","dpextra");
			break;
    case 13:
      dummyMode(dpe);
      dpscValue("dpf","Debounce");
      break;
		default:
//			console.warn("what A choice? ",choice);
			break;
	}
	if(choice) {
    ebi('fsa');
		document.getElementById("axion").setAttribute("onchange","dpAxionChange(event.target);");
	}	else {
    dbi('fsa');
  }
}

function dummyMode(dpe){
  var hid=document.createElement("input");
  hid.type="hidden";
  hid.value="1";
  hid.name="dpc";
  hid.setAttribute("checked","checked");
  dpe.appendChild(hid);
}

function dynpEnter(i){ ajaxPOST("dpin",{pin: i}); }

function dynpSelect(i){
	document.getElementById("dpsel").value=i;
  ebi("fsp");
}

function gpAddField(name,tit,ipf,hangoff){
	var lbl=document.createElement("label");
	lbl.setAttribute("for",name);
	lbl.innerHTML=tit;
	var field=document.createElement("div");
	field.className="fel";
	field.appendChild(lbl);
	field.appendChild(ipf);
	document.getElementById(hangoff).appendChild(field);
}

function gpSelect(data){
	var opts=data.opts;
  var sel=document.getElementById(data.id);
  if(!sel){
  	sel=document.createElement("select");
    sel.name=data.name;
 		if(data.id) sel.id=data.id;  
    gpAddField(data.name,data.tit,sel,data.ho);
  }
  else if(parseInt(data.clr)) sel.innerHTML="";

	var selopt;	
	for(var i=0;i<opts.length;i++){
		selopt=document.createElement("option");
    selopt.innerHTML=opts[i].disp;
 		if(opts[i].value) selopt.value=opts[i].value;
    else selopt.value=opts[i].disp;
    if(data.cur) if(selopt.value==data.cur) selopt.setAttribute("selected","");
		sel.appendChild(selopt);
	}
}

function hanger(h){
  var hang=document.createElement("div");
  hang.id=h;
  document.getElementById("axdata").appendChild(hang);  
}

function jsonDespatch(msg){
  var jis=JSON.parse(msg);
  for(var o in jis) ajf.get(o)(jis[o]);
}

function killclick(i){ if(confirm("Do you really want to delete GPIO "+i)) ajaxPOST("kill", {pin: i} );  }

function loseDynpHandler(th){
  th.removeAttribute("onmouseenter");
  th.removeAttribute("onclick");
  th.removeAttribute("tooltip");
  th.removeAttribute("class");
}

function loseDynpHandlers(){
  document.querySelectorAll("th:not([class='dpu'])").forEach(function(th){ loseDynpHandler(th); });  
}

function makeRadio(name,value){
	var r=document.createElement("input");
	r.type="radio";
	r.name=name;
	r.id=name+value;
	r.value=value;
	if(value=="0") r.setAttribute("checked","");
	return r;
}

function mqttControl(t){
  var b=t.classList.contains("led-red");
  setVar(t.getAttribute("value"),b ? "1":"0");  
}

function nike(n){ ajaxPOST("nike", {do: n} );}

function onePin(pin){
    var p=parseInt(pin.p)
    var type=parseInt(pin.t);
    var style=parseInt(pin.s);
    var dno=parseInt(pin.d);
    if(style){
      pins[p].setAttribute("style","visibility:visible"); // refac?
      pins[p+18].setAttribute("style","visibility:visible");
      pins[p].setAttribute("title", pinstyle[style]);
      pins[p].id="p"+p;
      if(style==2 || style==12) setClick(p);
      lbls[p].innerHTML=pinDetailsShort(type,dno);
      lbls[p].setAttribute( "title", pinDetails(p,type,dno));     
    }
    else {
      if(!type) ths[p].setAttribute("class","dpu");
      else ths[p].setAttribute("X","");
    }
}

function pinDetails(pin,type,digitalPin){
		var rv="GPIO"+pin+" is "+pinDetailsShort(type,digitalPin);
		switch(type){
			case 1:
				return rv+" MAY AFFECT BOOTING - USE CAUTION";
			case 2:
				return rv+" CANNOT USE AT SAME TIME AS SERIAL";													
			case 3:
				return rv+" CANNOT USE AT SAME TIME AS SERIAL";													
			case 4:
				return rv+" Standard GPIO pin";													
			case 5:
				return rv+" NONSTANDARD GPIO - MAY CONFLICT WITH WAKE/SLEEP";													
			case 6:
				return rv+" Analog to Digitial Converter";													
			case 7:
				return rv+" Builtin LED";	
			case 8:
				return rv+" Builtin Button";	
			case 9:
				return rv+" Builtin Relay";												
			default:
				return rv+" UNNAMED PIN "+digitalPin;
		}	
}

function pinDetailsShort(type,digitalPin){
		switch(type){
			case 1:
			case 4:
			case 5:
				return "D"+digitalPin;
			case 2:
				return "RX";													
			case 3:
				return "TX";																					
			case 6:
				return "AD";													
			case 7:
				return "LD";	
			case 8:
				return "BN";	
			case 9:
				return "RY";												
			default:
				return "&nbsp;&nbsp;";	
		}
}

function postForm(e){
	e.preventDefault();
  var f=e.target;
	var fields=Array.from(f.elements).filter(e => e.getAttribute("name"));
  formdata={};
	for(var i=0;i<fields.length;i++){
    if(fields[i].type=="checkbox") formdata[fields[i].name]=fields[i].checked ? "1":"0";
    else {
      if(!(fields[i].type=="radio" && !(fields[i].checked))) formdata[fields[i].name]=fields[i].value;
    }
  }
  ajaxPOST("form",formdata);
  return false;
}

function preDespatch(e){ jsonDespatch(e.data); }

function resetSel(s){
  var ssel=document.getElementById(s);
  ssel.value=0;
  fn=ssel.onchange;
  fn({target: {value: 0}});
}

function selchange(e){ document.getElementById("invoke").value=e.target.value; }

function setClick(i){
	pins[i].setAttribute("onclick","nike("+i+");");
	pins[i].setAttribute("class",pins[i].getAttribute("class")+" output");
}

function setPin(p,s){
  var is=parseInt(s);
  setLED(pins[p],is);
}

function setTab(t){
  source.addEventListener(t,preDespatch,false);
  ajaxPOST(t);
  tab=t;
}

function setVar(n,v){ ajaxPOST("svar",{name: n, value: v}); }

function setLED(e,b){
  e.classList.remove(b ? "led-red":"led-green");
  e.classList.add(b ? "led-green":"led-red");  
}

function rtcl(e){
  var b=e.classList.contains("led-green");
  setLED(e,!b);
}

function fup(f){
  var form = document.forms.namedItem("ota");
  var cmd=f.getAttribute("cmd");
  var fi="ota"+cmd;
  var ipf=document.getElementById(fi);
  var sz=ipf.files[0].size;
  var lim=parseInt(ipf.getAttribute("omax"));
  if(sz > lim) alert("NO CAN DO: ",sz," > ",lim);
  else {
    form.action="ota/"+cmd;
    form.setAttribute("sz",sz);
  }
}

document.addEventListener("DOMContentLoaded", function() {
	pins=document.getElementsByClassName("pin");
	lbls=document.getElementsByClassName("lbl");
	dlys=document.getElementsByClassName("hand");
	chx=document.getElementsByClassName("chx");
	ths=document.getElementsByTagName("th");
	for(var i=0;i<dlys.length;i++){ // lazy load images
		setTimeout(function(x){
			var c=x.classList[1];
			x.src=c+".png";			
			},750,dlys[i]);
	}

	ephs=document.getElementsByClassName("eph");

  if(!!window.EventSource){
    source=new EventSource("/evt");
    source.addEventListener('exec', preDespatch);
    source.addEventListener('wifi', preDespatch);
    show("wifi");
    tab="wifi";
    }

  var form = document.forms.namedItem("ota");
  form.addEventListener('submit', function(ev) {
    oData = new FormData(form);
    var cmd=ev.target.action;
    var sz=ev.target.getAttribute("sz"); 
    var oReq = new XMLHttpRequest();
    oReq.open("POST", cmd , true);
    oReq.setRequestHeader("X-Esparto-Size", sz);
    oReq.send(oData);
    ev.preventDefault();
  }, false);

});