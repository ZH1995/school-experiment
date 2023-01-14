/**
 * Created by lemo on 17-4-17.
 */
angular.module('register-service', [])
.factory('RegisterService', function($http){
	return {
		register: function(username, phoneNumber, password) {
			var requestData = {
		    "userName": username,
        "phoneNumber": phoneNumber,
        "password": password
      };
		  return $http({
				method: "POST",
				url: "http://localhost:10101/user/register",
				data: JSON.stringify(requestData),
				headers: {"Content-Type": "application/x-www-form-urlencoded"}
			});
		}
	}
});
