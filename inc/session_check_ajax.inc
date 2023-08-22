<?php
$sessionOk = isSessionAlive();
$sessionNotOk = !$sessionOk;

$result = array();
$result["sessionOk"] = $sessionOk;
$result["sessionNotOk"] = $sessionNotOk;

echo json_encode($result);
exit;
?>
