<?php

require_once "dao_base.php";


class SeatTemps extends DAOBase
{
	public $index = null;
	public $seatid = null;
	public $temp = null;
	public $date = null;

	public function __construct()
	{
		$this->_table_name = SeatTemps::TableName();
	}

	public static function TableName()
	{
		return "SeatTemps";
	}

	public function insert()
	{
		return $this->insertRecord("seattemps_index, seattemps_seatid, seattemps_temp, seattemps_date",
			"'', '$this->seatid', '$this->temp', cast('$this->date' as date)");
	}

	public static function FindAll()
	{
		$res = DAOBase::executeQuery(SeatTemps::TableName(), "*", false);
		return SeatTemps::SeatsFromResource($res);
	}

	public static function FindBySeatsID($seats_id)
	{
		$res = DAOBase::executeQuery(SeatTemps::TableName(), "*", false, "seattemps_seatid = '${seats_id}'");
		return SeatTemps::SeatsFromResource($res);
	}

	public static function SeatsFromResource($res)
	{
		$results = array();
		while ($row = mysql_fetch_object($res))
		{
			$seattemps = new SeatTemps();
			$seattemps->index = $row->seattemps_index;
			$seattemps->seatid = $row->seattemps_seatid;
			$seattemps->temp = $row->seattemps_temp;
			$seattemps->date = $row->seattemps_date;

			$results[] = $seattemps;
		}
		return $results;
	}
}

?>