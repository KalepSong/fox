
extern zend_class_entry *fox_msgcrypt_ce;

ZEPHIR_INIT_CLASS(Fox_MsgCrypt);

PHP_METHOD(Fox_MsgCrypt, __construct);
PHP_METHOD(Fox_MsgCrypt, encrypt);
PHP_METHOD(Fox_MsgCrypt, decrypt);
PHP_METHOD(Fox_MsgCrypt, _getRandomStr);
PHP_METHOD(Fox_MsgCrypt, setFixout);

ZEND_BEGIN_ARG_INFO_EX(arginfo_fox_msgcrypt___construct, 0, 0, 2)
	ZEND_ARG_INFO(0, appid)
	ZEND_ARG_INFO(0, appkey)
	ZEND_ARG_INFO(0, fixout)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_fox_msgcrypt_encrypt, 0, 0, 1)
	ZEND_ARG_INFO(0, text)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_fox_msgcrypt_decrypt, 0, 0, 1)
	ZEND_ARG_INFO(0, encrypted)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_fox_msgcrypt_setfixout, 0, 0, 1)
	ZEND_ARG_INFO(0, fixout)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(fox_msgcrypt_method_entry) {
	PHP_ME(Fox_MsgCrypt, __construct, arginfo_fox_msgcrypt___construct, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
	PHP_ME(Fox_MsgCrypt, encrypt, arginfo_fox_msgcrypt_encrypt, ZEND_ACC_PUBLIC)
	PHP_ME(Fox_MsgCrypt, decrypt, arginfo_fox_msgcrypt_decrypt, ZEND_ACC_PUBLIC)
	PHP_ME(Fox_MsgCrypt, _getRandomStr, NULL, ZEND_ACC_PRIVATE)
	PHP_ME(Fox_MsgCrypt, setFixout, arginfo_fox_msgcrypt_setfixout, ZEND_ACC_PUBLIC)
	PHP_FE_END
};
