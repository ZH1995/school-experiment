/**
 * Created by lemo on 17-4-12.
 */
angular.module('collectionList-controller',[])
.controller('CollectionListCtrl', ['$scope', '$stateParams', '$timeout','CollectionListService', function($scope, $stateParams, $timeout, CollectionListService){

  $scope.userInfo = JSON.parse(sessionStorage.getItem("user"));
  // 初始化变量
  $scope.isHaveMoreData = true;
  $scope.collectionList = [];
	$scope.pagination = {
		pageSize: 7,
		currentPage: 0
	};

	// 加载更多
	$scope.loadMore = function() {

    var collectAction = 2;
		CollectionListService.getCollectionList($scope.userInfo.uid, collectAction, $scope.pagination.pageSize,
                                            $scope.pagination.currentPage++)
		.success(function(obj){
			if (obj.errno != 0 || obj.data.list.length == 0) {
        $scope.isHaveMoreData = false;
        return;
      }
			$scope.collectionList = $scope.collectionList.concat(obj.data.list);
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
		$scope.collectionList = [];
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
