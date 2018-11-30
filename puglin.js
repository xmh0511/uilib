window.excute_user_js = function(id,method_str){
    //eval(method_str);
   // if(typeof(window.external)!="undefined"  && typeof(window.external.invoke) !="undefined"){
        var str = {
            fn:"method_call_success",
            params:[String(id)]
        }
        window.external.invoke(JSON.stringify(str));
   // }
}

window.excute_native_method = function(){
    var method_name = arguments[0];
    var params = [];
    for(var i=1; i<arguments.length; i++){
        params.push(arguments[i]);
    }
    var str = {
        fn:method_name,
        params:params
    }
    //if(typeof(window.external)!="undefined" && typeof(window.external.invoke) !="undefined"){
        window.external.invoke(JSON.stringify(str));
    //}
}

window.onload  = function(){
    window.excute_native_method("loadcomplete");
}
window.messagebox = function(title,content){
    window.excute_native_method("messagebox",title,content);
}
window.open_dialog = function(url,title,width,height,is_resizeable){
    if(url[0]=="."&&url[1]=="/"){
        var adom = document.createElement("a"); 
        adom.href = "./";
        var base_path = adom.href;
        //alert(base_path+url);
        var n_url= base_path+url;
        window.excute_native_method("opennewdialog",n_url,title,width,height,is_resizeable);
    }
}