/**
 * Created by lemo on 17-4-12.
 */
angular.module('commentList-service', [])
.factory('CommentListService', function($http){
	return {
		getCommentList: function(uid, messageId, pageSize, currentPage) {
			var requestData = {
			  "uid": uid,
        "messageId": messageId,
        "pageSize": pageSize,
        "currentPage": currentPage
      };
			console.log("come in");
			return $http({
				method: "POST",
				url: "http://localhost:10101/comment/list",
				data: JSON.stringify(requestData),
				headers: {"Content-Type": "application/x-www-form-urlencoded"}
			});
		}
	}
});
