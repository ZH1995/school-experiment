<?php
/**
 * Created by PhpStorm.
 * User: lemo
 * Date: 17-5-4
 * Time: 下午4:02
 */
class MessageModel {
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

    public function executeSql($sql) {
        $this->_pdo->query('set names utf8;');
        $res = $this->_pdo->exec($sql);
        if ($res > 0) {
           return true;
        }
        return false;
    }

    public function addMessage($messageTitle, $coverPic, $authorName, $authorImg, $tagId, $messageContent) {
        if (empty($this->filterContent($messageContent))) {
            return false;
        }
        $time = time();
        $sql = "insert into tblMessage (message_title, message_content, cover_pic, author_name, author_img, tag_id, create_time) VALUES ('$messageTitle', '$messageContent', '$coverPic', '$authorName', '$authorImg', $tagId, $time)";
        return $this->executeSql($sql);
    }

    public function filterContent($messageContent) {
        $content = strip_tags($messageContent);
        $wordList = array("操你妈", "王八蛋");
        $blacklist="/".implode("|",$wordList)."/i";
        if (preg_match($blacklist, $content, $matches)) {
            return false;
        }
        return true;
    }

    public function getMessageInfoById($messageId) {
        $sql = "select message_title, cover_pic, author_name, author_img, tag_id, weight, message_content from tblMessage where message_id=$messageId";
        $res = $this->querySql($sql);
        return $res[0];
    }

    public function updateMessage($messageTitle, $coverPic, $authorName, $authorImg, $tagId, $messageContent, $weight, $messageId) {
        if (empty($this->filterContent($messageContent))) {
            return false;
        }
        $time = time();
        $sql = "update tblMessage set message_title='$messageTitle', message_content='$messageContent', cover_pic='$coverPic', author_name='$authorName', author_img='$authorImg', tag_id=$tagId, create_time=$time, weight=$weight where message_id=$messageId";
        return $this->executeSql($sql);
    }
}