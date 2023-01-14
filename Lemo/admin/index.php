<?php

define('APPLICATION_PATH', dirname(__FILE__));
define('BASE_URL', 'http://localhost/lemo-admin/');
$application = new Yaf_Application( APPLICATION_PATH . "/conf/application.ini");

$application->bootstrap()->run();
?>
