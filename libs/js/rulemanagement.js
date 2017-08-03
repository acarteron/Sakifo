function submitedRule(args){
    var modal=new Modal();
    var res="";
    for( var i = 0 ; i < args["request"].length ; i++ ){
	res+="<h5>"+args["request"][i]+"</h5>";
    }
    modal.addHtml("",res);
    document.getElementById("modals").innerHTML = modal.getModal();
    $('#myModal').modal('show');
}
function loadRuleAST(){
    var rulename=document.getElementById("Nameform").value;
    var ruleast=document.getElementById("ASTform").value;
    var ruleeplname=document.getElementById("EPLform").value;
    var ruleforce=document.getElementById("fwrite").checked;

    if( ruleast !=="" && ruleeplname !== "" ){
	var modal=new Modal();
	modal.addHtml("Warning","AST form rule and EPL Esper form rule cannot have content at the same time, you must choose");
	document.getElementById("modals").innerHTML = modal.getModal();
	$('#myModal').modal('show');	
    }else{
	var rule={}
	rule["name"]=rulename;
	rule["force"]=ruleforce;
	if(ruleast !=="" ){
	    rule["kind"]="ast";
	    rule["expression"]=ruleast;	    
	}else{
	    rule["kind"]="epl";
	    rule["expression"]=ruleeplname;
	}
	getSomethingArgs(submitedRule,"/rulemanager",rule);
    }
}
