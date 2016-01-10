namespace Fox;

class Common {

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
	public static function rtn(boolean  status,  string message = "",  data=[]) {
	    var res=[];
	    let res["rtn"]=  status ? true : false;
	    let res["msg"]= message ? message : (status ? "操作成功" : "操作失败");
		let res["data"] = data;
		return res;
	}
}