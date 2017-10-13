<!DOCTYPE html>
<?php
header("Content-type:text/html; charset=utf8");

$host_name = "localhost";
$host_user = "root";
$host_passwd = "yubo";
$db_name = "xiaozhi";
$table_persion_name = "persion";
$table_product_info = "product";


$my_conn = mysql_connect($host_name,$host_user,$host_passwd);
mysql_select_db("$db_name",$my_conn);
mysql_query("SET NAMES UTF-8");

	if($my_conn){
		echo "";
	}
	else{
		echo "链接失败!";
	}

#$str_sql = "select * from "
#$result = mysql_query()
?>
