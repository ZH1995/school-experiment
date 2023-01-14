/**
 * Created by lemo on 17-4-12.
 */
angular.module('newList-service', [])
.factory('NewListService', function($http){
  var newList = {
    0: {
      "content": "这是一个消息",
      "create_time": "2016-12-28 13:45:13"
    }
  };
	return {
		getNewList: function() {
			return newList;
		}
	}
});
