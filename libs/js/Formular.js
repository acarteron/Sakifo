var Formular = function () {
    //this.form_b="<div class=\"container-fluid main\">\n";
    //this.form_b+="<div id=\"about\" class=\"well page active\">\n";
    //this.form_b="<div class=\"row\">\n";
    this.form_b="<div class=\"formular\">";//class=\"col-md-8\" >\n";
    this.form_e="</div>";//</div>";//</div></div>";
    this.items=[];
}

Formular.prototype.addSelect = function(id,elements){
    var select="<select class=\"form-control\" id=\""+id+"\"  selected=\"\">\n";
    for(  i = 0; i < elements.length; i++ ){
	select+="<option>"+elements[i]+"</option>";
    }
    select+="</select><br>";
    this.items.push(select);
}
Formular.prototype.addSelectPlus = function(id,elements,callback){
    var onCh="onChange=\" changeFunc(this)  \"";
    var select="<select class=\"form-control\" id=\""+id+"\" "+onCh+"  selected=\"\" name=\""+callback+"\" >\n";
    for(  i = 0; i < elements.length; i++ ){
	select+="<option value=\""+elements[i]+"\">"+elements[i]+"</option>";
    }
    select+="<option>Add</option>"
    select+="</select><br><div id=\""+callback+"\"></div>";
    this.items.push(select);
}
Formular.prototype.addSelectAddDefault = function(id,elements,callback){
    var onCh="onChange=\" changeFunc(this)  \"";
    var select="<select class=\"form-control\" id=\""+id+"\" "+onCh+"  selected=\"\" name=\""+callback+"\" >\n";
    select+="<option selected=\"selected\">Select vehicule category</option>";
    for(  i = 0; i < elements.length; i++ ){
	select+="<option value=\""+elements[i]+"\">"+elements[i]+"</option>";
    }
    select+="</select><br><div id=\""+callback+"\"></div>";
    this.items.push(select);
}

Formular.prototype.addForm = function(elements){
    var form="<div class=\"form-group label-floating\">\n<label class=\"control-label\" for=\""+elements["id"]+"\">"+elements["placeholder"]+"</label>\n<input class=\"form-control\" id=\""+elements["id"]+"\"  type=\""+elements["type"]+"\" value=\"\">\n</div>\n<br>";
    this.items.push(form);
}
Formular.prototype.addFormDate = function(elements){
    var form="<input class=\"datepicker form-control\" id=\""+elements["id"]+"\" autofocus  type=\""+elements["type"]+"\" value=\"\">\n</div>\n<br>";
    this.items.push(form);
}

Formular.prototype.addButton = function(elements){
    var button="<br>\n<button class=\"btn btn-primary\" onclick=\""+elements["onclick"]+"\"  value=\""+elements["value"]+"\" id=\""+elements["id"]+"\" data-toggle=\""+elements["data-toggle"]+"\" data-target=\""+elements["data-target"]+"\" >"+elements["name"]+"</button>";
    this.items.push(button);
}

Formular.prototype.addHtml = function(elements){
    this.items.push(elements);
}

Formular.prototype.getForm = function(){
    var form=this.form_b;
    for(  i = 0; i < this.items.length; i++ ){
	form+=this.items[i];
    }
    form+=this.form_e;
    return form;
}
Formular.prototype.getForm_no = function(){
    var form="";//this.form_b;
    for(  i = 0; i < this.items.length; i++ ){
	form+=this.items[i];
    }
    //form+=this.form_e;
    return form;
}


// function setFormulaire(vehitype){
    
//     var formulaire="<div class=\"container-fluid main\">";
//     formulaire+="<div id=\"about\" class=\"well page active\">\n";
//     formulaire+="<div class=\"row\">\n";
//     formulaire+="<div class=\"col-md-6\">\n";
//     formulaire+="<select class=\"form-control\" id=\"vehitype\"  selected=\"\">\n";
//     formulaire+="<option>type11</option>\n";
//     formulaire+="<option>type222</option>\n";
//     formulaire+="</select>\n";
//     formulaire+="<br>\n";
//     formulaire+="<input class=\"form-control floating-label\" id=\"vehimat\" placeholder=\"Immatriculation\" type=\"text\" value=\"\">\n";
//     formulaire+="<br>\n";
//     formulaire+="<input class=\"form-control floating-label\" id=\"vehikilo\" placeholder=\"Kilometres\" type=\"number\" value=\"\">\n";
//     formulaire+="<br>\n";
//     formulaire+="<input class=\"form-control floating-label\" id=\"vehilocation\" placeholder=\"Localisation\" type=\"text\" value=\"\">\n";
//     formulaire+="<br>\n<br>\n<button class=\"btn btn-primary\" onclick=\"loadvehicules()\"  value=\"\quotation\" id=\"quotation\">Devis</button>";
//     formulaire+="</div></div><br><br></div>\n";
//     document.getElementById("demo").innerHTML = formulaire;
// }
