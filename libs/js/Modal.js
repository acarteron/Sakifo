var Modal = function () {
    
    this.modal_b="<div class=\"modal fade\" id=\"myModal\" role=\"dialog\"> <div class=\"modal-dialog\"><div class=\"modal-content\"><div class=\"modal-header\"><button type=\"button\" class=\"close\" data-dismiss=\"modal\" aria-hidden=\"true\">×</button><h4></h4> </div><div class=\"modal-body\">";
    this.modal_e="</div></div></div></div>";
    this.items=[];
}
Modal.prototype.addHtml = function(id,args_){
    var elem="<div class=\"jumbotron\">";
    elem+=args_;
    elem+="</div>";
    this.items.push(elem);
}
Modal.prototype.addLabeledElement = function(id,title,elements){
    var elem="<div class=\"jumbotron\" id=\""+id+"\"> <legend>"+title+"</legend>";
    for(var name in elements) {
	//propnames.push(elements[name]);
	if(name!="_id"){
	    elem+="<label class=\"control-label\">"+name+" :</label>";
	    elem+=" "+elements[name];
	    elem+="<br>";
	}
    };
    elem+="<div>";
    this.items.push(elem);
}
Modal.prototype.getModal = function(){
    var modal=this.modal_b;
    for(  i = 0; i < this.items.length; i++ ){
	modal+=this.items[i];
    }
    modal+=this.modal_e;
    return modal;
}
	//modal+="<div class=\"jumbotron\"> This is a simple hero unit, a simple jumbotron-style component for calling extra attention to featured content or information. <a class=\"btn btn-primary btn-lg\">Learn more</a></p></div>"
