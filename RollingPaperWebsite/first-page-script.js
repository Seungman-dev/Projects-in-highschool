blur();

document.getElementById("usernameinput");
onsubmit = function(){
    var sc = document.getElementById("number-check");
    localStorage.setItem('filename', sc.value);
    open("rolling-paper.html");
//    close();
}

