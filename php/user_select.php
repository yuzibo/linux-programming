<!DOCTYPE html>
<html>
<head>
<meta http-equiv="Content-Type" content="text/html"; charset="utf8">
<title> 查看客户 </title>
</head>

<body>
<div align="center">
<?php


require "config.php";

error_reporting($level = null);

$flag = mysql_query("SET NAMES utf8");

$client_name = $_POST[user_name];

$result = mysql_query("SELECT * FROM persion where p_name='$client_name'");

if(!$result){
		die('Error:' . mysql_error());
	}
	
echo "<table border='1'>
<tr>
<th>姓名</th>
<th>产品1数量</th>
<th>产品1单价</th>
<th>产品2数量</th>
<th>产品2单价</th>
<th>电话</th>

</tr>";

while($row = mysql_fetch_row($result))
  {
  echo "<tr>";
  echo "<td>" . $row[0] . "</td>";
  echo "<td>" . $row[2] . "</td>";
  echo "<td>" . $row[3] . "</td>";
  echo "<td>" . $row[4] . "</td>";
  echo "<td>" . $row[5] . "</td>";
  echo "<td>" . $row[1] . "</td>";
  echo "</tr>";
  }
echo "</table>";

mysql_close($con);

?>
<a href="user_update.php"><h3>修改客户信息</h3></a>
</div>
</body>
</html>