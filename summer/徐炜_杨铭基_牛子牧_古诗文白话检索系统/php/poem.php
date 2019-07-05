<?php
header("Content-Type:text/html; charset=utf-8");
@set_time_limit(0);
$str = $_POST['text'];
$set_charset = 'export LANG=zh_CN.UTF-8;';
$command = $set_charset.'python3 ../poem.py ';
$command .= $str;
$result = passthru($command);
echo $result;
?>