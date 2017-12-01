const char html_sta_home[] PROGMEM = R"(<body>
<style> table, th, td {border: 0px solid black;padding: 6px; border-collapse: collapse; }</style>
<div data-role='page' id='page_home'><div data-role='header'><h3 id='head_name'>OG</h3></div>
<div data-role='content'><div data-role='fieldcontain'>
<table><tr><td><b>Door&nbsp;State:<br></td><td><label id='lbl_status'>-</label></td>
<td rowspan="2"><img id='pic' src='' style='width:112px;height:64px;'></td>
</tr><tr><td><b><label id='lbl_vstatus1'>Vehicle&nbsp;State:&nbsp</label></b></td>
<td><label id='lbl_vstatus'>-</label></td></tr>
<tr><td><b>Distance:</b></td><td><label id='lbl_dist'>-</label></td><td></td></tr>
<tr><td><b>Read&nbsp;Count:</b></td><td><label id='lbl_beat'>-</label></td><td></td></tr>
<tr><td><b>WiFi&nbsp;Signal:</b></td><td colspan="2"><label id='lbl_rssi'>-</label></td></tr>
<tr><td><b>Device&nbsp;Key:</b></td><td colspan="2" ><input type='password' size=20 maxlength=32 name='dkey' id='dkey'></td></tr>
<tr><td colspan=3><label id='msg'></label></td></tr>
</table><br />
<div data-role='controlgroup' data-type='horizontal'>
<button data-theme='b' id='btn_click'>Button</button>  
<button data-theme='b' id='btn_opts'>Options</button>
<button data-theme='b' id='btn_log'>Show Log</button>
</div>
<span style='display:block;height:5px'></span>
<div data-role='controlgroup' data-type='horizontal'>
<button data-theme='c' id='btn_rap'>Reset to AP Mode</button>
<button data-theme='c' id='btn_rbt'>Reboot</button>
</div>
</div>
</div>
<div data-role='footer' data-theme='c'>
<p>&nbsp; OpenGarage Firmware <label id='fwv'>-</label>&nbsp;<a href='update' target='_top' data-role='button' data-inline=true data-mini=true>Update</a></p>
</div>
</div>
<script>
var si;
function clear_msg() {$('#msg').text('');}
function show_msg(s,t,c) {
$('#msg').text(s).css('color',c);
if(t>0) setTimeout(clear_msg, t);
}
$('#btn_opts').click(function(e){window.open('vo', '_top');});
$('#btn_log').click(function(e){window.open('vl', '_top');});
$('#btn_rbt').click(function(e){
if(confirm('Reboot the device now?')){
var comm = 'cc?reboot=1&dkey='+($('#dkey').val());
clear_msg();
$.getJSON(comm, function(jd) {
if(jd.result!=1) show_msg('Check device key and try again.',2000,'red');
else {
show_msg('Rebooting. Please wait...',0,'green');
clearInterval(si);
setTimeout(function(){location.reload(true);}, 10000);
}
});
}
});   
$('#btn_rap').click(function(e){
if(confirm('Reset the device to AP mode?')){
var comm = 'cc?apmode=1&dkey='+($('#dkey').val());
clear_msg();
$.getJSON(comm, function(jd) {
if(jd.result!=1) show_msg('Check device key and try again.',2000,'red');
else {
clearInterval(si);
$('#msg').html('Device is now in AP mode. Log on<br>to SSID OG_xxxxxx, then <br> open or click <a href="http://192.168.4.1">http://192.168.4.1</a><br>to configure.').css('color','green');
}
});
}
});  
$('#btn_click').click(function(e) {
show_msg('Sending command.....',5000,'green');
navigator.vibrate([500]);
var comm = 'cc?click=1&dkey='+($('#dkey').val());
$.getJSON(comm)
.done(function( jd ) {
if(jd.result!=1) {
show_msg('Check device key and try again.',2000,'red');
}else{clear_msg();};
})
.fail(function( jqxhr, textStatus, error ) {
var err = error;
$('#msg').text('Request Failed: ' + err).css('color','red');
});
});
$(document).ready(function() {
show(); si=setInterval('show()', 5000);
});
function show() {
$.getJSON('jc', function(jd) {
$('#fwv').text('v'+(jd.fwv/100>>0)+'.'+(jd.fwv/10%10>>0)+'.'+(jd.fwv%10>>0));
$('#lbl_dist').text(jd.dist +' (cm)').css('color', jd.dist==450?'red':'black');
$('#lbl_status').text(jd.door?'OPEN':'CLOSED').css('color',jd.door?'red':'green'); 
//Hide or Show vehicle info
if (jd.vehicle >=2){ //2 is unknown, 3 disabled
$('#lbl_vstatus1').hide();
$('#lbl_vstatus').text('');
}else {
$('#lbl_vstatus1').show()
$('#lbl_vstatus').text(jd.vehicle?'Present':'Absent');
}
//Open Door (1)
if (jd.door){
if (jd.vehicle>=3){ //3 is disabled
$('#pic').attr('src', '/DoorOpen.png');
}else if (jd.vehicle==2){
$('#pic').attr('src', '/OpenUnknown.png');  
}else{
$('#pic').attr('src', jd.vehicle?'/OpenPresent':'/OpenAbsent');  
}
}else{ //Closed Door 
if (jd.vehicle>=3){ //3 is disabled
$('#pic').attr('src', '/DoorShut.png');
}else if (jd.vehicle==2){
$('#pic').attr('src', '/ClosedUnknown.png');  //This should be impossible
}else{
$('#pic').attr('src', jd.vehicle?'/ClosedPresent':'/ClosedAbsent');  
}
}
$('#lbl_beat').text(jd.rcnt);
$('#lbl_rssi').text((jd.rssi>-71?'Good':(jd.rssi>-81?'Weak':'Poor')) +' ('+ jd.rssi +' dBm)');
$('#head_name').text(jd.name);
$('#btn_click').html(jd.door?'Close Door':'Open Door').button('refresh');
});
}
</script>
</body>)";
