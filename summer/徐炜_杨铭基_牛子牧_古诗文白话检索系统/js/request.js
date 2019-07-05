var cnt = 1;
function test(frm,event){
	var event=window.event?window.event:event;   
	if(event.keyCode==13){
		search();
	}
}
function load() {
	$("#load").html('');
	$("#load").append('搜索中');
	for (i = 0; i < cnt; ++i)
	{
		$("#load").append('.');
	}
	cnt = cnt % 3 + 1;
}
function search()
{
	document.getElementById("load").style.display="block";
	var interval = setInterval(load, 1000);
	$(".result").remove();
	document.getElementById("search_result").style.display="block";
	var xmlhttp = new XMLHttpRequest();
	xmlhttp.onreadystatechange = function() {
		if (xmlhttp.readyState == 4 && xmlhttp.status == 200) {
			document.getElementById("load").style.display="none";
			clearInterval(interval);
			var str = xmlhttp.responseText;
			var poems = str.split('#');
			for (var i = 0; i < poems.length; ++i)
			{
				if (poems[i].length == 0 || !poems[i].trim()) continue;
				var list = poems[i].split('&');
				var id = list[0];
				var title = list[1];
				var abstract = list[2];
				$("#search_result").append('<div class="result" id="'+ (i+1) +'"><div class="title"><a href="https://www.gswen.cn/poetry/' + id + '.html" target="_blank">' + title + '</a></div><div class="abstract">' + abstract + '</div><br>');
			}
		}
	}
	xmlhttp.open("POST", "php/poem.php", true);
	xmlhttp.setRequestHeader("CONTENT-TYPE", "application/x-www-form-urlencoded");
	xmlhttp.send("text=" + myform.sentence.value);
}