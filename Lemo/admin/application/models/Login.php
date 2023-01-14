<?php
/**
 * Created by PhpStorm.
 * User: lemo
 * Date: 17-5-4
 * Time: 下午3:08
 */
class LoginModel{

    private $_dbms = "mysql";
    private $_host = "localhost";
    private $_dbName = "lemo";
    private $_user = "root";
    private $_password = "123456";
    private $_pdo;

    public function __construct() {
        $dsn = "$this->_dbms:host=$this->_host;dbname=$this->_dbName";
        try{
            $this->_pdo = new PDO($dsn, $this->_user, $this->_password);
        } catch (PDOException $e) {
            die("pdo fail");
        }
    }

    public function querySql($sql) {
        $this->_pdo->query('set names utf8;');
        $res = $this->_pdo->query($sql);
        $result = array();
        foreach ($res as $row) {
            $result[] = $row;
        }
        return $result;
    }

    public function getUserInfoByPhoneAndPwd($phoneNumber, $password) {
        $sql = "select uname, uid, level from tblUser where phone_number=$phoneNumber and password=$password";
        $res = $this->querySql($sql);
        return array(
            "userName" => $res[0]["uname"],
            "uid" => $res[0]["uid"],
            "level" => $res[0]["level"],
        );
    }
}