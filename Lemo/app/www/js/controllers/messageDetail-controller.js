/**
 * Created by zh1995 on 17-4-12.
 */
angular.module('messageDetail-controller',[])
.controller('MessageDetailCtrl', ['$scope', '$stateParams', 'MessageDetailService', function($scope, $stateParams, MessageDetailService){

  $scope.hasGood = false;
  $scope.thumbsUpColor = "";
  $scope.hasCollect = false;
  $scope.collectIcon = "";
  $scope.messageId = $stateParams.messageId;
  $scope.userInfo = JSON.parse(sessionStorage.getItem("user"));

  MessageDetailService.getMessageDetail($scope.userInfo.uid, $stateParams.messageId)
    .success(function (obj) {
      $scope.messageDetail = obj.data;
      $scope.hasGood = obj.data.hasGood;
      $scope.hasCollect = obj.data.hasCollect;
      if ($scope.hasGood === false) {
        $scope.thumbsUpColor = "badge-stable";
      } else {
        $scope.thumbsUpColor = "badge-assertive";
      }
      if ($scope.hasCollect === false) {
        $scope.collectIcon = "ion-android-star-outline";
      } else {
        $scope.collectIcon = "ion-android-star";
      }

    }).error(function (obj) {
      alert("Network error " + obj);
  });

  // 处理点赞
  $scope.thumbsUp = function () {
    if ($scope.hasGood === true) {
      $scope.messageDetail["goodNum"] --;
      $scope.thumbsUpColor = "badge-stable";
      $scope.hasGood = false;
    } else {
      $scope.messageDetail["goodNum"] ++;
      $scope.thumbsUpColor = "badge-assertive";
      $scope.hasGood = true;
    }

    var goodAction = 1;
    MessageDetailService.dealUserMessageAction($scope.userInfo.uid, $scope.messageId, $scope.hasGood, goodAction)
      .error(function (obj) {
        alert("Network error " + obj);
    });
  };

  // 处理收藏
  $scope.collectMessage = function () {
    if ($scope.hasCollect === true) {
      $scope.hasCollect = false;
      $scope.collectIcon = "ion-android-star-outline";
    } else {
      $scope.hasCollect = true;
      $scope.collectIcon = "ion-android-star";
    }

    var collectAction = 2;
    MessageDetailService.dealUserMessageAction($scope.userInfo.uid, $scope.messageId, $scope.hasCollect, collectAction)
      .error(function (obj) {
        alert("Network error " + obj);
      })
  }

}]);
