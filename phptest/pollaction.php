<!-- 20110527 ysoftman -->
<meta http-equiv="Content-Type" content="text/html; charset=UTF-8">

<?php
// 20110527 ysoftman
// mysql로 데이터 관리하기
echo "-----------------------------------------------------------------<br>";

// php?command=poll&&name=aaa&&ip=10.10.10.10 와 같이 넘어 올때 인자 파싱
$param_command = $_GET[command];
$param_name = $_GET[name];
$param_ip = $_GET[ip];
//echo "command = $param_command<br>";
//echo "name = $param_name<br>";
//echo "ip = $param_ip<br>";

// mysql 접속에 필요한 정보
$dbhost = "localhost";
$dbuser = "root";
$dbpassword = "qwer1234";
$dbdatabase = "test";
$dbtable = "tbpoll";


// @ 를 mysql 함수 앞에 붙이면 에러발생시 에러 메시지를 출력하지 않는다.
// db 접속
$dbconnect=mysql_connect($dbhost, $dbuser, $dbpassword);
if ($dbconnect == false)
{
	echo "error mysql_connect()<br>";
}
// database 선택
if (mysql_select_db($dbdatabase, $dbconnect) == false)
{
	echo "error mysql_select_db()<br>";
}

// mysql에서 db 스키마 생성하기
// mysql> show databases;
// mysql> use test;
// mysql> drop table tbpoll;
// mysql> create table tbpoll(name varchar(20), cnt int, ip varchar(1024));
// mysql> show tables;
// mysql> desc tbpoll;

// 테스트 예시
// 데이터 입력
//$query = "insert into $dbtable (name, cnt, ip) values ('aaa', 1, '1.1.1.1')";
// 데이터 삭제
//$query = "delete from $dbtable where name = 'aaa' and cnt = 1";
// 데이터 변경
//$query = "update $dbtable set cnt = 0 where name = 'aaa'";
// 데이터 검색
//$query = "select * from $dbtable";
//mysql_query($query, $dbconnect);


// 모든 데이터 검색해서 보여주기
if ($param_command == "select_all")
{
	echo "$param_command<br>";
	$query = "select * from $dbtable order by name";
	$result = mysql_query($query, $dbconnect);
	if ($result == false)
	{
		echo "error mysql_query()<br>";
	}
	// <pre> 태그에 탭(&#9) 을 사용할 수 있다.
	echo "<pre>name &#9 &#9 cnt &#9 &#9 ip<br></pre>";
	while ($row = mysql_fetch_array($result))
	{
		echo "<pre>$row[0] &#9 &#9 $row[1] &#9 &#9 $row[2]<br>";
	}
	if ($result == false)
	{
		echo "error mysql_query()<br>";
	}
}

// 모든 데이터 리셋하기
else if ($param_command == "reset_all")
{
	echo "$param_command<br>";
	$query = "delete from $dbtable";
	$result = mysql_query($query, $dbconnect);
	if ($result == false)
	{
		echo "error mysql_query()<br>";
	}
}

// 선택한 항목의 카운트 증가시키기
else if ($param_command == "poll")
{
	echo "$param_command $param_name<br>";
	$query = "select cnt, ip from $dbtable where name = '$param_name'";
	$result = mysql_query($query, $dbconnect);
	if ($result == false)
	{
		echo "error mysql_query()<br>";
	}
	else
	{
		$row = mysql_fetch_array($result, MYSQL_NUM);
		//echo "result = $row[0]<br>";
		// 만약 cnt 가 null 이면 name 이 없음으로 name 을 추가한다.
		if ($row[0] == NULL)
		{
			$cnt = 1;
			$query = "insert into $dbtable (name, cnt, ip) values ('$param_name',null,null)";
			mysql_query($query, $dbconnect);
			$ip = $param_ip;
		}
		else
		{
			// 기존에 있는 항목이라면 cnt 와 ip 만 변경
			$cnt = $row[0]+1;
			// 문자열 합치기는 . 연사자 이용
			// ip 를 추가 해준다.
			$ip = $row[1]." ".$param_ip;
		}
		echo "count $cnt<br>";
		echo "ip $ip<br>";
		// cnt, ip 저장
		$query = "update $dbtable set cnt = $cnt , ip = '$ip' where name = '$param_name'";
		mysql_query($query, $dbconnect);
	}
}
// mysql 닫기
if (mysql_close($dbconnect) == false)
{
	echo "error mysql_close()<br>";
}
?>

