/**
 * Created by lemo on 17-4-12.
 */
angular.module('messageDetail-service', [])
.factory('MessageDetailService', function($http){
	return {
		getMessageDetail: function(uid, messageId) {
			var requestData = {
			  "uid": uid,
			  "messageId": messageId
      };
			return $http({
				method: "POST",
				url: "http://localhost:10101/message/content",
				data: JSON.stringify(requestData),
				headers: {"Content-Type": "application/x-www-form-urlencoded"}
			});
		},

    dealUserMessageAction: function (uid, messageId, status, userAction) {
      var requestData = {
		    "uid": uid,
        "messageId": messageId,
        "status": status == false ? 0 : 1,
        "userAction": userAction
      };
		  return $http({
				method: "POST",
				url: "http://localhost:10101/message/userAction",
				data: JSON.stringify(requestData),
				headers: {"Content-Type": "application/x-www-form-urlencoded"}
			});
    }

	}
});
