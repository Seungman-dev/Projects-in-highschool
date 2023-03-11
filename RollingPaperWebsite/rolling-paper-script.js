blur();

var filename;
if(localStorage.getItem('filename')){
    filename = localStorage.getItem('filename')
}

if(filename == "박정은" || filename == "담임쌤"){
    filename = "담임샘";
}

var titlename = filename + "님의 2022년";
document.title = titlename

document.write("<h1 class='rollingpaper-style'>" + titlename + "</h1><div id='rolling-paper-line'></div><br>")

path = "Rolling-Paper-Storage/" + filename + "/";

document.write('<img src="' + path + filename + ' 워드클라우드.png" alt="image" id="word-cloud"><br><br>')

//로컬 파일 읽어오기
var result;
function readTextFile(file)
{
    var rawFile = new XMLHttpRequest();
    rawFile.open("GET", file, false);
    rawFile.onreadystatechange = function ()
    {
        if(rawFile.readyState === 4)
        {
            if(rawFile.status === 200 || rawFile.status == 0)
            {
                var allText = rawFile.responseText;
                // alert(allText);
                result = allText;
            }
        }
    }
    rawFile.send(null);
}


readTextFile(path + filename + ".txt");



if(result === undefined){
    alert("존재하지 않는 롤링페이퍼입니다.\n확인 클릭시 창이 꺼집니다.");
    close();
}
else{

    result = "<div class='commentbox'>" + result;
    result = result.replaceAll('B', "</div><div class='commentbox'>");
    result = result + "</div>"
    document.write(result);
}