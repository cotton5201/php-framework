<?php
/*
>>>>mysql 5.x
-- 데이터베이스 생성 (root 계정으로 실행)
create database 디비명 default character set utf8 collate utf8_general_ci;

-- 접속계정 생성 (root 계정으로 실행)
grant all privileges on 디비명.* to '유저명'@'127.0.0.1' identified by '';

flush privileges;



>>>>mysql 8.0
CREATE USER '유저명'@'127.0.0.1' IDENTIFIED BY '';
GRANT ALL ON 디비명.* TO '유저명'@'127.0.0.1';

flush privileges;


>>> 회원 비밀번호 디코딩 방법
SELECT hex(aes_encrypt('', md5(''))) AS COL
UNION ALL
SELECT aes_decrypt(unhex(''), md5('')) AS COL
;
*/


@header("P3P: CP='ALL CURa ADMa DEVa TAIa OUR BUS IND PHY ONL UNI PUR FIN COM NAV INT DEM CNT STA POL HEA PRE LOC OTC'");

## MySQL DB Connection Info
$dbhost = "";	// 호스트명
$dbname = "";	// 디비명
$dbuser = "";	// 유저명
$dbpass = "";	// 유저패스워드

$dsn = "mysql:host=$dbhost;dbname=$dbname;charset=utf8";
$connect = new PDO($dsn, $dbuser, $dbpass);
$connect -> setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);
?>
