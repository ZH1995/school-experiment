/**
 * Created by lemo on 17-4-17.
 */
angular.module('modifyUserInfo-service', [])
.factory('ModifyUserInfoService', function($http){

	return {
		modifyUserInfo: function(uid, userName, userSign, headImg) {
			var requestData = {
			  "uid": uid,
        "userName": userName,
        "userSign": userSign,
        "headImg": headImg
      };
		  return $http({
				method: "POST",
				url: "http://localhost:10101/user/modify",
				data: JSON.stringify(requestData),
				headers: {"Content-Type": "application/x-www-form-urlencoded"}
			});
		}
	}
});
