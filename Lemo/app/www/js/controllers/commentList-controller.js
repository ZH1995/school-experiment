/**
 * Created by lemo on 17-4-12.
 */
angular.module('commentList-controller',[])
.controller('CommentListCtrl', ['$scope', '$stateParams', '$timeout', 'CommentListService', function($scope, $stateParams, $timeout, CommentListService){

  $scope.userInfo = JSON.parse(sessionStorage.getItem("user"));
  $scope.messageId = $stateParams.messageId;

  // 初始化变量
  $scope.isHaveMoreData = true;
  $scope.commentList = [];
	$scope.pagination = {
		pageSize: 7,
		currentPage: 0
	};

	// 加载更多
	$scope.loadMore = function() {

		CommentListService.getCommentList($scope.userInfo.uid, $scope.messageId,
                                      $scope.pagination.pageSize, $scope.pagination.currentPage++)
		.success(function(obj){
			if (obj.errno != 0 || obj.data.list.length == 0) {
        $scope.isHaveMoreData = false;
        return;
      }
			$scope.commentList = $scope.commentList.concat(obj.data.list);
		})
		.finally(function(){
			$timeout(function(){
				$scope.$broadcast("scroll.infiniteScrollComplete");
				$scope.$broadcast('scroll.refreshComplete');
			}, 2000);
		});
	};

	// 下拉刷新
	$scope.doRefresh = function () {
		$scope.commentList = [];
		$scope.pagination = {
			pageSize: 7,
			currentPage: 0
		};
		$scope.loadMore();
  };

	$scope.$on("stateChangeSuccess", function(){
	  console.log("state change");
		$scope.loadMore();
	});


}]);
