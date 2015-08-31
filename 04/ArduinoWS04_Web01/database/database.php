<?php

/*------------------------------------------------------------------------------
 * データベース管理クラス（Singleton）
------------------------------------------------------------------------------*/
class DB
{
	private static $_instance = null;
	
	private $_db;
	private $_is_init_db;

	private $_database_address   = "localhost:8889";			// データベースアドレス
	private $_database_name      = "arduino_ws0401";			// データベース名
	private $_database_user_name = "root";						// データベースユーザ名
	private $_database_password  = "root";						// データベースパスワード

	/*----------------------------------------------------------------------
	 * コンストラクタ
	----------------------------------------------------------------------*/
	private function __construct()
	{
		$this->setupDB();
	}

	/*------------------------------------------------------------------------------
	 * DBセットアップ
	------------------------------------------------------------------------------*/
	public function setupDB()
	{
		if (!$this->_is_init_db)
		{
			// MySQLに接続する
			$this->_db = mysql_connect($this->_database_address, $this->_database_user_name, $this->_database_password);		
			
			// データベースを選択する
			mysql_select_db($this->_database_name, $this->_db);
			$this->checkError();
			
			$this->executeQuery("SET NAMES UTF8");

			$this->_is_init_db = true;
		}
	}

	/*------------------------------------------------------------------------------
	 * トランザクション開始
	 * 注意：トランザクションは、InnoDBのみ動作する
	------------------------------------------------------------------------------*/
	public function startTransaction()
	{
		$this->executeQuery("SET AUTOCOMMIT=0");
		return $this->executeQuery("BEGIN");
	}

	public function endTransaction()
	{
		return $this->executeQuery("SET AUTOCOMMIT = 1");
	}

	/*------------------------------------------------------------------------------
	 * ロールバックする
	------------------------------------------------------------------------------*/	
	public function rollback()
	{
		return $this->executeQuery("ROLLBACK");
	}

	/*------------------------------------------------------------------------------
	 * クエリを完了する
	------------------------------------------------------------------------------*/	
	public function commit()
	{
		return $this->executeQuery("COMMIT");
	}

	/*------------------------------------------------------------------------------
	 * MySQLエラーチェック
	------------------------------------------------------------------------------*/
	public function checkError()
	{
		$err_no = mysql_errno($this->_db);
		if ($err_no != 0)
		{
			echo "".mysql_errno($this->_db).": ".mysql_error($this->_db);
		}
	}
	
	/*------------------------------------------------------------------------------
	 * データベースを返す
	------------------------------------------------------------------------------*/
	public function database()
	{
		return $this->_db;
	}
	
	/*------------------------------------------------------------------------------
	 * クエリを実行する
	------------------------------------------------------------------------------*/
	public function executeQuery($query)
	{
		return mysql_query($query, $this->_db);
	}
	
	/*------------------------------------------------------------------------------
	 * テーブルを作成する
	 * @param 作成するテーブル名
	 * @param 列名とデータ型
	------------------------------------------------------------------------------*/
	public function createTable($table_name, $value_type)
	{
		$query = "create table ".$table_name."(".$value_type.")";
		//echo $query;
		$this->executeQuery($query);
		$this->checkError();
	}
	
	/*------------------------------------------------------------------------------
	 * 指定したテーブルが存在するかどうかを確認する
	 * @param 存在確認をしたいテーブルの名前
	------------------------------------------------------------------------------*/
	public function isExistTable($table_name)
	{
		return mysql_num_rows(mysql_query("show tables from ".$this->_database_name." like '".$table_name."'"));
	}
	
	/*------------------------------------------------------------------------------
	 * インスタンスを返す
	------------------------------------------------------------------------------*/
	public static function GetInstance()
	{
		if (is_null(self::$_instance))
		{
			self::$_instance = new self();
		}
		
		return self::$_instance;
	}
}

?>