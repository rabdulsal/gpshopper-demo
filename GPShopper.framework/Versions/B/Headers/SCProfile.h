//
//  SCProfile.h
//  schumacher
//
//  Created by kimberly on 6/3/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "InfoPacket.h"


enum SCProfileRemoteStatus
{
    SCProfileRemoteNone,
    SCProfileRemoteBusy,
    SCProfileRemoteSuccess,
    SCProfileRemoteFail
};

/**
 Stores a user's profile information.
 Maps to database table gpshopper_1_1.MobileUserProfile.
 
 ### Updating profile values ###
 
 Changing values in a profile takes two steps:
 
   1. Staging the changes locally.
   2. Submitting the changes remotely.
 
 For example:
 
     [profile stageFirstName: @"My new first name"];
     [profile stageLastName: @"My new last name"];
     [profile sendUpdates];
 
 ### Observing changes ###
 
 Currently, SCProfile supports two systems for observing changes:
 
 - **Key-value observing.**  On remote changes, SCProfile _also_ updates the following values,
 which can be observed with _addObserver:forKeyPath:options:context:_
   - fetchStatus
   - updateStatus
 - **NSNotification.**  On remote changes, SCProfile updates the following values,
 and then sends the notification "scprofile_updated":
   - fetched
   - fetchFailed
   - updateFailed
 */
@interface SCProfile : NSObject
{
    NSString *firstName;
    NSString *lastName;
    NSString *email;
    NSString *defaultZipcode;
    NSDictionary *supplemental;

    NSString *stagedFirstName;
    NSString *stagedLastName;
    NSString *stagedEmail;
    NSString *stagedDefaultZipcode;
    NSMutableDictionary *stagedSupplementalUpdates;
    
    SCObjectRetriever *fetchRetriever;
    SCObjectRetriever *saveRetriever;
    
    BOOL fetched;
    BOOL fetchFailed;
    BOOL updateFailed;
}

/** @name Latest recorded values */

/** First name.  (ex. @"John") */
@property (readonly) NSString *firstName;

/** Last name.  (ex @"Doe") */
@property (readonly) NSString *lastName;

/** Email address.  (ex. @"john.doe@example.com") */
@property (readonly) NSString *email;

/** Default zipcode. */
@property (readonly) NSString *defaultZipcode;

/**
 Supplemental profile info.
 
 Name-value pairs (strings only).  Used for app-specific user information.
 */
@property (readonly) NSDictionary *supplemental;

/** @name Locally staged values */

/** Locally staged first name. */
@property (readonly) NSString *stagedFirstName;

/** Locally staged last name. */
@property (readonly) NSString *stagedLastName;

/** Locally staged email address. */
@property (readonly) NSString *stagedEmail;

/** Locally staged default zipcode. */
@property (readonly) NSString *stagedDefaultZipcode;

/** Locally staged supplemental value. */
-(NSString *)stagedSupplementalValueForKey: (NSString *)k;

/**
 Retrieve the existing profile values.
 
 Triggers a remote call, which in time will update fetched, fetchFailed, and fetchStatus.
 */
-(void)fetch;

/** @name Staging new values */

/** Stage new value for first name. */
-(void)stageUpdatedFirstName: (NSString *)fn;

/** Stage new value for last name. */
-(void)stageUpdatedLastName: (NSString *)ln;

/** Stage new value for email. */
-(void)stageUpdatedEmail: (NSString *)e;

/** Stage new value for zipcode. */
-(void)stageUpdatedDefaultZipcode: (NSString *)z;

/** Stage new supplemental key-value pair. */
-(void)stageSupplementalValue: (NSString *)v
                       forKey: (NSString *)k;

/** Remove previously staged supplemental value. */
-(void)removeStageSupplementalForKey: (NSString *)k;

/** @returns YES if there are any staged changes, NO otherwise. */
-(BOOL)hasStagedUpdates;

/** Clears all staged updates. */
-(void)resetUpdates;

/**
 Submits updates to frontends.
 
 Triggers a remote call, which in time will update updateFailed and updateStatus.
 */
-(void)sendUpdates;

/** Clears all data. */
-(void)clear;

/** @name Status (key-value observing) */

/** @return Status of last update:  none, busy, success, fail. */
@property (readonly) enum SCProfileRemoteStatus updateStatus;

/** @return Status of last fetch: none, busy, success, fail. */
@property (readonly) enum SCProfileRemoteStatus fetchStatus;

/** @name Status (for use with NSNotification) */

/** @return YES if profile data has been fetched successfully from the frontends. */
@property (readonly) BOOL fetched;

/** @return YES if last profile fetch failed. */
@property (readonly) BOOL fetchFailed;

/** @return YES if last profile update failed. */
@property (readonly) BOOL updateFailed;

+(NSString *)requestUrl;
+(void)setRequestUrl: (NSString *)s;

+(SCProfile *)defaultProfile;

@end
