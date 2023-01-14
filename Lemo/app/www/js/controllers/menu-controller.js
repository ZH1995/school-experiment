/**
 * Created by lemo on 17-4-12.
 */
angular.module('menu-controller',[])
.controller('MenuCtrl', ['$scope', '$ionicPopup', '$state', function($scope, $ionicPopup, $state){
  $scope.userInfo = JSON.parse(sessionStorage.getItem("user"));
  // 确认弹出框
  $scope.showConfirm = function() {
      $ionicPopup.confirm({
          title: "确认退出当前登录？",
          okText:"确认",
          cancelText:"取消"
      })
      .then(function(res) {
          if(res) {
              $state.go('login');
          } else {
             return false;
          }
      });
  };
}]);
