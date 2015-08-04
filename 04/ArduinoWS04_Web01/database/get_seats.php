<?php

require_once "./dao/seats.php";

$seats = Seats::FindAll();
echo json_encode($seats);

?>