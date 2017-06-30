<?php   
//if (session_status() == PHP_SESSION_NONE) {
   session_start();
//}
error_reporting(E_ALL);
if(!defined('DS')){
	define('DS', DIRECTORY_SEPARATOR);
	define('ROOT', dirname(__FILE__)); 
}

if(!defined('TABLE_CLASS')){
	define('TABLE_CLASS', ROOT.DS.'db');
	define('DATA_CLASS', ROOT.DS.'dt');
	define('VIEW_CLASS', ROOT.DS.'view');
	define('HELPER_CLASS', ROOT.DS.'helper');
	define('FORM_CLASS', ROOT.DS.'form');
}
	


function myautoload($className) {
    if (file_exists(TABLE_CLASS. DS . strtolower($className) . '.class.inc')) {
        require_once(TABLE_CLASS. DS . strtolower($className) . '.class.inc');
    }elseif(file_exists(DATA_CLASS. DS . strtolower($className) . '.class.inc')) {
        require_once(DATA_CLASS. DS . strtolower($className) . '.class.inc');
       }else if (file_exists(VIEW_CLASS. DS . strtolower($className) . '.class.inc')) {
            require_once(VIEW_CLASS. DS . strtolower($className) . '.class.inc');
          }elseif (file_exists(HELPER_CLASS. DS . strtolower($className) . '.class.inc')) {
               require_once(HELPER_CLASS. DS . strtolower($className) . '.class.inc');
            }elseif (file_exists(HELPER_CLASS. DS . strtolower($className) . '.class.php')) {
               require_once(HELPER_CLASS. DS . strtolower($className) . '.class.php');
            }elseif (file_exists(FORM_CLASS. DS . strtolower($className) . '.class.inc')) {
                require_once(FORM_CLASS. DS . strtolower($className) . '.class.inc');
              } 
}
spl_autoload_register('myautoload');
//set_time_limit(0);
date_default_timezone_set("Asia/Jakarta");
//ini_set('memory_limit','-1');
 
?>