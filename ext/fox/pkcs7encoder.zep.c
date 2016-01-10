
#ifdef HAVE_CONFIG_H
#include "../ext_config.h"
#endif

#include <php.h>
#include "../php_ext.h"
#include "../ext.h"

#include <Zend/zend_operators.h>
#include <Zend/zend_exceptions.h>
#include <Zend/zend_interfaces.h>

#include "kernel/main.h"
#include "kernel/string.h"
#include "kernel/memory.h"
#include "kernel/object.h"
#include "kernel/operators.h"
#include "kernel/fcall.h"
#include "kernel/concat.h"


ZEPHIR_INIT_CLASS(Fox_PKCS7Encoder) {

	ZEPHIR_REGISTER_CLASS(Fox, PKCS7Encoder, fox, pkcs7encoder, fox_pkcs7encoder_method_entry, 0);

	zend_declare_property_long(fox_pkcs7encoder_ce, SL("block_size"), 32, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC TSRMLS_CC);

	return SUCCESS;

}

/**
 * 对需要加密的明文进行填充补位
 * @param text 需要进行填充补位操作的明文
 * @return 补齐明文字符串
 */
PHP_METHOD(Fox_PKCS7Encoder, encode) {

	int ZEPHIR_LAST_CALL_STATUS, index;
	zval *text, *text_length = NULL, *pad_chr = NULL, *amount_to_pad = NULL, *tmp = NULL, *_0, *_1, *_2;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &text);



	ZEPHIR_INIT_VAR(text_length);
	ZVAL_LONG(text_length, zephir_fast_strlen_ev(text));
	_0 = zephir_fetch_static_property_ce(fox_pkcs7encoder_ce, SL("block_size") TSRMLS_CC);
	_1 = zephir_fetch_static_property_ce(fox_pkcs7encoder_ce, SL("block_size") TSRMLS_CC);
	ZEPHIR_INIT_VAR(_2);
	mod_function(_2, text_length, _1 TSRMLS_CC);
	ZEPHIR_INIT_VAR(amount_to_pad);
	zephir_sub_function(amount_to_pad, _0, _2);
	if (ZEPHIR_IS_LONG(amount_to_pad, 0)) {
		ZEPHIR_OBS_NVAR(amount_to_pad);
		zephir_read_static_property_ce(&amount_to_pad, fox_pkcs7encoder_ce, SL("block_size") TSRMLS_CC);
	}
	ZEPHIR_CALL_FUNCTION(&pad_chr, "chr", NULL, 17, amount_to_pad);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(tmp);
	ZVAL_STRING(tmp, "", 1);
	index = 0;
	while (1) {
		if (ZEPHIR_LE_LONG(amount_to_pad, index)) {
			break;
		}
		zephir_concat_self(&tmp, pad_chr TSRMLS_CC);
		index += 1;
	}
	ZEPHIR_CONCAT_VV(return_value, text, tmp);
	RETURN_MM();

}

/**
 * 对解密后的明文进行补位删除
 * @param decrypted 解密后的明文
 * @return 删除填充补位后的明文
 */
PHP_METHOD(Fox_PKCS7Encoder, decode) {

	zend_bool _2;
	int ZEPHIR_LAST_CALL_STATUS;
	zval *text, *pad = NULL, _0, *_1, _3, _4;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &text);



	ZEPHIR_SINIT_VAR(_0);
	ZVAL_LONG(&_0, -1);
	ZEPHIR_INIT_VAR(_1);
	zephir_substr(_1, text, zephir_get_intval(&_0), 0, ZEPHIR_SUBSTR_NO_LENGTH);
	ZEPHIR_CALL_FUNCTION(&pad, "ord", NULL, 18, _1);
	zephir_check_call_status();
	_2 = ZEPHIR_LT_LONG(pad, 1);
	if (!(_2)) {
		_2 = ZEPHIR_GT_LONG(pad, 32);
	}
	if (_2) {
		ZEPHIR_INIT_NVAR(pad);
		ZVAL_LONG(pad, 0);
	}
	ZEPHIR_SINIT_VAR(_3);
	ZVAL_LONG(&_3, 0);
	ZEPHIR_SINIT_VAR(_4);
	ZVAL_LONG(&_4, ((zephir_fast_strlen_ev(text) - zephir_get_numberval(pad))));
	zephir_substr(return_value, text, 0 , zephir_get_intval(&_4), 0);
	RETURN_MM();

}

