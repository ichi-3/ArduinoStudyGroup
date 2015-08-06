<?php

require_once "./dao/seattemps.php";

$seat_id = $_GET['seat_id'];
$temp = $_GET['temp'];

if (is_null($seat_id) || is_null($temp))
{
	echo "1";
	return;
}

// $db = DB::GetInstance();

// トランザクションスタート（注意：トランザクションはInnoDBのみ動作する）
// if (!$db->startTransaction())
// {
// 	// echo "ERROR: Failed to start transaction.\n";
// 	echo "1";
// 	return;
// }

date_default_timezone_set('Asia/Tokyo');

$seattemps = new SeatTemps();
$seattemps->seatid = $seat_id;
$seattemps->temp = $temp;
$seattemps->date = date("Y-m-d");
if (!$seattemps->insert())
{
	// $db->rollback();
	// $db->endTransaction();

	echo "1";
	return;
}

// $db->commit();
// $db->endTransaction();

echo "0";


?>