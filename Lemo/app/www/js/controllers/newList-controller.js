/**
 * Created by lemo on 17-4-12.
 */
angular.module('newList-controller',[])
.controller('NewListCtrl', ['$scope', '$stateParams', 'NewListService', function($scope, $stateParams, NewListService){

  $scope.newList = NewListService.getNewList();

}]);
