<?php

require_once "./dao/seats.php";

$seat_id = $_GET['seat_id'];
$on = $_GET['on'];

if (is_null($seat_id) || is_null($on))
{
	echo "1";
	return;
}

if (!($on == 0 || $on == 1))
{
	echo "1";
	return;
}

$db = DB::GetInstance();

// トランザクションスタート（注意：トランザクションはInnoDBのみ動作する）
if (!$db->startTransaction())
{
	// echo "ERROR: Failed to start transaction.\n";
	echo "1";
	return;
}


$seats = new Seats();
$seats->index = $seat_id;
$seats->on = $on;
$seats->update();

$db->commit();
$db->endTransaction();

echo "0";

?>