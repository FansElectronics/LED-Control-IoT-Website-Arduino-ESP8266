<?php
include 'koneksi.php';
$id = $_GET['id'];
$nilai = mysqli_query($mysqli, "SELECT nilai FROM led WHERE id='$id'");
if($val = mysqli_fetch_array($nilai)){
	echo "#";
	echo $val['nilai'];
	echo "#@";
}
?>