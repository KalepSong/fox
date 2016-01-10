<?php
//加密字符串
class MsgCrypt
{

    /**
     * appid
     * appkey
     * fixout true:同一字符串密文任何时候均相同；false: 同一字符串不同时间密文输出不同
     */
    public function __construct($appid, $appkey, $fixout = false){}

    //加密
    public function encrypt($text) {}

    //解密
    public function decrypt($text){}

    //设置输出密文是否固定，默认不固定(false)
    public function setFixout($fixout){}
}