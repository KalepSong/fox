<?php 
$appid = 12444;
$appkey = 'appkey';


//true: 同一字符串同一个时间加密字符串相同；
//false：同一字符串不同时间加密字符串不同
$fixout = true;
$crypt = new  \Fox\MsgCrypt($appid, $appkey);

$str = 'Kalep MsgCrypt test';

echo $str . '<BR>=====<BR>';
$res = $crypt->encrypt($str);


echo '<pre>';
var_dump($res);
          
$res = $crypt->setFixout(true)->encrypt($str);
        
var_dump($res);
echo '<BR>================<BR>';

$res = $crypt->decrypt($res['data']);
    
echo '<BR>================<BR>';
var_dump($res);