/**
 * Created by lemo on 17-4-12.
 */
angular.module('writeComment-service', [])
.factory('WriteCommentService', function($http){

	return {
		publicMessageComment: function(uid, replyUid, messageId, commentContent) {
		  var requestData = {
		    "uid": uid,
        "replyUid": replyUid,
        "messageId": messageId,
        "commentContent": commentContent
      };
		  return $http({
				method: "POST",
				url: "http://localhost:10101/comment/write",
				data: JSON.stringify(requestData),
				headers: {"Content-Type": "application/x-www-form-urlencoded"}
			});
		}
	}
});
