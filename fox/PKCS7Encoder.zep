namespace Fox;

class PKCS7Encoder {
    public static block_size = 32;

    /**
     * 对需要加密的明文进行填充补位
     * @param text 需要进行填充补位操作的明文
     * @return 补齐明文字符串
     */
     public static function encode(text)->string {
        var text_length = strlen ( text );
        //计算需要填充的位数
        var pad_chr,amount_to_pad,tmp;
        let amount_to_pad = self::block_size - (text_length % self::block_size);
        if(amount_to_pad == 0) {
            let amount_to_pad = self::block_size;
        }
        //获得补位所用的字符
        let pad_chr = chr ( amount_to_pad );
        let tmp = "";
        var index=0;

        loop{
            if index >= amount_to_pad{break;}
            let tmp .= pad_chr;
            let index += 1;
        }

        return text . tmp;
    }

    /**
     * 对解密后的明文进行补位删除
     * @param decrypted 解密后的明文
     * @return 删除填充补位后的明文
     */
     public static function decode(text) {
        var pad;
        let pad = ord ( substr ( text, - 1 ) );
        if(pad < 1 || pad > 32) {
            let pad = 0;
        }
        return substr ( text, 0, (strlen ( text ) - pad) );
    }
}
