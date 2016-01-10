#!/usr/bin/env php
<?php
$appid = 12444;
$appkey = 'appkey';


//true: m~P~L0m~@0m~W符串m~P~L0m~@个m~W0m~W0m~J| 0m~F0m~W符串m~[0m~P~L0m~[
//false0m~Zm~P~L0m~@0m~W符串0m~Mm~P~Lm~W0m~W0m~J| 0m~F0m~W符串0m~Mm~P~L
$fixout = true;
$crypt = new  \Fox\MsgCrypt($appid, $appkey);

$str = 'Kalep MsgCrypt test';

echo $str . "\n=========\n";
$res = $crypt->encrypt($str);


echo "\n";
print_r($res);

$res = $crypt->setFixout(true)->encrypt($str);

var_dump($res);
echo "\n=========\n";

$res = $crypt->decrypt($res['data']);

echo "\n=========\n";
var_dump($res);