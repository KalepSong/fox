<?php
namespace Fox;

class Common
{

    /**
     * 格式化返回数据
     *
     * @param bool status
     * @param string message
     * @param array message
     * @return   array('rtn' =>true/false, 'msg'=> $message, 'data'=>$data);
     *
     * @example
     *
     * @author Kalep
     */
    public static function rtn($status, $message = "", $data = array()) {}
}