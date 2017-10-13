<!DOCTYPE HTML>
<div align="center">
<?php
require "config.php";


error_reporting($level = null);


$userName = $_POST[user_name];
$userTel = $_POST[user_tel];
$p1_num = $_POST[pro1_nu];
$p1_pri = $_POST[pro1_pr];
$p2_num = $_POST[pro2_nu];
$p2_pri = $_POST[pro2_pr];

$flag = mysql_query("SET NAMES utf8");

$sql = "INSERT INTO $table_persion_name(p_name,p_tel,p_p1,p_p1_pri,p_p2,p_p2_pri) values ('$userName','$userTel',$p1_num,$p1_pri,$p2_num,$p2_pri)";

$flag = mysql_query($sql,$my_conn);

if(!$flag){
		die('Error:' . mysql_error());
	}
	
	echo "添加一条记录";

echo "<br>";
	
$flag = mysql_query("SET NAMES utf8");

$result = mysql_query("SELECT * FROM persion ");

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
  echo "<td>" . $row[1] . "</td>";
  echo "</tr>";
  }
echo "</table>";

echo "<br>";
echo "</br>";

mysql_close($con);

?>

</div>

<div align="center">
<a href="index.php" >返回首页</a>

</div>
