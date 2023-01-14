// Ionic Starter App

// angular.module is a global place for creating, registering and retrieving Angular modules
// 'starter' is the name of this angular module example (also set in a <body> attribute in index.html)
// the 2nd parameter is an array of 'requires'
// 'starter.controllers' is found in controllers_bk.js
angular.module('starter', ['ionic', 'starter.controllers', 'starter.services'])

.run(function($ionicPlatform) {
  $ionicPlatform.ready(function() {
    // Hide the accessory bar by default (remove this to show the accessory bar above the keyboard
    // for form inputs)
    if (window.cordova && window.cordova.plugins.Keyboard) {
      cordova.plugins.Keyboard.hideKeyboardAccessoryBar(true);
      cordova.plugins.Keyboard.disableScroll(true);

    }
    if (window.StatusBar) {
      // org.apache.cordova.statusbar required
      StatusBar.styleDefault();
    }
  });
})

.config(function($stateProvider, $urlRouterProvider, $ionicConfigProvider) {
  //使用$ionicConfigProvider服务解决ionic项目生成的导航栏在手机顶部的问题
  $ionicConfigProvider.platform.ios.tabs.style('standard');
  $ionicConfigProvider.platform.ios.tabs.position('bottom');
  $ionicConfigProvider.platform.android.tabs.style('standard');
  $ionicConfigProvider.platform.android.tabs.position('standard');

  $ionicConfigProvider.platform.ios.navBar.alignTitle('center');
  $ionicConfigProvider.platform.android.navBar.alignTitle('left');

  $stateProvider

    .state('app', {
      url: '/app',
      cache: false,
      abstract: true,
      templateUrl: 'templates/menu.html',
      controller: 'MenuCtrl'
    })

    .state('app.messageList', {
      url: '/messageList/:listTitle/:tagId',
      cache: false,
      views: {
        'menuContent': {
          templateUrl: 'templates/messageList.html',
          controller: 'MessageListCtrl'
        }
      }
    })


  .state('app.messageDetail', {
    url: '/messageDetail/:messageId',
    cache: false,
    views: {
      'menuContent': {
        templateUrl: 'templates/messageDetail.html',
        controller: 'MessageDetailCtrl'
      }
    }
  })

  .state('app.collectionList', {
    url: '/collectionList',
    cache: false,
    views: {
      'menuContent': {
        templateUrl: 'templates/collectionList.html',
        controller: 'CollectionListCtrl'
      }
    }
  })

  .state('app.modifyUserInfo', {
    url: '/modifyUserInfo',
    cache: false,
    views: {
      'menuContent': {
        templateUrl: 'templates/modifyUserInfo.html',
        controller: 'ModifyUserInfoCtrl'
      }
    }
  })

  .state('app.newList', {
    url: '/newList',
    cache: false,
    views: {
      'menuContent': {
        templateUrl: 'templates/newList.html',
        controller: 'NewListCtrl'
      }
    }
  })

  .state('app.writeComment', {
    url: '/writeComment/:messageId/:replyUid/:replyName',
    cache: false,
    views: {
      'menuContent': {
        templateUrl: 'templates/writeComment.html',
        controller: 'WriteCommentCtrl'
      }
    }
  })

  .state('login',{
      url:'/login',
      templateUrl:'templates/login.html',
      controller:'LoginCtrl'
  })

  .state('register',{
      url:'/register',
      templateUrl:'templates/register.html',
      controller:'RegisterCtrl'
  })

  .state('app.commentList', {
    url: '/commentList/:messageId',
    cache: false,
    views: {
      'menuContent': {
        templateUrl: 'templates/commentList.html',
        controller: 'CommentListCtrl'
      }
    }

  });
  // if none of the above states are matched, use this as the fallback
  $urlRouterProvider.otherwise('/login');
});
