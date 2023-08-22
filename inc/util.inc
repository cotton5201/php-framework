<?php
/**
 * 세션 생존 여부 파악
 */
function isSessionAlive() {
	return isset($_SESSION['member_no']);
}

/**
 * 세션 만료 여부 파악
 */
function isSessionExpired() {
	return isSessionAlive() == false;
}

/**
 * session 사용자 이름 조회
 */
function getSessionMemberName() {
	return $_SESSION["member_nm"];
}

/**
 * 값 유무 검사
 */
function isEmpty($value) {
	return !isNotEmpty($value);
}

/**
 * 값 유무 검사
 */
function isNotEmpty($value) {
	return isset($value);
}

/**
 * 메세지 출력 후 이전 페이지로 이동 처리
 */
function showMessageAndGoBack($msg) {
	echo '
		<!doctype html>
		<html lang="ko">
		<head>
			<meta charset="utf-8">
			<script type="text/javascript">
				alert("'.$msg.'");
				window.history.back();
			</script>
		</head>
		<body></body>
		</html>
	';
}

/**
 * 메세지 출력 후 목적지 페이지로 이동(치환) 처리
 */
function showMessageAndPageReplace($msg, $targetUrl) {
	echo '
		<!doctype html>
		<html lang="ko">
		<head>
			<meta charset="utf-8">
			<script type="text/javascript">
				alert("'.$msg.'");
				window.location.replace("'.$targetUrl.'");
			</script>
		</head>
		<body></body>
		</html>
	';
}

/**
 * ajax 요청에 대한 응답 처리
 * @param $resultCode
 * @param $resultMessage
 */
function echoAjaxResponse($resultCode, $resultMessage) {
	$ok = ($resultCode > 0);
	$notOk = !$ok;
	
	$result = array();
	$result["notOk"] = $notOk;
	$result["ok"] = $ok;
	$result["code"] = $resultCode;
	$result["message"] = $resultMessage;
	
	echo json_encode($result, JSON_HEX_TAG | JSON_HEX_APOS | JSON_HEX_QUOT | JSON_HEX_AMP);
}

/**
 * 원래 문자열이 값이 없는 경우 대체 문자열로 반환 처리
 */
function nvl2($original, $replacement) {
	if(isset($original) == false || $original == '') {
		return $replacement;
	}
	return $original;
}

/**
 * 모든 공백 제거
 */
function trimAll($msg) {
	return preg_replace("/\s+/", "", $msg);
}

/**
 * 페이징 정보 반환
 */
function getPagingInfo($totcnt, $page_num, $list_size, $paging_block_size) {
	// 전체 페이지 계산
	$totalpage = ceil($totcnt / $list_size);

	// 시작페이지 계산
	$startpage = ((int)(($page_num - 1) / $paging_block_size) * $paging_block_size) + 1;
	$endpage = ((int)((($page_num - 1) + $paging_block_size) / $paging_block_size)) * $paging_block_size;
	if($totalpage <= $endpage) {
		$endpage = $totalpage;
	}

	// 이전 페이지 계산
	$beforepage = $page_num - 1;
	if($beforepage < $startpage) {
		$beforepage = $startpage;
	}

	// 다음 페이지 계산
	$afterpage = $page_num + 1;
	if($afterpage > $totalpage) {
		$afterpage = $totalpage;
	}
	if($afterpage == 0) {
		$afterpage = 1;
	}

	// 반환값 설정
	$returnvalue = array();
	$returnvalue["totcnt"]			= (int)$totcnt;
	$returnvalue["pagenum"]			= (int)$page_num;
	$returnvalue["rowsize"]			= (int)$list_size;
	$returnvalue["pagingblocksize"]	= (int)$paging_block_size;
	$returnvalue["totalpage"]		= (int)$totalpage;
	$returnvalue["startpage"]		= (int)$startpage;
	$returnvalue["endpage"]			= (int)$endpage;
	$returnvalue["beforepage"]		= (int)$beforepage;
	$returnvalue["afterpage"]		= (int)$afterpage;
	$returnvalue["beginpage"]		= 1;

	return $returnvalue;
}

/**
 * 페이징 컴포넌트 렌더링
 */
function makePagenation($url, $paginginfo, $param) {
	$current_pagenum = $param['page_num'];
	$url_param = $param;
	
	if($paginginfo["startpage"] == $paginginfo["endpage"]) {
		return;
	}

	if($paginginfo['totcnt'] > 0) {
		echo '<ul class="pagination">';
		
		// start page
		$url_param['page_num'] = $paginginfo["beginpage"];
		$url_str = $url . '?'.http_build_query($url_param);
		echo '<!-- set go to start page -->';
		echo '<li class="all-prv"><a href="'.$url_str.'" title="처음 페이지로 이동" data-page_num="'.$url_param['page_num'].'"><span aria-hidden="true">맨 처음으로 이동</span></a></li>';

		// before block page
		$url_param['page_num'] = $paginginfo["beforepage"];
		$url_str = $url . '?'.http_build_query($url_param);
		echo '<!-- set go to before block page -->';
		echo '<li class="prv"><a href="'.$url_str.'"  title="이전 페이지로 이동" data-page_num="'.$url_param['page_num'].'"></a></li>';

		// paging number buttons
		for($i=$paginginfo["startpage"]; $i<=$paginginfo["endpage"]; $i++) {
			$active = $current_pagenum == $i ? 'on' : '';
			$url_param['page_num'] = $i;
			$url_str = $url . '?'.http_build_query($url_param);
			echo '<li class="'.$active.'" ><a href="'.$url_str.'"  data-page_num="'.$i.'">'.$i.'</a></li>';
		}
		
		// after block page
		$url_param['page_num'] = $paginginfo["afterpage"];
		$url_str = $url . '?'.http_build_query($url_param);
		echo '<!-- set go to next block page -->';
		echo '<li class="nxt"><a href="'.$url_str.'" title="다음 페이지로 이동" data-page_num="'.$paginginfo["afterpage"].'"></a></li>';
		
		// last page
		$url_param['page_num'] = $paginginfo["totalpage"];
		$url_str = $url . '?'.http_build_query($url_param);
		echo '<!-- set go to end page -->';
		echo '<li class="all-nxt"><a href="'.$url_str.'"  title="마지막 페이지로 이동" data-page_num="'.$paginginfo["totalpage"].'"><span aria-hidden="true">맨 마지막으로 이동</span></a></li>';
		
		echo '</ul>';
	}
}

/**
 * 메세지 출력
 */
function showMessage($msg) {
	echo '
		<!doctype html>
		<html lang="ko">
		<head>
			<meta charset="utf-8">
			<script type="text/javascript">
				alert("'.$msg.'");
			</script>
		</head>
		<body></body>
		</html>
	';
}

/**
 * session 사용자 번호 조회
 */
function getSessionMemberNo() {
	return $_SESSION["member_no"];
}

/**
 * session 사용자 아이디 조회
 */
function __getSessionMemberId() {
	return $_SESSION["member_id"];
}

/**
 * Random UUID 반환 처리
 */
function getRandomUUID() {
	return sprintf(
		'%04x%04x-%04x-%04x-%04x-%04x%04x%04x',
		// 32 bits for "time_low"
		mt_rand(0, 0xffff), mt_rand(0, 0xffff),
		// 16 bits for "time_mid"
		mt_rand(0, 0xffff),
		// 16 bits for "time_hi_and_version",
		// four most significant bits holds version number 4
		mt_rand(0, 0x0fff) | 0x4000,
		// 16 bits, 8 bits for "clk_seq_hi_res",
		// 8 bits for "clk_seq_low",
		// two most significant bits holds zero and one for variant DCE1.1
		mt_rand(0, 0x3fff) | 0x8000,
		// 48 bits for "node"
		mt_rand(0, 0xffff), mt_rand(0, 0xffff), mt_rand(0, 0xffff)
	);
}

/**
 * 현 사이트의 URL을 반환 처리
 */
function getSiteURL() {
	return $_SERVER['SERVER_NAME'];
}


/**
 * 목록 번호 조회
 */
function getListNo($record_count, $loop_index, $page_num, $list_size) {
	return $record_count - (($page_num-1)*$list_size+$loop_index);
}

/**
 * 배열 내에서 주어진 값이 있는지 여부 검사
 */
function hasValInArr($search_value, $target_array) {
	foreach($target_array as $item) {
		if($item == $search_value) {
			return true;
		}
	}
	return false;
}

/**
 * 년도 목록 selectbox 구성 함수
 */
function makeYearListToHtml($selected_value, $size = 10) {
	$this_year = date('Y');
	$to_year = date('Y') - $size;
	foreach (range($this_year, $to_year) as $year) {
		echo '<option value="'.$year.'"'.($year == $selected_value ? ' selected="selected"' : '').'>'.$year.'</option>';
	}
}

/**
 * 값 디버깅
 */
function consoleLog( $data ){
	echo '<script>';
	echo 'console.log('. json_encode( $data ) .')';
	echo '</script>';
}

/**
 * 값 디버깅2
 */
function debug( $data ){
	echo '<div style="border:1px solid #000; background-color:#ff0; color:#00f; margin:10px; padding:10px;">';
	echo $data;
	echo '</div>';
}

/**
 * 모바일 기기 접속 여부 판단
 */
function isMobile() {
	return preg_match("/(android|avantgo|blackberry|bolt|boost|cricket|docomo|fone|hiptop|mini|mobi|palm|phone|pie|tablet|up\.browser|up\.link|webos|wos)/i", $_SERVER["HTTP_USER_AGENT"]);
}

/**
 * 모바일 기기 접속인 경우 특정 url로 이동 처리
 */
function mobileMove($url) {
	if(isMobile()) {
		header("Location: " . $url);
	}
}

/**
 * PC 기기 접속인 경우 특정 url로 이동 처리
 */
function pcMove($url) {
	if(isMobile() == false) {
		header("Location: " . $url);
	}
}

/**
 * 8글자 날짜 문자열을 10글자 문자열로 변환
 */
function converToDateFormat($str, $splitor='.') {
	$year = substr($str, 0, 4);
	$month = substr($str, 4, 2);
	$day = substr($str, 6, 2);
	return $year . $splitor . $month . $splitor . $day . $splitor;
}

/**
 * Replaces any parameter placeholders in a query with the value of that
 * parameter. Useful for debugging. Assumes anonymous parameters from 
 * $params are are in the same order as specified in $query
 *
 * @param string $query The sql query with parameter placeholders
 * @param array $params The array of substitution parameters
 * @return string The interpolated query
 */
function interpolateQuery($query, $params) {
	$keys = array();
	$values = $params;

	# build a regular expression for each parameter
	foreach ($params as $key => $value) {
		if (is_string($key)) {
			$keys[] = '/:'.$key.'/';
		} else {
			$keys[] = '/[?]/';
		}

		if (is_string($value))
			$values[$key] = "'" . $value . "'";

		if (is_array($value))
			$values[$key] = "'" . implode("','", $value) . "'";

		if (is_null($value))
			$values[$key] = 'NULL';
	}

	$query = preg_replace($keys, $values, $query);

	return $query;
}

/**
 * 값을 JSON 문자열로 변환하여 반환하는 함수
 */
function toJson($value) {
	return json_encode($value, JSON_NUMERIC_CHECK);
}

/**
 * select query 결과를 json으로 변환하는 함수
 */
function toJsonResultSet($select_result, $key_name) {
	$arr = array();
	foreach($select_result as $item) {
		array_push($arr, $item[$key_name]);
	}
	return json_encode($arr, JSON_NUMERIC_CHECK);
}
?>
