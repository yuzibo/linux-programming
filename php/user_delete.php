<!DOCTYPE html>
<html>
<head>
<meta http-equiv="Content-Type" content="text/html"; charset="utf8">
<title> 删除客户 </title>
</head>

<body>
<div align="center">
<?php


require "config.php";

error_reporting($level = null);

$flag = mysql_query("SET NAMES utf8");

$client_name = $_POST[user_name];
$result = mysql_query("delete from persion where p_name='$client_name'");

$result = mysql_query("SELECT * FROM persion where p_name='$client_name'");
if(!$result){
		die('Error:' . mysql_error());
	}
	

$result = mysql_query("SELECT * FROM persion");

if(!$result){
		die('Error:' . mysql_error());
	}

	
	
echo "<table border='1'>
<tr>
<th>姓名</th>
<th>电话</th>
</tr>";

while($row = mysql_fetch_row($result))
  {
  echo "<tr>";
  echo "<td>" . $row[0] . "</td>";
  echo "<td>" . $row[1] . "</td>";
  echo "</tr>";
  }
echo "</table>";


mysql_close($con);


?>
</div>

<div align="center">
<form action="user_select.php" method="post">
	<h3>客户信息浏览</h3>
	客户姓名：<input type="text" name="user_name"/> <br/>
		
		<input type="submit" value="查看该客户信息" />		
	</form>

<form action="user_delete.php" method="post">
 	<h3>删除客户信息</h3> 
 	客户姓名：<input type="text" name="user_name"/> <br><br/>
		<input type="submit" value="删除客户" />
	</form>
	
</div>
</body>
</html>