/**
 * Created by lemo on 17-4-12.
 */
angular.module('collectionList-service', [])
.factory('CollectionListService', function($http){
	return {
		getCollectionList: function(uid, userAction, pageSize, currentPage) {
			var requestData = {
			  "uid": uid,
        "userAction": userAction,
        "pageSize": pageSize,
        "currentPage": currentPage
      };
			return $http({
				method: "POST",
				url: "http://localhost:10101/action/list",
				data: JSON.stringify(requestData),
				headers: {"Content-Type": "application/x-www-form-urlencoded"}
			});
		}
	}
});
