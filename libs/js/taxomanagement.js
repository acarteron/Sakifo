function submitedTaxo(args){
    var modal=new Modal();
    var res="";
    if( args["request"] !== "false" ){
	modal.addHtml(""," taxonomy file saved ");
    }else{
	modal.addHtml("","rule could not be saved");
    }
    document.getElementById("modals").innerHTML = modal.getModal();
    editTaxo();
    $('#myModal').modal('show');
    load_js("loadmaterial.js");
}
function confirmTaxo(){
    var taxoTxt="";
    taxoTxt=document.getElementById("taxoTxt").value;

    if(taxoTxt !== "")
     	postSomething(submitedTaxo,"/taxonomy",taxoJson=JSON.parse(taxoTxt));
}
function displayTaxo(taxoJson){
    var form=new Formular();
    
    form.addHtml("<legend>Taxo for rule display</legend>");

    form.addHtml("<div class=\"form-group label-floating\"><label for=\"taxoTxt\" class=\"control-label\">Taxo rules</label><textarea class=\"form-control\" rows=\"20\" id=\"taxoTxt\">"+JSON.stringify(taxoJson, null, 2)+"</textarea></div>");
    
    form.addButton({"id":"confrmTaxo","onclick":"confirmTaxo()","value":"setTaxo","name":"Confirm"});
    document.getElementById("rulemngr").innerHTML=form.getForm();
    load_js("loadmaterial.js");
}
function editTaxo(){
    getSomething(displayTaxo,"/taxonomy");
}
