const char html_sta_logs[] PROGMEM = R"(<body>
<div data-role='page' id='page_log'>
<div data-role='header'><h3><label id='lbl_name'></label> Log</h3></div>    
<div data-role='content'>
<p>Below are the most recent <label id='lbl_nr'></label> record(s):</p>
<p>Current time is <label id='lbl_time'></label></p>
<div data-role="controlgroup" data-type="horizontal">
<button data-theme="b" id="btn_back">Back</button>
<button data-theme="c" id="btn_clear">Clear</button>
</div>
<div data-role='fieldcontain'>
<table id='tab_log' border='1' cellpadding='4' style='border-collapse:collapse;'><tr><td align='center'><b>Event</b></td><td align='center'><b>DateTime</b></td><td align='center'><b>Details</b></td></tr></table>
</div>
</div>
</div>
</div>
<script>
var curr_time = 0;
var date = new Date();
$("#btn_back").click(function(){history.back();});
$('#btn_clear').click(function(e){
    if(confirm('Confirm Erase Logs (Y/N)')){
         $.getJSON('clearlog');
         show_log();
    }
}); 
$(document).ready(function(){
show_log();
setInterval(show_time, 1000);
});
function show_time() {
curr_time ++;
date.setTime(curr_time*1000);
$('#lbl_time').text(date.toLocaleString());
}
function show_log() {
$.getJSON('jl', function(jd) {
$('#lbl_name').text(jd.name);
curr_time = jd.time;
$('#tab_log').find('tr:gt(0)').remove();
var logs=jd.logs;
logs.sort(function(a,b){return b[0]-a[0];});
$('#lbl_nr').text(logs.length);
var ldate = new Date();
for(var i=0;i<logs.length;i++) {
ldate.setTime(logs[i][0]*1000);
//var r='<tr><td align="center">'+ldate.toLocaleString()+'</td><td align="center">'+(logs[i][1]?'OPEN':'closed')+'</td><td align="center">'+logs[i][2]+'</td></tr>';
var r='<tr></td><td align="left"><img id="pic" src="/' + (logs[i][1]?'DoorOpen.png':'DoorShut.png') +'" style="width:20px;height:15px;">'+(logs[i][1]?' Opened':' Closed')+'<td align="center">'+ldate.toLocaleString()+'</td><td align="center">'+logs[i][2]+' cm</td></tr>';
$('#tab_log').append(r);
}
});
setTimeout(show_log, 10000);
}
</script>
</body>)";
