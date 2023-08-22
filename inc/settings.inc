<?php 
error_reporting(E_ALL ^E_NOTICE);

// Db configuration
include "db_config.inc";

// Utils
include "util.inc";

// Commons
include "common.inc";

// Constants
include "constants.inc";

// Define timezone
date_default_timezone_set('Asia/Seoul');

// Session user
session_start();
?>