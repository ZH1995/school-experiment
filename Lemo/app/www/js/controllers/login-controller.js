/**
 * Created by lemo on 17-4-17.
 */
angular.module('login-controller',[])
.controller('LoginCtrl', ['$scope', '$ionicPopup', '$timeout', '$state', 'LoginService', function($scope, $ionicPopup, $timeout, $state, LoginService){

	$scope.formUser = {};

	$scope.doLogin = function(){
        LoginService.login(this.formUser.phoneNumber, this.formUser.password).success(function (obj) {
            if (obj.errno != 0) {
                $scope.showErrorMesPopup("手机号或密码错误");
                return -1;
            }
            $scope.showSuccessMesPopup("正在登录请稍后");
            sessionStorage.setItem("user", JSON.stringify(obj.data));
        }).error(function (obj) {
            $scope.showErrorMesPopup("网络错误，请保持网络畅通");
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

    $scope.showSuccessMesPopup = function(title) {
        var myPopup = $ionicPopup.show({
            title: '<b>'+title+'</b>',
            template: '<p style="text-align: center"><ion-spinner icon="android" class="spinner-positive"></ion-spinner></p>'
        });
        $timeout(function() {
            myPopup.close(); // 2秒后关闭
            $state.go("app.messageList",{listTitle: '热点新闻', tagId:1001});
        }, 2000);
    };
}]);
