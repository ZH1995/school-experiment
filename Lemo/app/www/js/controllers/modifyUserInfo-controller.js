/**
 * Created by lemo on 17-4-17.
 */
angular.module('modifyUserInfo-controller',[])
.controller('ModifyUserInfoCtrl', ['$scope', '$ionicPopup', '$timeout', '$state', '$ionicHistory', 'ModifyUserInfoService', function($scope, $ionicPopup, $timeout, $state, $ionicHistory, ModifyUserInfoService){
  $scope.userInfo = JSON.parse(sessionStorage.getItem("user"));
  $scope.formUser = {
      "userName": $scope.userInfo["uname"],
      "userSign": $scope.userInfo["userSign"],
      "choice": "0"
  };

  $scope.doSubmit = function(){
	    var headImg = "";
	    if ($scope.formUser.choice === 1) {
	        headImg = $scope.userInfo.headImg;
        }

        ModifyUserInfoService.modifyUserInfo($scope.userInfo.uid, $scope.formUser.userName, $scope.formUser.userSign, headImg).success(function (obj) {
            if (obj.errno != 0) {
                $scope.showErrorMesPopup("修改信息失败");
                return -1;
            }
            sessionStorage.removeItem("user");
            $scope.userInfo = obj.data;
            sessionStorage.setItem("user", JSON.stringify(obj.data));
            $scope.showSuccessMesPopup("修改信息成功");
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
            $state.go("login");
        }, 2000);
    };
}]);
