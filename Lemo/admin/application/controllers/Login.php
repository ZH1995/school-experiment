<?php
/**
 * Created by PhpStorm.
 * User: lemo
 * Date: 17-5-4
 * Time: 下午12:23
 */
class LoginController extends Yaf_Controller_Abstract {

    /**
     * 默认动作
     * Yaf支持直接把Yaf_Request_Abstract::getParam()得到的同名参数作为Action的形参
     */
    public function loginAction() {

        $phoneNumber = $this->getRequest()->getPost("phoneNumber");
        $password = $this->getRequest()->getPost("password");

        # 校验参数是否合法
        if (!preg_match("/^\d*$/", $phoneNumber) || strlen($phoneNumber) != 11) {
            $this->getView()->assign("msg", "手机号输入错误");
            $this->getView()->display("error/error.phtml");
            return False;
        }
        if (!preg_match("/^\w*$/", $password) || strlen($password) < 6 || strlen($password) > 12) {
            $this->getView()->assign("msg", "密码输入错误");
            $this->getView()->display("error/error.phtml");
            return False;
        }

        $loginModel = new LoginModel();
        $userInfo = $loginModel->getUserInfoByPhoneAndPwd($phoneNumber, $password);

        # 验权
        if (empty($userInfo["uid"])) {
            $this->getView()->assign("msg", "用户不存在");
            $this->getView()->display("error/error.phtml");
            return False;
        }
        if ($userInfo["level"] == 0) {
            $this->getView()->assign("msg", "权限不够，请联系57435302@qq.com开通权限");
            $this->getView()->display("error/error.phtml");
            return False;
        }

        # 缓存用户信息
        $session = Yaf_Session::getinstance();
        $session->userInfo = $userInfo;
        $this->getView()->assign("userInfo", $userInfo);
        $this->getView()->display("menu/menu.phtml");
        return FALSE;
    }
}