<?php
/**
 * Created by PhpStorm.
 * User: lemo
 * Date: 17-5-4
 * Time: 上午10:31
 */
class HomeController extends Yaf_Controller_Abstract {

    /**
     * 默认动作
     * Yaf支持直接把Yaf_Request_Abstract::getParam()得到的同名参数作为Action的形参
     * 对于如下的例子, 当访问http://localhost/lemo-admin/index.php/index/home/home 的时候, 你就会发现不同
     */
    public function homeAction() {
        $this->getView()->display("home/home.phtml");
        return FALSE;
    }
}