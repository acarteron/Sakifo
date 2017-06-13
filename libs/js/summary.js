function loadWhatTheShit(){
    var d=new Date();
    var date=formatDateMinusOne(d);
    document.getElementById("date_yesterday").innerHTML = date;
    getSomething(displaySummary,"/summary/"+date);
}
function getPrev(){
    var date=formatDateMinusOne(document.getElementById("date_yesterday").innerHTML);
    document.getElementById("date_yesterday").innerHTML = date;
    getSomething(displaySummary,"/summary/"+date);
}
function getNext(){
    var date=formatDatePlusOne(document.getElementById("date_yesterday").innerHTML);
    document.getElementById("date_yesterday").innerHTML = date;
    getSomething(displaySummary,"/summary/"+date);
}
function displaySummary(summary){
    var date_y=summary.date;
    var prio_list=summary["priorities"];
    var results=summary.results;
    var container="<div class=\"container\"><div class=\"panel-group\" id=\"accordion\">";
    var all_prios=[];
    for( var k = 0 ; k < prio_list.length ; k ++){
	var one_prio={name:"",number:0};
	one_prio.name=prio_list[k];
	all_prios.push(one_prio);
    }	
    for(var i = 0 ; i < results.length ; i ++) {
	var test_res=results[i];
	var begin_panel="<div class=\"panel panel-default\"><div class=\"panel-heading\"><h4 class=\"panel-title\"><a data-toggle=\"collapse\" data-parent=\"#accordion\" href=\"#collapse"+i+"\">";
	
	var end_panel_header="</a></h4></div><div id=\"collapse"+i+"\" class=\"panel-collapse collapse\"><div class=\"panel-body\">";
	var end_panel="</div></div></div>";
	var body="";
	var user_prio_enabled_lits=test_res.priorities;
	var user_rules_list=[];
	var prio_numbers=[];
	var only_battery=true;
	for(var j=0;j<user_prio_enabled_lits.length;j++){
	    var user_prio=user_prio_enabled_lits[j]
	    var one_prio={name:"",number:0};
	    var rule_for_prio=summary[user_prio];
	    one_prio.name=user_prio;
	    for( var k = 0 ; k < rule_for_prio.length ; k ++){
		var test=test_res[one_prio.name];		
		var test1_2=rule_for_prio[k];
		var test2=test[test1_2];
		if(test2!==undefined){
		    if(test1_2!=='batteryAlert'&&test1_2!=='batteryWarning')
			only_battery=false;
		    var rule_name="<div class=\"panel panel-default\"><div class=\"panel-heading\"><span class=\"label label-default\">"+one_prio.name+"</span> "+test1_2+"</div>  <div class=\"panel-body\">";
		    var streams_array=test2.streams;
		    var rule_panel_body="<ul>";
		    for(var l=0;l<streams_array.length;l++){
			var roles_array=streams_array[l].roles;
			rule_panel_body+="<li>";
			for(var m=0;m<roles_array.length;m++){
			    rule_panel_body+=roles_array[m].role.location+" "+roles_array[m].role.kind+"<br>";
			}
			var date_rule=streams_array[l].timestamp; 
			var time_rule_inst=new Date(Number(date_rule));
			rule_panel_body+=formatDateTime(time_rule_inst)+"</li>";
		    }
		    rule_panel_body+="</ul></div></div>";
		    rule_name+=rule_panel_body;
		    body+=rule_name;
		    var test3=test2.number;	
		    one_prio.number+=Number(test3);
		}
	    }
	    user_rules_list.push(results[i][user_prio_enabled_lits[j]]);
	    prio_numbers.push(one_prio);
	}
	var bad_tings="";
	for( var k = 0 ; k < prio_list.length ; k ++){
	   
	    var found=0;
	    var number_f="";
	    for(var j=0;j<prio_numbers.length&&found===0;j++){	
		if(prio_numbers[j].name===prio_list[k]){
		    number_f=prio_numbers[j].number;
		    all_prios[k].number+=number_f;
		    found=1;
		}
	    }
	    if(found===0){
		bad_tings+="<span class=\"label label-primary\">"+prio_list[k]+"</span>";
	    }else{
		if(only_battery===false)
		    bad_tings+="<span class=\"label label-danger\">"+prio_list[k]+": "+number_f+"</span>";
		else
		    bad_tings+="<span class=\"label label-info\">"+prio_list[k]+": "+number_f+"</span>";
	    }	    
	}	
	var header="<h4>"+results[i].user.replace("_","")+"</h4> "+bad_tings;
	container+=begin_panel+header+end_panel_header+body+end_panel;	
    }

    
    var end_container="</div>";
    
    var main_header="<div class=\"panel panel-default\"><div class=\"panel-body\">";
    for( var i = 0 ; i < all_prios.length ; i ++){
	var name=all_prios[i].name;
	var number=all_prios[i].number;
	if(number===0)
	    main_header+="<span class=\"label label-primary\">"+name+"</span>";
	else
	    main_header+="<span class=\"label label-danger\">"+name+": "+number+"</span>";
    }
    main_header+="</div></div>";
    document.getElementById("date_yesterday").innerHTML = date_y;

    document.getElementById("demo").innerHTML = main_header+container;
}
