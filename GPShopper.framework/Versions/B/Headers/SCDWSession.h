//
//  SCDWSession.h
//
//  Created by James Lee on 7/30/14.
//  Copyright (c) 2014 James Lee. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <Security/Security.h>

#import "SCDWCart.h"
#import "SCDWProfile.h"
#import "SCDWWishlist.h"
#import "SCDWRetriever.h"

extern NSString *const SCDWSessionUpdateNotification;

typedef NS_ENUM(NSUInteger, SCDWSessionStatus) {
    kSCDWUnregistered,
    kSCDWLoginSuccess,
    kSCDWSessionReady
};

@protocol SCDWSessionDelegate <NSObject>
@optional
- (void)loginSucceeded;
- (void)loginFailedWithError:(NSError *)error;
- (void)sessionReady;
- (void)sessionFailedWithError:(NSError *)error;
- (void)sessionNeedsUpdateSession;
@end


// SCDWSession is a singleton -
// All it's public properties & methods can be accessed via static accessor methods

@interface SCDWSession : NSObject

+ (SCDWCart *)cart;
+ (SCDWProfile *)profile;
+ (SCDWWishlist *)wishlist;
+ (NSArray *)savedAddresses;
+ (SCDWSessionStatus)status;
+ (void)loginWithUsername:(NSString *)username password:(NSString *)password;
+ (void)createAccountWithUsername:(NSString *)username password:(NSString *)password profile:(SCDWProfile *)profile;
+ (void)logout;

+ (void)setDelegate:(id<SCDWSessionDelegate>)delegate;
+ (void)fetchAddresses;
//+ (void)registerDelegateForUpdates:(id<SCDWSessionDelegate>)delegate;

+ (NSString *)keychainUsername;
+ (NSString *)keychainPassword;
+ (void)saveUsername:(NSString *)username password:(NSString *)password;

@end