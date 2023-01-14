<?php
/**
 * Created by PhpStorm.
 * User: lemo
 * Date: 17-5-4
 * Time: 下午3:42
 */
class MessageController extends Yaf_Controller_Abstract {

    /**
     * 默认动作
     * Yaf支持直接把Yaf_Request_Abstract::getParam()得到的同名参数作为Action的形参
     */
    public function addMessageAction() {
        $session = Yaf_Session::getinstance();
        $this->getView()->assign("userInfo", $session->userInfo);
        $this->getView()->display("message/addMessage.phtml");
        return FALSE;
    }

    public function updateMessageAction() {
        # 获取表单数据
        $messageId = $this->getRequest()->getPost("messageId");

        # 获取缓存用户信息
        $session = Yaf_Session::getinstance();
        $this->getView()->assign("userInfo", $session->userInfo);

        # 查数据库
        $messageModel = new MessageModel();
        $messageInfo = $messageModel->getMessageInfoById($messageId);
        if (empty($messageInfo)) {
            $this->getView()->assign("msg", "文章不存在");
            $this->getView()->display("error/error.phtml");
        } else {
            $this->getView()->assign("messageId", $messageId);
            $this->getView()->assign("messageInfo", $messageInfo);
            $this->getView()->display("message/updateMessage.phtml");
        }
        return FALSE;
    }

    public function selectMessageAction() {
        $session = Yaf_Session::getinstance();
        $this->getView()->assign("userInfo", $session->userInfo);
        $this->getView()->display("message/selectMessage.phtml");
        return FALSE;
    }

    public function menuAction() {
        $session = Yaf_Session::getinstance();
        $this->getView()->assign("userInfo", $session->userInfo);
        $this->getView()->display("menu/menu.phtml");
        return FALSE;
    }

    public function submitAddMessageAction() {
        # 获取表单
        $messageTitle = $this->getRequest()->getPost("messageTitle");
        $coverPic = $this->getRequest()->getPost("coverPic");
        $authorName = $this->getRequest()->getPost("authorName");
        $authorImg = $this->getRequest()->getPost("authorImg");
        $tagId = $this->getRequest()->getPost("tagId");
        $messageContent = $this->getRequest()->getPost("messageContent");

        # 获取用户信息缓存
        $session = Yaf_Session::getinstance();
        $this->getView()->assign("userInfo", $session->userInfo);

        # 添加入库
        $messageModel = new MessageModel();
        $res = $messageModel->addMessage($messageTitle, $coverPic, $authorName, $authorImg, $tagId, $messageContent);
        if (empty($res)) {
            $this->getView()->assign("msg", "添加文章失败，请联系57743532@qq.com");
            $this->getView()->display("error/error.phtml");
        } else {
            $this->getView()->display("menu/menu.phtml");
        }
        return FALSE;
    }

    public function submitUpdateMessageAction() {
        # 获取表单数据
        $messageTitle = $this->getRequest()->getPost("messageTitle");
        $coverPic = $this->getRequest()->getPost("coverPic");
        $authorName = $this->getRequest()->getPost("authorName");
        $authorImg = $this->getRequest()->getPost("authorImg");
        $tagId = $this->getRequest()->getPost("tagId");
        $weight = $this->getRequest()->getPost("weight");
        $messageContent = $this->getRequest()->getPost("messageContent");

        # 获取参数
        $param = $this->getRequest()->getParams();
        $messageId = $param["messageId"];

        # 获取用户信息缓存
        $session = Yaf_Session::getinstance();
        $this->getView()->assign("userInfo", $session->userInfo);

        # 更新数据库
        $messageModel = new MessageModel();
        $res = $messageModel->updateMessage($messageTitle, $coverPic, $authorName, $authorImg, $tagId, $messageContent, $weight, $messageId);
        if (empty($res)) {
            $this->getView()->assign("msg", "更新文章失败，请联系57743532@qq.com");
            $this->getView()->display("error/error.phtml");
        } else {
            $this->getView()->display("menu/menu.phtml");
        }
        return FALSE;
    }

}