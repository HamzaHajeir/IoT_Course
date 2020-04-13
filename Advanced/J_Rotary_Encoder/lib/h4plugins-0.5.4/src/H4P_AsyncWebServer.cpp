/*
 MIT License

Copyright (c) 2019 Phil Bowles <h4plugins@gmail.com>
   github     https://github.com/philbowles/esparto
   blog       https://8266iot.blogspot.com     
   groups     https://www.facebook.com/groups/esp8266questions/
              https://www.facebook.com/Esparto-Esp8266-Firmware-Support-2338535503093896/
                			  

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/
#include<H4P_WiFiSelect.h>
#ifndef H4P_NO_WIFI
#include<H4P_AsyncWebServer.h>
#include<H4P_BinaryThing.h>

extern  void h4AddAwsHandlers();

void  H4P_AsyncWebServer::_hookIn(){ 
    DEPEND(wifi);
    H4Plugin* p=isLoaded(onofTag());
    if(p) _btp=reinterpret_cast<H4P_BinaryThing*>(p);
}

void H4P_AsyncWebServer::_rest(AsyncWebServerRequest *request){
	if(!_webAuth(request)) return;
	h4.queueFunction(bind([this](AsyncWebServerRequest *request){
        H4EVENT("_rest %s",request->client()->remoteIP().toString().c_str());
		string chop=replaceAll(CSTR(request->url()),"/rest/","");
        string msg="";
        uint32_t res=h4cmd._simulatePayload(CSTR(chop),aswsTag());
        if(isLoaded(cerrTag())) msg=h4ce.getErrorMessage(res);
        string j="{\"res\":"+stringFromInt(res)+",\"msg\":\""+msg+"\",\"lines\":[";
        string fl;
        if(!res){
            for(auto &l:lines){
                if(l.back()=='\n') l.pop_back();
                fl+="\""+l+"\",";
            }
            if(fl.size()) fl.pop_back();
        }
        j+=fl+"]}";
        request->send(200,"application/json",CSTR(j));
        lines.clear();
	},request),nullptr,H4P_TRID_ASWS);
}

void H4P_AsyncWebServer::_setBothNames(const string& host,const string& friendly){
    if(isLoaded(upnpTag())) h4wifi._setPersistentValue(nameTag(),friendly,false);
    h4wifi.host(host);
}

void H4P_AsyncWebServer::_start(){
	reset();

    if(isLoaded(onofTag())){
        _cb[onofTag()]="1";
        _evts=new AsyncEventSource("/evt");
        _evts->onConnect([this](AsyncEventSourceClient *client){
            H4EVENT("SSE Client %08x n=%d",client,client->lastId());
            client->send(_btp->state() ? "1":"0",onofTag(),millis(),1000);
        });
        addHandler(_evts);
    } else _cb[onofTag()]="0";

    on("/",HTTP_GET, [this](AsyncWebServerRequest *request){ 
        H4EVENT("Root %s",request->client()->remoteIP().toString().c_str());
        _cb["wifi"]=stringFromInt(WiFi.getMode());
        request->send(SPIFFS,"/sta.htm",String(),false,aswsReplace);
    });

    on("/",HTTP_POST, [this](AsyncWebServerRequest *request){ 
        H4EVENT("Root POST %s",request->client()->remoteIP().toString().c_str());
    	H4P_CONFIG_BLOCK rp;
	    int params = request->params();
	    for(int i=0;i<params;i++){
		    AsyncWebParameter* p = request->getParam(i);
		    rp[CSTR(p->name())]=CSTR(p->value());
	    }
        h4wifi.change(rp[ssidTag()],rp[pskTag()]);
        //
        _setBothNames(rp[deviceTag()],rp[nameTag()]);
    });

	on("/rest",HTTP_GET,[this](AsyncWebServerRequest *request){ _rest(request); });

    h4AddAwsHandlers();
    serveStatic("/", SPIFFS, "/").setCacheControl("max-age=31536000");
    // 404 ?
    begin();
    _upHooks();
}

void H4P_AsyncWebServer::_stop(){ 
    end();
    _downHooks();
}

bool H4P_AsyncWebServer::_webAuth(AsyncWebServerRequest *request){
	if(_cb[userTag()]!=""){
		if(!request->authenticate(CSTR(_cb["auser"]),CSTR(_cb["apasswd"]),NULL,false)) {
			request->requestAuthentication(NULL,false);
			return false;
		}
	} return true;
}

String H4P_AsyncWebServer::aswsReplace(const String& var){
    string v=CSTR(var);
    return _cb.count(v) ? String(CSTR(_cb[v])):"?";
}

#endif // H4_WIFI