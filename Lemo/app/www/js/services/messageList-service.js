/**
 * Created by zh1995 on 17-4-12.
 */
angular.module('messageList-service', [])
.factory('MessageListService', function($http){
	return {
		getMessageList: function(uid, tagId, pageSize, currentPage) {
			var requestData = {
			    "uid": uid,
        	    "tagId": tagId,
                "pageSize": pageSize,
                "currentPage": currentPage
            };
			if (tagId === "1001") {
				return $http({
                    method: "POST",
                    url: "http://localhost:10101/message/hotspot",
                    data: JSON.stringify(requestData),
                    headers: {"Content-Type": "application/x-www-form-urlencoded"}
                });
			} else {
                return $http({
                    method: "POST",
                    url: "http://localhost:10101/message/list",
                    data: JSON.stringify(requestData),
                    headers: {"Content-Type": "application/x-www-form-urlencoded"}
                });
            }
		}
	}
});
