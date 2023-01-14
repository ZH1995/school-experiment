/**
 * Created by lemo on 17-4-12.
 */
angular.module('writeComment-controller',[])
.controller('WriteCommentCtrl', ['$scope', '$ionicPopup', '$timeout', '$ionicHistory', '$stateParams', 'WriteCommentService', function($scope, $ionicPopup, $timeout, $ionicHistory, $stateParams, WriteCommentService){

  $scope.userInfo = JSON.parse(sessionStorage.getItem("user"));
  $scope.replyUid = $stateParams.replyUid;
  $scope.messageId = $stateParams.messageId;
  if ($scope.replyUid === 0 || $stateParams.replyName === "空") {
    $scope.writeTitle = "写评论";
  } else {
    $scope.writeTitle = "回复" + $stateParams.replyName;
  }
  
  $scope.commentContent = "";
  $scope.doPublic = function () {

    WriteCommentService.publicMessageComment($scope.userInfo.uid, $scope.replyUid, $scope.messageId, $scope.commentContent)
      .success(function (obj) {
        $scope.showSuccessMesPopup("评论发布成功");
      }) .error(function (obj) {
        $scope.showErrorMesPopup("评论发布失败");
    });
  };

  $scope.showSuccessMesPopup = function(title) {
      var myPopup = $ionicPopup.show({
          title: '<b>'+title+'</b>',
          template: '<p style="text-align: center"><ion-spinner icon="android" class="spinner-positive"></ion-spinner></p>'
      });
      $timeout(function() {
          myPopup.close(); // 2秒后关闭
          $ionicHistory.goBack();
      }, 2000);
  };

  $scope.showErrorMesPopup = function(title) {
      var myPopup = $ionicPopup.show({
          title: '<b>'+title+'</b>'
      });
      $timeout(function() {
          myPopup.close(); // 2秒后关闭
      }, 2000);
  };

}]);
