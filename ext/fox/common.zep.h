
extern zend_class_entry *fox_common_ce;

ZEPHIR_INIT_CLASS(Fox_Common);

PHP_METHOD(Fox_Common, rtn);

ZEND_BEGIN_ARG_INFO_EX(arginfo_fox_common_rtn, 0, 0, 1)
	ZEND_ARG_INFO(0, status)
	ZEND_ARG_INFO(0, message)
	ZEND_ARG_INFO(0, data)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(fox_common_method_entry) {
	PHP_ME(Fox_Common, rtn, arginfo_fox_common_rtn, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_FE_END
};
