const char html_sta_options[] PROGMEM = R"(<body>
<style>
table, th, td {
border: 0px solid black;
padding: 1px;
border-collapse: collapse;
}
</style>
<div data-role='page' id='page_opts'>
<div data-role='header'><h3>Edit Options</h3></div>    
<div data-role='content'>
<fieldset data-role='controlgroup' data-type='horizontal'>
<input type='radio' name='opt_group' id='basic' onclick='toggle_opt()' checked><label for='basic'>Basic</label>
<input type='radio' name='opt_group' id='cloud' onclick='toggle_opt()'><label for='cloud'>Integration</label>
<input type='radio' name='opt_group' id='other' onclick='toggle_opt()'><label for='other'>Advanced</label>        
</fieldset>
<div id='div_basic'>
<table cellpadding=2>
<tr><td><b>Device Name:</b></td><td><input type='text' size=10 maxlength=32 id='name' data-mini='true' value='-'></td></tr>
<tr><td><b>Sensor Type:</b></td><td>
<select name='mnt' id='mnt' data-mini='true' onChange='disable_dth()'>
<option value=0>Ceiling Mount</option>
<option value=1>Side Mount</option>
<option value=2>Switch (Low Mount)</option>
<option value=3>Switch (High Mount)</option>
</select></td></tr> 
<tr><td><b>Door Threshold (cm): </b></td><td><input type='text' size=3 maxlength=4 id='dth' data-mini='true' value=0></td></tr>
<tr><td><b>Vehicle Threshold (cm):</b><br><small>(Set to 0 to disable) </small></td><td><input type='text' size=3 maxlength=4 id='vth' data-mini='true' value=0 ></td></tr>
<tr><td><b>Read Interval (s):</b></td><td><input type='text' size=3 maxlength=3 id='riv' data-mini='true' value=0></td></tr>
<tr><td><b>Click Time (ms):</b></td><td><input type='text' size=3 maxlength=5 id='cdt' value=0 data-mini='true'></td></tr>
<tr><td><b>Sound Alarm:</b></td><td>
<select name='alm' id='alm' data-mini='true'>      
<option value=0>Disabled</option>
<option value=1>5 seconds</option>                  
<option value=2>10 seconds</option>      
</select></td></tr>
</table>
</div>
<div id='div_cloud' style='display:none;'>
<table cellpadding=1>
<tr><td><b>Accessibility:</b></td><td>
<select name='acc' id='acc' data-mini='true'>
<option value=0>Direct IP Only</option>
<option value=1>Direct IP + Cloud</option>                  
<option value=2>Cloud Only</option>
</select></td></tr>      
<tr><td><b>Blynk Token:<a href='#BlynkInfo' data-rel='popup' data-role='button' data-inline='true' data-transition='pop' data-icon='info' data-theme='c' data-iconpos='notext'>Setup info</a><div data-role='popup' id='BlynkInfo' class='ui-content' data-theme='b' style='max-width:320px;'><p>Blynk provides remote access and monitoring. Install the app and use this QR to configure <a href='https://github.com/OpenGarage/OpenGarage-Firmware/blob/master/OGBlynkApp/og_blynk_1.0.png' target='_blank'>Blynk QR</a></p></div></b></td><td><input type='text' size=20 maxlength=32 id='auth' data-mini='true' value='-'></td></tr>
<tr><td><b>IFTTT Key:<a href='#ifttInfo' data-rel='popup' data-role='button' data-inline='true' data-transition='pop' data-icon='info' data-theme='c' data-iconpos='notext'>Learn more</a><div data-role='popup' id='ifttInfo' class='ui-content' data-theme='b' style='max-width:320px;'><p><a href='https://ifttt.com' target='_blank'>IFTTT</a> provides additional notification options (e.g. SMS, email) besides Blynk.</p></div></b></td><td><input type='text' size=20 maxlength=64 id='iftt' data-mini='true' value='-'></td></tr>
<tr><td><b>MQTT Server:<a href='#mqttInfo' data-rel='popup' data-role='button' data-inline='true' data-transition='pop' data-icon='info' data-theme='c' data-iconpos='notext'>Learn more</a><div data-role='popup' id='mqttInfo' class='ui-content' data-theme='b' style='max-width:320px;'><p>MQTT provides additional workflow options through tools like NodeRed (e.g. SMS, email).</p></div></b></td><td><input type='text' size=16 maxlength=20 id='mqtt' data-mini='true' value=''></td></tr>
</table> 

<table>
<tr><td colspan=4><b>Automation:</b></td></tr>
<tr><td colspan=4></td></tr><tr><td colspan=4></td></tr>
<tr><td colspan=4>If open for longer than:</td></tr>
<tr><td><input type='text' size=3 maxlength=3 id='ati' value=30 data-mini='true'></td><td>minutes:</td><td><input type='checkbox' id='ato0' data-mini='true'><label for='ato0'>Notify me</label></td><td><input type='checkbox' id='ato1' data-mini='true'><label for='ato1'>Auto-close</label></td></tr>

<tr><td colspan=4>If open after time:<small> (Use UTC 24hr format)</small>:</td></tr>
<tr><td><input type='text' size=3 maxlength=3 id='atib' value=3 data-mini='true'></td><td> UTC:</td><td><input type='checkbox' id='atob0' data-mini='true'><label for='atob0'>Notify me</label></td><td><input type='checkbox' id='atob1' data-mini='true'><label for='atob1'>Auto-close</label></td></tr>
</table><table>
<tr><td colspan=4>Change Notifications:</td></tr>
<tr><td><input type='checkbox' id='atoc0' data-mini='true'><label for='atoc0'>Door<br> Open</label></td><td><input type='checkbox' id='atoc1' data-mini='true' ><label for='atoc1'>Door<br> Close</label></td>
<td><input type='checkbox' id='atoc2' data-mini='true' disabled><label for='atoc2'>Vehicle<br> Leave</label></td><td><input type='checkbox' id='atoc3' data-mini='true' disabled ><label for='atoc3'>Vehicle<br> Arrive</label></td></tr>
</table>
</div>
<div id='div_other' style='display:none;'>
<table cellpadding=2>
<tr><td><b>HTTP Port:</b></td><td><input type='text' size=5 maxlength=5 id='htp' value=0 data-mini='true'></td></tr>
<tr><td colspan=2><input type='checkbox' id='usi' data-mini='true'><label for='usi'>Use Static IP</label></td></tr>
<tr><td><b>Device IP:</b></td><td><input type='text' size=15 maxlength=15 id='dvip' data-mini='true' disabled></td></tr>
<tr><td><b>Gateway IP:</b></td><td><input type='text' size=15 maxlength=15 id='gwip' data-mini='true' disabled></td></tr>
<tr><td><b>Subnet:</b></td><td><input type='text' size=15 maxlength=15 id='subn' data-mini='true' disabled></td></tr> 
<tr><td><b>Pin 4 (GPIO5)- Ext:</b></td><td>
<select name='Ext Pin 4' id='Ep4' data-mini='true'>
<option value=0>Disabled</option>
<option value=1>US Vehicle A</option>
<option value=2>US Door/Vehicle B</option>
<option value=3>Switch - B</option>
<option value=4>Temp Humidity (DHT11)</option>
</select></td></tr> 
<tr><td colspan=2><input type='checkbox' id='cb_key' data-mini='true'><label for='cb_key'>Change Device Key</label></td></tr>
<tr><td><b>New Key:</b></td><td><input type='password' size=24 maxlength=32 id='nkey' data-mini='true' disabled></td></tr>
<tr><td><b>Confirm:</b></td><td><input type='password' size=24 maxlength=32 id='ckey' data-mini='true' disabled></td></tr>      
</table>
</div>
<br />
<table cellpadding=2>
<tr><td><b>Device Key:</b></td><td><input type='password' size=24 maxlength=32 id='dkey' data-mini='true'></td></tr>
<tr><td colspan=2><p id='msg'></p></td></tr>
</table>
<div data-role='controlgroup' data-type='horizontal'>
<a href='#' data-role='button' data-inline='true' data-theme='a' id='btn_back'>Back</a>
<a href='#' data-role='button' data-inline='true' data-theme='b' id='btn_submit'>Submit</a>      
</div>
<table>
</table>
</div>
<div data-role='footer' data-theme='c'>
<p>&nbsp; OpenGarage Firmware <label id='fwv'>-</label>&nbsp;<a href='update' target='_top' data-role='button' data-inline=true data-mini=true>Update</a></p>
</div> 
</div>
<script>
function clear_msg() {$('#msg').text('');}  
function disable_dth() {
if (parseInt($('#mnt option:selected').val()) >1){
$('#dth').textinput('disable'); 
$('#vth').textinput('disable'); 
}else{$('#dth').textinput('enable');}
}
function show_msg(s) {$('#msg').text(s).css('color','red'); setTimeout(clear_msg, 2000);}
function goback() {history.back();}
function eval_cb(n)  {return $(n).is(':checked')?1:0;}
$('#cb_key').click(function(e){
$('#nkey').textinput($(this).is(':checked')?'enable':'disable');
$('#ckey').textinput($(this).is(':checked')?'enable':'disable');
});
$('#usi').click(function(e){
$('#dvip').textinput($(this).is(':checked')?'enable':'disable');
$('#gwip').textinput($(this).is(':checked')?'enable':'disable');
$('#subn').textinput($(this).is(':checked')?'enable':'disable');      
});
function toggle_opt() {
$('#div_basic').hide();
$('#div_cloud').hide();
$('#div_other').hide();
if(eval_cb('#basic')) $('#div_basic').show();
if(eval_cb('#cloud')) $('#div_cloud').show();
if(eval_cb('#other')) $('#div_other').show();
}
$('#btn_back').click(function(e){
e.preventDefault(); goback();
});
$('#btn_submit').click(function(e){
e.preventDefault();
if(confirm('Submit changes?')) {
var comm='co?dkey='+encodeURIComponent($('#dkey').val());
comm+='&acc='+$('#acc').val();
comm+='&mnt='+$('#mnt').val();
comm+='&dth='+$('#dth').val();
comm+='&vth='+$('#vth').val();
comm+='&riv='+$('#riv').val();
comm+='&alm='+$('#alm').val();
comm+='&htp='+$('#htp').val();
comm+='&cdt='+$('#cdt').val();
comm+='&ati='+$('#ati').val();
comm+='&atib='+$('#atib').val();
var ato=0;
for(var i=1;i>=0;i--) { ato=(ato<<1)+eval_cb('#ato'+i); }
comm+='&ato='+ato;
var atob=0;
for(var i=1;i>=0;i--) { atob=(atob<<1)+eval_cb('#atob'+i); }
comm+='&atob='+atob;
var atoc=0;
for(var i=1;i>=0;i--) { atoc=(atoc<<1)+eval_cb('#atoc'+i); }
comm+='&atoc='+atoc;
comm+='&name='+encodeURIComponent($('#name').val());
comm+='&auth='+encodeURIComponent($('#auth').val());
comm+='&iftt='+encodeURIComponent($('#iftt').val());
comm+='&mqtt='+encodeURIComponent($('#mqtt').val());
if($('#cb_key').is(':checked')) {
if(!$('#nkey').val()) {
if(!confirm('New device key is empty. Are you sure?')) return;
}
comm+='&nkey='+encodeURIComponent($('#nkey').val());
comm+='&ckey='+encodeURIComponent($('#ckey').val());
}
if($('#usi').is(':checked')) {
comm+='&usi=1&dvip='+($('#dvip').val())+'&gwip='+($('#gwip').val());
} else {
comm+='&usi=0';
}
$.getJSON(comm, function(jd) {
if(jd.result!=1) {
if(jd.result==2) show_msg('Check device key and try again.');
else show_msg('Error code: '+jd.result+', item: '+jd.item);
} else {
$('#msg').html('<font color=green>Options are successfully saved. Note that<br>changes to some options may require a reboot.</font>');
setTimeout(goback, 4000);
}
});
}
});
$(document).ready(function() {
$.getJSON('jo', function(jd) {
$('#fwv').text('v'+(jd.fwv/100>>0)+'.'+(jd.fwv/10%10>>0)+'.'+(jd.fwv%10>>0));
$('#acc').val(jd.acc).selectmenu('refresh');
$('#alm').val(jd.alm).selectmenu('refresh');
$('#mnt').val(jd.mnt).selectmenu('refresh');
if(jd.mnt>1) $('#dth').textinput('disable'); 
if(jd.mnt>0) $('#vth').textinput('disable'); 
$('#dth').val(jd.dth);
$('#vth').val(jd.vth);
$('#riv').val(jd.riv);
$('#htp').val(jd.htp);
$('#cdt').val(jd.cdt);
$('#ati').val(jd.ati);
$('#atib').val(jd.atib);
for(var i=0;i<=1;i++) {if(jd.ato&(1<<i)) $('#ato'+i).attr('checked',true).checkboxradio('refresh');}
for(var i=0;i<=1;i++) {if(jd.atob&(1<<i)) $('#atob'+i).attr('checked',true).checkboxradio('refresh');}
for(var i=0;i<=1;i++) {if(jd.atoc&(1<<i)) $('#atoc'+i).attr('checked',true).checkboxradio('refresh');}
$('#name').val(jd.name);
$('#auth').val(jd.auth);
$('#iftt').val(jd.iftt);
$('#mqtt').val(jd.mqtt);
$('#dvip').val(jd.dvip);
$('#gwip').val(jd.gwip);
$('#subn').val(jd.subn);
if(jd.usi>0) $('#usi').attr('checked',true).checkboxradio('refresh');
$('#dvip').textinput(jd.usi>0?'enable':'disable');
$('#gwip').textinput(jd.usi>0?'enable':'disable');
$('#subn').textinput(jd.usi>0?'enable':'disable');      
});
});
</script>
</body>)";
