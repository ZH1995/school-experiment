/**
 * Created by lemo on 17-4-12.
 */
angular.module('messageList-controller',[])
.controller('MessageListCtrl', ['$scope', '$stateParams', '$timeout', 'MessageListService', function($scope, $stateParams, $timeout, MessageListService){

  $scope.userInfo = JSON.parse(sessionStorage.getItem("user"));

  // 设置页面标题和tagId值
  if ($stateParams.listTitle == null) {
    $scope.listTitle = "热点新闻";
    $scope.tagId = 1001;
  } else {
    $scope.listTitle = $stateParams.listTitle;
    $scope.tagId = $stateParams.tagId;
  }

  // 初始化变量
  $scope.isHaveMoreData = true;
  $scope.messageList = [];
	$scope.pagination = {
		pageSize: 7,
		currentPage: 0
	};

	// 加载更多
	$scope.loadMore = function() {
		MessageListService.getMessageList($scope.userInfo.uid, $scope.tagId,
                                      $scope.pagination.pageSize, $scope.pagination.currentPage++)
		.success(function(obj){
			if (obj.errno != 0 || obj.data.list.length == 0) {
        $scope.isHaveMoreData = false;
        return;
      }
			$scope.messageList = $scope.messageList.concat(obj.data.list);
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
		$scope.messageList = [];
		$scope.pagination = {
			pageSize: 7,
			currentPage: 0
		};
		$scope.loadMore();
  };

	$scope.$on("stateChangeSuccess", function(){
		$scope.loadMore();
	});

}]);
