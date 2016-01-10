
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
#include "kernel/memory.h"
#include "kernel/string.h"
#include "kernel/object.h"
#include "ext/spl/spl_exceptions.h"
#include "kernel/exception.h"
#include "kernel/fcall.h"
#include "kernel/concat.h"
#include "kernel/operators.h"
#include "kernel/array.h"


ZEPHIR_INIT_CLASS(Fox_MsgCrypt) {

	ZEPHIR_REGISTER_CLASS(Fox, MsgCrypt, fox, msgcrypt, fox_msgcrypt_method_entry, 0);

	zend_declare_property_string(fox_msgcrypt_ce, SL("appid"), "", ZEND_ACC_PRIVATE TSRMLS_CC);

	zend_declare_property_string(fox_msgcrypt_ce, SL("appkey"), "", ZEND_ACC_PRIVATE TSRMLS_CC);

	zend_declare_property_null(fox_msgcrypt_ce, SL("fixout"), ZEND_ACC_PRIVATE TSRMLS_CC);

	return SUCCESS;

}

/**
 *  appid
 *  appkey
 *  fixout true:同一字符串密文任何时候均相同；false: 同一字符串不同时间密文输出不同
 */
PHP_METHOD(Fox_MsgCrypt, __construct) {

	zend_bool fixout;
	zval *appid, *appkey, *fixout_param = NULL, *_0;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 1, &appid, &appkey, &fixout_param);

	if (!fixout_param) {
		fixout = 0;
	} else {
	if (unlikely(Z_TYPE_P(fixout_param) != IS_BOOL)) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'fixout' must be a bool") TSRMLS_CC);
		RETURN_MM_NULL();
	}
	fixout = Z_BVAL_P(fixout_param);
	}


	ZEPHIR_INIT_VAR(_0);
	zephir_md5(_0, appkey);
	zephir_update_property_this(this_ptr, SL("appkey"), _0 TSRMLS_CC);
	zephir_update_property_this(this_ptr, SL("appid"), appid TSRMLS_CC);
	if (fixout) {
		zephir_update_property_this(this_ptr, SL("fixout"), ZEPHIR_GLOBAL(global_true) TSRMLS_CC);
	} else {
		zephir_update_property_this(this_ptr, SL("fixout"), ZEPHIR_GLOBAL(global_false) TSRMLS_CC);
	}
	ZEPHIR_MM_RESTORE();

}

PHP_METHOD(Fox_MsgCrypt, encrypt) {

	zephir_fcall_cache_entry *_10 = NULL;
	int ZEPHIR_LAST_CALL_STATUS;
	zval *text = NULL, *random = NULL, *module = NULL, *size = NULL, *iv = NULL, *pkc_encoder = NULL, *encrypted = NULL, *e = NULL, _0$$3 = zval_used_for_init, _1$$3 = zval_used_for_init, *_2$$3 = NULL, *_3$$3, *_4$$3, _5$$3, _6$$3, *_7$$3, *_8$$3 = NULL, *_9$$3, *_11$$3, *_12$$3, *_13$$4, *_14$$4;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &text);

	ZEPHIR_SEPARATE_PARAM(text);



	/* try_start_1: */

		ZEPHIR_CALL_METHOD(&random, this_ptr, "_getrandomstr", NULL, 1);
		zephir_check_call_status_or_jump(try_end_1);
		ZEPHIR_SINIT_VAR(_0$$3);
		ZVAL_STRING(&_0$$3, "N", 0);
		ZEPHIR_SINIT_VAR(_1$$3);
		ZVAL_LONG(&_1$$3, zephir_fast_strlen_ev(text));
		ZEPHIR_CALL_FUNCTION(&_2$$3, "pack", NULL, 2, &_0$$3, &_1$$3);
		zephir_check_call_status_or_jump(try_end_1);
		_3$$3 = zephir_fetch_nproperty_this(this_ptr, SL("appid"), PH_NOISY_CC);
		ZEPHIR_INIT_VAR(_4$$3);
		ZEPHIR_CONCAT_VVVV(_4$$3, random, _2$$3, text, _3$$3);
		ZEPHIR_CPY_WRT(text, _4$$3);
		ZEPHIR_SINIT_NVAR(_0$$3);
		ZVAL_STRING(&_0$$3, "rijndael-128", 0);
		ZEPHIR_SINIT_NVAR(_1$$3);
		ZVAL_STRING(&_1$$3, "cbc", 0);
		ZEPHIR_CALL_FUNCTION(&size, "mcrypt_get_block_size", NULL, 3, &_0$$3, &_1$$3);
		zephir_check_call_status_or_jump(try_end_1);
		ZEPHIR_SINIT_NVAR(_0$$3);
		ZVAL_STRING(&_0$$3, "rijndael-128", 0);
		ZEPHIR_SINIT_NVAR(_1$$3);
		ZVAL_STRING(&_1$$3, "", 0);
		ZEPHIR_SINIT_VAR(_5$$3);
		ZVAL_STRING(&_5$$3, "cbc", 0);
		ZEPHIR_SINIT_VAR(_6$$3);
		ZVAL_STRING(&_6$$3, "", 0);
		ZEPHIR_CALL_FUNCTION(&module, "mcrypt_module_open", NULL, 4, &_0$$3, &_1$$3, &_5$$3, &_6$$3);
		zephir_check_call_status_or_jump(try_end_1);
		_7$$3 = zephir_fetch_nproperty_this(this_ptr, SL("appkey"), PH_NOISY_CC);
		ZEPHIR_SINIT_NVAR(_0$$3);
		ZVAL_LONG(&_0$$3, 0);
		ZEPHIR_SINIT_NVAR(_1$$3);
		ZVAL_LONG(&_1$$3, 16);
		ZEPHIR_INIT_VAR(iv);
		zephir_substr(iv, _7$$3, 0 , 16 , 0);
		ZEPHIR_INIT_VAR(pkc_encoder);
		object_init_ex(pkc_encoder, fox_pkcs7encoder_ce);
		if (zephir_has_constructor(pkc_encoder TSRMLS_CC)) {
			ZEPHIR_CALL_METHOD(NULL, pkc_encoder, "__construct", NULL, 0);
			zephir_check_call_status_or_jump(try_end_1);
		}
		ZEPHIR_CALL_METHOD(&_8$$3, pkc_encoder, "encode", NULL, 5, text);
		zephir_check_call_status_or_jump(try_end_1);
		ZEPHIR_CPY_WRT(text, _8$$3);
		_9$$3 = zephir_fetch_nproperty_this(this_ptr, SL("appkey"), PH_NOISY_CC);
		ZEPHIR_CALL_FUNCTION(NULL, "mcrypt_generic_init", NULL, 6, module, _9$$3, iv);
		zephir_check_call_status_or_jump(try_end_1);
		ZEPHIR_CALL_FUNCTION(&encrypted, "mcrypt_generic", NULL, 7, module, text);
		zephir_check_call_status_or_jump(try_end_1);
		ZEPHIR_CALL_FUNCTION(NULL, "mcrypt_generic_deinit", NULL, 8, module);
		zephir_check_call_status_or_jump(try_end_1);
		ZEPHIR_CALL_FUNCTION(NULL, "mcrypt_module_close", NULL, 9, module);
		zephir_check_call_status_or_jump(try_end_1);
		ZEPHIR_CALL_FUNCTION(&_8$$3, "base64_encode", NULL, 11, encrypted);
		zephir_check_call_status_or_jump(try_end_1);
		ZEPHIR_INIT_VAR(_11$$3);
		ZVAL_BOOL(_11$$3, 1);
		ZEPHIR_INIT_VAR(_12$$3);
		ZVAL_STRING(_12$$3, "OKx", ZEPHIR_TEMP_PARAM_COPY);
		ZEPHIR_RETURN_CALL_CE_STATIC(fox_common_ce, "rtn", &_10, 10, _11$$3, _12$$3, _8$$3);
		zephir_check_temp_parameter(_12$$3);
		zephir_check_call_status_or_jump(try_end_1);
		RETURN_MM();

	try_end_1:

	if (EG(exception)) {
		ZEPHIR_CPY_WRT(e, EG(exception));
		if (zephir_instance_of_ev(e, zend_exception_get_default(TSRMLS_C) TSRMLS_CC)) {
			zend_clear_exception(TSRMLS_C);
			ZEPHIR_INIT_VAR(_13$$4);
			ZVAL_BOOL(_13$$4, 0);
			ZEPHIR_INIT_VAR(_14$$4);
			ZVAL_STRING(_14$$4, "EncryptAESError", ZEPHIR_TEMP_PARAM_COPY);
			ZEPHIR_RETURN_CALL_CE_STATIC(fox_common_ce, "rtn", &_10, 10, _13$$4, _14$$4);
			zephir_check_temp_parameter(_14$$4);
			zephir_check_call_status();
			RETURN_MM();
		}
	}
	ZEPHIR_MM_RESTORE();

}

PHP_METHOD(Fox_MsgCrypt, decrypt) {

	zephir_fcall_cache_entry *_6 = NULL;
	int ZEPHIR_LAST_CALL_STATUS;
	zval *encrypted, *ciphertext_dec = NULL, *module = NULL, *iv = NULL, *decrypted = NULL, *e = NULL, *pkc_encoder = NULL, *result = NULL, *content = NULL, *len_list = NULL, *xml_len = NULL, *xml_content = NULL, *from_appid = NULL, *_18, *_21, *_22, _0$$3 = zval_used_for_init, _1$$3 = zval_used_for_init, _2$$3, _3$$3, *_4$$3, *_5$$3, *_7$$4, *_8$$4, _9$$5, _10$$5, _11$$5, _12$$5, *_13$$5, _14$$5 = zval_used_for_init, _15$$5, *_16$$7, *_17$$7, *_19$$8, *_20$$8;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &encrypted);




	/* try_start_1: */

		ZEPHIR_CALL_FUNCTION(&ciphertext_dec, "base64_decode", NULL, 12, encrypted);
		zephir_check_call_status_or_jump(try_end_1);
		ZEPHIR_SINIT_VAR(_0$$3);
		ZVAL_STRING(&_0$$3, "rijndael-128", 0);
		ZEPHIR_SINIT_VAR(_1$$3);
		ZVAL_STRING(&_1$$3, "", 0);
		ZEPHIR_SINIT_VAR(_2$$3);
		ZVAL_STRING(&_2$$3, "cbc", 0);
		ZEPHIR_SINIT_VAR(_3$$3);
		ZVAL_STRING(&_3$$3, "", 0);
		ZEPHIR_CALL_FUNCTION(&module, "mcrypt_module_open", NULL, 4, &_0$$3, &_1$$3, &_2$$3, &_3$$3);
		zephir_check_call_status_or_jump(try_end_1);
		_4$$3 = zephir_fetch_nproperty_this(this_ptr, SL("appkey"), PH_NOISY_CC);
		ZEPHIR_SINIT_NVAR(_0$$3);
		ZVAL_LONG(&_0$$3, 0);
		ZEPHIR_SINIT_NVAR(_1$$3);
		ZVAL_LONG(&_1$$3, 16);
		ZEPHIR_INIT_VAR(iv);
		zephir_substr(iv, _4$$3, 0 , 16 , 0);
		_5$$3 = zephir_fetch_nproperty_this(this_ptr, SL("appkey"), PH_NOISY_CC);
		ZEPHIR_CALL_FUNCTION(NULL, "mcrypt_generic_init", NULL, 6, module, _5$$3, iv);
		zephir_check_call_status_or_jump(try_end_1);
		ZEPHIR_CALL_FUNCTION(&decrypted, "mdecrypt_generic", NULL, 13, module, ciphertext_dec);
		zephir_check_call_status_or_jump(try_end_1);
		ZEPHIR_CALL_FUNCTION(NULL, "mcrypt_generic_deinit", NULL, 8, module);
		zephir_check_call_status_or_jump(try_end_1);
		ZEPHIR_CALL_FUNCTION(NULL, "mcrypt_module_close", NULL, 9, module);
		zephir_check_call_status_or_jump(try_end_1);

	try_end_1:

	if (EG(exception)) {
		ZEPHIR_CPY_WRT(e, EG(exception));
		if (zephir_instance_of_ev(e, zend_exception_get_default(TSRMLS_C) TSRMLS_CC)) {
			zend_clear_exception(TSRMLS_C);
			ZEPHIR_INIT_VAR(_7$$4);
			ZVAL_BOOL(_7$$4, 0);
			ZEPHIR_INIT_VAR(_8$$4);
			ZVAL_STRING(_8$$4, "DecryptAESError", ZEPHIR_TEMP_PARAM_COPY);
			ZEPHIR_RETURN_CALL_CE_STATIC(fox_common_ce, "rtn", &_6, 10, _7$$4, _8$$4);
			zephir_check_temp_parameter(_8$$4);
			zephir_check_call_status();
			RETURN_MM();
		}
	}

	/* try_start_2: */

		ZEPHIR_INIT_VAR(pkc_encoder);
		object_init_ex(pkc_encoder, fox_pkcs7encoder_ce);
		if (zephir_has_constructor(pkc_encoder TSRMLS_CC)) {
			ZEPHIR_CALL_METHOD(NULL, pkc_encoder, "__construct", NULL, 0);
			zephir_check_call_status_or_jump(try_end_1);
		}
		ZEPHIR_CALL_METHOD(&result, pkc_encoder, "decode", NULL, 14, decrypted);
		zephir_check_call_status_or_jump(try_end_1);
		if (zephir_fast_strlen_ev(result) < 16) {
			RETURN_MM_STRING("", 1);
		}
		ZEPHIR_SINIT_VAR(_9$$5);
		ZVAL_LONG(&_9$$5, 16);
		ZEPHIR_SINIT_VAR(_10$$5);
		ZVAL_LONG(&_10$$5, zephir_fast_strlen_ev(result));
		ZEPHIR_INIT_VAR(content);
		zephir_substr(content, result, 16 , zephir_get_intval(&_10$$5), 0);
		ZEPHIR_SINIT_VAR(_11$$5);
		ZVAL_LONG(&_11$$5, 0);
		ZEPHIR_SINIT_VAR(_12$$5);
		ZVAL_LONG(&_12$$5, 4);
		ZEPHIR_INIT_VAR(_13$$5);
		zephir_substr(_13$$5, content, 0 , 4 , 0);
		ZEPHIR_SINIT_VAR(_14$$5);
		ZVAL_STRING(&_14$$5, "N", 0);
		ZEPHIR_CALL_FUNCTION(&len_list, "unpack", NULL, 15, &_14$$5, _13$$5);
		zephir_check_call_status_or_jump(try_end_1);
		ZEPHIR_OBS_VAR(xml_len);
		zephir_array_fetch_long(&xml_len, len_list, 1, PH_NOISY, "fox/MsgCrypt.zep", 86 TSRMLS_CC);
		ZEPHIR_SINIT_NVAR(_14$$5);
		ZVAL_LONG(&_14$$5, 4);
		ZEPHIR_INIT_VAR(xml_content);
		zephir_substr(xml_content, content, 4 , zephir_get_intval(xml_len), 0);
		ZEPHIR_SINIT_VAR(_15$$5);
		ZVAL_LONG(&_15$$5, (zephir_get_numberval(xml_len) + 4));
		ZEPHIR_INIT_VAR(from_appid);
		zephir_substr(from_appid, content, zephir_get_intval(&_15$$5), 0, ZEPHIR_SUBSTR_NO_LENGTH);

	try_end_2:

	if (EG(exception)) {
		ZEPHIR_CPY_WRT(e, EG(exception));
		if (zephir_instance_of_ev(e, zend_exception_get_default(TSRMLS_C) TSRMLS_CC)) {
			zend_clear_exception(TSRMLS_C);
			ZEPHIR_INIT_VAR(_16$$7);
			ZVAL_BOOL(_16$$7, 0);
			ZEPHIR_INIT_VAR(_17$$7);
			ZVAL_STRING(_17$$7, "IllegalBuffer", ZEPHIR_TEMP_PARAM_COPY);
			ZEPHIR_RETURN_CALL_CE_STATIC(fox_common_ce, "rtn", &_6, 10, _16$$7, _17$$7);
			zephir_check_temp_parameter(_17$$7);
			zephir_check_call_status();
			RETURN_MM();
		}
	}
	_18 = zephir_fetch_nproperty_this(this_ptr, SL("appid"), PH_NOISY_CC);
	if (!ZEPHIR_IS_EQUAL(from_appid, _18)) {
		ZEPHIR_INIT_VAR(_19$$8);
		ZVAL_BOOL(_19$$8, 0);
		ZEPHIR_INIT_VAR(_20$$8);
		ZVAL_STRING(_20$$8, "ValidateAppidError", ZEPHIR_TEMP_PARAM_COPY);
		ZEPHIR_RETURN_CALL_CE_STATIC(fox_common_ce, "rtn", &_6, 10, _19$$8, _20$$8);
		zephir_check_temp_parameter(_20$$8);
		zephir_check_call_status();
		RETURN_MM();
	}
	ZEPHIR_INIT_VAR(_21);
	ZVAL_BOOL(_21, 1);
	ZEPHIR_INIT_VAR(_22);
	ZVAL_STRING(_22, "OK", ZEPHIR_TEMP_PARAM_COPY);
	ZEPHIR_RETURN_CALL_CE_STATIC(fox_common_ce, "rtn", &_6, 10, _21, _22, xml_content);
	zephir_check_temp_parameter(_22);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * 随机生成16位字符串
 * @return string 生成的字符串
 */
PHP_METHOD(Fox_MsgCrypt, _getRandomStr) {

	zval *pol = NULL, *_0, _4, _5, *_1$$3, *_2$$3, *_3$$4 = NULL;
	int ZEPHIR_LAST_CALL_STATUS;

	ZEPHIR_MM_GROW();

	ZEPHIR_INIT_VAR(pol);
	ZVAL_STRING(pol, "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789abcdefghijklmnopqrstuvwxyz", 1);
	_0 = zephir_fetch_nproperty_this(this_ptr, SL("fixout"), PH_NOISY_CC);
	if (zephir_is_true(_0)) {
		_1$$3 = zephir_fetch_nproperty_this(this_ptr, SL("appkey"), PH_NOISY_CC);
		ZEPHIR_INIT_VAR(_2$$3);
		ZEPHIR_CONCAT_VV(_2$$3, pol, _1$$3);
		ZEPHIR_INIT_NVAR(pol);
		zephir_md5(pol, _2$$3);
	} else {
		ZEPHIR_CALL_FUNCTION(&_3$$4, "str_shuffle", NULL, 16, pol);
		zephir_check_call_status();
		ZEPHIR_CPY_WRT(pol, _3$$4);
	}
	ZEPHIR_SINIT_VAR(_4);
	ZVAL_LONG(&_4, 1);
	ZEPHIR_SINIT_VAR(_5);
	ZVAL_LONG(&_5, 16);
	zephir_substr(return_value, pol, 1 , 16 , 0);
	RETURN_MM();

}

