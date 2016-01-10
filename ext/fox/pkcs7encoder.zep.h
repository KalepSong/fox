
extern zend_class_entry *fox_pkcs7encoder_ce;

ZEPHIR_INIT_CLASS(Fox_PKCS7Encoder);

PHP_METHOD(Fox_PKCS7Encoder, encode);
PHP_METHOD(Fox_PKCS7Encoder, decode);

ZEND_BEGIN_ARG_INFO_EX(arginfo_fox_pkcs7encoder_encode, 0, 0, 1)
	ZEND_ARG_INFO(0, text)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_fox_pkcs7encoder_decode, 0, 0, 1)
	ZEND_ARG_INFO(0, text)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(fox_pkcs7encoder_method_entry) {
	PHP_ME(Fox_PKCS7Encoder, encode, arginfo_fox_pkcs7encoder_encode, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Fox_PKCS7Encoder, decode, arginfo_fox_pkcs7encoder_decode, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_FE_END
};
