function submitedOrder(args){
    var modal=new Modal();
    var res="";
    if( args["request"] !== "false" ){
	modal.addHtml(""," order file saved ");
    }else{
	modal.addHtml("","rule could not be saved");
    }
    document.getElementById("modals").innerHTML = modal.getModal();
    editOrder();
    $('#myModal').modal('show');
    load_js("loadmaterial.js");
}
function confirmOrder(){
    var orderTxt="";
    orderTxt=document.getElementById("orderTxt").value;

    orderJson=JSON.parse(orderTxt);
    priorities=[];
 
    for (var i in orderJson) {
        priorities.push(i);
    }
    orderJson["priorities"]=priorities;
    if(orderTxt !== "")
     	postSomething(submitedOrder,"/order",orderJson);
}
function displayOrder(orderJson){
    var form=new Formular();
    var orders={};
    
    for( var k = 0 ; k < orderJson["priorities"].length ; k ++){
	orders[orderJson["priorities"][k]]=orderJson[orderJson["priorities"][k]];
    }	
    
    form.addHtml("<legend>Order for rule display</legend>");

    form.addHtml("<div class=\"form-group label-floating\"><label for=\"orderTxt\" class=\"control-label\">Order rules</label><textarea class=\"form-control\" rows=\"20\" id=\"orderTxt\">"+JSON.stringify(orders, null, 2)+"</textarea></div>");
    
    form.addButton({"id":"confrmOrder","onclick":"confirmOrder()","value":"setOrder","name":"Confirm"});
    document.getElementById("rulemngr").innerHTML=form.getForm();
    load_js("loadmaterial.js");
}
function editOrder(){
    getSomething(displayOrder,"/order");
}
