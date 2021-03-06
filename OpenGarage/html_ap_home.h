const char html_ap_home[] PROGMEM = R"(<body>
<style> table, th, td {	border: 0px solid black;  border-collapse: collapse;}
table#rd th { border: 1px solid black;}
table#rd td {	border: 1px solid black; border-collapse: collapse;}</style>
<caption><b>OpenGarage WiFi Config</caption><br><br>
<table cellspacing=4 id='rd'>
<tr><td>SSID</td><td>Strength</td><td>Power Level</td></tr>
<tr><td>(Scanning...)</td></tr>
</table>
<br><br>
<table cellspacing=16>
<tr><td><input type='text' name='ssid' id='ssid'></td><td>(SSID)</td></tr>
<tr><td><input type='password' name='pass' id='pass'></td><td>(Password)</td></tr>
<tr><td><input type='text' name='auth' id='auth'></td><td><label id='lbl_auth'>(Auth Token)</label></td></tr>
<tr><td colspan=2><p id='msg'></p></td></tr>
<tr><td><button type='button' id='butt' onclick='sf();' style='height:36px;width:180px'>Submit</button></td><td></td></tr>
</table>
<script>
function id(s) {return document.getElementById(s);}
function sel(i) {id('ssid').value=id('rd'+i).value;}
var tci;
function tryConnect() {
var xhr=new XMLHttpRequest();
xhr.onreadystatechange=function() {
if(xhr.readyState==4 && xhr.status==200) {
var jd=JSON.parse(xhr.responseText);
if(jd.ip==0) return;
var ip=''+(jd.ip%256)+'.'+((jd.ip/256>>0)%256)+'.'+(((jd.ip/256>>0)/256>>0)%256)+'.'+(((jd.ip/256>>0)/256>>0)/256>>0);
id('msg').innerHTML='<b><font color=green>Connected! Device IP: '+ip+'</font></b><br>Device is rebooting. Switch back to<br>the above WiFi network, and then<br>click the button below to redirect.'
id('butt').innerHTML='Go to '+ip;id('butt').disabled=false;
id('butt').onclick=function rd(){window.open('http://'+ip);}
clearInterval(tci);
}
}    
xhr.open('POST', 'jt', true); xhr.send();    
}
function sf() {
id('msg').innerHTML='';
var xhr=new XMLHttpRequest();
xhr.onreadystatechange=function() {
if(xhr.readyState==4 && xhr.status==200) {
var jd=JSON.parse(xhr.responseText);
if(jd.result==1) { tci=setInterval(tryConnect, 10000); return; }
id('msg').innerHTML='<b><font color=red>Error code: '+jd.result+', item: '+jd.item+'</font></b>';
id('butt').innerHTML='Submit';
id('butt').disabled=false;id('ssid').disabled=false;id('pass').disabled=false;id('auth').disabled=false;
}
}
var comm='cc?ssid='+encodeURIComponent(id('ssid').value)+'&pass='+encodeURIComponent(id('pass').value)+'&auth='+id('auth').value;
xhr.open('GET', comm, true); xhr.send();
id('butt').innerHTML='Connecting...';
id('butt').disabled=true;id('ssid').disabled=true;id('pass').disabled=true;id('auth').disabled=true;
}

function loadSSIDs() {
  //Hide auth info to more clearly support multiple tools without breaking app
  id('auth').hidden =true;
  id('lbl_auth').hidden =true;
  var xhr=new XMLHttpRequest();
  xhr.onreadystatechange=function() {
    if(xhr.readyState==4 && xhr.status==200) {
      id('rd').deleteRow(1);
      var i;
      var jd=JSON.parse(xhr.responseText);
      //TODO Sort and remove dups
      for(i=0;i<jd.ssids.length;i++) {
        var signalstrength= jd.rssis[i]>-71?'Ok':(jd.rssis[i]>-81?'Weak':'Poor');
        var row=id('rd').insertRow(-1);
        row.innerHTML ="<tr><td><input name='ssids' id='rd"+i+"' onclick='sel(" + i + ")' type='radio' value='"+jd.ssids[i]+"'>" + jd.ssids[i] + "</td>"  + "<td align='center'>"+signalstrength+"</td>" + "<td align='center'>("+jd.rssis[i] +" dbm)</td>" + "</tr>";
      }
    }
  };
  xhr.open('GET','js',true); xhr.send();
  }
  setTimeout(loadSSIDs, 1000);
</script>
</body>)";
