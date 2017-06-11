function loadWhatTheShit(){
    var d=new Date();
    var date=formatDateMinusOne(d);
    document.getElementById("date_yesterday").innerHTML = date;
    getSomething(displaySummary,"/summary/"+date);
}
function getPrev(){
    //var d=strToDate(document.getElementById("date_yesterday").innerHTML);
    var date=formatDateMinusOne(document.getElementById("date_yesterday").innerHTML);
    document.getElementById("date_yesterday").innerHTML = date;
    getSomething(displaySummary,"/summary/"+date);
}
function getNext(){
    //var d=strToDate(document.getElementById("date_yesterday").innerHTML);
    var date=formatDatePlusOne(document.getElementById("date_yesterday").innerHTML);
    document.getElementById("date_yesterday").innerHTML = date;
    getSomething(displaySummary,"/summary/"+date);
}
function displaySummary(summary){
    date_y=summary.date;
    document.getElementById("date_yesterday").innerHTML = date_y;
    var prio_list=summary["priorities"];
    var results=summary.results;
    var container="<div class=\"container\"><div class=\"panel-group\" id=\"accordion\">";
   
    for(var i = 0 ; i < results.length ; i ++) {
	var test_res=results[i];
	//var begin_panel="<div class=\"panel panel-default\"><div class=\"panel-heading\"><h4 class=\"panel-title\"><a data-toggle=\"collapse\" data-parent=\"#accordion\" href=\"#collapse"+i+"\">";

	var begin_panel="<div class=\"panel panel-default\"><div class=\"panel-heading\"><h4 class=\"panel-title\"><a data-toggle=\"collapse\" href=\"#collapse"+i+"\">";
	
	var end_panel_header="</a></h4></div><div id=\"collapse"+i+"\" class=\"panel-collapse collapse\"><div class=\"panel-body\">";
	var end_panel="</div></div></div>";
	var body="";
	var user_prio_enabled_lits=test_res.priorities;
	var user_rules_list=[];
	var prio_numbers=[];
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
		    //console.log(test3);
		    one_prio.number+=Number(test3);
		}
	    }
	    user_rules_list.push(results[i][user_prio_enabled_lits[j]]);
	    prio_numbers.push(one_prio);
	}
	//console.log(JSON.stringify(prio_numbers));
	var bad_tings="";
	for( var k = 0 ; k < prio_list.length ; k ++){
	    //bad_tings+=prio_list[k]+": ";
	    var found=0;
	    var number_f="";
	    for(var j=0;j<prio_numbers.length&&found===0;j++){	
		if(prio_numbers[j].name===prio_list[k]){
		    number_f=prio_numbers[j].number;
		    found=1;
		}
	    }
	    if(found===0){
		bad_tings+="<span class=\"label label-primary\">"+prio_list[k]+"</span>";
	    }else{
		bad_tings+="<span class=\"label label-warning\">"+prio_list[k]+": "+number_f+"</span>";
	    }
	    
	}
	
	var header="<h4>"+results[i].user.replace("_","")+"</h4> "+bad_tings;//JSON.stringify(prio_list)+" "+JSON.stringify(prio_numbers);
	//body=JSON.stringify(user_rules_list);
	container+=begin_panel+header+end_panel_header+body+end_panel;
	
    }
    var end_container="</div>";
    document.getElementById("demo").innerHTML = container;
}


/*

<div class="container">
  <p><strong>Note:</strong> The <strong>data-parent</strong> attribute makes sure that all collapsible elements under the specified parent will be closed when one of the collapsible item is shown.</p>
  <div class="panel-group" id="accordion">
    <div class="panel panel-default">
      <div class="panel-heading">
        <h4 class="panel-title">
          <a data-toggle="collapse" data-parent="#accordion" href="#collapse1">Collapsible Group 1</a>
        </h4>
      </div>
      <div id="collapse1" class="panel-collapse collapse in">
        <div class="panel-body">Lorem ipsum dolor sit amet, consectetur adipisicing elit,
        sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam,
        quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat.</div>
      </div>
    </div>
    <div class="panel panel-default">
      <div class="panel-heading">
        <h4 class="panel-title">
          <a data-toggle="collapse" data-parent="#accordion" href="#collapse2">Collapsible Group 2</a>
        </h4>
      </div>
      <div id="collapse2" class="panel-collapse collapse">
        <div class="panel-body">Lorem ipsum dolor sit amet, consectetur adipisicing elit,
        sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam,
        quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat.</div>
      </div>
    </div>
    <div class="panel panel-default">
      <div class="panel-heading">
        <h4 class="panel-title">
          <a data-toggle="collapse" data-parent="#accordion" href="#collapse3">Collapsible Group 3</a>
        </h4>
      </div>
      <div id="collapse3" class="panel-collapse collapse">
        <div class="panel-body">Lorem ipsum dolor sit amet, consectetur adipisicing elit,
        sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam,
        quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat.</div>
      </div>
    </div>
  </div> 
</div>

*/
