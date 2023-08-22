<?php 
if(isSessionExpired()) {
	echo '
		<script type="text/javascript">
			alert("세션이 종료되었습니다.");
			window.location.replace("../LGN/logout.php");
		</script>
	';
	exit;
}
?>