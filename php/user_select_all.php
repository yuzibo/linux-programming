<!DOCTYPE html>
<html>
<head>
<meta http-equiv="Content-Type" content="text/html"; charset="utf8">
<title> 客户信息 </title>
</head>

<body>

<div align="center">

<?php
require "config.php";

error_reporting($level = null);

$flag = mysql_query("SET NAMES utf8");

$result = mysql_query("SELECT * FROM persion ");

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

echo "<br>";



echo "</br>";

mysql_close($con);
?>
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