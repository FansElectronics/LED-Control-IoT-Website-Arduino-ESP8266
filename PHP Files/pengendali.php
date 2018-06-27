<?php
include 'koneksi.php';
$id = $_GET['id'];
$nilai = $_GET['nilai'];
mysqli_query($mysqli, "UPDATE led SET nilai='$nilai' WHERE id='$id'");
header("location:index.php");
// www.fanselectronics.com/pengendali.php?id=1&nilai=0
// http://localhost/tutorial-iot/pengedali.php?id=1&nilai=1
?>
