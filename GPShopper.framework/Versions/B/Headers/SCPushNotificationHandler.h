//
//  SCPushNotificationHandler.h
//  gpsIphone
//
//  Created by PJ Caraher on 11/14/13.
//  Copyright (c) 2013 Hui Zhu. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "SCPushNotification.h"

#define kSCPushNotificationHandlerAcceptedNotification @"SCPushNotificationHandlerAccepted"

/**
 The SCPushNotificationHandler coordinates the Alerting of the receipt of a SCPushNotification
 and prompting the user whether or not they wish to take action.
 
 The major benefit provided by this class is that it allows for the defering of taking a
 SCPushNotification action until after the user accepts the prompt.
 
 The SCPushNotificationHandler will post a notification that a response has occurred.
 The object associated with that notification will be the SCPushNotification.
 
 */
@interface SCPushNotificationHandler : NSObject <UIAlertViewDelegate>

/**
 The Notification's userInfo.
 */
@property (nonatomic, retain) NSDictionary *userInfo;

/**
 Take the given Notification userInfo dictionary, create SCPushNotification and then associate
 it with an instance of SCPushNotificationHandler.  The SCPushNotificationHandler will then present
 the user with a UIAlertView whose contents are taken from the SCPushNotification.
 
 The userInfo is the NSDictionary presented by the PushNotification.
 
 If the Accept option of the presented UIAlertView is chosen, a kSCPushNotificationHandlerAcceptedNotification
 will be posted.  The object of this Notification will be the associated PushNotification.
 */
+(void)handleRemoteNotification:(NSDictionary *)userInfo;

/**
 Take the given Notification userInfo dictionary, create SCPushNotification and then associate
 it with an instance of SCPushNotificationHandler.  The SCPushNotificationHandler will then present
 the user with a UIAlertView whose contents are taken from the SCPushNotification.
 
 The userInfo is the NSDictionary presented by the UILocalNotification.
 
 If the Accept option of the presented UIAlertView is chosen, a kSCPushNotificationHandlerAcceptedNotification
 will be posted.  The object of this Notification will be the associated PushNotification.
 */
+(void)handleLocalNotification:(NSDictionary *)userInfo;

/**
 Take the given Notification userInfo dictionary, create SCPushNotification and then associate
 it with an instance of SCPushNotificationHandler.  The SCPushNotificationHandler will then present
 the user with a UIAlertView whose contents are taken from the SCPushNotification.
 
 The userInfo is the NSDictionary presented by the PushNotification.
 
 If the Accept option of the presented UIAlertView is chosen, the delegate will then be used in the
 SCPushNotification's performActionWithDelegate method.
 */
+(void)handleRemoteNotification:(NSDictionary *)userInfo delegate:(id<PushNotificationDelegate>)delegate;

/**
 Take the given Notification userInfo dictionary, create SCPushNotification and then associate
 it with an instance of SCPushNotificationHandler.  The SCPushNotificationHandler will then present
 the user with a UIAlertView whose contents are taken from the SCPushNotification.
 
 The userInfo is the NSDictionary presented by the UILocalNotification.
 
 If the Accept option of the presented UIAlertView is chosen, the delegate will then be used in the
 SCPushNotification's performActionWithDelegate method.
 */
+(void)handleLocalNotification:(NSDictionary *)userInfo delegate:(id<PushNotificationDelegate>)delegate;

@end
