
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
#include "kernel/array.h"
#include "kernel/operators.h"


ZEPHIR_INIT_CLASS(Fox_Common) {

	ZEPHIR_REGISTER_CLASS(Fox, Common, fox, common, fox_common_method_entry, 0);

	return SUCCESS;

}

/**
 * 格式化返回数据
 *
 * @param bool status
 * @param string message
 * @param array message
 * @return
 *
 * @example
 *
 * @author kalep
 */
PHP_METHOD(Fox_Common, rtn) {

	zval *message = NULL;
	zval *status_param = NULL, *message_param = NULL, *data = NULL, *res = NULL, *_0 = NULL, *_1 = NULL;
	zend_bool status;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 2, &status_param, &message_param, &data);

	status = zephir_get_boolval(status_param);
	if (!message_param) {
		ZEPHIR_INIT_VAR(message);
		ZVAL_STRING(message, "", 1);
	} else {
		zephir_get_strval(message, message_param);
	}
	if (!data) {
		ZEPHIR_INIT_VAR(data);
		array_init(data);
	}


	ZEPHIR_INIT_VAR(res);
	array_init(res);
	ZEPHIR_INIT_VAR(_0);
	if (status) {
		ZEPHIR_INIT_NVAR(_0);
		ZVAL_BOOL(_0, 1);
	} else {
		ZEPHIR_INIT_NVAR(_0);
		ZVAL_BOOL(_0, 0);
	}
	zephir_array_update_string(&res, SL("rtn"), &_0, PH_COPY | PH_SEPARATE);
	ZEPHIR_INIT_VAR(_1);
	if (!(!message) && Z_STRLEN_P(message)) {
		ZEPHIR_CPY_WRT(_1, message);
	} else {
		if (status) {
			ZEPHIR_INIT_NVAR(_1);
			ZVAL_STRING(_1, "操作成功", 1);
		} else {
			ZEPHIR_INIT_NVAR(_1);
			ZVAL_STRING(_1, "操作失败", 1);
		}
	}
	zephir_array_update_string(&res, SL("msg"), &_1, PH_COPY | PH_SEPARATE);
	zephir_array_update_string(&res, SL("data"), &data, PH_COPY | PH_SEPARATE);
	RETURN_CCTOR(res);

}

