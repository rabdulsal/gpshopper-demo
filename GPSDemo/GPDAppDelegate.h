//
//  GPDAppDelegate.h
//  GPSDemo
//
//  Created by James Lee on 5/2/14.
//  Copyright (c) 2014 James Lee. All rights reserved.
//

#import <UIKit/UIKit.h>


@interface GPDAppDelegate : UIResponder <UIApplicationDelegate, BrowseDelegate, GPSSDKConfigurationDelegate, SCGeoFenceManagerDelegate, PushNotificationDelegate, SCBeaconDeviceManagerDelegate>

@property (strong, nonatomic) UIWindow *window;
@property (strong, nonatomic) UITabBarController *tabBarController;
@property (strong, nonatomic) NSMutableArray *viewControllers;

@end
