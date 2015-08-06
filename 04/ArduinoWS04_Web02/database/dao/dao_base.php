<?php

require_once "database.php";


/*------------------------------------------------------------------------------
 * データベースアクセスオブジェクト（Abstract class）
------------------------------------------------------------------------------*/
class DAOBase
{
	protected $_table_name;						// テーブル名


	/*------------------------------------------------------------------------------
	 * コンストラクタ
	------------------------------------------------------------------------------*/
	public function __construct()
	{
		$this->_table_name = "";
	}
	
	
	/*------------------------------------------------------------------------------
	 * 検索クエリを実行する
	 * @param 検索するカラム名
	 * @param 重複を許す？（true：許さない、false：許す）
	 * @param 検索条件
	 * @return 検索結果の配列
	------------------------------------------------------------------------------*/
	public static function executeQuery($table_name, $column_name, $is_distinct, $condition = "")
	{
		$db = DB::GetInstance();
		$query = "";
		
		
		if ($is_distinct)					// 重複を許さない
		{
			$query = "SELECT DISTINCT ".$column_name." FROM ".$table_name;
		}
		else								// 重複を許す
		{
			$query = "SELECT ".$column_name." FROM ".$table_name;
		}
		
		
		if (!($condition === ""))			// 検索条件の追加
		{
			$query .= " WHERE ".$condition;
		}
		// echo $query."<br>";
		
		$res = $db->executeQuery($query);
		$db->checkError();
		return $res;
	}
	
	/*------------------------------------------------------------------------------
	 * レコードを更新するクエリを実行する
	------------------------------------------------------------------------------*/
	protected function updateQuery($column_name, $new_value, $condition = "")
	{
		$db = DB::GetInstance();
		$query = "UPDATE ".$this->_table_name." SET ".$column_name." = '".$new_value."'";
	
		if (!($condition === ""))			// 検索条件の追加
		{
			$query .= " WHERE ".$condition;
		}
		// echo $query."<br>";
	
		// クエリ実行
		$db->executeQuery($query);
		$db->checkError();
	}
	

	/*------------------------------------------------------------------------------
	 * レコードを挿入する
	------------------------------------------------------------------------------*/
	protected function insertRecord($column_name, $value)
	{
		$db = DB::GetInstance();
		$query = "INSERT INTO ".$this->_table_name." (".$column_name.") VALUES (".$value.")";
		// echo $query."<br>";
		
		// クエリ実行
		$res = $db->executeQuery($query);
		$db->checkError();

		return $res;
	}
	
	
	/*------------------------------------------------------------------------------
	 * レコードを削除する
	------------------------------------------------------------------------------*/
	protected function deleteRecord($condition = "")
	{
		$db = DB::GetInstance();
		$query = "DELETE FROM ".$this->_table_name;
		
		if (!($condition === ""))
		{
			$query .= " WHERE ".$condition;
		}
		
		$db->executeQuery($query);
		$db->checkError();
	}
	
	
	/*------------------------------------------------------------------------------
	 * テーブル名を返す
	 * @return テーブル名
	------------------------------------------------------------------------------*/
	public function getTableName()
	{
		return $this->_table_name;
	}
}

?>