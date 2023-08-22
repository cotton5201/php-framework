<?php
// check only post method
if(isset($_POST) == false) {
	echoAjaxResponse(999, '올바른 요청이 아닙니다.');
	exit;
}
?>