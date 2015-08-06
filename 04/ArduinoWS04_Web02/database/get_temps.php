<?php

require_once "./dao/seattemps.php";

$seat_id = $_GET['seat_id'];

if (is_null($seat_id))
{
	return;
}

$seattemps = SeatTemps::FindBySeatsID($seat_id);
echo json_encode($seattemps);

?>