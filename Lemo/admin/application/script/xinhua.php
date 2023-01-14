<?php
function getPage($url) {
	$content = file_get_contents($url);
	return mb_convert_encoding($content, "UTF-8", "GBK");
}

function filterContent($messageContent) {
	$content = strip_tags($messageContent);
	$wordList = array("操你妈", "王八蛋");
	$blackList = "/".implode("|", $wordList)."/i";
	if (preg_match($blackList, $content, $matches)) {
		return false;
	}
	return true;
}

function hasPic($section) {
	$content = strip_tags($section);
	$wordList = array("摄", "供图");
	$blackList = "/".implode("|", $wordList)."/i";
	if (preg_match($blackList, $content, $matches)) {
		return true;
	}
	return false;
}

function insertMessage($sql) {
	$dsn = "mysql:host=127.0.0.1;dbname=lemo;";
	$pdo = new PDO($dsn, "root", "123456");
	$pdo->query("set names utf8");
	$res = $pdo->exec($sql);
	if ($res > 0) {
		return true;
	}
	return false;
}



require_once("phpQuery/phpQuery.php");

$paramList = getopt("u:t:");
$url = $paramList["u"];
$tagId = $paramList["t"];

$authorName = "新华网";
$authorImg = "http://image/techweb.com.cn/upload/2011/1223/1324637002630.jpg";

$url = "http://news.xinhuanet.com/politics/2017-05/13/c_1120965725.htm";
$page = getPage($url);


phpQuery::newDocumentFile($url);

$title = pq(".header .h-news")->find(".h-title")->text();
$createTime = pq(".header .h-news")->find(".h-time")->text();
$pList = pq("#p-detail")->find("p");
$createTime = strtotime($createTime);


$content = "";
foreach ($pList as $p) {
	$pContent = pq($p)->text();
	$pContent = trim($pContent);	
	#$img = pq($p)->find("img");
	if (empty($pContent) || hasPic($pContent)) {
		continue;
	}
	$content .= "<p>" . $pContent . "</p>";
}
#$content = mysql_real_escape_string($content);
$sql = "insert into tblMessage (message_title, message_content, cover_pic, author_name, author_img, tag_id, create_time) values ('" . $title . "', '" . $content . "', '" . $url . "', '" . $authorName . "', '" . $authorImg . "', " . $tagId . ", " . $createTime . ")";

$res = insertMessage($sql);

var_dump($res);



