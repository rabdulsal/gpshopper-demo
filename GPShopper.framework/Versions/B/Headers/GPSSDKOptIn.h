//
//  GPSSDKOptIn.h
//  gpsIphone
//
//  Created by kimberly on 2/12/14.
//  Copyright (c) 2014 Hui Zhu. All rights reserved.
//

#import <Foundation/Foundation.h>

/**
 Specifies an opt-in alert.
 
 This is intended for use with SDK features,
 to obtain permission from an individual user
 to use a given a feature.
 */
@interface GPSSDKOptIn : NSObject

/**
 Title for the opt-in.
 */
@property (readonly) NSString *title;

/**
 Summarizes the feature
 and what permissions the user is granting
 by using the feature.
 
 For example "This feature uses your device's location." or similar.
 */
@property (readonly) NSString *message;

/**
 Url to which the user can be directed for additional details.
 */
@property (readonly) NSString *url;

/**
 Bool indicating if this SDK is enabled.  If not enabled, the title, message, etc. will be empty.
 */
@property (readonly) BOOL enabled;

-(id)initWithTitle: (NSString *)t
           message: (NSString *)m
               url: (NSString *)u;

@end