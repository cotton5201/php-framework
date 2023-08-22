<?php
/**
 * 프로그램명 : 현 요청이 POST 방식 요청인지 여부 검사
 */
// check only post method
if(isset($_POST) == false) {
	showMessageAndGoBack('올바른 요청이 아닙니다.');
	exit;
}
?>