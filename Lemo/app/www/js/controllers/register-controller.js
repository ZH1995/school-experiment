/**
 * Created by lemo on 17-4-17.
 */
angular.module('register-controller',[])
.controller('RegisterCtrl',['$scope','$ionicPopup', '$timeout', '$state', '$ionicHistory', 'RegisterService', function($scope, $ionicPopup, $timeout, $state, $ionicHistory, RegisterService) {
    $scope.formUser = {};

    $scope.goBack = function () {
      $ionicHistory.goBack();
    };
    $scope.doRegister = function(){

        if ($scope.formUser.password != $scope.formUser.rePassword) {
            $scope.showErrorMesPopup("密码不一致，请重新输入");
            return ;
        }
        RegisterService.register($scope.formUser.username, $scope.formUser.phoneNumber, $scope.formUser.password)
          .success(function(obj){
            if(obj.errno == 0){
                sessionStorage.setItem("user", JSON.stringify(obj.data));
                $scope.showSuccessMesPopup("注册成功");
                $timeout(function() {
                    // TODO: 打算把用户ID存入Session
                    $state.go("app.messageList",{listTitle: '热点新闻', tagId:1001});
                }, 2000);
            }else{
                $scope.showErrorMesPopup("账号失败,请重新注册！");
            }
        });
    };


    $scope.showErrorMesPopup = function(title) {
        var myPopup = $ionicPopup.show({
            title: '<b>'+title+'</b>'
        });
        $timeout(function() {
            myPopup.close(); // 2秒后关闭
        }, 1000);
    };


    //  验证成功后提示框
    $scope.showSuccessMesPopup = function(title) {
        var myPopup = $ionicPopup.show({
            title: '<b>'+title+'</b>',
            template: '<p style="text-align: center"><ion-spinner icon="android"></ion-spinner></p>'
        });
        $timeout(function() {
            myPopup.close(); // 2秒后关闭
        }, 2000);
    };
}]);
