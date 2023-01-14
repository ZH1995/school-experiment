/**
 * Created by lemo on 17-4-17.
 */
angular.module('login-service', [])
.factory('LoginService', function($http){

	return {
		login: function(phoneNumber, password) {
			var requestData = {
        "phoneNumber": phoneNumber,
        "password": password
      };
		  return $http({
				method: "POST",
				url: "http://localhost:10101/user/login",
				data: JSON.stringify(requestData),
				headers: {"Content-Type": "application/x-www-form-urlencoded"}
			});
		}
	}
});
