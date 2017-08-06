function submitedRule(args){
    var modal=new Modal();
    var res="";
    for( var i = 0 ; i < args["request"].length ; i++ ){
	res+="<h5>"+args["request"][i]+"</h5>";
    }
    modal.addHtml("",res);
    document.getElementById("modals").innerHTML = modal.getModal();
    $('#myModal').modal('show');
    load_js("loadmaterial.js");
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
	load_js("loadmaterial.js");
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
	postSomething(submitedRule,"/rulemanager",rule);
    }
}
function submitedRemoveRule(args){
    var modal=new Modal();
    var res="";
    if( args["request"] !== "false" ){
	modal.addHtml("","rule "+args["request"]+" deleted");
    }else{
	modal.addHtml("","rule could not be deleted");
    }
    document.getElementById("modals").innerHTML = modal.getModal();
    $('#myModal').modal('show');
    load_js("loadmaterial.js");
}
function confirmRemoveRule(){
    var ruleName="";
    ruleName=document.getElementById("rmRuleRef").value;
    if(ruleName !== "")
	deleteSomething(submitedRemoveRule,"/rule/"+ruleName);
}
function rmRuleManagement(rulelst){
    var form=new Formular();
    var rulesnames=[];
    rulesnames.push('');
    for( i = 0 ; i < rulelst['rules'].length ; i++ ){
	rulesnames.push(rulelst['rules'][i]['name']);
    }
    form.addHtml("<legend>Remove rule</legend>");
    form.addSelect("rmRuleRef",rulesnames,"rmRule");
    form.addButton({"id":"confrmRule","onclick":"confirmRemoveRule()","value":"rmRule","name":"Remove"});
    document.getElementById("rulemngr").innerHTML=form.getForm();
    load_js("loadmaterial.js");
}
function removeRules(){
    getSomething(rmRuleManagement,"/rules");
}
