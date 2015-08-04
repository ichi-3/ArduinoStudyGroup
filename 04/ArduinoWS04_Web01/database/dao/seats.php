<?php

require_once "dao_base.php";


class Seats extends DAOBase
{
	public $index = null;
	public $on = 0;

	public function __construct()
	{
		$this->_table_name = Seats::TableName();
	}

	public static function TableName()
	{
		return "Seats";
	}

	public static function FindAll()
	{
		$res = DAOBase::executeQuery(Seats::TableName(), "*", false);
		return Seats::SeatsFromResource($res);
	}

	public static function FindBySeatsID($seats_id)
	{
		$res = DAOBase::executeQuery(Seats::TableName(), "*", false, "seats_index = '${seats_id}'");
		return Seats::SeatsFromResource($res);
	}

	public function update()
	{
		DAOBase::updateQuery("seats_on", $this->on, "seats_index = '".$this->index."'");
	}

	public static function SeatsFromResource($res)
	{
		$results = array();
		while ($row = mysql_fetch_object($res))
		{
			$seats = new Seats();
			$seats->index = $row->seats_index;
			$seats->on = $row->seats_on;

			$results[] = $seats;
		}
		return $results;
	}
}

?>