namespace Fox;

class MsgCrypt {
    private appid="";
    private appkey="";
    private fixout;

    /**
    *  appid
    *  appkey
    *  fixout true:同一字符串密文任何时候均相同；false: 同一字符串不同时间密文输出不同
    */
    public function __construct(appid, appkey, boolean! fixout=false) {
        let this->appkey = md5(appkey );
        let this->appid = appid;
        let this->fixout = fixout;
    }
    
    public function encrypt(text) {
        var random;
        var module;
        var size;
        var iv;
        var pkc_encoder;
        var encrypted;
        var e;
        try {
            //获得16位随机字符串，填充到明文之前
            let random = this->_getRandomStr ();
            let text = random . pack ( "N", strlen ( text ) ) . text . this->appid;
            // 网络字节序
            let size = mcrypt_get_block_size ( MCRYPT_RIJNDAEL_128, MCRYPT_MODE_CBC );
            let module = mcrypt_module_open ( MCRYPT_RIJNDAEL_128, "", MCRYPT_MODE_CBC, "" );
            let iv = substr ( this->appkey, 0, 16 );
            //使用自定义的填充方式对明文进行补位填充
            let  pkc_encoder = new PKCS7Encoder ();
            let text = pkc_encoder->encode ( text );
            mcrypt_generic_init ( module, this->appkey, iv );
            //加密
            let encrypted = mcrypt_generic ( module, text );
            mcrypt_generic_deinit ( module );
            mcrypt_module_close ( module );
            
            //使用BASE64对加密后的字符串进行编码
            return \Fox\Common::rtn ( true, "OK", base64_encode ( encrypted ) );
        }
        catch \Exception,e {
            return \Fox\Common::rtn ( false, "EncryptAESError" );
        }
    }
    
    public  function decrypt(encrypted) {
        var ciphertext_dec;
        var module;
        var iv;
        var decrypted;
        var e;
        var pkc_encoder;
        var result,content, len_list,xml_len,xml_content,from_appid;
        try {
            //使用BASE64对需要解密的字符串进行解码
            let ciphertext_dec = base64_decode ( encrypted );
            let module = mcrypt_module_open ( MCRYPT_RIJNDAEL_128, "", MCRYPT_MODE_CBC, "" );
            let iv = substr ( this->appkey, 0, 16 );
            mcrypt_generic_init ( module, this->appkey, iv );
            
            //解密
            let decrypted = mdecrypt_generic ( module, ciphertext_dec );
            mcrypt_generic_deinit ( module );
            mcrypt_module_close ( module );
        }
        catch \Exception, e  {
            return \Fox\Common::rtn ( false, "DecryptAESError" );
        }
        
        try {
            //去除补位字符
            let pkc_encoder = new PKCS7Encoder ();
            let result = pkc_encoder->decode ( decrypted );
            //去除16位随机字符串,网络字节序和AppId
            if strlen ( result ) < 16   {
                return "";
            }
            let content = substr ( result, 16, strlen ( result ) );
            let len_list = unpack ( "N", substr ( content, 0, 4 ) );
            let xml_len = len_list [1];
            
            let xml_content = substr ( content, 4, xml_len );

            let from_appid = substr ( content, xml_len + 4 );
        }
        catch \Exception,e{
            return \Fox\Common::rtn ( false, "IllegalBuffer" );
        }
        
        if(from_appid != this->appid) {
            return \Fox\Common::rtn ( false, "ValidateAppidError" );
        }
        
        return \Fox\Common::rtn ( true, "OK", xml_content );
    }
    
    /**
     * 随机生成16位字符串
     * @return string 生成的字符串
     */
    private function _getRandomStr()->string {
        var pol = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789abcdefghijklmnopqrstuvwxyz";
        if this->fixout{
            let pol = md5(pol . this->appkey);
        }
        else{
            let pol = str_shuffle(pol);
        }
        return substr(pol,1,16);
    }
	
	public function setFixout(fixout){
		let this->fixout=fixout;
		return this;
	}
}