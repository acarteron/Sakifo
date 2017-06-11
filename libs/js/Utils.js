function strToDate(dateStr) {
    var parts = dateStr.split("-");
    return new Date(parts[2], parts[1] - 1, parts[0]);
}
Number.prototype.padLeft = function(base,chr){
    var  len = (String(base || 10).length - String(this).length)+1;
    return len > 0? new Array(len).join(chr || '0')+this : this;
}
function formatDateTime(date) {
    var d = new Date(date),
	dformat = [d.getFullYear(),
		   (d.getMonth()+1).padLeft(),
		   d.getDate().padLeft()].join('-') +' ' +
        [d.getHours().padLeft(),
         d.getMinutes().padLeft(),
         d.getSeconds().padLeft()].join(':');
    return dformat;
}

function formatDate(date) {
    var d = new Date(date),
        month = '' + (d.getMonth() + 1),
        day = '' + d.getDate(),
        year = d.getFullYear();

    if (month.length < 2) month = '0' + month;
    if (day.length < 2) day = '0' + day;

    return [year, month, day].join('-');
}
function formatDateMinusOne(date) {
    var d = new Date(date);
    d.setDate(d.getDate()-1);
    d = new Date(d),
        month = '' + (d.getMonth() + 1),
        day = '' + d.getDate(),
        year = d.getFullYear();

    if (month.length < 2) month = '0' + month;
    if (day.length < 2) day = '0' + day;

    return [year, month, day].join('-');
}
function formatDatePlusOne(date) {
    var d = new Date(date);
    d.setDate(d.getDate()+1);
    d = new Date(d),
        month = '' + (d.getMonth() + 1),
        day = '' + d.getDate(),
        year = d.getFullYear();

    if (month.length < 2) month = '0' + month;
    if (day.length < 2) day = '0' + day;

    return [year, month, day].join('-');
}


 

function changeFunc(callback,select) {
    callback(select);
}

function load_js(file){
    var script = document.createElement('script');
    script.setAttribute('type','application/javascript');
    script.src="libs/js/"+file;
    document.body.appendChild(script);
    document.body.removeChild(script);
}
function load_html(file){
    var script = document.createElement('div');
    script.setAttribute('type','text/html');
    script.src="libs/html/"+file;
    document.body.appendChild(script);
    document.body.removeChild(script);
}

function getSomething(callback,url){
    var xhttp = new XMLHttpRequest();
    xhttp.onreadystatechange = function() {
	if(xhttp.readyState == 1){
		document.getElementById("demo").innerHTML = "<div class=\"wrapperloading\">  <div class=\"loading up\"></div>  <div class=\"loading down\"></div></div>";
	}
	// if(xhttp.readyState == 2){
	// 	//document.getElementById("demo").innerHTML = "lolilol";
	// }
	// if(xhttp.readyState == 3){
	// 	//document.getElementById("demo").innerHTML = "lolilolul";
	// }
	if (xhttp.readyState == 4 && xhttp.status == 200) {
	    var myArr = JSON.parse(xhttp.responseText);
	    callback(myArr);
	}
    }
    xhttp.open("GET",url, true);
    xhttp.setRequestHeader("Content-type", "text/plain");
    xhttp.setRequestHeader("Data-type", "text");
    xhttp.send();
}
function getSomethingArgs(callback,url,args){
    var xhttp = new XMLHttpRequest();
    xhttp.onreadystatechange = function() {
	// if(xhttp.readyState == 1){
	// 	document.getElementById("demo").innerHTML = "<div class=\"wrapperloading\">  <div class=\"loading up\"></div>  <div class=\"loading down\"></div></div>";
	// }
	// if(xhttp.readyState == 2){
	// 	//document.getElementById("demo").innerHTML = "lolilol";
	// }
	// if(xhttp.readyState == 3){
	// 	//document.getElementById("demo").innerHTML = "lolilolul";
	// }
	if (xhttp.readyState == 4 && xhttp.status == 200) {
	    var myArr = JSON.parse(xhttp.responseText);
	    callback(myArr);
	}
    }
    xhttp.open("POST",url, true);
    xhttp.setRequestHeader("Content-type", "application/json");
    xhttp.setRequestHeader("Data-type", "text");
    xhttp.send(JSON.stringify(args));
}
